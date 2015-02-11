#pragma once

#ifndef blake_impl_H_
#define blake_impl_H_

#include <stdint.h>

// Performs BlakePerm on 'in' to give 'out'

void BlakeSingleRound(uint64_t* in, uint64_t* out);

void BlakePerm(uint64_t* in, uint64_t* out);
void BlakeExpand(uint8_t* in, size_t inLength, uint8_t* out);

int Blake512(unsigned char *in, uint64_t inlen, unsigned char *out);

#endif
