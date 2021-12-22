#include "arithmatic.h"
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
        std::cout << FAIL_COLOR << "[FAILED] " << testname << RESET_COLOR << std::endl;
        ofs << "[FAILED] " << testname << std::endl;
        return false;
    }
}

void HalfAdderTest() {
    bool ok = true;
    std::tuple<bit_t, bit_t> res;
    res = HalfAdder(zero, zero);
    ok &= (std::get<0>(res) == zero);
    ok &= (std::get<1>(res) == zero);
    res = HalfAdder(zero, one);
    ok &= (std::get<0>(res) == one);
    ok &= (std::get<1>(res) == zero);
    res = HalfAdder(one, zero);
    ok &= (std::get<0>(res) == one);
    ok &= (std::get<1>(res) == zero);
    res = HalfAdder(one, one);
    ok &= (std::get<0>(res) == zero);
    ok &= (std::get<1>(res) == one);
    EXPECT_EQ(ok, "HalfAdderTest");
}

void FullAdderTest() {
    bool ok = true;
    std::tuple<bit_t, bit_t> res;
    res = FullAdder(zero, zero, zero);
    ok &= (std::get<0>(res) == zero);
    ok &= (std::get<1>(res) == zero);
    res = FullAdder(zero, zero, one);
    ok &= (std::get<0>(res) == one);
    ok &= (std::get<1>(res) == zero);
    res = FullAdder(zero, one, zero);
    ok &= (std::get<0>(res) == one);
    ok &= (std::get<1>(res) == zero);
    res = FullAdder(zero, one, one);
    ok &= (std::get<0>(res) == zero);
    ok &= (std::get<1>(res) == one);
    res = FullAdder(one, zero, zero);
    ok &= (std::get<0>(res) == one);
    ok &= (std::get<1>(res) == zero);
    res = FullAdder(one, zero, one);
    ok &= (std::get<0>(res) == zero);
    ok &= (std::get<1>(res) == one);
    res = FullAdder(one, one, zero);
    ok &= (std::get<0>(res) == zero);
    ok &= (std::get<1>(res) == one);
    res = FullAdder(one, one, one);
    ok &= (std::get<0>(res) == one);
    ok &= (std::get<1>(res) == one);
    EXPECT_EQ(ok, "FullAdderTest");
}

void Add16Test() {
    bool ok = true;
    ok &= (Add16(0x0000, 0xffff) == 0x0000 + 0xffff);
    ok &= (Add16(0xffff, 0x0000) == 0xffff + 0x0000);
    ok &= (Add16(0x0000, 0x0001) == 0x0000 + 0x0001);
    ok &= (Add16(0x0001, 0x0000) == 0x0001 + 0x0000);
    ok &= (Add16(0x1234, 0x5678) == 0x1234 + 0x5678);
    ok &= (Add16(0x9abc, 0x0def) == 0x9abc + 0x0def);
    ok &= (Add16(0xffff, 0x0001) == 0x0000);
    ok &= (Add16(0x1234, 0xffff) == 0x1233);
    ok &= (Add16(0xfabc, 0xbcd8) == 0xb794);
    EXPECT_EQ(ok, "Add16Test");
}

void Inc16Test() {
    bool ok = true;
    ok &= (Inc16(0x0000) == 0x0001);
    ok &= (Inc16(0xffff) == 0x0000);
    ok &= (Inc16(0x0001) == 0x0002);
    ok &= (Inc16(0x1234) == 0x1235);
    ok &= (Inc16(0x9abc) == 0x9abd);
    EXPECT_EQ(ok, "Inc16Test");
}

void ALUTestSimple() {
    bool ok = true;

    bit16_t x = 0x0000;
    bit16_t y = 0xffff;

    std::tuple<bit16_t, bit_t, bit_t> res;
    res = ALU(x, y, 1, 0, 1, 0, 1, 0); // 0
    ok &= (std::get<0>(res) == 0x0000);

    res = ALU(x, y, 1, 1, 1, 1, 1, 1); // 1
    ok &= (std::get<0>(res) == 0x0001);

    res = ALU(x, y, 1, 1, 1, 0, 1, 0); // -1
    ok &= (std::get<0>(res) == 0xffff);

    res = ALU(x, y, 0, 0, 1, 1, 0, 0); // x
    ok &= (std::get<0>(res) == 0x0000);

    res = ALU(x, y, 1, 1, 0, 0, 0, 0); // y
    ok &= (std::get<0>(res) == 0xffff);

    res = ALU(x, y, 0, 0, 1, 1, 0, 1); // !x
    ok &= (std::get<0>(res) == 0xffff);

    res = ALU(x, y, 1, 1, 0, 0, 0, 1); // !y
    ok &= (std::get<0>(res) == 0x0000);

    res = ALU(x, y, 0, 0, 1, 1, 1, 1); // -x
    ok &= (std::get<0>(res) == 0x0000);

    res = ALU(x, y, 1, 1, 0, 0, 1, 1); // -y
    ok &= (std::get<0>(res) == 0x0001);

    res = ALU(x, y, 0, 1, 1, 1, 1, 1); // x+1
    ok &= (std::get<0>(res) == 0x0001);

    res = ALU(x, y, 1, 1, 0, 1, 1, 1); // y+1
    ok &= (std::get<0>(res) == 0x0000);

    res = ALU(x, y, 0, 0, 1, 1, 1, 0); // x-1
    ok &= (std::get<0>(res) == 0xffff);

    res = ALU(x, y, 1, 1, 0, 0, 1, 0); // y-1
    ok &= (std::get<0>(res) == 0xfffe);

    res = ALU(x, y, 0, 0, 0, 0, 1, 0); // x+y
    ok &= (std::get<0>(res) == 0xffff);

    res = ALU(x, y, 0, 1, 0, 0, 1, 1); // x-y
    ok &= (std::get<0>(res) == 0x0001);

    res = ALU(x, y, 0, 0, 0, 1, 1, 1); // y-x
    ok &= (std::get<0>(res) == 0xffff);

    res = ALU(x, y, 0, 0, 0, 0, 0, 0); // x&y
    ok &= (std::get<0>(res) == 0x0000);

    res = ALU(x, y, 0, 1, 0, 1, 0, 1); // x|y
    ok &= (std::get<0>(res) == 0xffff);

    x = 0xf111, y = 0x137f;

    res = ALU(x, y, 1, 0, 1, 0, 1, 0); // 0
    ok &= (std::get<0>(res) == 0x0000);

    res = ALU(x, y, 1, 1, 1, 1, 1, 1); // 1
    ok &= (std::get<0>(res) == 0x0001);

    res = ALU(x, y, 1, 1, 1, 0, 1, 0); // -1
    ok &= (std::get<0>(res) == 0xffff);

    res = ALU(x, y, 0, 0, 1, 1, 0, 0); // x
    ok &= (std::get<0>(res) == 0xf111);

    res = ALU(x, y, 1, 1, 0, 0, 0, 0); // y
    ok &= (std::get<0>(res) == 0x137f);

    res = ALU(x, y, 0, 0, 1, 1, 0, 1); // !x
    ok &= (std::get<0>(res) == 0x0eee);

    res = ALU(x, y, 1, 1, 0, 0, 0, 1); // !y
    ok &= (std::get<0>(res) == 0xec80);

    res = ALU(x, y, 0, 0, 1, 1, 1, 1); // -x
    ok &= (std::get<0>(res) == 0x0eef);

    res = ALU(x, y, 1, 1, 0, 0, 1, 1); // -y
    ok &= (std::get<0>(res) == 0xec81);

    res = ALU(x, y, 0, 1, 1, 1, 1, 1); // x+1
    ok &= (std::get<0>(res) == 0xf112);

    res = ALU(x, y, 1, 1, 0, 1, 1, 1); // y+1
    ok &= (std::get<0>(res) == 0x1380);

    res = ALU(x, y, 0, 0, 1, 1, 1, 0); // x-1
    ok &= (std::get<0>(res) == 0xf110);

    res = ALU(x, y, 1, 1, 0, 0, 1, 0); // y-1
    ok &= (std::get<0>(res) == 0x137e);

    res = ALU(x, y, 0, 0, 0, 0, 1, 0); // x+y
    ok &= (std::get<0>(res) == 0x0490);

    res = ALU(x, y, 0, 1, 0, 0, 1, 1); // x-y
    ok &= (std::get<0>(res) == 0xdd92);

    res = ALU(x, y, 0, 0, 0, 1, 1, 1); // y-x
    ok &= (std::get<0>(res) == 0x226e);

    res = ALU(x, y, 0, 0, 0, 0, 0, 0); // x&y
    ok &= (std::get<0>(res) == 0x1111);

    res = ALU(x, y, 0, 1, 0, 1, 0, 1); // x|y
    ok &= (std::get<0>(res) == 0xf37f);

    EXPECT_EQ(ok, "ALUTestSimple");
}

void ALUTestStats() {
    bool ok = true;

    bit16_t x = 0x0000;
    bit16_t y = 0xffff;

    std::tuple<bit16_t, bit_t, bit_t> res;
    res = ALU(x, y, 1, 0, 1, 0, 1, 0); // 0
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == one);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 1, 1, 1, 1); // 1
    ok &= (std::get<0>(res) == 0x0001);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 1, 0, 1, 0); // -1
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 0, 1, 1, 0, 0); // x
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == one);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 0, 0, 0, 0); // y
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 0, 1, 1, 0, 1); // !x
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 1, 1, 0, 0, 0, 1); // !y
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == one);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 0, 1, 1, 1, 1); // -x
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == one);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 0, 0, 1, 1); // -y
    ok &= (std::get<0>(res) == 0x0001);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 1, 1, 1, 1, 1); // x+1
    ok &= (std::get<0>(res) == 0x0001);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 0, 1, 1, 1); // y+1
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == one);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 0, 1, 1, 1, 0); // x-1
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 1, 1, 0, 0, 1, 0); // y-1
    ok &= (std::get<0>(res) == 0xfffe);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 0, 0, 0, 1, 0); // x+y
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 1, 0, 0, 1, 1); // x-y
    ok &= (std::get<0>(res) == 0x0001);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 0, 0, 1, 1, 1); // y-x
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 0, 0, 0, 0, 0); // x&y
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == one);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 1, 0, 1, 0, 1); // x|y
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    x = 0xf111, y = 0x137f;

    res = ALU(x, y, 1, 0, 1, 0, 1, 0); // 0
    ok &= (std::get<0>(res) == 0x0000);
    ok &= (std::get<1>(res) == one);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 1, 1, 1, 1); // 1
    ok &= (std::get<0>(res) == 0x0001);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 1, 0, 1, 0); // -1
    ok &= (std::get<0>(res) == 0xffff);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 0, 1, 1, 0, 0); // x
    ok &= (std::get<0>(res) == 0xf111);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 1, 1, 0, 0, 0, 0); // y
    ok &= (std::get<0>(res) == 0x137f);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 0, 1, 1, 0, 1); // !x
    ok &= (std::get<0>(res) == 0x0eee);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 0, 0, 0, 1); // !y
    ok &= (std::get<0>(res) == 0xec80);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 0, 1, 1, 1, 1); // -x
    ok &= (std::get<0>(res) == 0x0eef);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 1, 1, 0, 0, 1, 1); // -y
    ok &= (std::get<0>(res) == 0xec81);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 1, 1, 1, 1, 1); // x+1
    ok &= (std::get<0>(res) == 0xf112);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 1, 1, 0, 1, 1, 1); // y+1
    ok &= (std::get<0>(res) == 0x1380);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 0, 1, 1, 1, 0); // x-1
    ok &= (std::get<0>(res) == 0xf110);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 1, 1, 0, 0, 1, 0); // y-1
    ok &= (std::get<0>(res) == 0x137e);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 0, 0, 0, 1, 0); // x+y
    ok &= (std::get<0>(res) == 0x0490);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 1, 0, 0, 1, 1); // x-y
    ok &= (std::get<0>(res) == 0xdd92);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    res = ALU(x, y, 0, 0, 0, 1, 1, 1); // y-x
    ok &= (std::get<0>(res) == 0x226e);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 0, 0, 0, 0, 0); // x&y
    ok &= (std::get<0>(res) == 0x1111);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == zero);

    res = ALU(x, y, 0, 1, 0, 1, 0, 1); // x|y
    ok &= (std::get<0>(res) == 0xf37f);
    ok &= (std::get<1>(res) == zero);
    ok &= (std::get<2>(res) == one);

    EXPECT_EQ(ok, "ALUTestStats");
}

void print_scores() {
    std::cout << "[RESULT] Tests passed: " << tests_passed << " / " << tests_run << std::endl;
    ofs << "[RESULT] Tests passed: " << tests_passed << " / " << tests_run << std::endl;
}

int main(int argc, char const* argv[])
{
    initialize();

    HalfAdderTest();
    FullAdderTest();
    Add16Test();
    Inc16Test();
    ALUTestSimple();
    ALUTestStats();

    print_scores();
    return 0;
}
