//
// Created by mirro on 2019/09/16.
//
#include <iostream>
#include <fstream>

#include "Converter.h"
#include "Structures/instruction.h"
#include "Object_.h"

// #define ON_DEBUG

#ifdef ON_DEBUG

#define DEBUG_OUT(message, target) cout << "debug | " << message << target << endl

#else

#define DEBUG_OUT(message, target)

#endif

void Converter::IRtoWC(string const& file_name) {
    // read `.ir` file
    string ir = string(file_name);
    ir += ".ir";
    ifstream fin;
    fin.open(ir.c_str(), ios::in | ios::binary);
    if (!fin) {
        cout << "error : file '" << ir.c_str() << "' didn't open" << endl;
        exit(1);
    }
    // TODO read
    fin.close();

    // TODO convert

    // write `.wc` file
    string wc = string(file_name);
    wc += ".wc";
    ofstream fout;
    fout.open(wc.c_str(), ios::out | ios::binary | ios::trunc);
    if (!fout) {
        cout << "error : file '" << wc.c_str() << "' didn't open" << endl;
        exit(1);
    }
    // TODO write
    fout.close();
}
VirtualMachine* Converter::IRtoMemory(string const& file_name) {
    // read `.ir` file
    string ir = string(file_name);
    ir += ".ir";
    ifstream fin;
    fin.open(ir.c_str(), ios::in | ios::binary);
    if (!fin) {
        cout << "error : file '" << ir.c_str() << "' didn't open" << endl;
        exit(1);
    }
    // TODO read
    fin.close();
    return new VirtualMachine(nullptr, nullptr, nullptr, nullptr);
}
VirtualMachine* Converter::WCtoMemory(string const& file_name) {
    input.clear();
    position = 0;
    string wc = string(file_name);
    wc += ".wc";
    ifstream fin;
    fin.open(wc.c_str(), ios::in | ios::binary);
    if (!fin) {
        cout << "error | file `"<< wc.c_str() <<"` didn't open" << endl;
        exit(1);
    }
    while (!fin.eof()) {
        uint8_t byte = 0;
        fin.read((char*) &byte, sizeof(uint8_t));
        input.push_back(byte);
    }
    fin.close();

    uint32_t magic = *read_int();
    DEBUG_OUT("magic : ", magic);
    if (magic != 0xdeadbeef) {
        cout << "error | magic is invalid" << endl;
    }

    uint32_t entry_point = *read_int();
    DEBUG_OUT("entry point : ", entry_point);

    uint32_t registers_size = *read_int();
    DEBUG_OUT("registers size : ", registers_size);
    auto* registers = new Object_*[registers_size];

    uint32_t references_size = *read_int();
    DEBUG_OUT("references size : ", references_size);

    uint32_t functions_size = *read_int();
    DEBUG_OUT("functions size : ", functions_size);
    auto* functions = new uint32_t[functions_size];
    functions = (uint32_t*) read(sizeof(uint32_t) * functions_size);

    int32_t instructions_size = *read_int();
    DEBUG_OUT("instructions size : ", instructions_size);
    auto* instructions = new instruction[instructions_size];
    instructions = (instruction*) read(sizeof(instruction) * instructions_size);

    uint32_t constant_pool_size = *read_int();
    DEBUG_OUT("constant pool size : ", constant_pool_size);
    auto* constant_pool = new Object_*[constant_pool_size];

    for (uint32_t i = 0; i < constant_pool_size; i++) {
        uint32_t tag = *read_int();
        uint32_t size;
        switch (tag) {
            case 0x0: // int
                constant_pool[i] = (Object_ *) *read_int();
                break;
            case 0x1: // string
                size = *read_int();
                constant_pool[i] = (Object_ *) read(size);
                break;
            default:
                cout << "error | illegal constant type `" << tag << "`" << endl;
                exit(1);
        }
    }
    return new VirtualMachine(registers, functions, instructions, constant_pool);
}
uint8_t* Converter::read(const int32_t length) {
    auto bytes = new uint8_t[length];
    for (int i = 0; i < length; i++) {
        bytes[i] = input[position + i];
    }
    position += length;
    return bytes;
}
uint32_t* Converter::read_int() {
    auto bytes = read(4);
    DEBUG_OUT("read_int called and returned : ", *(uint32_t*)bytes);
    return (uint32_t*)bytes;
}
#undef DEBUG_OUT