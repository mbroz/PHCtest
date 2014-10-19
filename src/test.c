/*
 * Trivial test program for PHC (Password Hashing Competition) candidates
 *
 * Copyright (C) 2014 Milan Broz <gmazyland@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <getopt.h>
#include <stdarg.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int PHS(void *out, size_t outlen, const void *in, size_t inlen,
    const void *salt, size_t saltlen, unsigned int t_cost, unsigned int m_cost);

static size_t opt_salt_len = 16;
static size_t opt_in_len = 8;
static size_t opt_out_len = 32;
static unsigned int opt_mcost = 1;
static unsigned int opt_tcost = 1;
static unsigned int opt_repeat = 1;
static int opt_verbose = 0;
static int opt_fork = 0;
static int opt_display_hash = 0;
static char *opt_out_file = NULL;
static char *opt_vector_file = NULL;

static void print_hex(FILE *f, unsigned int buf_len, const char *buf)
{
	size_t i;

	for (i = 0; i < buf_len; i++)
		fprintf(f, "%02x", (unsigned char)buf[i]);
}

static void printl(const char *format, ...)
{
	va_list argp;
	char *target = NULL;

	if (opt_verbose) {
		va_start(argp, format);
		if (vasprintf(&target, format, argp) > 0)
			printf("%s\n", target);
		va_end(argp);
		free(target);
	}
}

static int time_ms(struct timespec *start, struct timespec *end, double *ms)
{
        double start_ms, end_ms;

        start_ms = start->tv_sec * 1000.0 + start->tv_nsec / (1000.0 * 1000);
        end_ms   = end->tv_sec * 1000.0 + end->tv_nsec / (1000.0 * 1000);

        *ms = end_ms - start_ms;
        return 0;
}

static int test_phc(size_t key_len, char *key, size_t salt_len, char *salt,
		    size_t pwd_len, char *pwd,
		    unsigned int t_cost, unsigned int m_cost,
		    double *ms, long *muse)
{
	char key_cmp[key_len];
	struct timespec start, end;
	struct rusage rstart, rend;
	int r;

	memcpy(key_cmp, key, key_len);

	if (clock_gettime(CLOCK_MONOTONIC, &start) < 0) {
		printl("Cannot use CLOCK_MONOTONIC.");
		return 1;
	}

	if (getrusage(RUSAGE_SELF, &rstart) < 0) {
		printl("Cannot use RUSAGE_SELF.");
		return 1;
	}

	if ((r = PHS(key, key_len, pwd, pwd_len, salt, salt_len, t_cost, m_cost)) != 0) {
		printl("Error running PHS, %i.\n", r);
		return 1;
	}

	if (getrusage(RUSAGE_SELF, &rend) < 0)
		return 1;

	if (clock_gettime(CLOCK_MONOTONIC, &end) < 0)
		return 1;

        if (time_ms(&start, &end, ms) < 0)
                return 1;

	if (!memcmp(key, key_cmp, key_len)) {
		printl("Error, output key unchanged.\n");
		return 1;
	}

	*muse = rend.ru_maxrss - rstart.ru_maxrss;
	if (*muse < 0)
		return 1;
	if (*muse == 0) /* HACK to help display data with log scale */
		*muse = 1;

	return 0;
}

static double ms_mean(double *ms, int count)
{
	int i;
	double d = 0;

	for (i = 0; i < count; i++)
		d += ms[i];

	return d / (double)count;
}

static long muse_mean(long *muse, int count)
{
	int i;
	long l = 0;

	for (i = 0; i < count; i++)
		l += muse[i];

	return l / count;
}

static int test_phc_wrapper(void)
{
	char key[opt_out_len], pwd[opt_in_len], salt[opt_salt_len];
	FILE *f = NULL;
	int status = EXIT_SUCCESS, count = 0;
	double ms[opt_repeat];
	long muse[opt_repeat];

	if (opt_out_file) {
		f = fopen(opt_out_file, "a+");
		setvbuf(f, NULL, _IONBF, 0);
	}

	while (count < opt_repeat) {
		memset(key, 0xab, opt_out_len);
		memset(pwd, 0xcd, opt_in_len);
		memset(salt,0xef, opt_salt_len);

		if (test_phc(opt_out_len, key, opt_salt_len, salt, opt_in_len, pwd, opt_tcost,
			     opt_mcost, &ms[count], &muse[count])) {
			fprintf(f ?: stdout, "# ERROR %zu %zu %d %d\n",
				opt_in_len, opt_out_len, opt_mcost, opt_tcost);
			status = EXIT_FAILURE;
			break;
		}
		printl("[%02d] Cost: %d,%d In %zu, Out %zu, Time %02.2f, memory %lu",
			count, opt_tcost, opt_mcost, opt_in_len, opt_out_len, ms[count], muse[count]);
		count++;
	}

	if (status == EXIT_SUCCESS) {
		// in out m_cost t_cost time [ms] memory[kb]
		fprintf(f ?: stdout , "%zu %zu %u %d %2.0f %li",
			opt_in_len, opt_out_len, opt_mcost, opt_tcost,
			ms_mean(ms, opt_repeat), muse_mean(muse, opt_repeat));
		if (opt_display_hash) {
			fprintf(f ?: stdout , " :");
			print_hex(f ?: stdout, opt_out_len, key);
		}
		fprintf(f ?: stdout , "\n");
	}

	if (f) {
		fflush(f);
		fclose(f);
	}

	return status;
}

static int test_phc_wrapper_fork(void)
{
	pid_t cpid;
	int status;

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}

	if (cpid == 0)
		_exit(test_phc_wrapper() ? EXIT_FAILURE : EXIT_SUCCESS);

	wait(&status);
	return status ? EXIT_FAILURE : EXIT_SUCCESS;
}

static size_t from_hex(const char *hex, char *bin, size_t bin_size)
{
	char buf[3] = "xx\0", *endp;
	size_t i, len;

	len = strlen(hex);
	if (len % 2 || len > bin_size)
		return 1;
	len /= 2;

	for (i = 0; i < len; i++) {
		memcpy(buf, &hex[i * 2], 2);
		bin[i] = strtoul(buf, &endp, 16);
		if (endp != &buf[2])
			return -1;
	}
	return len;
}

static int test_vector(const char *password_hex, const char *salt_hex,
		       unsigned int t_cost, unsigned int m_cost, const char *out_hex)
{
	static char password[4096], salt[4096], out[4096], real_out[4096];
	size_t password_len = from_hex(password_hex, password, sizeof(password));
	size_t salt_len = from_hex(salt_hex, salt, sizeof(salt));
	size_t out_len = from_hex(out_hex, out, sizeof(out));
	int r;

	if (password_len < 0 || salt_len < 0 || out_len < 0)
		return 1;

	r = PHS(real_out, out_len, password, password_len, salt, salt_len, t_cost, m_cost);
	if (r)
		return r;

	if (memcmp(real_out, out, out_len)) {
		printf("ERROR: output differs: ");
		print_hex(stdout, out_len, real_out);
		printf("\n");
		return 1;
	}

	return 0;
}

static int test_vectors(const char *file)
{
	FILE *f = NULL;
	static char line[4096], password[4096], salt[4096], out[4096];
	unsigned int m_cost, t_cost;
	int r = 0, line_num = 0;

	if (!file)
		return 1;

	f = fopen(file, "r");
	if (!f)
		return 1;

	while (!r && fgets(line, sizeof(line), f)) {
		if (sscanf(line, "password:%4096s salt:%4096s t_cost:%u m_cost:%u -> %4096s",
			password, salt, &t_cost, &m_cost, out) == 5) {
		} else if (sscanf(line, "password: salt:%4096s t_cost:%u m_cost:%u -> %4096s",
			salt, &t_cost, &m_cost, out) == 4) {
			password[0] = '\0';
		} else if (sscanf(line, "password:%4096s salt: t_cost:%u m_cost:%u -> %4096s",
			password, &t_cost, &m_cost, out) == 4) {
			salt[0] = '\0';
		} else {
			printf("ERROR[%i]: malformed vector format: %s", line_num, line);
			r = 1;
			continue;
		}
		r = test_vector(password, salt, t_cost, m_cost, out);
		if (r)
			printf("LINE[%i]: %s", line_num, line);
		line_num++;
	}

	fclose(f);
	if (!r)
		printf("Vectors: %s, lines %i OK\n", file, line_num);
	return r;
}

static struct option long_options[] =
{
	{"verbose",  no_argument,       NULL, 'v'},
	{"fork",     no_argument,       NULL, 'w'},
	{"hash",     no_argument,       NULL, 'h'},
	{"salt_len", required_argument, NULL, 's'},
	{"in_len",   required_argument, NULL, 'i'},
	{"out_len",  required_argument, NULL, 'o'},
	{"mcost",    required_argument, NULL, 'm'},
	{"tcost",    required_argument, NULL, 't'},
	{"out_file", required_argument, NULL, 'f'},
	{"repeat",   required_argument, NULL, 'r'},
	{"vector",   required_argument, NULL, 'V'},
	{0, 0, NULL, 0}
};

int main (int argc, char *argv[])
{
	int c, r, option_index = 0;

	while ((c = getopt_long (argc, argv, "vwhs:i:o:m:t:f:r:V:", long_options, &option_index)) != -1) {
		switch (c) {
		case 'v': opt_verbose  = 1; break;
		case 'w': opt_fork     = 1; break;
		case 'h': opt_display_hash = 1; break;
		case 's': opt_salt_len = atoi(optarg); break;
		case 'i': opt_in_len   = atoi(optarg); break;
		case 'o': opt_out_len  = atoi(optarg); break;
		case 'm': opt_mcost    = atoi(optarg); break;
		case 't': opt_tcost    = atoi(optarg); break;
		case 'r': opt_repeat   = atoi(optarg); break;
		case 'f': opt_out_file = strdup(optarg); break;
		case 'V': opt_vector_file = strdup(optarg); break;
		case '?':
		default: perror("bad option"); exit(EXIT_FAILURE); break;
		}
	}

	if (opt_vector_file)
		return test_vectors(opt_vector_file);

	if (opt_fork)
		r = test_phc_wrapper_fork();
	else
		r = test_phc_wrapper();

	printl("Exit status %i.", r);
	return r;
}
