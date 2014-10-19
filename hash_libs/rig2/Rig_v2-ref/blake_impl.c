/*
	Implementation of the 'Rig' Password Hashing Scheme
	September 25, 2014
	Author: Arpan Jati (arpanj@iiitd.ac.in)
	Rig : v2.0
*/

#include "rig.h"
#include "BLAKE/blake2.h"
#include <memory.h>
#include "blake_impl.h"

void PrintBytes(const char* String, unsigned char* Bytes, int32_t Length)
{
	int k;
	printf("\n %s \n", String);
	for (k = 0; k < Length; k++)
	{
		printf("%02X", Bytes[k]);
		if (((k + 1) % 8) == 0) printf(" ");
		if (((k + 1) % 32) == 0) printf("| %08X [ %08d ] \n", k - 0x1F, (k - 0x1F));
	}
	printf("\n");
}


#define rotr64(w,c) ((w) >> (c)) | ((w) << (64 - c))

#define G(a,b,c,d) \
do {\
	a = a + b; \
	d = rotr64(d ^ a, 32); \
	c = c + d; \
	b = rotr64(b ^ c, 24); \
	a = a + b; \
	d = rotr64(d ^ a, 16); \
	c = c + d; \
	b = rotr64(b ^ c, 63); \
} while (0)

// Perform a single invocation of the blake compression function

#define ROUND_BL  \
do {\
	G(v[0], v[4], v[8], v[12]); \
	G(v[1], v[5], v[9], v[13]); \
	G(v[2], v[6], v[10], v[14]); \
	G(v[3], v[7], v[11], v[15]); \
	G(v[0], v[5], v[10], v[15]); \
	G(v[1], v[6], v[11], v[12]); \
	G(v[2], v[7], v[8], v[13]); \
	G(v[3], v[4], v[9], v[14]); \
} while (0)


void BlakeSingleRound(uint64_t* in, uint64_t* out)
{
	int i;
	uint64_t v[16];
	memcpy(v, in, 128);

	ROUND_BL;

	for (i = 0; i < 8; i++)
	{
		out[i] = v[i] ^ v[i + 8];
	}
}

// Performs BlakeExpand on an arbitrary length input 
// to expand it to 8 KiB of state information.

void BlakeExpand(uint8_t* in, size_t inLength, uint8_t* out)
{
	int i = 0;
	// 1 added byte for the counter.
	uint8_t* HashIn = (uint8_t*)malloc(inLength + 1);

	memcpy(HashIn, in, inLength);

	// Apply the blake layer
	for (i = 0; i < 128; i++)
	{
		HashIn[inLength] = i;
		// Use full Blake2b to expand the input.
		Blake512(HashIn, inLength + 1, (uint8_t*)(out + (i << 6)));
	}
	free(HashIn);
}

// Performs BlakePerm compression on input to give the output
// Takes an input of 16 KiB to return 8 KiB

void BlakePerm(uint64_t* in, uint64_t* out)
{
	uint64_t i = 0, j = 0, t[8];

	// Apply the blake layer (128 invocations)
	for (i = 0; i < 128; i++) {

		BlakeSingleRound(in + (i << 4), t);

		// Apply the permutation for all the qwords
		for (j = 0; j < 8; j++) {

			// Calculate address for permutation 
			// [address = (i * 109 + 512) % 1024]		
			out[((((i << 3) + j) * 109) + 512) & 0x3FF] = t[j];
		}
	}
}

int Blake512(unsigned char *in, uint64_t inlen, unsigned char *out)
{
	return blake2b(out, in, NULL, BLAKE2B_OUTBYTES, inlen, 0);
}


