#ifndef __SEQUENTIAL_H__
#define __SEQUENTIAL_H__
#include "bit.h"
#include "arithmatic.h"

struct DFF_t {
    bit_t val;
    bit_t DFF(bit_t in);
};

bit_t Bit(bit_t in, bit_t load, DFF_t** dffs, int n = 1);
bit16_t Register(bit16_t in, bit_t load, DFF_t** dffs, int n = 16);
bit16_t RAM8(bit16_t in, bit_t load, bit4_t address, DFF_t** dffs, int n = 128);
bit16_t RAM64(bit16_t in, bit_t load, bit8_t address, DFF_t** dffs, int n = 1024);
bit16_t RAM512(bit16_t in, bit_t load, bit16_t address, DFF_t** dffs, int n = 8192);
bit16_t RAM4K(bit16_t in, bit_t load, bit16_t address, DFF_t** dffs, int n = 65536);
bit16_t RAM16K(bit16_t in, bit_t load, bit16_t address, DFF_t** dffs, int n = 262144);
bit16_t PC(bit16_t in, bit_t inc, bit_t load, bit_t reset, DFF_t** dffs, int n = 16);

#endif // __SEQUENTIAL_H__