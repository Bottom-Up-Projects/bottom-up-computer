#include "sequential.h"
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

void BitTest(){
    bool ok = true;

    DFF_t **dffs = new DFF_t*[1];
    for(int i = 0; i < 1; i++){
        dffs[i] = new DFF_t();
    }

    ok &= (Bit(0, 0, dffs) == 0);
    ok &= (Bit(0, 1, dffs) == 0);
    ok &= (Bit(1, 0, dffs) == 0);
    ok &= (Bit(1, 1, dffs) == 0);
    ok &= (Bit(0, 0, dffs) == 1);
    ok &= (Bit(0, 1, dffs) == 1);
    ok &= (Bit(1, 0, dffs) == 0);
    ok &= (Bit(1, 1, dffs) == 0);
    ok &= (Bit(1, 0, dffs) == 1);
    ok &= (Bit(0, 1, dffs) == 1);
    ok &= (Bit(1, 1, dffs) == 0);

    delete[] dffs;

    EXPECT_EQ(ok, "BitTest");
}

void RegisterTest() {
    bool ok = true;

    DFF_t **dffs = new DFF_t*[16];
    for(int i = 0; i < 16; i++){
        dffs[i] = new DFF_t();
    }

    ok &= (Register(0x0000, 0, dffs) == 0x0000);
    ok &= (Register(0x0000, 1, dffs) == 0x0000);
    ok &= (Register(0xffff, 0, dffs) == 0x0000);
    ok &= (Register(0xffff, 1, dffs) == 0x0000);
    ok &= (Register(0x0000, 0, dffs) == 0xffff);
    ok &= (Register(0xabcd, 1, dffs) == 0xffff);
    ok &= (Register(0x1234, 0, dffs) == 0xabcd);
    ok &= (Register(0x1234, 1, dffs) == 0xabcd);
    ok &= (Register(0xffff, 0, dffs) == 0x1234);
    ok &= (Register(0xffff, 1, dffs) == 0x1234);
    ok &= (Register(0x0000, 1, dffs) == 0xffff);
    ok &= (Register(0xabcd, 0, dffs) == 0x0000);

    delete[] dffs;

    EXPECT_EQ(ok, "RegisterTest");
}

void RAM8Test() {
    bool ok = true;

    DFF_t **dffs = new DFF_t*[128];
    for(int i = 0; i < 128; i++){
        dffs[i] = new DFF_t();
    }

    ok &= (RAM8(0x1234, 1, 0b000, dffs) == 0x0000);
    ok &= (RAM8(0x5678, 1, 0b001, dffs) == 0x0000);
    ok &= (RAM8(0x9abc, 1, 0b010, dffs) == 0x0000);
    ok &= (RAM8(0xdef0, 1, 0b011, dffs) == 0x0000);
    ok &= (RAM8(0xaaaa, 1, 0b100, dffs) == 0x0000);
    ok &= (RAM8(0x5555, 1, 0b101, dffs) == 0x0000);
    ok &= (RAM8(0xffff, 1, 0b110, dffs) == 0x0000);
    ok &= (RAM8(0x0000, 1, 0b111, dffs) == 0x0000);

    ok &= (RAM8(0x5678, 1, 0b000, dffs) == 0x1234);
    ok &= (RAM8(0x9abc, 1, 0b001, dffs) == 0x5678);
    ok &= (RAM8(0xdef0, 1, 0b010, dffs) == 0x9abc);
    ok &= (RAM8(0xaaaa, 1, 0b011, dffs) == 0xdef0);
    ok &= (RAM8(0x5555, 1, 0b100, dffs) == 0xaaaa);
    ok &= (RAM8(0xffff, 1, 0b101, dffs) == 0x5555);
    ok &= (RAM8(0x0000, 1, 0b110, dffs) == 0xffff);
    ok &= (RAM8(0x1234, 1, 0b111, dffs) == 0x0000);

    ok &= (RAM8(0x9abc, 0, 0b000, dffs) == 0x5678);
    ok &= (RAM8(0xdef0, 0, 0b001, dffs) == 0x9abc);
    ok &= (RAM8(0xaaaa, 0, 0b010, dffs) == 0xdef0);
    ok &= (RAM8(0x5555, 0, 0b011, dffs) == 0xaaaa);
    ok &= (RAM8(0xffff, 0, 0b100, dffs) == 0x5555);
    ok &= (RAM8(0x0000, 0, 0b101, dffs) == 0xffff);
    ok &= (RAM8(0x1234, 0, 0b110, dffs) == 0x0000);
    ok &= (RAM8(0x5678, 0, 0b111, dffs) == 0x1234);

    ok &= (RAM8(0xdef0, 0, 0b000, dffs) == 0x5678);
    ok &= (RAM8(0xaaaa, 0, 0b001, dffs) == 0x9abc);
    ok &= (RAM8(0x5555, 0, 0b010, dffs) == 0xdef0);
    ok &= (RAM8(0xffff, 0, 0b011, dffs) == 0xaaaa);
    ok &= (RAM8(0x0000, 0, 0b100, dffs) == 0x5555);
    ok &= (RAM8(0x1234, 0, 0b101, dffs) == 0xffff);
    ok &= (RAM8(0x5678, 0, 0b110, dffs) == 0x0000);
    ok &= (RAM8(0x9abc, 0, 0b111, dffs) == 0x1234);

    delete[] dffs;
    EXPECT_EQ(ok, "RAM8Test");
}

void RAM64Test() {
    bool ok = true;

    DFF_t **dffs = new DFF_t*[1024];
    for(int i = 0; i < 1024; i++){
        dffs[i] = new DFF_t();
    }
    
    ok &= (RAM64(0x1234, 1, 0x03, dffs) == 0x0000);
    ok &= (RAM64(0x5678, 1, 0x04, dffs) == 0x0000);
    ok &= (RAM64(0x9abc, 1, 0x11, dffs) == 0x0000);
    ok &= (RAM64(0xdef0, 1, 0x18, dffs) == 0x0000);
    ok &= (RAM64(0xaaaa, 1, 0x2f, dffs) == 0x0000);
    ok &= (RAM64(0x5555, 1, 0x3e, dffs) == 0x0000);
    ok &= (RAM64(0xffff, 1, 0x3f, dffs) == 0x0000);

    ok &= (RAM64(0x5678, 1, 0x03, dffs) == 0x1234);
    ok &= (RAM64(0x9abc, 1, 0x04, dffs) == 0x5678);
    ok &= (RAM64(0xdef0, 1, 0x11, dffs) == 0x9abc);
    ok &= (RAM64(0xaaaa, 1, 0x18, dffs) == 0xdef0);
    ok &= (RAM64(0x5555, 1, 0x2f, dffs) == 0xaaaa);
    ok &= (RAM64(0xffff, 1, 0x3e, dffs) == 0x5555);
    ok &= (RAM64(0x0000, 1, 0x3f, dffs) == 0xffff);
    ok &= (RAM64(0x1234, 1, 0x00, dffs) == 0x0000);

    ok &= (RAM64(0x9abc, 0, 0x03, dffs) == 0x5678);
    ok &= (RAM64(0xdef0, 0, 0x04, dffs) == 0x9abc);
    ok &= (RAM64(0xaaaa, 0, 0x11, dffs) == 0xdef0);
    ok &= (RAM64(0x5555, 0, 0x18, dffs) == 0xaaaa);
    ok &= (RAM64(0xffff, 0, 0x2f, dffs) == 0x5555);
    ok &= (RAM64(0x0000, 0, 0x3e, dffs) == 0xffff);
    ok &= (RAM64(0x1234, 0, 0x3f, dffs) == 0x0000);
    ok &= (RAM64(0x5678, 0, 0x00, dffs) == 0x1234);

    ok &= (RAM64(0xdef0, 0, 0x03, dffs) == 0x5678);
    ok &= (RAM64(0xaaaa, 0, 0x04, dffs) == 0x9abc);
    ok &= (RAM64(0x5555, 0, 0x11, dffs) == 0xdef0);
    ok &= (RAM64(0xffff, 0, 0x18, dffs) == 0xaaaa);
    ok &= (RAM64(0x0000, 0, 0x2f, dffs) == 0x5555);
    ok &= (RAM64(0x1234, 0, 0x3e, dffs) == 0xffff);
    ok &= (RAM64(0x5678, 0, 0x3f, dffs) == 0x0000);
    ok &= (RAM64(0x9abc, 0, 0x00, dffs) == 0x1234);

    ok &= (RAM64(0xffff, 0, 0x01, dffs) == 0x0000);
    ok &= (RAM64(0x0000, 0, 0x02, dffs) == 0x0000);
    ok &= (RAM64(0x1234, 0, 0x05, dffs) == 0x0000);
    ok &= (RAM64(0x5678, 0, 0x06, dffs) == 0x0000);
    ok &= (RAM64(0x9abc, 0, 0x19, dffs) == 0x0000);
    ok &= (RAM64(0xdef0, 0, 0x1a, dffs) == 0x0000);
    ok &= (RAM64(0xaaaa, 0, 0x3d, dffs) == 0x0000);

    delete[] dffs;
    EXPECT_EQ(ok, "RAM64Test");
}

void RAM512Test() {
    bool ok = true;

    DFF_t **dffs = new DFF_t*[8192];
    for(int i = 0; i < 8192; i++){
        dffs[i] = new DFF_t();
    }

    ok &= (RAM512(0x1234, 1, 0x001, dffs) == 0x0000);
    ok &= (RAM512(0x5678, 1, 0x00f, dffs) == 0x0000);
    ok &= (RAM512(0x9abc, 1, 0x01f, dffs) == 0x0000);
    ok &= (RAM512(0xdef0, 1, 0x03f, dffs) == 0x0000);
    ok &= (RAM512(0xaaaa, 1, 0x07f, dffs) == 0x0000);
    ok &= (RAM512(0x5555, 1, 0x0ff, dffs) == 0x0000);
    ok &= (RAM512(0xffff, 1, 0x1ab, dffs) == 0x0000);

    ok &= (RAM512(0x5678, 1, 0x001, dffs) == 0x1234);
    ok &= (RAM512(0x9abc, 1, 0x00f, dffs) == 0x5678);
    ok &= (RAM512(0xdef0, 1, 0x01f, dffs) == 0x9abc);
    ok &= (RAM512(0xaaaa, 1, 0x03f, dffs) == 0xdef0);
    ok &= (RAM512(0x5555, 1, 0x07f, dffs) == 0xaaaa);
    ok &= (RAM512(0xffff, 1, 0x0ff, dffs) == 0x5555);
    ok &= (RAM512(0x0000, 1, 0x1ab, dffs) == 0xffff);

    ok &= (RAM512(0x9abc, 0, 0x001, dffs) == 0x5678);
    ok &= (RAM512(0xdef0, 0, 0x00f, dffs) == 0x9abc);
    ok &= (RAM512(0xaaaa, 0, 0x01f, dffs) == 0xdef0);
    ok &= (RAM512(0x5555, 0, 0x03f, dffs) == 0xaaaa);
    ok &= (RAM512(0xffff, 0, 0x07f, dffs) == 0x5555);
    ok &= (RAM512(0x0000, 0, 0x0ff, dffs) == 0xffff);
    ok &= (RAM512(0x1234, 0, 0x1ab, dffs) == 0x0000);

    ok &= (RAM512(0xdef0, 0, 0x001, dffs) == 0x5678);
    ok &= (RAM512(0xaaaa, 0, 0x00f, dffs) == 0x9abc);
    ok &= (RAM512(0x5555, 0, 0x01f, dffs) == 0xdef0);
    ok &= (RAM512(0xffff, 0, 0x03f, dffs) == 0xaaaa);
    ok &= (RAM512(0x0000, 0, 0x07f, dffs) == 0x5555);
    ok &= (RAM512(0x1234, 0, 0x0ff, dffs) == 0xffff);
    ok &= (RAM512(0x5678, 0, 0x1ab, dffs) == 0x0000);

    delete[] dffs;
    EXPECT_EQ(ok, "RAM512Test");
}

void RAM4KTest() {
    bool ok = true;

    DFF_t **dffs = new DFF_t*[65536];
    for(int i = 0; i < 65536; i++){
        dffs[i] = new DFF_t();
    }

    ok &= (RAM4K(0x1234, 1, 0x001, dffs) == 0x0000);
    ok &= (RAM4K(0x5678, 1, 0x03f, dffs) == 0x0000);
    ok &= (RAM4K(0x9abc, 1, 0x0a7, dffs) == 0x0000);
    ok &= (RAM4K(0xdef0, 1, 0x2f9, dffs) == 0x0000);
    ok &= (RAM4K(0xaaaa, 1, 0x8cc, dffs) == 0x0000);
    ok &= (RAM4K(0x5555, 1, 0x8ff, dffs) == 0x0000);
    ok &= (RAM4K(0xafff, 1, 0xb07, dffs) == 0x0000);
    ok &= (RAM4K(0xffff, 1, 0xf78, dffs) == 0x0000);

    ok &= (RAM4K(0x5678, 1, 0x001, dffs) == 0x1234);
    ok &= (RAM4K(0x9abc, 1, 0x03f, dffs) == 0x5678);
    ok &= (RAM4K(0xdef0, 1, 0x0a7, dffs) == 0x9abc);
    ok &= (RAM4K(0xaaaa, 1, 0x2f9, dffs) == 0xdef0);
    ok &= (RAM4K(0x5555, 1, 0x8cc, dffs) == 0xaaaa);
    ok &= (RAM4K(0xafff, 1, 0x8ff, dffs) == 0x5555);
    ok &= (RAM4K(0xffff, 1, 0xb07, dffs) == 0xafff);
    ok &= (RAM4K(0x0000, 1, 0xf78, dffs) == 0xffff);

    ok &= (RAM4K(0x9abc, 0, 0x001, dffs) == 0x5678);
    ok &= (RAM4K(0xdef0, 0, 0x03f, dffs) == 0x9abc);
    ok &= (RAM4K(0xaaaa, 0, 0x0a7, dffs) == 0xdef0);
    ok &= (RAM4K(0x5555, 0, 0x2f9, dffs) == 0xaaaa);
    ok &= (RAM4K(0xafff, 0, 0x8cc, dffs) == 0x5555);
    ok &= (RAM4K(0xffff, 0, 0x8ff, dffs) == 0xafff);
    ok &= (RAM4K(0x0000, 0, 0xb07, dffs) == 0xffff);
    ok &= (RAM4K(0x1234, 0, 0xf78, dffs) == 0x0000);

    ok &= (RAM4K(0xdef0, 0, 0x001, dffs) == 0x5678);
    ok &= (RAM4K(0xaaaa, 0, 0x03f, dffs) == 0x9abc);
    ok &= (RAM4K(0x5555, 0, 0x0a7, dffs) == 0xdef0);
    ok &= (RAM4K(0xffff, 0, 0x2f9, dffs) == 0xaaaa);
    ok &= (RAM4K(0x0000, 0, 0x8cc, dffs) == 0x5555);
    ok &= (RAM4K(0x1234, 0, 0x8ff, dffs) == 0xafff);
    ok &= (RAM4K(0x5678, 0, 0xb07, dffs) == 0xffff);
    ok &= (RAM4K(0x9abc, 0, 0xf78, dffs) == 0x0000);

    delete[] dffs;
    EXPECT_EQ(ok, "RAM4KTest");
}

void RAM16KTest() {
    bool ok = true;

    std::cout << "[TESTING] This test may take a while..." << std::endl;

    DFF_t **dffs = new DFF_t*[262144];
    for(int i = 0; i < 262144; i++){
        dffs[i] = new DFF_t();
    }

    for(int i = 0; i < 16384; i+=500){
        ok &= (RAM16K(i+1, 1, i, dffs) == 0);
    }
    
    for(int i = 0; i < 16384; i+=500){
        ok &= (RAM16K(i+2, 1, i, dffs) == i+1);
    }
    
    for(int i = 0; i < 16384; i+=500){
        ok &= (RAM16K(2*i, 1, i, dffs) == i+2);
    }
    
    for(int i = 0; i < 16384; i+=500){
        ok &= (RAM16K(i+1, 0, i, dffs) == 2*i);
    }

    for(int i = 0; i < 16384; i+=500){
        ok &= (RAM16K(0x1234, 1, i, dffs) == 2*i);
    }

    for(int i = 0; i < 16384; i+=500){
        ok &= (RAM16K(0xabcd, 0, i, dffs) == 0x1234);
    }

    for(int i = 0; i < 16384; i+=500){
        ok &= (RAM16K(0x1234, 0, i, dffs) == 0x1234);
    }

    delete[] dffs;
    EXPECT_EQ(ok, "RAM16KTest");
}

void PCTest(){
    bool ok = true;
    
    DFF_t **dffs = new DFF_t*[16];
    for(int i = 0; i < 16; i++){
        dffs[i] = new DFF_t();
    }

    ok &= (PC(0x1234, 0, 0, 1, dffs) == 0x0000);
    ok &= (PC(0x1234, 0, 1, 0, dffs) == 0x0000);
    ok &= (PC(0x5678, 1, 0, 0, dffs) == 0x1234);
    ok &= (PC(0x5678, 0, 1, 1, dffs) == 0x1235);
    ok &= (PC(0x5678, 1, 0, 0, dffs) == 0x0000);
    ok &= (PC(0x5678, 1, 1, 0, dffs) == 0x0001);
    ok &= (PC(0x9abc, 0, 0, 1, dffs) == 0x5678);
    ok &= (PC(0xfffe, 0, 1, 0, dffs) == 0x0000);
    ok &= (PC(0x1234, 1, 0, 1, dffs) == 0xfffe);
    ok &= (PC(0xffff, 0, 1, 0, dffs) == 0x0000);
    ok &= (PC(0x1234, 1, 0, 0, dffs) == 0xffff);
    ok &= (PC(0x1234, 1, 1, 0, dffs) == 0x0000);

    delete[] dffs;
    EXPECT_EQ(ok, "PCTest");
}

void print_scores() {
    std::cout << "[RESULT] Tests passed: " << tests_passed << " / " << tests_run << std::endl;
    ofs << "[RESULT] Tests passed: " << tests_passed << " / " << tests_run << std::endl;
}

int main(int argc, char const* argv[])
{
    initialize();

    BitTest();
    RegisterTest();
    RAM8Test();
    RAM64Test();
    RAM512Test();
    RAM4KTest();
    RAM16KTest();
    PCTest();

    print_scores();
    return 0;
}
