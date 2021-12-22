#include "bit.h"

bit_t::bit_t() : bit(0) {}
bit_t::bit_t(int bit) : bit(bit&1) {}
bit_t bit_t::operator=(int bit) {
    this->bit = bit&1;
    return *this;
}

bool bit_t::operator==(bit_t other){
    return bit == other.bit;
}

bool bit_t::operator==(int other){
    return bit == (other&1);
}

template <unsigned int N>
bit_array_t<N>::bit_array_t() {
    for (unsigned int i = 0; i < N; i++) {
        bit[i] = 0;
    }
}

template <unsigned int N>
bit_array_t<N>::bit_array_t(unsigned int bits) {
    for (unsigned int i = 0; i < N; i++) {
        bit[i] = bits&1;
        bits >>= 1;
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
    return bit[idx] == 1;
}

template <unsigned int N>
bit_array_t<N> bit_array_t<N>::operator=(unsigned int bits)
{
    for (unsigned int i = 0; i < N; i++) {
        bit[i] = bits&1;
        bits >>= 1;
    }
    return *this;
}

template <unsigned int N>
bool bit_array_t<N>::operator==(bit_array_t<N> other) {
    for (unsigned int i = 0; i < N; i++) {
        if (!(bit[i] == other.bit[i])) {
            return false;
        }
    }
    return true;
}

template <unsigned int N>
bool bit_array_t<N>::operator==(unsigned int other) {
    for (unsigned int i = 0; i < N; i++) {
        if (bit[i].bit != (other&1)) {
            return false;
        }
        other >>= 1;
    }
    return true;
}

const bit_t ZERO(0);
const bit_t ONE(1);

template class bit_array_t<2>;
template class bit_array_t<4>;
template class bit_array_t<8>;
template class bit_array_t<16>;
template class bit_array_t<32>;

bit_t Nand(bit_t a, bit_t b)
{
    return bit_t(!(a.bit & b.bit)); // You cannot use & or ! in other places.
}

// You need to implement the following functions:
bit_t Not(bit_t in)
{
    bit_t out;
    return out;
}
bit_t And(bit_t a, bit_t b)
{
    bit_t out;
    return out;
}
bit_t Or(bit_t a, bit_t b)
{
    bit_t out;
    return out;
}
bit_t Xor(bit_t a, bit_t b)
{
    bit_t out;
    return out;
}
bit_t Mux(bit_t a, bit_t b, bit_t sel)
{
    bit_t out;
    return out;
}
std::tuple<bit_t, bit_t> DMux(bit_t in, bit_t sel)
{
    bit_t a, b;
    return std::make_tuple(a, b);
}

bit16_t Not16(bit16_t in)
{
    bit16_t out;
    return out;
}
bit16_t And16(bit16_t a, bit16_t b)
{
    bit16_t out;
    return out;
}
bit16_t Or16(bit16_t a, bit16_t b)
{
    bit16_t out;
    return out;
}
bit16_t Mux16(bit16_t a, bit16_t b, bit_t sel)
{
    bit16_t out;
    return out;
}
bit_t Or8Way(bit8_t in)
{
    bit_t out;
    return out;
}
bit16_t Mux4Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit2_t sel)
{
    bit16_t out;
    return out;
}
bit16_t Mux8Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit16_t e, bit16_t f, bit16_t g, bit16_t h, bit4_t sel)
{
    bit16_t out;
    return out;
}
std::tuple<bit_t, bit_t, bit_t, bit_t> DMux4Way(bit_t in, bit2_t sel)
{
    bit_t a, b, c, d;
    return std::make_tuple(a, b, c, d);
}
std::tuple<bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t> DMux8Way(bit_t in, bit4_t sel)
{
    bit_t a, b, c, d, e, f, g, h;
    return std::make_tuple(a, b, c, d, e, f, g, h);
}