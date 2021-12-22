#ifndef __ARITHMATIC_H__
#define __ARITHMATIC_H__
#include "bit.h"
#include "tuple"

std::tuple<bit_t, bit_t> HalfAdder(bit_t a, bit_t b);
std::tuple<bit_t, bit_t> FullAdder(bit_t a, bit_t b, bit_t cin);
bit16_t Add16(bit16_t a, bit16_t b);
bit16_t Inc16(bit16_t in);
std::tuple<bit16_t, bit_t, bit_t> ALU(bit16_t x, bit16_t y, bit_t zx, bit_t nx, bit_t zy, bit_t ny, bit_t f, bit_t no);

#endif // __ARITHMATIC_H__