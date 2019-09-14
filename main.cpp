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
            2,          // registers size
            1,          // functions size
            7,          // instructions size
            0x10000000, // copy  r0 c0
            0x10010100, // copy  r1 c1
            0x10020200, // copy  r2 c2
            0x22030102, // mul   r3 r1 r2
            0x20040003, // add   r4 r0 r3
            0x31040000, // print r4
            0x00000000, // stop
            3,          // constant pool size
            0,          // tag int
            1,          // c0
            0,          // tag int
            2,          // c1
            0,          // tag int
            3           // c2
    };
    for (int instruction : test2) {
        fout.write((char*) &instruction, sizeof(int));
    }

    fout.close();

    fout.open(R"(hello.wc)", ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file 'hello.wc' didn't open" << endl;
        return 1;
    }
    unsigned int hello[] = {
            0xdeadbeef, // magic
            1,          // registers size
            1,          // functions size
            3,          // instructions size
            0x10000000, // copy  r0 c0
            0x30000000, // print_string r0
            0x00000000, // stop
            1,          // constant pool size
            1,          // tag
            12,
            0x6c6c6568, // c0
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