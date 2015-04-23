/*
 * -----------------------------------------------------------------------
 * (c) Thomas Pornin 2014. This software is provided 'as-is', without
 * any express or implied warranty. In no event will the author be held
 * liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to no restriction.
 *
 * Technical remarks and questions can be addressed to:
 * <pornin@bolet.org>
 * -----------------------------------------------------------------------
 */

/*
 * This commnad-line tool generates a new set of delegation parameters,
 * for a provided work factor. The modulus is extracted from an existing
 * encoded modulus, private key or set of delegation parameters.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "makwa.h"

static void
fail(char *fmt,...)
{
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "FAIL: ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
	abort();
}

#define CF(x)   do { \
		int error_code = (x); \
		if (error_code < 0) { \
			fail("line %ld: %s returned %d\n", \
				(long)__LINE__, #x, error_code); \
			abort(); \
		} \
	} while (0)

static void *
xmalloc(size_t len)
{
	void *x;

	if (len == 0) {
		return NULL;
	}
	x = malloc(len);
	if (x == NULL) {
		fail("memory allocation failure: %lu bytes\n",
			(unsigned long)len);
	}
	return x;
}

static void
xfree(void *x)
{
	if (x != NULL) {
		free(x);
	}
}

static void
usage(void)
{
	fprintf(stderr,
"usage: deleggen [ -genX | -gen1 ] infile workfactor outfile\n");
	exit(EXIT_FAILURE);
}

static void *
read_file(char *name, size_t *data_len)
{
	FILE *f;
	unsigned char *buf;
	size_t ptr, len;

	f = fopen(name, "rb");
	if (f == NULL) {
		fail("could not open file '%s' for reading", name);
	}
	buf = NULL;
	ptr = 0;
	len = 0;
	for (;;) {
		unsigned char tmp[8192];
		size_t rlen, nptr;

		rlen = fread(tmp, 1, sizeof tmp, f);
		if (rlen == 0) {
			break;
		}
		nptr = ptr + rlen;
		if (nptr > len) {
			unsigned char *nbuf;
			size_t nlen;

			nlen = len << 1;
			if (nlen < nptr) {
				nlen = nptr;
			}
			nbuf = xmalloc(nlen);
			memcpy(nbuf, buf, ptr);
			xfree(buf);
			buf = nbuf;
			len = nlen;
		}
		memcpy(buf + ptr, tmp, rlen);
		ptr = nptr;
	}
	*data_len = ptr;
	return buf;
}

static void
write_file(char *name, const void *data, size_t data_len)
{
	FILE *f;

	f = fopen(name, "wb");
	if (f == NULL) {
		fail("could not open file '%s' for writing", name);
	}
	if (fwrite(data, 1, data_len, f) != data_len) {
		fail("short write in file '%s': %lu bytes",
			name, (unsigned long)data_len);
	}
	fclose(f);
}

static int
eq_nocase(const char *s1, const char *s2)
{
	for (;;) {
		int c1 = *s1 ++;
		int c2 = *s2 ++;

		if (c1 == 0 || c2 == 0) {
			return c1 == c2;
		}
		if (c1 >= 'A' && c1 <= 'Z') {
			c1 += 'a' - 'A';
		}
		if (c2 >= 'A' && c2 <= 'Z') {
			c2 += 'a' - 'A';
		}
		if (c1 != c2) {
			return 0;
		}
	}
}

int
main(int argc, char *argv[])
{
	char *nargv[3];
	int i, nargc;
	char *infile, *swf, *outfile;
	long work_factor;
	char *cptr;
	unsigned char *param, *dp;
	size_t param_len, dp_len;
	int param_type;

	nargc = 0;
	param_type = MAKWA_RANDOM_PAIRS;
	for (i = 1; i < argc; i ++) {
		if (eq_nocase(argv[i], "-genX")) {
			param_type = MAKWA_GENERATOR_EXPAND;
		} else if (eq_nocase(argv[i], "-gen1")) {
			param_type = MAKWA_GENERATOR_ONLY;
		} else {
			if (nargc >= 3) {
				usage();
			}
			nargv[nargc ++] = argv[i];
		}
	}
	if (nargc != 3) {
		usage();
	}
	infile = nargv[0];
	swf = nargv[1];
	outfile = nargv[2];
	work_factor = strtol(swf, &cptr, 0);
	if (*swf == 0 || *cptr != 0 || work_factor < 0) {
		usage();
	}
	param = read_file(infile, &param_len);
	CF(makwa_delegation_generate_gen(param, param_len,
		work_factor, param_type, NULL, &dp_len));
	dp = xmalloc(dp_len);
	CF(makwa_delegation_generate_gen(param, param_len,
		work_factor, param_type, dp, &dp_len));
	write_file(outfile, dp, dp_len);
	xfree(param);
	xfree(dp);
	return 0;
}
