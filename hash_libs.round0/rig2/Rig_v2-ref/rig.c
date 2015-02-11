/*
	Implementation of the 'Rig' Password Hashing Scheme
	September 25, 2014
	Author: Arpan Jati (arpanj@iiitd.ac.in)
	Rig : v2.0
*/

#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <stdint.h>
#include <memory.h>
#include "rig.h"
#include "constants.h"

/* Perform the setup-phase (topmost layer) of RIG.

ChainingValue is the output of the H1 (called alpha). This value is expanded
in this phase by using the chosen function H2.

AlphaSet is the set of all values of array 'a' and,
KeySet is the set of all values of array 'k'.

One can note that in this phase the XOR difference of AlphaSet and KeySet
is the ChainingValue. This is intended. The following layers in the Iterative
Transformation phase does not have this relation.

NOTE: The previous version of this function was called 'PerformLayer_Zero', it
is renamed to make the naming consistent with the design document.

The previous versions of this method used 'memcpy' for faster memory writes,
as the algorithm is primarily memory bound. In this version we have removed
those in favour of a more concise and clean code. The optimizers in most
compilers work really well and the performance difference is negligible.
We tried AVX-2 intrinsics like _mm256_stream_si256, _mm256_stream_load_si256,
_mm256_xor_si256, gather instruction and several other techniques to no avail
as the algorithm is primarily DRAM bandwidth and latency bound and hence the
performance difference is minimal.

*/

int PerformSetupPhase(uint8_t *ChainingValue, AlphaData* AlphaSet,
	HashData* KeySet, uint64_t M, uint64_t * Count)
{
	uint64_t i = 0, j = 0, inIdx = 1;
	const uint64_t Hlen = H_BYTES_OUT / 8;

	uint64_t Hin[LAYER_LENGTH / 8];
	
	uint64_t t[Hlen];

	uint64_t AlphaData[Hlen];
	uint8_t Count_Bytes[CNT_BYTES];

	memcpy(AlphaData, ChainingValue, H_BYTES_OUT);

	for (i = 0; i < M; i++)	{
		inIdx = 1;
		LongToBytes((++(*Count)), Count_Bytes);
		Hin[0] = ((uint64_t*)Count_Bytes)[0];

		uint64_t* a = (uint64_t*)AlphaSet[i];
		uint64_t* k = (uint64_t*)KeySet[i];

		if (i == 0)	{
			memcpy(t, PI_CONST, H_BYTES_OUT); // Load Pi
		}

		for (j = 0; j < Hlen; j++) {
			a[j] = AlphaData[j] ^ t[j];
			Hin[inIdx++] = a[j];

			if (j < Hlen - 1) {
				Hin[Hlen + inIdx - 1] = t[j];
				k[j] = t[j];
			}
		}
		HASH_LAYER(Hin, t);
	}

	memcpy(ChainingValue, t, H_BYTES_OUT);

	return SUCCESS;
}

/*
Perform the Iterative Transformation phase of RIG (subsequent layers)

In this phase the KeySet and AlphaSet is updated iteratively.

Bit-reversal permutation is performed on indices of 'k',
For implementation, we are using Catena styled alternate row bit-permutation, 
because it does not uses one extra array for memory, and also causes less
memory accesses, leading to faster runtimes (10-15% depending on
the number of iterations).

*/
int PerformIteration(AlphaData* AlphaSet, HashData* KeySet, 
	uint8_t* ChainingValue,	uint64_t M, uint64_t m_cost, 
	uint64_t * Count, uint64_t row)
{
	uint64_t i = 0, address = 0, j = 0, k = 0, inIdx = 1;

	const uint64_t Hlen = H_BYTES_OUT / 8;

	uint64_t Hin[LAYER_LENGTH / 8];
	
	uint64_t t[Hlen]; // Temp

	uint8_t Count_Bytes[CNT_BYTES];

	for (i = 0; i < M; i++)	{

		inIdx = 1;
		LongToBytes((++(*Count)), Count_Bytes);
		Hin[0] = ((uint64_t*)Count_Bytes)[0];

		// Perform bit-reversal address generation on the data.
		address = (row & 1) ? i : (BitReverse64(i) >> (64 - m_cost));

		uint64_t* a = (uint64_t*)AlphaSet[i];
		uint64_t* k = (uint64_t*)KeySet[address];

		if (i == 0)	{
			memcpy(t, ChainingValue, H_BYTES_OUT);
		}

		for (j = 0; j < Hlen; j++) {
			a[j] ^= t[j];
			Hin[inIdx++] = a[j];

			if (j < Hlen - 1) {
				k[j] ^= t[j];
				Hin[Hlen + inIdx - 1] = k[j];
			}
		}

		HASH_LAYER(Hin, t);
	}

	memcpy(ChainingValue, t, H_BYTES_OUT);

	return SUCCESS;
}

size_t getAlphaDataLength(size_t inLen, size_t sLen)
{
	return inLen + sLen + (CNT_BYTES * 4);
}

// Prepare alpha from password and salt.
void PrepareAlphaData(uint8_t* input, size_t inLen, uint8_t* salt,
	size_t sLen, uint64_t t_cost, uint64_t outputBits, uint8_t* bytes)
{
	int count = 0;

	uint8_t _T[CNT_BYTES];
	uint8_t _OutputBits[CNT_BYTES];

	uint8_t _PWLen[CNT_BYTES];
	uint8_t _SaltLen[CNT_BYTES];

	LongToBytes(t_cost, _T);
	LongToBytes(outputBits, _OutputBits);
	LongToBytes(inLen, _PWLen);
	LongToBytes(sLen, _SaltLen);

	memcpy(bytes, input, inLen);
	memcpy(bytes + inLen, _PWLen, CNT_BYTES);
	memcpy(bytes + inLen + CNT_BYTES, salt, sLen);
	memcpy(bytes + inLen + sLen + CNT_BYTES, _SaltLen, CNT_BYTES);
	memcpy(bytes + inLen + sLen + CNT_BYTES * 2, _T, CNT_BYTES);
	memcpy(bytes + inLen + sLen + CNT_BYTES * 3, _OutputBits, CNT_BYTES);
}

int PHS_FULL(void *out, size_t outlen, const void *in, size_t inlen,
	const void *salt, size_t saltlen, uint32_t t_cost, uint32_t m_cost)
{
	uint32_t i, ret = SUCCESS;

	if (t_cost < 1) return ERROR_TIME_LESS;
	if (m_cost < 1) return ERROR_COST_LESS;
	if (m_cost > 31) return ERROR_COST_MORE;
	if ((saltlen > 256) || (saltlen < 0)) return ERROR_SALTLEN_INVALID;
		
	uint8_t* alpha = (uint8_t *)malloc(H_BYTES_OUT);
	size_t alphaDataLength = getAlphaDataLength(inlen, saltlen);
	uint8_t* alphaData = (uint8_t *)malloc(alphaDataLength);

	PrepareAlphaData((uint8_t*)in, inlen, (uint8_t*)salt, saltlen, 
		t_cost, (outlen * 8), alphaData);

	HASH_INPUT(alphaData, alphaDataLength, alpha);
	free(alphaData);	

	uint64_t __M = ((uint64_t)1 << m_cost);

	uint8_t* ChainingValue = (uint8_t*)malloc(H_BYTES_OUT);

	memcpy(ChainingValue, alpha, H_BYTES_OUT);
	
	// TODO: The large mallocs in the lines below may fail if there isn't enough memory.
	// Need to put a alloc-check.

	HashData* KeySet = (HashData*)malloc((size_t)(H_BYTES_KS * __M));
	AlphaData* AlphaSet = (AlphaData*)malloc((size_t)(H_BYTES_OUT * __M));

	uint64_t Count = 0;
	uint64_t M = ((uint64_t)1 << m_cost);

	ret = PerformSetupPhase(ChainingValue, AlphaSet, KeySet, M, &Count);
	if (ret != SUCCESS) return ret;

	for (i = 0; i < t_cost; i++)
	{
		ret = PerformIteration(AlphaSet, KeySet, ChainingValue, M, m_cost, &Count, i);
		if (ret != SUCCESS) return ret;
	}

	uint8_t CNT[CNT_BYTES];
	LongToBytes(++Count, CNT);

	uint8_t _M[CNT_BYTES];
	LongToBytes(M, _M);

	uint8_t *H3_in = (uint8_t *)malloc(CNT_BYTES * 2 + H_BYTES_OUT + saltlen);

	memcpy(H3_in, CNT, CNT_BYTES);
	memcpy(H3_in + CNT_BYTES, ChainingValue, H_BYTES_OUT);
	memcpy(H3_in + CNT_BYTES + H_BYTES_OUT, salt, saltlen);
	memcpy(H3_in + CNT_BYTES + H_BYTES_OUT + saltlen, _M, CNT_BYTES);

	uint8_t H3_Out[H3_BYTES_OUT];

	HASH_OUTPUT(H3_in, CNT_BYTES * 2 + H_BYTES_OUT + saltlen, H3_Out);

	free(H3_in);
	free(KeySet);
	free(AlphaSet);
	free(ChainingValue);
	free(alpha);

	if (outlen <= H3_BYTES_OUT)
	{
		for (i = 0; i < outlen; i++)
		{
			((uint8_t*)out)[i] = H3_Out[i];
		}
	}
	else
	{
		return ERROR_INVALID_OUT_HLEN;
	}

	return SUCCESS;
}

int PHS(void *out, size_t outlen, const void *in, size_t inlen,
	const void *salt, size_t saltlen, unsigned int t_cost, unsigned int m_cost)
{
	return PHS_FULL(out, outlen, in, inlen, salt, saltlen, t_cost, m_cost);
}

const char * GetError(int Error)
{
	switch (Error)
	{

	case ERROR_TIME_LESS:
		return "Time Cost should be greater than 0";

	case ERROR_COST_LESS:
		return "Memory cost should be greater than 0";

	case ERROR_COST_MORE:
		return "Memory cost should be less than or equal to 32";

	case ERROR_SALTLEN_INVALID:
		return "Salt Length should be greater than 0, and less than 256 bytes";

	case ERROR_COST_MULTIPLE:
		return "Memory Cost is not a power of 2";

	case ERROR_INVALID_OUT_HLEN:
		return "Invalid Output Hash Length";

	default:
		return "Undefined Error";
	}
}

// Kind of redundant on Little-Endian platforms.
// TODO: Fix with platform check.
void LongToBytes(uint64_t val, uint8_t* b)
{
	b[7] = (uint8_t)((val >> 40) & 0xff);
	b[6] = (uint8_t)((val >> 36) & 0xff);
	b[5] = (uint8_t)((val >> 32) & 0xff);
	b[4] = (uint8_t)((val >> 28) & 0xff);

	b[3] = (uint8_t)((val >> 24) & 0xff);
	b[2] = (uint8_t)((val >> 16) & 0xff);
	b[1] = (uint8_t)((val >> 8) & 0xff);
	b[0] = (uint8_t)((val >> 0) & 0xff);
}


