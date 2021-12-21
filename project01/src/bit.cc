#include "bit.h"

bit_t::bit_t() : bit(0) {}
bit_t::bit_t(int bit) : bit(bit&1) {}
bit_t bit_t::operator=(int bit) {
    this->bit = bit&1;
    return *this;
}

template <unsigned int N>
bit_array_t<N>::bit_array_t() {
    for (int i = 0; i < N; i++) {
        bit[i] = 0;
    }
}

template <unsigned int N>
void bit_array_t<N>::set(unsigned int idx)
{
    bit[idx] = 1;
}

template <unsigned int N>
void bit_array_t<N>::clear(unsigned int idx)
{
    bit[idx] = 0;
}

template <unsigned int N>
bool bit_array_t<N>::test(unsigned int idx)
{
    return bit[idx];
}

bit_t Nand(bit_t a, bit_t b)
{
    return bit_t(!(a.bit & b.bit)); // You cannot use & or ! in other places.
}

// You need to implement the following functions:
bit_t Not(bit_t in)
{
    return bit_t();
}
bit_t And(bit_t a, bit_t b)
{
    return bit_t();
}
bit_t Or(bit_t a, bit_t b)
{
    return bit_t();
}
bit_t Xor(bit_t a, bit_t b)
{
    return bit_t();
}
bit_t Mux(bit_t a, bit_t b, bit_t sel)
{
    return bit_t();
}
bit_t DMux(bit_t in, bit_t sel)
{
    return bit_t();
}

bit16_t Not16(bit16_t in)
{
    return bit16_t();
}
bit16_t And16(bit16_t a, bit16_t b)
{
    return bit16_t();
}
bit16_t Or16(bit16_t a, bit16_t b)
{
    return bit16_t();
}
bit16_t Mux16(bit16_t a, bit16_t b, bit_t sel)
{
    return bit16_t();
}
bit_t Or8Way(bit8_t in)
{
    return bit_t();
}
bit16_t Mux4Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit2_t sel)
{
    return bit16_t();
}
bit16_t Mux8Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit16_t e, bit16_t f, bit16_t g, bit16_t h, bit4_t sel)
{
    return bit16_t();
}
std::tuple<bit_t, bit_t, bit_t, bit_t> DMux4Way(bit_t in, bit2_t sel)
{
    return std::make_tuple(bit_t(), bit_t(), bit_t(), bit_t());
}
std::tuple<bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t> DMux8Way(bit_t in, bit4_t sel)
{
    return std::make_tuple(bit_t(), bit_t(), bit_t(), bit_t(), bit_t(), bit_t(), bit_t(), bit_t());
}