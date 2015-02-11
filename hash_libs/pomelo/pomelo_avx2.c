// PHC submission:  POMELO v2  
// Designed by:     Hongjun Wu (Email: wuhongjun@gmail.com)  
// This code was written by Hongjun Wu on Jan 31, 2015.  

// This code give the C implementation of POMELO using the AVX2 implementation. 

// m_cost is an integer, 0 <= m_cost <= 25; the memory size is 2**(13+m_cost) bytes   
// t_cost is an integer, 0 <= t_cost <= 25; the number of steps is roughly:  2**(8+m_cost+t_cost)    
// For the machine today, it is recommended that: 5 <= t_cost + m_cost <= 25;   
// one may use the parameters: m_cost = 15; t_cost = 0; (256 MegaByte memory)    

#include <stdlib.h>
#include <string.h>  
#include <immintrin.h> 

#define XOR256(x,y)       _mm256_xor_si256((x),(y))        /*XOR256(x,y) = x ^ y, where x and y are two 256-bit word*/
#define ADD256(x,y)       _mm256_add_epi64((x), (y))   
#define OR256(x,y)        _mm256_or_si256((x),(y))         /*OR(x,y)  = x | y, where x and y are two 256-bit word*/
#define SHIFTL256(x,n)    _mm256_slli_epi64((x), (n)) 
#define ROTL256(x,n)      OR256( _mm256_slli_epi64((x), (n)), _mm256_srli_epi64((x),(64-n)) )   /*Rotate 4 64-bit unsigned integers in x to the left by n-bit positions*/
#define ROTL256_64(x)     _mm256_permute4x64_epi64((x), _MM_SHUFFLE(2,1,0,3))  /*Rotate x by 64-bit  positions to the left*/
#define ROTL256_128(x)    _mm256_permute4x64_epi64((x), _MM_SHUFFLE(1,0,3,2))  /*Rotate x by 128-bit positions to the left*/
#define ROTL256_192(x)    _mm256_permute4x64_epi64((x), _MM_SHUFFLE(0,3,2,1))  /*Rotate x by 192-bit positions to the left*/

// Function F0 update the state using a nonlinear feedback shift register in the expansion (step 3)   
#define F0(i)  {            \
    i0 = ((i) - 0)  & mask; \
    i1 = ((i) - 2)  & mask; \
    i2 = ((i) - 3)  & mask; \
    i3 = ((i) - 7)  & mask; \
    i4 = ((i) - 13) & mask; \
    S[i0] = XOR256(ADD256(XOR256(S[i1], S[i2]), S[i3]), S[i4]);  \
    S[i0] = ROTL256_64(S[i0]);  \
    S[i0] = ROTL256(S[i0],17);  \
}

// Function F update the state using a nonlinear feedback shift register 
#define F(i)  {             \
    i0 = ((i) - 0)  & mask; \
    i1 = ((i) - 2)  & mask; \
    i2 = ((i) - 3)  & mask; \
    i3 = ((i) - 7)  & mask; \
    i4 = ((i) - 13) & mask; \
    S[i0] = ADD256(S[i0], XOR256(ADD256(XOR256(S[i1], S[i2]), S[i3]), S[i4]));      \
    S[i0] = ROTL256_64(S[i0]);  \
    S[i0] = ROTL256(S[i0],17); \
}

// Function G update the state using function F together with Key-INdependent random memory accesses  
#define G(i,random_number)  {                                                       \
    index_global = (random_number >> 16) & mask;                                    \
    for (j = 0; j < 32; j++)                                                        \
    {                                                                               \
        F(i+j);                                                                     \
        index_global   = (index_global + 1) & mask;                                 \
        index_local    = (i + j - 0x1000 + (random_number & 0x1fff)) & mask;        \
        S[i0]          = ADD256(S[i0],SHIFTL256(S[index_local],1));                 \
        S[index_local] = ADD256(S[index_local],  SHIFTL256(S[i0],2));               \
        S[i0]          = ADD256(S[i0],SHIFTL256(S[index_global],1));                \
        S[index_global]= ADD256(S[index_global], SHIFTL256(S[i0],3));               \
        random_number += (random_number << 2);                                      \
        random_number  = (random_number << 19) ^ (random_number >> 45)  ^ 3141592653589793238ULL;   \
    }                                                                               \
}

// Function H update the state using function F together with Key-dependent random memory accesses  
#define H(i, random_number)  {                                                      \
    index_global = (random_number >> 16) & mask;                                    \
    for (j = 0; j < 32; j++)                                                        \
    {                                                                               \
        F(i+j);                                                                     \
        index_global   = (index_global + 1) & mask;                                 \
        index_local    = (i + j - 0x1000 + (random_number & 0x1fff)) & mask;        \
        S[i0]          = ADD256(S[i0],SHIFTL256(S[index_local],1));                 \
        S[index_local] = ADD256(S[index_local],  SHIFTL256(S[i0],2));               \
        S[i0]          = ADD256(S[i0],SHIFTL256(S[index_global],1));                \
        S[index_global]= ADD256(S[index_global], SHIFTL256(S[i0],3));               \
        random_number  = ((unsigned long long*)S)[(i3 << 2)];                       \
    }                                                                               \
}

void* aligned_malloc(size_t required_bytes, size_t alignment); 
void aligned_free(void *p); 
int PHS(void *out, size_t outlen, const void *in, size_t inlen, const void *salt, size_t saltlen, unsigned int t_cost, unsigned int m_cost);

int PHS(void *out, size_t outlen, const void *in, size_t inlen, const void *salt, size_t saltlen, unsigned int t_cost, unsigned int m_cost)
{
    unsigned long long i,j,k;         
    unsigned long long i0,i1,i2,i3,i4;
    __m256i *S; 
    unsigned long long random_number, index_global, index_local; 
    unsigned long long state_size, mask;  

    //check the size of password, salt, and output. Password at most 256 bytes; salt at most 64 bytes; output at most 256 bytes.  
    if (inlen > 256 || saltlen > 64 || outlen > 256 || inlen < 0 || saltlen < 0 || outlen < 0) return 1;  

    //Step 1: Initialize the state S          
    state_size = 1ULL << (13+m_cost);    // state size is 2**(13+m_cost) bytes 
    S = (__m256i *)aligned_malloc(state_size,32);   // aligned malloc is needed; otherwise it is only aligned to 16 bytes when using GCC.        
    mask = (1ULL << (8+m_cost)) - 1;     // mask is used for modulation: modulo size_size/32

    //Step 2: Load the password, salt, input/output sizes into the state S
    for (i = 0; i < inlen; i++)   ((unsigned char*)S)[i] = ((unsigned char*)in)[i];         // load password into S
    for (i = 0; i < saltlen; i++) ((unsigned char*)S)[inlen+i] = ((unsigned char*)salt)[i]; // load salt into S
    for (i = inlen+saltlen; i < 384; i++) ((unsigned char*)S)[i] = 0;      
    ((unsigned char*)S)[384] = inlen & 0xff;          // load password length (in bytes) into S;
    ((unsigned char*)S)[385] = (inlen >> 8) & 0xff;   // load password length (in bytes) into S;
    ((unsigned char*)S)[386] = saltlen;               // load salt length (in bytes) into S;
    ((unsigned char*)S)[387] = outlen & 0xff;         // load output length (in bytes into S)
    ((unsigned char*)S)[388] = (outlen >> 8) & 0xff;  // load output length (in bytes into S) 
    ((unsigned char*)S)[389] = 0; 
    ((unsigned char*)S)[390] = 0; 
    ((unsigned char*)S)[391] = 0; 

    ((unsigned char*)S)[392] = 1;
    ((unsigned char*)S)[393] = 1;
    for (i = 394; i < 416; i++) ((unsigned char*)S)[i] = ((unsigned char*)S)[i-1] + ((unsigned char*)S)[i-2];    

    //Step 3: Expand the data into the whole state  
    for (i = 13; i < (1ULL << (8+m_cost)); i=i+1)  F0(i); 

    //Step 4: Update the state using function G  
    random_number = 123456789ULL;    
    for (i = 0; i < (1ULL << (7+m_cost+t_cost)); i=i+32)  G(i,random_number); 

    //Step 5: Update the state using function H     
    for (i = 1ULL << (7+m_cost+t_cost);  i < (1ULL << (8+m_cost+t_cost)); i=i+32)  H(i,random_number);  

    //Step 6: Update the state using function F 
    for (i = 0; i < (1ULL << (8+m_cost)); i=i+1)  F(i);       

    //Step 7: Generate the output   
    memcpy(out, ((unsigned char*)S)+state_size-outlen, outlen);
    memset(S, 0, state_size);  // clear the memory 
    aligned_free(S);           // free the memory

    return 0;
}
