#include "bit.h"
#include <iostream>
#include <fstream>

#define PASS_COLOR "\033[1;32m"
#define FAIL_COLOR "\033[1;31m"
#define RESET_COLOR "\033[0m"

std::ofstream ofs;

int tests_passed = 0;
int tests_run = 0;

bit_t zero(0);
bit_t one(1);

void initialize() {
    ofs.open("result.txt");
    std::cout << "The result of the test is also written to result.txt." << std::endl;
}

bool EXPECT_EQ(bool exp, const char* testname = "default testname") {
    tests_run++;
    if (exp) {
        std::cout << PASS_COLOR << "[PASSED] " << testname << RESET_COLOR << std::endl;
        ofs << "[PASSED] " << testname << std::endl;
        tests_passed++;
        return true;
    } else {
        std::cout << FAIL_COLOR << "[FAILED] " << testname << FAIL_COLOR << std::endl;
        ofs << "[FAILED] " << testname << std::endl;
        return false;
    }
}

void NotTest() {
    bool ok = true;

    ok &= (zero == Not(one));
    ok &= (one == Not(zero));

    EXPECT_EQ(ok, "NotTest");
}

void AndTest() {
    bool ok = true;

    ok &= (zero == And(zero, zero));
    ok &= (zero == And(zero, one));
    ok &= (zero == And(one, zero));
    ok &= (one == And(one, one));

    EXPECT_EQ(ok, "AndTest");
}

void OrTest() {
    bool ok = true;

    ok &= (zero == Or(zero, zero));
    ok &= (one == Or(zero, one));
    ok &= (one == Or(one, zero));
    ok &= (one == Or(one, one));

    EXPECT_EQ(ok, "OrTest");
}

void XorTest() {
    bool ok = true;

    ok &= (zero == Xor(zero, zero));
    ok &= (one == Xor(zero, one));
    ok &= (one == Xor(one, zero));
    ok &= (zero == Xor(one, one));

    EXPECT_EQ(ok, "XorTest");
}

void MuxTest() {
    bool ok = true;

    ok &= (zero == Mux(zero, zero, zero));
    ok &= (zero == Mux(zero, zero, one));
    ok &= (zero == Mux(zero, one, zero));
    ok &= (one == Mux(zero, one, one));
    ok &= (one == Mux(one, zero, zero));
    ok &= (zero == Mux(one, zero, one));
    ok &= (one == Mux(one, one, zero));
    ok &= (one == Mux(one, one, one));

    EXPECT_EQ(ok, "MuxTest");
}

void DMuxTest() {
    bool ok = true;

    std::tuple<bit_t, bit_t> res;

    res = DMux(zero, zero);
    ok &= (zero == std::get<0>(res) && zero == std::get<1>(res));
    res = DMux(zero, one);
    ok &= (zero == std::get<0>(res) && zero == std::get<1>(res));
    res = DMux(one, zero);
    ok &= (one == std::get<0>(res) && zero == std::get<1>(res));
    res = DMux(one, one);
    ok &= (zero == std::get<0>(res) && one == std::get<1>(res));

    EXPECT_EQ(ok, "DMuxTest");
}

void Not16Test() {
    bool ok = true;

    ok &= (Not16(0x0000) == 0xffff);
    ok &= (Not16(0xffff) == 0x0000);
    ok &= (Not16(0xaaaa) == 0x5555);
    ok &= (Not16(0x5555) == 0xaaaa);
    ok &= (Not16(0xf0f0) == 0x0f0f);
    ok &= (Not16(0x0f0f) == 0xf0f0);
    ok &= (Not16(0x3333) == 0xcccc);
    ok &= (Not16(0xcccc) == 0x3333);

    EXPECT_EQ(ok, "Not16Test");
}

void And16Test() {
    bool ok = true;

    ok &= (And16(0x0000, 0x0000) == 0x0000);
    ok &= (And16(0x0000, 0xffff) == 0x0000);
    ok &= (And16(0xffff, 0x0000) == 0x0000);
    ok &= (And16(0xffff, 0xffff) == 0xffff);
    ok &= (And16(0xaaaa, 0x5555) == 0x0000);
    ok &= (And16(0x5555, 0xaaaa) == 0x0000);
    ok &= (And16(0xf0f0, 0x0f0f) == 0x0000);
    ok &= (And16(0x0f0f, 0xf0f0) == 0x0000);
    ok &= (And16(0x3333, 0xcccc) == 0x0000);
    ok &= (And16(0xcccc, 0x3333) == 0x0000);
    ok &= (And16(0xafaf, 0x5555) == 0x0505);
    ok &= (And16(0x5555, 0xafaf) == 0x0505);
    ok &= (And16(0x3f3f, 0xcccc) == 0x0c0c);
    ok &= (And16(0xcccc, 0x3f3f) == 0x0c0c);
    ok &= (And16(0x3acf, 0x5555) == 0x1045);
    ok &= (And16(0x5555, 0x3acf) == 0x1045);
    ok &= (And16(0xabcd, 0xdcba) == 0x8888);
    ok &= (And16(0xdcba, 0xabcd) == 0x8888);

    EXPECT_EQ(ok, "And16Test");
}

void Or16Test() {
    bool ok = true;

    ok &= (Or16(0x0000, 0x0000) == 0x0000);
    ok &= (Or16(0x0000, 0xffff) == 0xffff);
    ok &= (Or16(0xffff, 0x0000) == 0xffff);
    ok &= (Or16(0xffff, 0xffff) == 0xffff);
    ok &= (Or16(0xaaaa, 0x5555) == 0xffff);
    ok &= (Or16(0x5555, 0xaaaa) == 0xffff);
    ok &= (Or16(0xf0f0, 0x0f0f) == 0xffff);
    ok &= (Or16(0x0f0f, 0xf0f0) == 0xffff);
    ok &= (Or16(0x3333, 0xcccc) == 0xffff);
    ok &= (Or16(0xcccc, 0x3333) == 0xffff);
    ok &= (Or16(0xafaf, 0x5555) == 0xffff);
    ok &= (Or16(0x5555, 0xafaf) == 0xffff);
    ok &= (Or16(0x3f3f, 0xcccc) == 0xffff);
    ok &= (Or16(0xcccc, 0x3f3f) == 0xffff);
    ok &= (Or16(0x3acf, 0x5555) == 0x7fdf);
    ok &= (Or16(0x5555, 0x3acf) == 0x7fdf);
    ok &= (Or16(0x1234, 0xabcd) == 0xbbfd);
    ok &= (Or16(0xabcd, 0x1234) == 0xbbfd);
    ok &= (Or16(0x1256, 0xa481) == 0xb6d7);
    ok &= (Or16(0xa481, 0x1256) == 0xb6d7);

    EXPECT_EQ(ok, "Or16Test");
}

void Mux16Test() {
    bool ok = true;

    ok &= (Mux16(0x0000, 0xffff, 0) == 0x0000);
    ok &= (Mux16(0x0000, 0xffff, 1) == 0xffff);
    ok &= (Mux16(0xffff, 0x0000, 0) == 0xffff);
    ok &= (Mux16(0xffff, 0x0000, 1) == 0x0000);
    ok &= (Mux16(0xaaaa, 0x5555, 0) == 0xaaaa);
    ok &= (Mux16(0xaaaa, 0x5555, 1) == 0x5555);
    ok &= (Mux16(0xf0f0, 0x0f0f, 0) == 0xf0f0);
    ok &= (Mux16(0xf0f0, 0x0f0f, 1) == 0x0f0f);
    ok &= (Mux16(0x3333, 0xcccc, 0) == 0x3333);
    ok &= (Mux16(0x3333, 0xcccc, 1) == 0xcccc);
    ok &= (Mux16(0xafaf, 0x5555, 0) == 0xafaf);
    ok &= (Mux16(0xafaf, 0x5555, 1) == 0x5555);

    EXPECT_EQ(ok, "Mux16Test");
}

void Or8WayTest() {
    bool ok = true;

    ok &= (Or8Way(0x00) == 0);
    ok &= (Or8Way(0xff) == 1);
    ok &= (Or8Way(0xaa) == 1);
    ok &= (Or8Way(0x55) == 1);
    ok &= (Or8Way(0x0f) == 1);
    ok &= (Or8Way(0xf0) == 1);
    ok &= (Or8Way(0xcc) == 1);
    ok &= (Or8Way(0x33) == 1);
    ok &= (Or8Way(0x01) == 1);
    ok &= (Or8Way(0x10) == 1);

    EXPECT_EQ(ok, "Or8WayTest");
}

void Mux4Way16Test() {
    bool ok = true;

    ok &= (Mux4Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0b00) == 0x0000);
    ok &= (Mux4Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0b01) == 0x3333);
    ok &= (Mux4Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0b10) == 0xcccc);
    ok &= (Mux4Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0b11) == 0xffff);
    ok &= (Mux4Way16(0x0303, 0x3c3c, 0xcfcf, 0xf0f0, 0b00) == 0x0303);
    ok &= (Mux4Way16(0x0303, 0x3c3c, 0xcfcf, 0xf0f0, 0b01) == 0x3c3c);
    ok &= (Mux4Way16(0x0303, 0x3c3c, 0xcfcf, 0xf0f0, 0b10) == 0xcfcf);
    ok &= (Mux4Way16(0x0303, 0x3c3c, 0xcfcf, 0xf0f0, 0b11) == 0xf0f0);

    EXPECT_EQ(ok, "Mux4Way16Test");
}

void Mux8Way16Test(){
    bool ok = true;

    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x0) == 0x0000);
    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x1) == 0x3333);
    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x2) == 0xcccc);
    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x3) == 0xffff);
    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x4) == 0xaaaa);
    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x5) == 0x5555);
    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x6) == 0x0f0f);
    ok &= (Mux8Way16(0x0000, 0x3333, 0xcccc, 0xffff, 0xaaaa, 0x5555, 0x0f0f, 0xf0f0, 0x7) == 0xf0f0);

    EXPECT_EQ(ok, "Mux8Way16Test");
}

void DMux4WayTest(){
    bool ok = true;

    auto res = DMux4Way(0xabcd, 0b00);
    ok &= (std::get<0>(res) == 0xabcd);
    ok &= (std::get<1>(res) == 0x0000);
    ok &= (std::get<2>(res) == 0x0000);
    ok &= (std::get<3>(res) == 0x0000);

    res = DMux4Way(0xabcd, 0b01);
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == 0xabcd);
    ok &= (std::get<2>(res) == 0x0000);
    ok &= (std::get<3>(res) == 0x0000);

    res = DMux4Way(0xabcd, 0b10);
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == 0x0000);
    ok &= (std::get<2>(res) == 0xabcd);
    ok &= (std::get<3>(res) == 0x0000);

    res = DMux4Way(0xabcd, 0b11);
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == 0x0000);
    ok &= (std::get<2>(res) == 0x0000);
    ok &= (std::get<3>(res) == 0xabcd);

    EXPECT_EQ(ok, "DMux4WayTest");
}

void DMux8WayTest(){
    bool ok = true;

    auto res = DMux8Way(0xabcd, 0x0);
    ok &= (std::get<0>(res) == 0xabcd);
    ok &= (std::get<1>(res) == 0x0000);
    ok &= (std::get<2>(res) == 0x0000);
    ok &= (std::get<3>(res) == 0x0000);
    ok &= (std::get<4>(res) == 0x0000);
    ok &= (std::get<5>(res) == 0x0000);
    ok &= (std::get<6>(res) == 0x0000);
    ok &= (std::get<7>(res) == 0x0000);

    res = DMux8Way(0xabcd, 0x5);
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == 0x0000);
    ok &= (std::get<2>(res) == 0x0000);
    ok &= (std::get<3>(res) == 0x0000);
    ok &= (std::get<4>(res) == 0x0000);
    ok &= (std::get<5>(res) == 0xabcd);
    ok &= (std::get<6>(res) == 0x0000);
    ok &= (std::get<7>(res) == 0x0000);

    res = DMux8Way(0xabcd, 0x7);
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == 0x0000);
    ok &= (std::get<2>(res) == 0x0000);
    ok &= (std::get<3>(res) == 0x0000);
    ok &= (std::get<4>(res) == 0x0000);
    ok &= (std::get<5>(res) == 0x0000);
    ok &= (std::get<6>(res) == 0x0000);
    ok &= (std::get<7>(res) == 0xabcd);

    EXPECT_EQ(ok, "DMux8WayTest");
}

void print_scores(){
    std::cout << "[RESULT] Tests passed: " << tests_passed << " / " << tests_run << std::endl;
    ofs << "[RESULT] Tests passed: " << tests_passed << " / " << tests_run << std::endl;
}

int main(int argc, char const* argv[])
{
    initialize();

    NotTest();
    AndTest();
    OrTest();
    XorTest();
    MuxTest();
    DMuxTest();
    Not16Test();
    And16Test();
    Or16Test();
    Mux16Test();
    Or8WayTest();
    Mux4Way16Test();
    Mux8Way16Test();
    DMux4WayTest();
    DMux8WayTest();

    print_scores();
    return 0;
}
