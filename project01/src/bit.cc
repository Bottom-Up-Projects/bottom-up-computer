#include "bit.h"

bit_t::bit_t() : bit(0) {}
bit_t::bit_t(int bit) : bit(bit & 1) {}
bit_t bit_t::operator=(int bit) {
    this->bit = bit & 1;
    return *this;
}

bool bit_t::operator==(bit_t other) {
    return bit == other.bit;
}

bool bit_t::operator==(int other) {
    return bit == (other & 1);
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
        bit[i] = bits & 1;
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
        bit[i] = bits & 1;
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
        if (bit[i].bit != (other & 1)) {
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

/*
a | not a
---------
0 | 1
1 | 0
*/
bit_t Not(bit_t in)
{
    return Nand(in, in);
}

/*
a | b | a & b
-------------
0 | 0 | 0
0 | 1 | 0
1 | 0 | 0
1 | 1 | 1
>> a * b
*/
bit_t And(bit_t a, bit_t b)
{
    return Not(Nand(a, b));
}

/*
a | b | a || b
---------------
0 | 0 | 0
0 | 1 | 1
1 | 0 | 1
1 | 1 | 1
>> ~(~a * ~b)
*/
bit_t Or(bit_t a, bit_t b)
{
    return Not(And(Not(a), Not(b)));
}

/*
a | b | a ^ b
-------------
0 | 0 | 0
0 | 1 | 1
1 | 0 | 1
1 | 1 | 0
>> ~a * b + a * ~b
*/
bit_t Xor(bit_t a, bit_t b)
{
    return Or(And(Not(a), b), And(a, Not(b)));
}

/*
a | b | sel | Mux(a, b, sel)
-----------------------------
0 | 0 | 0 | 0
0 | 0 | 1 | 0
0 | 1 | 0 | 0
0 | 1 | 1 | 1
1 | 0 | 0 | 1
1 | 0 | 1 | 0
1 | 1 | 0 | 1
1 | 1 | 1 | 1
>> a * ~sel + b * sel
*/
bit_t Mux(bit_t a, bit_t b, bit_t sel)
{
    return Or(And(Not(sel), a), And(sel, b));
}

/*
in | sel | Demux(in, sel)
-------------------------
0 | 0 | (0, 0)
0 | 1 | (0, 0)
1 | 0 | (1, 0)
1 | 1 | (0, 1)
>> a : in * ~sel
>> b : in * sel
*/
std::tuple<bit_t, bit_t> DMux(bit_t in, bit_t sel)
{
    return std::make_tuple(And(in, Not(sel)), And(in, sel));
}

bit16_t Not16(bit16_t in)
{
    in.bit[0] = Not(in.bit[0]);
    in.bit[1] = Not(in.bit[1]);
    in.bit[2] = Not(in.bit[2]);
    in.bit[3] = Not(in.bit[3]);
    in.bit[4] = Not(in.bit[4]);
    in.bit[5] = Not(in.bit[5]);
    in.bit[6] = Not(in.bit[6]);
    in.bit[7] = Not(in.bit[7]);
    in.bit[8] = Not(in.bit[8]);
    in.bit[9] = Not(in.bit[9]);
    in.bit[10] = Not(in.bit[10]);
    in.bit[11] = Not(in.bit[11]);
    in.bit[12] = Not(in.bit[12]);
    in.bit[13] = Not(in.bit[13]);
    in.bit[14] = Not(in.bit[14]);
    in.bit[15] = Not(in.bit[15]);
    
    return in;
}
bit16_t And16(bit16_t a, bit16_t b)
{
    bit16_t result;
    result.bit[0] = And(a.bit[0], b.bit[0]);
    result.bit[1] = And(a.bit[1], b.bit[1]);
    result.bit[2] = And(a.bit[2], b.bit[2]);
    result.bit[3] = And(a.bit[3], b.bit[3]);
    result.bit[4] = And(a.bit[4], b.bit[4]);
    result.bit[5] = And(a.bit[5], b.bit[5]);
    result.bit[6] = And(a.bit[6], b.bit[6]);
    result.bit[7] = And(a.bit[7], b.bit[7]);
    result.bit[8] = And(a.bit[8], b.bit[8]);
    result.bit[9] = And(a.bit[9], b.bit[9]);
    result.bit[10] = And(a.bit[10], b.bit[10]);
    result.bit[11] = And(a.bit[11], b.bit[11]);
    result.bit[12] = And(a.bit[12], b.bit[12]);
    result.bit[13] = And(a.bit[13], b.bit[13]);
    result.bit[14] = And(a.bit[14], b.bit[14]);
    result.bit[15] = And(a.bit[15], b.bit[15]);

    return result;
}
bit16_t Or16(bit16_t a, bit16_t b)
{
    bit16_t result;
    result.bit[0] = Or(a.bit[0], b.bit[0]);
    result.bit[1] = Or(a.bit[1], b.bit[1]);
    result.bit[2] = Or(a.bit[2], b.bit[2]);
    result.bit[3] = Or(a.bit[3], b.bit[3]);
    result.bit[4] = Or(a.bit[4], b.bit[4]);
    result.bit[5] = Or(a.bit[5], b.bit[5]);
    result.bit[6] = Or(a.bit[6], b.bit[6]);
    result.bit[7] = Or(a.bit[7], b.bit[7]);
    result.bit[8] = Or(a.bit[8], b.bit[8]);
    result.bit[9] = Or(a.bit[9], b.bit[9]);
    result.bit[10] = Or(a.bit[10], b.bit[10]);
    result.bit[11] = Or(a.bit[11], b.bit[11]);
    result.bit[12] = Or(a.bit[12], b.bit[12]);
    result.bit[13] = Or(a.bit[13], b.bit[13]);
    result.bit[14] = Or(a.bit[14], b.bit[14]);
    result.bit[15] = Or(a.bit[15], b.bit[15]);

    return result;
}
bit16_t Mux16(bit16_t a, bit16_t b, bit_t sel)
{
    bit16_t result;
    result.bit[0] = Mux(a.bit[0], b.bit[0], sel);
    result.bit[1] = Mux(a.bit[1], b.bit[1], sel);
    result.bit[2] = Mux(a.bit[2], b.bit[2], sel);
    result.bit[3] = Mux(a.bit[3], b.bit[3], sel);
    result.bit[4] = Mux(a.bit[4], b.bit[4], sel);
    result.bit[5] = Mux(a.bit[5], b.bit[5], sel);
    result.bit[6] = Mux(a.bit[6], b.bit[6], sel);
    result.bit[7] = Mux(a.bit[7], b.bit[7], sel);
    result.bit[8] = Mux(a.bit[8], b.bit[8], sel);
    result.bit[9] = Mux(a.bit[9], b.bit[9], sel);
    result.bit[10] = Mux(a.bit[10], b.bit[10], sel);
    result.bit[11] = Mux(a.bit[11], b.bit[11], sel);
    result.bit[12] = Mux(a.bit[12], b.bit[12], sel);
    result.bit[13] = Mux(a.bit[13], b.bit[13], sel);
    result.bit[14] = Mux(a.bit[14], b.bit[14], sel);
    result.bit[15] = Mux(a.bit[15], b.bit[15], sel);

    return result;
}
bit_t Or8Way(bit8_t in)
{
    bit_t result = ZERO;
    result = Or(result, Or(in.bit[0], in.bit[1]));
    result = Or(result, Or(in.bit[2], in.bit[3]));
    result = Or(result, Or(in.bit[4], in.bit[5]));
    result = Or(result, Or(in.bit[6], in.bit[7]));
    return result;
}

/*
sel1 | sel0 | out
0 | 0 | a
0 | 1 | b
1 | 0 | c
1 | 1 | d
>> ~sel1 * ~sel0 * a + ~sel1 * sel0 * b + sel1 * ~sel0 * c + sel1 * sel0 * d
>> ~sel1 * (~sel0 * a + sel0 * b) + sel1 * (~sel0 * c + sel0 * d)
*/
bit_t Mux4Way(bit_t a, bit_t b, bit_t c, bit_t d, bit2_t sel)
{
    return Mux(Mux(a, b, sel.bit[0]), Mux(c, d, sel.bit[0]), sel.bit[1]);
}

bit16_t Mux4Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit2_t sel)
{
    bit16_t result;
    result.bit[0] = Mux4Way(a.bit[0], b.bit[0], c.bit[0], d.bit[0], sel);
    result.bit[1] = Mux4Way(a.bit[1], b.bit[1], c.bit[1], d.bit[1], sel);
    result.bit[2] = Mux4Way(a.bit[2], b.bit[2], c.bit[2], d.bit[2], sel);
    result.bit[3] = Mux4Way(a.bit[3], b.bit[3], c.bit[3], d.bit[3], sel);
    result.bit[4] = Mux4Way(a.bit[4], b.bit[4], c.bit[4], d.bit[4], sel);
    result.bit[5] = Mux4Way(a.bit[5], b.bit[5], c.bit[5], d.bit[5], sel);
    result.bit[6] = Mux4Way(a.bit[6], b.bit[6], c.bit[6], d.bit[6], sel);
    result.bit[7] = Mux4Way(a.bit[7], b.bit[7], c.bit[7], d.bit[7], sel);
    result.bit[8] = Mux4Way(a.bit[8], b.bit[8], c.bit[8], d.bit[8], sel);
    result.bit[9] = Mux4Way(a.bit[9], b.bit[9], c.bit[9], d.bit[9], sel);
    result.bit[10] = Mux4Way(a.bit[10], b.bit[10], c.bit[10], d.bit[10], sel);
    result.bit[11] = Mux4Way(a.bit[11], b.bit[11], c.bit[11], d.bit[11], sel);
    result.bit[12] = Mux4Way(a.bit[12], b.bit[12], c.bit[12], d.bit[12], sel);
    result.bit[13] = Mux4Way(a.bit[13], b.bit[13], c.bit[13], d.bit[13], sel);
    result.bit[14] = Mux4Way(a.bit[14], b.bit[14], c.bit[14], d.bit[14], sel);
    result.bit[15] = Mux4Way(a.bit[15], b.bit[15], c.bit[15], d.bit[15], sel);

    return result;
}

/*
sel2 | sel1 | sel0 | out
0 | 0 | 0 | a
0 | 0 | 1 | b
0 | 1 | 0 | c
0 | 1 | 1 | d
1 | 0 | 0 | e
1 | 0 | 1 | f
1 | 1 | 0 | g
1 | 1 | 1 | h
>> ~sel2 * ~sel1 * ~sel0 * a + ~sel2 * ~sel1 * sel0 * b + ~sel2 * sel1 * ~sel0 * c + ~sel2 * sel1 * sel0 * d + sel2 * ~sel1 * ~sel0 * e + sel2 * ~sel1 * sel0 * f + sel2 * sel1 * ~sel0 * g + sel2 * sel1 * sel0 * h
>> ~sel2 * (~sel1 * (~sel0 * a + sel0 * b) + sel1 * (~sel0 * c + sel0 * d)) + sel2 * (~sel1 * (~sel0 * e + sel0 * f) + sel1 * (~sel0 * g + sel0 * h))
*/
bit_t Mux8Way(bit_t a, bit_t b, bit_t c, bit_t d, bit_t e, bit_t f, bit_t g, bit_t h, bit4_t sel)
{
    return Mux(Mux(Mux(a, b, sel.bit[0]), Mux(c, d, sel.bit[0]), sel.bit[1]),
               Mux(Mux(e, f, sel.bit[0]), Mux(g, h, sel.bit[0]), sel.bit[1]),
               sel.bit[2]);
}

bit16_t Mux8Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit16_t e, bit16_t f, bit16_t g, bit16_t h, bit4_t sel)
{
    bit16_t result;
    result.bit[0] = Mux8Way(a.bit[0], b.bit[0], c.bit[0], d.bit[0], e.bit[0], f.bit[0], g.bit[0], h.bit[0], sel);
    result.bit[1] = Mux8Way(a.bit[1], b.bit[1], c.bit[1], d.bit[1], e.bit[1], f.bit[1], g.bit[1], h.bit[1], sel);
    result.bit[2] = Mux8Way(a.bit[2], b.bit[2], c.bit[2], d.bit[2], e.bit[2], f.bit[2], g.bit[2], h.bit[2], sel);
    result.bit[3] = Mux8Way(a.bit[3], b.bit[3], c.bit[3], d.bit[3], e.bit[3], f.bit[3], g.bit[3], h.bit[3], sel);
    result.bit[4] = Mux8Way(a.bit[4], b.bit[4], c.bit[4], d.bit[4], e.bit[4], f.bit[4], g.bit[4], h.bit[4], sel);
    result.bit[5] = Mux8Way(a.bit[5], b.bit[5], c.bit[5], d.bit[5], e.bit[5], f.bit[5], g.bit[5], h.bit[5], sel);
    result.bit[6] = Mux8Way(a.bit[6], b.bit[6], c.bit[6], d.bit[6], e.bit[6], f.bit[6], g.bit[6], h.bit[6], sel);
    result.bit[7] = Mux8Way(a.bit[7], b.bit[7], c.bit[7], d.bit[7], e.bit[7], f.bit[7], g.bit[7], h.bit[7], sel);
    result.bit[8] = Mux8Way(a.bit[8], b.bit[8], c.bit[8], d.bit[8], e.bit[8], f.bit[8], g.bit[8], h.bit[8], sel);
    result.bit[9] = Mux8Way(a.bit[9], b.bit[9], c.bit[9], d.bit[9], e.bit[9], f.bit[9], g.bit[9], h.bit[9], sel);
    result.bit[10] = Mux8Way(a.bit[10], b.bit[10], c.bit[10], d.bit[10], e.bit[10], f.bit[10], g.bit[10], h.bit[10], sel);
    result.bit[11] = Mux8Way(a.bit[11], b.bit[11], c.bit[11], d.bit[11], e.bit[11], f.bit[11], g.bit[11], h.bit[11], sel);
    result.bit[12] = Mux8Way(a.bit[12], b.bit[12], c.bit[12], d.bit[12], e.bit[12], f.bit[12], g.bit[12], h.bit[12], sel);
    result.bit[13] = Mux8Way(a.bit[13], b.bit[13], c.bit[13], d.bit[13], e.bit[13], f.bit[13], g.bit[13], h.bit[13], sel);
    result.bit[14] = Mux8Way(a.bit[14], b.bit[14], c.bit[14], d.bit[14], e.bit[14], f.bit[14], g.bit[14], h.bit[14], sel);
    result.bit[15] = Mux8Way(a.bit[15], b.bit[15], c.bit[15], d.bit[15], e.bit[15], f.bit[15], g.bit[15], h.bit[15], sel);

    return result;
}

/*
in | sel1 | sel0 | out
0 | * | * | (0 0 0 0)
1 | 0 | 0 | (1 0 0 0)
1 | 0 | 1 | (0 1 0 0)
1 | 1 | 0 | (0 0 1 0)
1 | 1 | 1 | (1 1 0 0)
>> a : in * (~sel1 * ~sel0)
>> b : in * (~sel1 * sel0)
>> c : in * (sel1 * ~sel0)
>> d : in * (sel1 * sel0)
*/
std::tuple<bit_t, bit_t, bit_t, bit_t> DMux4Way(bit_t in, bit2_t sel)
{
    return std::make_tuple(And(And(in, Not(sel.bit[1])), Not(sel.bit[0])),
                           And(And(in, Not(sel.bit[1])), sel.bit[0]),
                           And(And(in, sel.bit[1]), Not(sel.bit[0])),
                           And(And(in, sel.bit[1]), sel.bit[0]));
}

std::tuple<bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t> DMux8Way(bit_t in, bit4_t sel)
{
    return std::make_tuple(And(And(And(in, Not(sel.bit[2])), Not(sel.bit[1])), Not(sel.bit[0])),
                           And(And(And(in, Not(sel.bit[2])), Not(sel.bit[1])), sel.bit[0]),
                            And(And(And(in, Not(sel.bit[2])), sel.bit[1]), Not(sel.bit[0])),
                            And(And(And(in, Not(sel.bit[2])), sel.bit[1]), sel.bit[0]),
                            And(And(And(in, sel.bit[2]), Not(sel.bit[1])), Not(sel.bit[0])),
                            And(And(And(in, sel.bit[2]), Not(sel.bit[1])), sel.bit[0]),
                            And(And(And(in, sel.bit[2]), sel.bit[1]), Not(sel.bit[0])),
                            And(And(And(in, sel.bit[2]), sel.bit[1]), sel.bit[0]));
}
