//
// Created by mirro on 2019/09/13.
//

#include "VirtualMachine.h"

int VirtualMachine::analyze() {
    int magic = read_int();
    if (magic != 0xdeadbeef) {
        cout << "error : magic is invalid" << endl;
    }

    int entry_point = read_int();
    // cout << "entry point : " << (unsigned int) entry_point << endl;

    int registers_size = read_int();
    // cout << "registers size : " << (unsigned int) registers_size << endl;
    registers = new Object_*[registers_size];

    int references_size = read_int();
    // cout << "references size : " << (unsigned int) functions_size << endl;

    int functions_size = read_int();
    // cout << "functions size : " << (unsigned int) functions_size << endl;
    functions = new int[functions_size];
    for (int i = 0; i < functions_size; i++) {
        functions[i] = read_int();
    }

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
    return entry_point;
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
void VirtualMachine::execute(int entry_point) {
    int* pc = instructions + functions[entry_point];
    int i;
#ifdef DIRECT_THREADED
    static void* table[] = {
        &&L_STOP,
        &&L_CALL,
        &&L_RETURN,
        &&L_BR,
        &&L_BR_N,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_COPY,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_ADD0,
        &&L_ADD1,
        &&L_ADD2,
        &&L_SUB0,
        &&L_SUB1,
        &&L_SUB2,
        &&L_MUL0,
        &&L_MUL1,
        &&L_MUL2,
        &&L_DIV0,
        &&L_DIV1,
        &&L_DIV2,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_NOP,
        &&L_PRINT0,
        &&L_PRINT1
    };
#endif
    INIT_DISPATCH {
        CASE(NOP) {
        } NEXT;
        CASE(STOP) {
            return;
        } NEXT;
        CASE(CALL) {
            // TODO
        } NEXT;
        CASE(RETURN) {
            // TODO
        } NEXT;
        CASE(BR) {

        } NEXT;
        CASE(BR_N) {

        } NEXT;
        CASE(COPY) {
            registers[operand1(i)] = constant_pool[operand2(i)];
        } NEXT;
        CASE(ADD0) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] + (int) registers[operand3(i)]);
        } NEXT;
        CASE(ADD1) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] + (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(ADD2) {
            registers[operand1(i)] = (Object_*) ((int) constant_pool[operand2(i)] + (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(SUB0) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] - (int) registers[operand3(i)]);
        } NEXT;
        CASE(SUB1) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] - (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(SUB2) {
            registers[operand1(i)] = (Object_*) ((int) constant_pool[operand2(i)] - (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(MUL0) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] * (int) registers[operand3(i)]);
        } NEXT;
        CASE(MUL1) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] * (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(MUL2) {
            registers[operand1(i)] = (Object_*) ((int) constant_pool[operand2(i)] * (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(DIV0) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] / (int) registers[operand3(i)]);
        } NEXT;
        CASE(DIV1) {
            registers[operand1(i)] = (Object_*) ((int) registers[operand2(i)] / (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(DIV2) {
            registers[operand1(i)] = (Object_*) ((int) constant_pool[operand2(i)] / (int) constant_pool[operand3(i)]);
        } NEXT;
        CASE(PRINT0) {
            cout << ((string*) constant_pool[operand1(i)])->c_str() << endl;
        } NEXT;
        CASE(PRINT1) {
            cout << (int) registers[operand1(i)] << endl;
        } NEXT;
    }
    END_DISPATCH;
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
unsigned int VirtualMachine::type(int instruction) {
    return instruction >> 24 & 0xff;
}
unsigned int VirtualMachine::operand1(int instruction) {
    return instruction >> 16 & 0xff;
}
unsigned int VirtualMachine::operand2(int instruction) {
    return instruction >> 8 & 0xff;
}
unsigned int VirtualMachine::operand3(int instruction) {
    return instruction & 0xff;
}