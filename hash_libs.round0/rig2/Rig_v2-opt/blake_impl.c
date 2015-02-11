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

#include <immintrin.h>

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


#define ROTR64_4(v,c) (_mm256_or_si256 (_mm256_srli_epi64(v,c),_mm256_slli_epi64(v,64-c)))

#define G_4(a,b,c,d) \
do { \
	a =  _mm256_add_epi64(a , b); \
	d = ROTR64_4( _mm256_xor_si256(d , a) , 32);  \
	c = _mm256_add_epi64(c, d); \
	b = ROTR64_4(_mm256_xor_si256(b, c), 24); \
	a = _mm256_add_epi64(a, b); \
	d = ROTR64_4(_mm256_xor_si256(d, a), 16); \
	c = _mm256_add_epi64(c, d); \
	b = ROTR64_4(_mm256_xor_si256(b, c), 63); \
} while (0)


void BlakeSingleRound_AVX2(uint64_t *in, uint64_t *out)
{
	// 'in' is an array having 16, 64bit ints.

	__m256i* in256 = (__m256i*) in;
	__m256i* out256 = (__m256i*) out;

	__m256i A = _mm256_load_si256(in256 + 0);
	__m256i B = _mm256_load_si256(in256 + 1);
	__m256i C = _mm256_load_si256(in256 + 2);
	__m256i D = _mm256_load_si256(in256 + 3);

	// Apply the G function to the 4 coulmns simultaneously.
	G_4(A, B, C, D);

	// Rotate the columns to the top accross longs.
	B = _mm256_permute4x64_epi64(B, _MM_SHUFFLE(0, 3, 2, 1)); // 4,5,6,7 -> 5,6,7,4
	C = _mm256_permute2x128_si256(C, C, 1); // 8,9,10,11 -> 10,11,8,9
	D = _mm256_permute4x64_epi64(D, _MM_SHUFFLE(2, 1, 0, 3)); // 12,13,14,15 -> 15,12,13,14

	G_4(A, B, C, D);

	// Undo the effect of rotations
	B = _mm256_permute4x64_epi64(B, _MM_SHUFFLE(2, 1, 0, 3));
	C = _mm256_permute2x128_si256(C, C, 1);
	D = _mm256_permute4x64_epi64(D, _MM_SHUFFLE(0, 3, 2, 1));

	// Unaligned stores / may be improved with _mm256_store_si256
	_mm256_storeu_si256(out256 + 0, _mm256_xor_si256(A, C));
	_mm256_storeu_si256(out256 + 1, _mm256_xor_si256(B, D));
}



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

		BlakeSingleRound_AVX2(in + (i << 4), t);

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
