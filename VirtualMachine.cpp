//
// Created by mirro on 2019/09/13.
//

#include "VirtualMachine.h"

void VirtualMachine::analyze() {
    int magic = read_int();
    if (magic != 0xdeadbeef) {
        cout << "error : magic is invalid" << endl;
    }

    int registers_size = read_int();
    // cout << "registers size : " << (unsigned int) registers_size << endl;
    registers = new Object_*[registers_size];

    int functions_size = read_int();
    // cout << "functions size : " << (unsigned int) functions_size << endl;

    int instructions_size = read_int();
    // cout << "instructions size : " << (unsigned int) instructions_size << endl;
    instructions = new int[instructions_size];
    for (int i = 0; i < instructions_size; i++) {
        instructions[i] = read_int();
    }

    int constant_pool_size = read_int();
    // cout << "constant pool size : " << (unsigned int) constant_pool_size << endl;
    constant_pool = new Object_*[constant_pool_size];
    for (int i = 0; i < constant_pool_size; i++) {
        constant_pool[i] = (Object_*) new string(20, ' ');
    }
    for (int i = 0; i < constant_pool_size; i++) {
        int tag = read_int();
        switch (tag) {
            case 0x0: // int
                constant_pool[i] = (Object_ *) read_int();
                break;
            case 0x1: // string
                int size = read_int();
                vector<uint8_t> bytes = read(size);
                string* s = new string(20, ' ');
                for (int j = 0; j < size; j++) {
                    (*(s))[j] = (char) bytes[j];
                }
                constant_pool[i] = (Object_ *) s;
                break;
        }
    }
}
// direct threading
#if defined __GNUC__ || defined __clnag__ || defined __INTEL_COMPILER
#define DIRECT_THREADED
#endif

#ifdef DIRECT_THREADED

#define INIT_DISPATCH JUMP;
#define CASE(op) L_ ## op:
#define NEXT i=*++pc; goto *table[type(i)]
#define JUMP i=*pc; goto *table[type(i)]
#define END_DISPATCH

#else

#define INIT_DISPATCH while(true) { i = *pc; switch (type(i)) {
#define CASE(op) case op:
#define NEXT pc++; break;
#define JUMP break
#define END_DISPATCH }}

#endif
void VirtualMachine::execute() {
    /* TODO impl
    int* pc = instructions;
    int i;
#ifdef DIRECT_THREADED
    static void* table[] = {

    };
#endif
    INIT_DISPATCH
        CASE() {

        } NEXT;
        CASE() {

        } NEXT;
    END_DISPATCH
    */
    while (true) {
        switch (type()) {
            case 0x00: // stop
                return;
            case 0x10: // copy
                registers[operand1()] = constant_pool[operand2()];
                break;
            case 0x20: // add
                registers[operand1()] = (Object_*) ((int) registers[operand2()] + (int) registers[operand3()]);
                break;
            case 0x21: // sub
                registers[operand1()] = (Object_*) ((int) registers[operand2()] - (int) registers[operand3()]);
                break;
            case 0x22: // mul
                registers[operand1()] = (Object_*) ((int) registers[operand2()] * (int) registers[operand3()]);
                break;
            case 0x23: // div
                registers[operand1()] = (Object_*) ((int) registers[operand2()] / (int) registers[operand3()]);
                break;
            case 0x30: // print_string
                cout << ((string*) constant_pool[operand1()])->c_str() << endl;
                break;
            case 0x31: // print
                cout << (int) registers[operand1()] << endl;
                break;
        }
        counter++;
    }
}
vector<uint8_t> VirtualMachine::read(const int length) {
    vector<uint8_t> bytes;
    bytes.reserve(length);
    for (int i = 0; i < length; i++) {
        bytes.push_back(input[position + i]);
    }
    position += length;
    return bytes;
}
unsigned int VirtualMachine::read_int() {
    vector<uint8_t> bytes = read(4);
    // little endian
    return bytes[0] |
           bytes[1] << 8 |
           bytes[2] << 16 |
           bytes[3] << 24;
}
unsigned int VirtualMachine::type() {
    return instructions[counter] >> 24 & 0xff;
}
unsigned int VirtualMachine::operand1() {
    return instructions[counter] >> 16 & 0xff;
}
unsigned int VirtualMachine::operand2() {
    return instructions[counter] >> 8 & 0xff;
}
unsigned int VirtualMachine::operand3() {
    return instructions[counter] & 0xff;
}