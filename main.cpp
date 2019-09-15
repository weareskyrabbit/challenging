#include <iostream>
#include <fstream>

#include "VirtualMachine.h"

using namespace std;

int main() {
    auto* vm = new VirtualMachine();
    // write
    ofstream fout;
    fout.open(R"(test2.wc)", ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file 'test2.wc' didn't open" << endl;
        return 1;
    }
    uint32_t test2[] = {
            0xdeadbeef, // magic
            0,          // entry point
            4,          // registers size
            0,          // references size
            1,          // functions size
            0,          // extent

            // main
            5,          // instructions size
            0x10010000, // copy   r1 c0
            0x28020102, // mul    r2 c1 c2
            0x20030102, // add    r3 r1 r2
            0x31030000, // print  r3
            0x00000000, // stop

            3,          // constant pool size

            // c0 1
            0,          // tag int
            1,

            // c1 2
            0,          // tag int
            2,

            // c2 3
            0,          // tag int
            3
    };
    for (uint32_t instruction : test2) {
        fout.write((char*) &instruction, sizeof(uint32_t));
    }

    fout.close();

    fout.open(R"(test3.wc)", ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file 'test3.wc' didn't open" << endl;
        return 1;
    }
    uint32_t test3[] = {
            0xdeadbeef, // magic
            0,          // entry point
            1,          // registers size
            0,          // references size
            2,          // functions size
            0,          // extent
            2,          // extent

            // main
            4,          // instructions size
            0x01010000, // call   1
            0x00000000, // stop
            // display
            0x30000000, // print_string c1
            0x02000000, // return

            1,          // constant pool size

            // c0 "display"
            1,          // tag string
            8,
            0x70736964,
            0x0079616c

    };
    for (uint32_t instruction : test3) {
        fout.write((char*) &instruction, sizeof(uint32_t));
    }

    fout.close();
    /*
    fout.open(R"(test4.wc)", ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file 'test4.wc' didn't open" << endl;
        return 1;
    }
    unsigned int test4[] = {
            0xdeadbeef, // magic
            0,          // entry point
            1,          // registers size
            0,          // references size
            1,          // functions size

            // main
            10,          // instructions size
            0x, // false  r1
            0x, // br_n   r1 6
            0x, // self   r2
            0x10030000, // copy   r3 c0
            0x, // call   r2 :puts
            0x03090000, // br     9
            0x, // self   r2
            0x10030100, // copy r3 c1
            0x, // call   r2 :puts
            0x00000000, // stop

            2,          // constant pool size
            // string "true"
            1,          // tag string
            // string "false"
            1,          // tag string

    };
    for (int instruction : test4) {
        fout.write((char*) &instruction, sizeof(int));
    }

    fout.close();
    */

    fout.open(R"(hello.wc)", ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file 'hello.wc' didn't open" << endl;
        return 1;
    }
    uint32_t hello[] = {
            0xdeadbeef, // magic
            0,          // entry point
            1,          // registers size
            0,          // references size
            1,          // functions size
            0,          // extent

            // main
            2,          // instructions size
            0x30000000, // print_string c0
            0x00000000, // stop

            1,          // constant pool size

            // c0 "hello world!"
            1,          // tag string
            12,
            0x6c6c6568,
            0x6f77206f,
            0x00646c72
    };
    for (uint32_t instruction : hello) {
        fout.write((char*) &instruction, sizeof(uint32_t));
    }

    fout.close();

    // load & execute
    uint32_t entry_point = vm->load(string("test2"));
    vm->execute(entry_point);

    // load & execute
    entry_point = vm->load(string("test3"));
    vm->execute(entry_point);

    // load & execute
    entry_point = vm->load(string("hello"));
    vm->execute(entry_point);
    return 0;
}