#ifndef __BIT_H__
#define __BIT_H__
#include <tuple>

struct bit_t {
    unsigned char bit : 1;

    bit_t();
    bit_t(int bit);

    bit_t operator=(int bit);
    bool operator==(bit_t other);
    bool operator==(int other);
};

template <unsigned int N>
struct bit_array_t {
    bit_t bit[N];
    bit_array_t<N>();
    bit_array_t<N>(unsigned int bits);

    void set(unsigned int idx);
    void clear(unsigned int idx);
    bool test(unsigned int idx);

    bit_array_t<N> operator=(unsigned int bits);
    bool operator==(bit_array_t<N> other);
    bool operator==(unsigned int other);
};

typedef bit_array_t<2> bit2_t;
typedef bit_array_t<4> bit4_t;
typedef bit_array_t<8> bit8_t;
typedef bit_array_t<16> bit16_t;
typedef bit_array_t<32> bit32_t;

extern const bit_t ZERO;
extern const bit_t ONE;

bit_t Nand(bit_t a, bit_t b);
bit_t Not(bit_t in);
bit_t And(bit_t a, bit_t b);
bit_t Or(bit_t a, bit_t b);
bit_t Xor(bit_t a, bit_t b);
bit_t Mux(bit_t a, bit_t b, bit_t sel);
std::tuple<bit_t, bit_t> DMux(bit_t in, bit_t sel);

bit16_t Not16(bit16_t in);
bit16_t And16(bit16_t a, bit16_t b);
bit16_t Or16(bit16_t a, bit16_t b);
bit16_t Mux16(bit16_t a, bit16_t b, bit_t sel);
bit_t Or8Way(bit8_t in);
bit16_t Mux4Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit2_t sel);
bit16_t Mux8Way16(bit16_t a, bit16_t b, bit16_t c, bit16_t d, bit16_t e, bit16_t f, bit16_t g, bit16_t h, bit4_t sel);
std::tuple<bit_t, bit_t, bit_t, bit_t> DMux4Way(bit_t in, bit2_t sel);
std::tuple<bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t, bit_t> DMux8Way(bit_t in, bit4_t sel);


#endif // __BIT_H__