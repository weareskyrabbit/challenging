#include <iostream>
#include <fstream>
#include <vector>

#include "VirtualMachine.h"

using namespace std;

int main() {
    vector<uint8_t> input;
    // write
    ofstream fout;
    fout.open(R"(test2.wc)", ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file 'test2.wc' didn't open" << endl;
        return 1;
    }
    unsigned int test2[] = {
            0xdeadbeef, // magic
            4,          // registers size
            0,          // references size
            1,          // functions size

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
    for (int instruction : test2) {
        fout.write((char*) &instruction, sizeof(int));
    }

    fout.close();

    fout.open(R"(test3.wc)", ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file 'test3.wc' didn't open" << endl;
        return 1;
    }
    unsigned int test3[] = {
            0xdeadbeef, // magic
            1,          // registers size
            0,          // references size
            2,          // functions size

            // main
            2,          // instructions size
            0x01000000, // call   c0
            0x00000000, // stop
            // hello
            2,          // instructions size
            0x30010000, // print_string c1
            0x02000000, // return

            2,          // constant pool size
            // TODO function

            // c1 "hello world!"
            1,          // tag string
            12,
            0x6c6c6568,
            0x6f77206f,
            0x21646c72

    };
    for (int instruction : test3) {
        fout.write((char*) &instruction, sizeof(int));
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
    unsigned int hello[] = {
            0xdeadbeef, // magic
            1,          // registers size
            0,          // references size
            1,          // functions size

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
            0x21646c72
    };
    for (int instruction : hello) {
        fout.write((char*) &instruction, sizeof(int));
    }

    fout.close();

    // read
    ifstream fin;
    fin.open(R"(test2.wc)", ios::in | ios::binary);
    if (!fin) {
        cout << "error : file 'test2.wc' didn't open" << endl;
        return 1;
    }
    while (!fin.eof()) {
        uint8_t byte = 0;
        fin.read((char*) &byte, sizeof(uint8_t));
        input.push_back(byte);
    }
    fin.close();
    VirtualMachine* vm = new VirtualMachine(input);

    // analyze
    vm->analyze();

    // execute
    vm->execute();

    input.clear();

    // read
    fin.open(R"(hello.wc)", ios::in | ios::binary);
    if (!fin) {
        cout << "error : file 'hello.wc' didn't open" << endl;
        return 1;
    }
    while (!fin.eof()) {
        uint8_t byte = 0;
        fin.read((char*) &byte, sizeof(uint8_t));
        input.push_back(byte);
    }
    fin.close();
    vm = new VirtualMachine(input);

    // analyze
    vm->analyze();

    // execute
    vm->execute();
    return 0;
}