
/*
	Implementation of the 'Rig' Password Hashing Scheme
	September 25, 2014
	Author: Arpan Jati (arpanj@iiitd.ac.in)
	Rig : v2.0
	*/

#ifndef RIG_H_
#define RIG_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "BLAKE/blake2.h"
#include "blake_impl.h"

// Length of the counter in bytes, not to be modified.
#define CNT_BYTES 8

/*

This version of code contains both the variants of 'Rig v2.0'.

The Rig construction as of now defines two variants:

1) Original Submission : Rig (Blake512(H1), BlakeSingleRound(H2), Blake512(H3))

NOTE: After analysing the Memory and CPU architecture and latency requirements
it wasnoted that it is a good idea to read and write in larger chunks to memory,
primarily to 'handle' the DRAM latecy. As 'Rig' was envisoned as a flexible
construction, we proposed two simple functions (see paper) 'BlakeExpand' and
'BlakePerm' to fully utilize the bandwidth, concurrency and parallelism offered by
modern CPUs. These two functions have password-independent memory access patterns
and hence are cache-timing attack resistant. We are also working on strong GPU
resistant functions which can be plugged into the 'Rig'-Construction.

2) Rig (BlakeExpand(H1), BlakePerm(H2), Blake512(H3))

This is the variant introduced in this version to improve performance.

It is enabled by default by the '#define HASH_BLAKE_PERM' statement.

If the original version is intented only the next line (no 51) needs
to be commented. All required changes would be made automatically.

*/

// Comment next line to enable Rig v1.1
#define HASH_BLAKE_PERM

#ifdef HASH_BLAKE_PERM

// This is defined as H1 in documentation
#define HASH_INPUT BlakeExpand

// This is defined as H2 in documentation
#define HASH_LAYER BlakePerm

// This is defined as H3 in documentation
#define HASH_OUTPUT Blake512

// Output length of H1 and H2 (Must be same)
#define H_BYTES_OUT 8192

// Reduced output of H2 to accomodate counter (in the structure).
#define H_BYTES_KS (H_BYTES_OUT - CNT_BYTES)

#define H3_BYTES_OUT 64

#else

// This is defined as H1 in documentation
#define HASH_INPUT Blake512

// This is defined as H2 in documentation
#define HASH_LAYER BlakeSingleRound

// This is defined as H3 in documentation
#define HASH_OUTPUT Blake512

// Output length of H1 and H2 (Must be same)
#define H_BYTES_OUT 64

// Reduced output of H2 to accomodate counter (in the structure).
#define H_BYTES_KS (H_BYTES_OUT - CNT_BYTES)

#define H3_BYTES_OUT 64

#endif

/////////////////////////

#define LAYER_LENGTH  (CNT_BYTES + H_BYTES_OUT + H_BYTES_KS)

typedef uint8_t AlphaData[H_BYTES_OUT];
typedef uint8_t HashData[H_BYTES_KS];

#define SUCCESS					0

#define ERROR_TIME_LESS			101
#define ERROR_COST_LESS			102
#define ERROR_COST_MORE			103
#define ERROR_SALTLEN_INVALID	104
#define ERROR_COST_MULTIPLE		105
#define ERROR_INVALID_OUT_HLEN	106

const char * GetError(int Error);
void LongToBytes(uint64_t val, uint8_t b[CNT_BYTES]);

int PHS(void *out, size_t outlen, const void *in, size_t inlen, const void *salt,
	size_t saltlen, unsigned int t_cost, unsigned int m_cost);

#define _SWAP(x,s,m) (((x) >>(s)) & (m)) | (((x) & (m))<<(s))

static uint64_t BitReverse64(uint64_t value)
{
	value = _SWAP(value, 32, 0x00000000FFFFFFFFull);
	value = _SWAP(value, 16, 0x0000FFFF0000FFFFull);
	value = _SWAP(value, 8, 0x00FF00FF00FF00FFull);
	value = _SWAP(value, 4, 0x0F0F0F0F0F0F0F0Full);
	value = _SWAP(value, 2, 0x3333333333333333ull);
	value = _SWAP(value, 1, 0x5555555555555555ull);

	return value;
}

static uint32_t BitReverse32(uint32_t x)
{
	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	return((x >> 16) | (x << 16));
}

void LongToBytes(uint64_t val, uint8_t* b);

#endif
