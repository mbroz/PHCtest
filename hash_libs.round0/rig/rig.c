

/*
  Implementation of the 'Rig' Password Hashing Scheme
	
   April 21, 2014

  Author: Arpan Jati (arpanj@iiitd.ac.in)
 */


#include <malloc.h>
#include <math.h>
#include <memory.h>
#include "rig.h"

// Rotates 'w', 'c' times to the right.
// With optimization ON, this is implemented as a ROR instruction. 
static inline uint64_t rotr64( const uint64_t w, const unsigned c )
{
	return (w >> c) | (w << (sizeof(w)*8-c));
}

#define G(a,b,c,d) \
	do { \
	a = a + b ; \
	d = rotr64(d ^ a, 32); \
	c = c + d; \
	b = rotr64(b ^ c, 24); \
	a = a + b ; \
	d = rotr64(d ^ a, 16); \
	c = c + d; \
	b = rotr64(b ^ c, 63); \
	} while(0)


// Operates a single round of BLAKE2B on 'v'
#define ROUND_BL  \
	do { \
	G(v[ 0],v[ 4],v[ 8],v[12]); \
	G(v[ 1],v[ 5],v[ 9],v[13]); \
	G(v[ 2],v[ 6],v[10],v[14]); \
	G(v[ 3],v[ 7],v[11],v[15]); \
	G(v[ 0],v[ 5],v[10],v[15]); \
	G(v[ 1],v[ 6],v[11],v[12]); \
	G(v[ 2],v[ 7],v[ 8],v[13]); \
	G(v[ 3],v[ 4],v[ 9],v[14]); \
	} while(0)

//
// Performs Blake State update in-place and returns the result.
// Input length 1024, output length 512
//
void PERFORM_BLAKE_STATE_F(byte* in,  byte* out)
{
	int i=0;
	u64 *v = (u64*)in;

	ROUND_BL;

	for(i=0;i<8;i++)
	{
		((u64*)out)[i] = v[i] ^ v[i+8];
	}
}

//
// If we consider the hashing as a sequence of row and column operations, this performs the first row.
//
int PerformLayer_Zero(byte *ChainingValue, AlphaData* AlphaSet, HashData* KeySet, COUNT_TYPE M, COUNT_TYPE * Count)
{
	COUNT_TYPE i = 0, j = 0;

	byte Input[LAYER_LENGTH];
	byte Temp[HASH_LEN_BYTES_OUT];
	byte ChainingValue_IN[HASH_LEN_BYTES_OUT];

	// Copy the Chaining Value
	memcpy(ChainingValue_IN, ChainingValue, HASH_LEN_BYTES_OUT);

	int longsInHlen = (int)ceil((float)HASH_LEN_BYTES_OUT / 8);

	memset(AlphaSet, 0, (size_t)(sizeof(AlphaData) * M));

	for (i = 0; i < M; i++)
	{
		(*Count)++;
		byte Count_Bytes[CNT_LEN_BYTES];
		LongToBytes(*Count, Count_Bytes);

		if (i == 0)
		{ 
			// Initialize Temp with PI
			memcpy(Temp, PI_CONST, HASH_LEN_BYTES_OUT);
		}

		// Create the initial AlphaSet
		for(j=0; j<longsInHlen; j++)
		{
			((u64*)AlphaSet[i])[j] = ((u64*)ChainingValue_IN)[j] ^ ((u64*)Temp)[j];
		}

		memcpy(Input, Count_Bytes, CNT_LEN_BYTES);
		memcpy(Input + CNT_LEN_BYTES, AlphaSet[i], HASH_LEN_BYTES_OUT);
		memcpy(Input + CNT_LEN_BYTES + HASH_LEN_BYTES_OUT, Temp, HASH_LEN_BYTES_KS);
		memcpy(KeySet[i], Temp, HASH_LEN_BYTES_KS);

		PERFORM_BLAKE_STATE_F(Input, Temp);
	}

	//Update the ChainingValue after the layer
	memcpy(ChainingValue, Temp, HASH_LEN_BYTES_OUT);

	return SUCCESS;
}

//
// If we consider the hashing as a sequence of row and column operations, this performs the rest of the rows.
//
int Perform_Layer(AlphaData* AlphaSet, HashData* KeySet, byte* ChainingValue, COUNT_TYPE M, COUNT_TYPE m_cost, COUNT_TYPE * Count)
{
	COUNT_TYPE i = 0, j = 0;
	int k = 0;
	u64 address = 0;

	byte Input[LAYER_LENGTH];	
	byte Temp[HASH_LEN_BYTES_OUT];

	int longsInHlen = (int)ceil((double)HASH_LEN_BYTES_OUT / 8);
	int longsInKeySet = (int)ceil((double)HASH_LEN_BYTES_KS / 8);

	for (i = 0; i < M; i++)
	{
		(*Count)++;
		byte Count_Bytes[CNT_LEN_BYTES];
		LongToBytes(*Count, Count_Bytes);

		// Get the address after bit reversal.
		address = BitReverse64(i) >> (64 - m_cost);

		// Copy the Chaining Value
		if (i == 0) 
		{
			memcpy(Temp, ChainingValue, HASH_LEN_BYTES_OUT); 
		}

		// Update AlphaSet
		for(j=0; j < longsInHlen; j++)
		{
			((u64*)AlphaSet[i])[j] ^=  ((u64*)Temp)[j];
		}

		// Update KeySet
		for(j=0; j < longsInKeySet; j++)
		{
			((u64*)KeySet[address])[j] ^= ((u64*)Temp)[j];
		}

		memcpy(Input, Count_Bytes, CNT_LEN_BYTES); // Count
		memcpy(Input + CNT_LEN_BYTES, AlphaSet[i], HASH_LEN_BYTES_OUT); // ALPHA		
		memcpy(Input + CNT_LEN_BYTES + HASH_LEN_BYTES_OUT, KeySet[address], HASH_LEN_BYTES_KS);

		// Perform Blake2B for one round
		PERFORM_BLAKE_STATE_F((unsigned char*)Input, Temp);
	}

	//Update the ChainingValue after the layer
	memcpy(ChainingValue, Temp, HASH_LEN_BYTES_OUT);

	return SUCCESS;
}


int GenerateAlpha(byte* Password, int PasswordLength, byte* Salt, int SaltLength, COUNT_TYPE t_cost, COUNT_TYPE OutputBits, byte* Alpha)
{
	int count = 0;

	int bytes_length = PasswordLength + SaltLength + (CNT_LEN_BYTES*2);

	byte* bytes = (byte*)malloc(bytes_length);

	byte _T[CNT_LEN_BYTES];
	byte _OutputBits[CNT_LEN_BYTES];
	LongToBytes(t_cost, _T);
	LongToBytes(OutputBits, _OutputBits);

	memset(bytes, 0, bytes_length);

	memcpy(bytes, Password, PasswordLength);
	memcpy(bytes + PasswordLength, Salt, SaltLength);
	memcpy(bytes + PasswordLength + SaltLength, _T, CNT_LEN_BYTES);
	memcpy(bytes + PasswordLength + SaltLength + CNT_LEN_BYTES, _OutputBits, CNT_LEN_BYTES);
	
	HASH(bytes, bytes_length, Alpha);
	free(bytes);

	return SUCCESS;
}

int PHS_FULL(void *out, size_t outlen, const void *in, size_t inlen, const void *salt, size_t saltlen, COUNT_TYPE t_cost, COUNT_TYPE m_cost)
{
	int ret = SUCCESS, i=0;
	u64 M_LOOP =0;

	if (t_cost < 1) return ERROR_TIME_LESS;
	if (m_cost < 1) return ERROR_COST_LESS;
	if (m_cost > 31) return ERROR_COST_MORE;
	if ((saltlen > 256) || (saltlen < 0)) return ERROR_SALTLEN_INVALID;

	byte* alpha = (byte *)malloc(HASH_LEN_BYTES_OUT);

	byte _salt[SALT_LEN_BYTES];

	for (i = 0; i < SALT_LEN_BYTES; i++)
	{
		_salt[i] = ((byte*)salt)[i];
	}

	// Calculate Alpha
	ret = GenerateAlpha((byte*)in, (int)inlen, _salt, (int)saltlen, t_cost,(outlen*8), alpha);

	if (ret != SUCCESS) return ret;

	u64 __M = (u64)pow((float)2, (int)m_cost + ITER_ROUNDS);

	byte ChainingValue[HASH_LEN_BYTES_OUT];
	memcpy(ChainingValue, alpha, HASH_LEN_BYTES_OUT);

	// Initialize Memory
	HashData* KeySet = (HashData*)malloc((size_t)(HASH_LEN_BYTES_KS * __M));
	AlphaData* AlphaSet = (AlphaData*)malloc((size_t)(HASH_LEN_BYTES_OUT * __M));

	if(KeySet == NULL) {
		free(alpha);
		return ERROR_MEM_ALLOC_FAIL;
	}
	if(AlphaSet == NULL) {
		free(alpha);
		free (KeySet);
		return ERROR_MEM_ALLOC_FAIL;
	}

	COUNT_TYPE Count = 0;

	for(M_LOOP = m_cost; M_LOOP <= (m_cost + ITER_ROUNDS); M_LOOP++)
	{			
		u64 M = (u64)pow((float)2, (int)M_LOOP);

		ret = PerformLayer_Zero(ChainingValue, AlphaSet, KeySet, M, &Count);
		
		if (ret != SUCCESS) return ret;

		for (i = 0; i < t_cost; i++)
		{
			ret = Perform_Layer(AlphaSet, KeySet, ChainingValue, M, M_LOOP, &Count);
			if (ret != SUCCESS) return ret;
		}

		byte CNT[CNT_LEN_BYTES];
		LongToBytes(++Count, CNT);

		byte _M[CNT_LEN_BYTES];
		LongToBytes(M, _M);

		byte *H3_in = (byte *)malloc(CNT_LEN_BYTES*2 + HASH_LEN_BYTES_OUT + saltlen);

		memcpy(H3_in, CNT, CNT_LEN_BYTES);
		memcpy(H3_in +  CNT_LEN_BYTES , ChainingValue, HASH_LEN_BYTES_OUT);
		memcpy(H3_in +  CNT_LEN_BYTES + HASH_LEN_BYTES_OUT, salt, saltlen);
		memcpy(H3_in +  CNT_LEN_BYTES + HASH_LEN_BYTES_OUT + saltlen, _M, CNT_LEN_BYTES);	

		//printf("\n\n %d", M);

		HASH(H3_in, CNT_LEN_BYTES*2 + HASH_LEN_BYTES_OUT + saltlen, ChainingValue);

		free(H3_in);
	}

	free(KeySet);
	free(AlphaSet);
	free(alpha);
	
	if (outlen <= HASH_LEN_BYTES_OUT)
	{
		for (u32 i = 0; i < outlen; i++)
		{
			((byte*)out)[i] = ChainingValue[i];
		}
	}
	else
	{
		return ERROR_INVALID_OUT_HLEN;
	}

	return SUCCESS;
}

int PHS(void *out, size_t outlen, const void *in, size_t inlen, const void *salt, size_t saltlen, unsigned int t_cost, unsigned int m_cost)
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

	case ERROR_MEM_ALLOC_FAIL:
		return "Memory Allocation Failed";

	default:
		return "Undefined Error";

	}
}


void LongToBytes(COUNT_TYPE val, byte* b)
{
#ifndef COUNT_32	
	b[7] = (byte)((val >> 40) & 0xff);
	b[6] = (byte)((val >> 36) & 0xff);
	b[5] = (byte)((val >> 32) & 0xff);
	b[4] = (byte)((val >> 28) & 0xff);
#endif

	b[3] = (byte)((val >> 24) & 0xff);
	b[2] = (byte)((val >> 16) & 0xff);
	b[1] = (byte)((val >> 8) & 0xff);
	b[0] = (byte)((val >> 0) & 0xff);
}



u64 BitReverse64(u64 value)
{	
	value = _SWAP(value, 32,  0x00000000FFFFFFFFull);
	value = _SWAP(value, 16,  0x0000FFFF0000FFFFull);
	value = _SWAP(value, 8,   0x00FF00FF00FF00FFull);
	value = _SWAP(value, 4,   0x0F0F0F0F0F0F0F0Full);
	value = _SWAP(value, 2,   0x3333333333333333ull);
	value = _SWAP(value, 1,   0x5555555555555555ull);

	return value;
}

u32 BitReverse32(register u32 x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));
}
