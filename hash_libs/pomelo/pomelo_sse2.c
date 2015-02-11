// PHC submission:  POMELO v2  
// Designed by:     Hongjun Wu (Email: wuhongjun@gmail.com)  
// This code was written by Hongjun Wu on Jan 31, 2015. 

// This code gives the C implementation of POMELO using the SSE2 instructions.  

// m_cost is an integer, 0 <= m_cost <= 25; the memory size is 2**(13+m_cost) bytes   
// t_cost is an integer, 0 <= t_cost <= 25; the number of steps is roughly:  2**(8+m_cost+t_cost)    
// For the machine today, it is recommended that: 5 <= t_cost + m_cost <= 25;   
// one may use the parameters: m_cost = 15; t_cost = 0; (256 MegaByte memory)    

#include <stdlib.h>
#include <string.h>  
#include <immintrin.h> 

#define ADD128(x,y)       _mm_add_epi64((x), (y))   
#define XOR128(x,y)       _mm_xor_si128((x),(y))     /*XOR(x,y) = x ^ y, where x and y are two 128-bit word*/
#define OR128(x,y)        _mm_or_si128((x),(y))      /*OR(x,y)  = x | y, where x and y are two 128-bit word*/
#define ROTL128(x,n)      XOR128(_mm_slli_epi64((x), (n)),  _mm_srli_epi64((x),(64-n)))  /*Rotate 2 64-bit unsigned integers in x to the left by n-bit positions*/
#define SHIFTL128(x,n)    _mm_slli_epi64((x), (n))      
#define SHIFTL64(x)       _mm_slli_si128(x, 8) 
#define SHIFTR64(x)       _mm_srli_si128(x, 8)

// Function F0 update the state using a nonlinear feedback shift register  
#define F0(i)  {               \
    i0 = ((i) - 0*2)  & mask1; \
    i1 = ((i) - 2*2)  & mask1; \
    i2 = ((i) - 3*2)  & mask1; \
    i3 = ((i) - 7*2)  & mask1; \
    i4 = ((i) - 13*2) & mask1; \
    S[i0]   = XOR128(ADD128(XOR128(S[i1],   S[i2]),   S[i3]),   S[i4]);    \
    S[i0+1] = XOR128(ADD128(XOR128(S[i1+1], S[i2+1]), S[i3+1]), S[i4+1]);  \
    temp = S[i0];                  \
    S[i0]   = XOR128(SHIFTL64(S[i0]),   SHIFTR64(S[i0+1]));  \
    S[i0+1] = XOR128(SHIFTL64(S[i0+1]), SHIFTR64(temp));   \
    S[i0]   = ROTL128(S[i0],  17);  \
    S[i0+1] = ROTL128(S[i0+1],17);  \
}

// Function F update the state using a nonlinear feedback shift register 
#define F(i)  {              \
    i0 = ((i) - 0*2)  & mask1; \
    i1 = ((i) - 2*2)  & mask1; \
    i2 = ((i) - 3*2)  & mask1; \
    i3 = ((i) - 7*2)  & mask1; \
    i4 = ((i) - 13*2) & mask1; \
    S[i0]   = ADD128(S[i0],XOR128(ADD128(XOR128(S[i1],   S[i2]),   S[i3]),   S[i4]));    \
    S[i0+1] = ADD128(S[i0+1],XOR128(ADD128(XOR128(S[i1+1], S[i2+1]), S[i3+1]), S[i4+1]));  \
    temp = S[i0];                  \
    S[i0]   = XOR128(SHIFTL64(S[i0]),   SHIFTR64(S[i0+1]));  \
    S[i0+1] = XOR128(SHIFTL64(S[i0+1]), SHIFTR64(temp));   \
    S[i0]   = ROTL128(S[i0],  17);  \
    S[i0+1] = ROTL128(S[i0+1],17);  \
}

#define G(i,random_number)  {                                                          \
    index_global = ((random_number >> 16) & mask) << 1;                                \
    for (j = 0; j < 64; j = j+2)                                                        \
    {                                                                                  \
        F(i+j);                                                                        \
        index_global     = (index_global + 2) & mask1;                                 \
        index_local      = (((i + j) >> 1) - 0x1000 + (random_number & 0x1fff)) & mask;\
        index_local      = index_local << 1;                                           \
        S[i0]            = ADD128(S[i0],  SHIFTL128(S[index_local],1));                \
        S[i0+1]          = ADD128(S[i0+1],SHIFTL128(S[index_local+1],1));              \
        S[index_local]   = ADD128(S[index_local],   SHIFTL128(S[i0],2));               \
        S[index_local+1] = ADD128(S[index_local+1], SHIFTL128(S[i0+1],2));             \
        S[i0]            = ADD128(S[i0],  SHIFTL128(S[index_global],1));               \
        S[i0+1]          = ADD128(S[i0+1],SHIFTL128(S[index_global+1],1));             \
        S[index_global]  = ADD128(S[index_global],  SHIFTL128(S[i0],3));               \
        S[index_global+1]= ADD128(S[index_global+1],SHIFTL128(S[i0+1],3));             \
        random_number   += (random_number << 2);                                       \
        random_number    = (random_number << 19) ^ (random_number >> 45)  ^ 3141592653589793238ULL;   \
    }                                                                                  \
}

#define H(i, random_number)  {                                                         \
    index_global = ((random_number >> 16) & mask) << 1;                                \
    for (j = 0; j < 64; j = j+2)                                                       \
    {                                                                                  \
        F(i+j);                                                                        \
        index_global     = (index_global + 2) & mask1;                                 \
        index_local      = (((i + j) >> 1) - 0x1000 + (random_number & 0x1fff)) & mask;\
        index_local      = index_local << 1;                                           \
        S[i0]            = ADD128(S[i0],  SHIFTL128(S[index_local],1));                \
        S[i0+1]          = ADD128(S[i0+1],SHIFTL128(S[index_local+1],1));              \
        S[index_local]   = ADD128(S[index_local],   SHIFTL128(S[i0],2));               \
        S[index_local+1] = ADD128(S[index_local+1], SHIFTL128(S[i0+1],2));             \
        S[i0]            = ADD128(S[i0],  SHIFTL128(S[index_global],1));               \
        S[i0+1]          = ADD128(S[i0+1],SHIFTL128(S[index_global+1],1));             \
        S[index_global]  = ADD128(S[index_global],  SHIFTL128(S[i0],3));               \
        S[index_global+1]= ADD128(S[index_global+1],SHIFTL128(S[i0+1],3));             \
        random_number  = ((unsigned long long*)S)[i3<<1];                                                        \
    }                                                                                     \
}       

int PHS(void *out, size_t outlen, const void *in, size_t inlen, const void *salt, size_t saltlen, unsigned int t_cost, unsigned int m_cost);

int PHS(void *out, size_t outlen, const void *in, size_t inlen, const void *salt, size_t saltlen, unsigned int t_cost, unsigned int m_cost)
{
    unsigned long long i,j;
    __m128i temp;          
    unsigned long long i0,i1,i2,i3,i4;
    __m128i *S;  
    unsigned long long random_number, index_global, index_local; 
    unsigned long long state_size, mask, mask1;  

    //check the size of password, salt and output. Password is at most 256 bytes; the salt is at most 32 bytes. 
    if (inlen > 256 || saltlen > 64 || outlen > 256 || inlen < 0 || saltlen < 0 || outlen < 0) return 1;  

    //Step 1: Initialize the state S          
    state_size = 1ULL << (13+m_cost);   // state size is 2**(13+m_cost) bytes 
    S = (__m128i *)malloc(state_size); 
    mask  = (1ULL << (8+m_cost)) - 1;   // mask is used for modulation: modulo size_size/32; 
    mask1 = (1ULL << (9+m_cost)) - 1;   // mask is used for modulation: modulo size_size/16; 

    //Step 2: Load the password, salt, input/output sizes into the state S
    for (i = 0; i < inlen; i++)   ((unsigned char*)S)[i] = ((unsigned char*)in)[i];         // load password into S
    for (i = 0; i < saltlen; i++) ((unsigned char*)S)[inlen+i] = ((unsigned char*)salt)[i]; // load salt into S
    for (i = inlen+saltlen; i < 384; i++) ((unsigned char*)S)[i] = 0;      
    ((unsigned char*)S)[384] = inlen & 0xff;         // load password length (in bytes) into S;
    ((unsigned char*)S)[385] = (inlen >> 8) & 0xff;  // load password length (in bytes) into S;
    ((unsigned char*)S)[386] = saltlen;              // load salt length (in bytes) into S;
    ((unsigned char*)S)[387] = outlen & 0xff;        // load output length (in bytes into S)
    ((unsigned char*)S)[388] = (outlen >> 8) & 0xff; // load output length (in bytes into S) 
    ((unsigned char*)S)[389] = 0; 
    ((unsigned char*)S)[390] = 0; 
    ((unsigned char*)S)[391] = 0;

    ((unsigned char*)S)[392] = 1;
    ((unsigned char*)S)[393] = 1;
    for (i = 394; i < 416; i++) ((unsigned char*)S)[i] = ((unsigned char*)S)[i-1] + ((unsigned char*)S)[i-2];    

    //Step 3: Expand the data into the whole state  
    for (i = 13*2; i < (1ULL << (9+m_cost)); i=i+2) F0(i);  
 
    //Step 4: Update the state using function G  
    random_number = 123456789ULL;    
    for (i = 0; i < (1ULL << (8+m_cost+t_cost)); i=i+64)    G(i,random_number);

    //Step 5: Update the state using function H     
    for (i = 1ULL << (8+m_cost+t_cost);  i < (1ULL << (9+m_cost+t_cost)); i=i+64)  H(i,random_number);

    //Step 6: Update the state using function F 
    for (i = 0; i < (1ULL << (9+m_cost)); i=i+2)  F(i);       

    //Step 7: Generate the output   
    memcpy(out, ((unsigned char*)S)+state_size-outlen, outlen);
    memset(S, 0, state_size);  // clear the memory 
    free(S);                   // free the memory

    return 0;
}
