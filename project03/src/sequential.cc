#include "sequential.h"
#include <vector>

bit_t DFF_t::DFF(bit_t in) {
    bit_t tmp = val;
    val = in;
    return tmp;
}


// You need to implement the following functions:
bit_t Bit(bit_t in, bit_t load, DFF_t** dffs, int n) {
    bit_t out;
    return out;
}
bit16_t Register(bit16_t in, bit_t load, DFF_t** dffs, int n) {
    bit16_t out;
    return out;
}
bit16_t RAM8(bit16_t in, bit_t load, bit4_t address, DFF_t** dffs, int n) {
    bit16_t out;
    return out;
}
bit16_t RAM64(bit16_t in, bit_t load, bit8_t address, DFF_t** dffs, int n) {
    bit16_t out;
    return out;
}
bit16_t RAM512(bit16_t in, bit_t load, bit16_t address, DFF_t** dffs, int n) {
    bit16_t out;
    return out;
}
bit16_t RAM4K(bit16_t in, bit_t load, bit16_t address, DFF_t** dffs, int n) {
    bit16_t out;
    return out;
}
bit16_t RAM16K(bit16_t in, bit_t load, bit16_t address, DFF_t** dffs, int n) {
    bit16_t out;
    return out;
}
bit16_t PC(bit16_t in, bit_t inc, bit_t load, bit_t reset, DFF_t** dffs, int n) {
    bit16_t out;
    return out;
}