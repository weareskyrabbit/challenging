//
// Created by mirro on 2019/09/13.
//

#include <fstream>
#include "VirtualMachine.h"

<<<<<<< HEAD
using namespace std;

#ifdef ON_DEBUG

#define DEBUG_OUT(message) cout << "DEBUG out: " << message << endl;

#else

#define DEBUG_OUT(message)

#endif

uint32_t VirtualMachine::load(string file_name) {
    input.clear();
    file_name += ".wc";
    ifstream fin;
    fin.open(file_name.c_str(), ios::in | ios::binary);
    if (!fin) {
        cout << "error : file `"<< file_name.c_str() <<"` didn't open" << endl;
        return 1;
    }
    while (!fin.eof()) {
        uint8_t byte = 0;
        fin.read((char*) &byte, sizeof(uint8_t));
        input.push_back(byte);
    }
    fin.close();

    uint32_t magic = *read_int();
    if (magic != 0xdeadbeef) {
        cout << "error : magic is invalid" << endl;
    }

    uint32_t entry_point = *read_int();
    // cout << "entry point : " << (unsigned int) entry_point << endl;

    uint32_t registers_size = *read_int();
    // cout << "registers size : " << (unsigned int) registers_size << endl;
    registers = new Object_*[registers_size];

    uint32_t references_size = *read_int();
    // cout << "references size : " << (unsigned int) functions_size << endl;

    uint32_t functions_size = *read_int();
    // cout << "functions size : " << (unsigned int) functions_size << endl;
    functions = new uint32_t[functions_size];
    functions = (uint32_t*)read(functions_size * sizeof(uint32_t));

    int32_t instructions_size = *read_int();
    // cout << "instructions size : " << (unsigned int) instructions_size << endl;
    instructions = new instruction[instructions_size];
    instructions = (instruction*)read(sizeof(instruction) * instructions_size);

    uint32_t constant_pool_size = *read_int();
    // cout << "constant pool size : " << (unsigned int) constant_pool_size << endl;
    constant_pool = new Object_*[constant_pool_size];

    for (uint32_t i = 0; i < constant_pool_size; i++) {
        uint32_t tag = *read_int();
        switch (tag) {
            case 0x0: // int
                constant_pool[i] = (Object_ *) read_int();
                break;
            case 0x1: // string
                uint32_t size = *read_int();
                constant_pool[i] = (Object_ *) read(size);
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
#define NEXT i=*++pc; goto *table[i.type]
#define JUMP i=*pc; goto *table[i.type]
#define END_DISPATCH

#else

#define INIT_DISPATCH while(true) { i = *pc; switch (i.type) {
#define CASE(op) case op:
#define NEXT pc++; break;
#define JUMP break
#define END_DISPATCH }}

#endif
void VirtualMachine::execute(int32_t entry_point) {
    instruction* pc = instructions + functions[entry_point];
    instruction i;
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
            runtime_stack.push(new Frame(pc + 1));
            pc = instructions + functions[i.operand[0]];
        } JUMP;
        CASE(RETURN) {
            pc = runtime_stack.top()->return_address;
            runtime_stack.pop();
        } JUMP;
        CASE(BR) {
            pc = instructions + i.operand[0];
        } JUMP;
        CASE(BR_N) {

        } JUMP;
        CASE(COPY) {
            registers[i.operand[0]] = constant_pool[i.operand[1]];
        } NEXT;
        CASE(ADD0) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] + (int) registers[i.operand[2]]);
        } NEXT;
        CASE(ADD1) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] + (int) constant_pool[i.operand[2]]);
        } NEXT;
        CASE(ADD2) {
            registers[i.operand[0]] = (Object_*) ((int) constant_pool[i.operand[1]] + (int) constant_pool[i.operand[2]]);
        } NEXT;
        CASE(SUB0) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] - (int) registers[i.operand[2]]);
        } NEXT;
        CASE(SUB1) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] - (int) constant_pool[i.operand[2]]);
        } NEXT;
        CASE(SUB2) {
            registers[i.operand[0]] = (Object_*) ((int) constant_pool[i.operand[1]] - (int) constant_pool[i.operand[2]]);
        } NEXT;
        CASE(MUL0) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] * (int) registers[i.operand[2]]);
        } NEXT;
        CASE(MUL1) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] * (int) constant_pool[i.operand[2]]);
        } NEXT;
        CASE(MUL2) {
            registers[i.operand[0]] = (Object_*) ((int) constant_pool[i.operand[1]] * (int) constant_pool[i.operand[2]]);
        } NEXT;
        CASE(DIV0) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] / (int) registers[i.operand[2]]);
        } NEXT;
        CASE(DIV1) {
            registers[i.operand[0]] = (Object_*) ((int) registers[i.operand[1]] / (int) constant_pool[i.operand[2]);
        } NEXT;
        CASE(DIV2) {
            registers[i.operand[0]] = (Object_*) ((int) constant_pool[i.operand[1]] / (int) constant_pool[i.operand[2]]);
        } NEXT;
        CASE(PRINT0) {
            printf("%s", (*constant_pool[i.operand[0]]).s);
        } NEXT;
        CASE(PRINT1) {
            printf("%u", *(uint32_t*)registers[i.operand[0]]);
        } NEXT;
    }
    END_DISPATCH;
}
uint8_t* VirtualMachine::read(const int32_t length) {
    auto bytes = new uint8_t[length];
    for (int i = 0; i < length; i++) {
        bytes[i] = input[position + i];
    }
    position += length;
    return bytes;
}
uint32_t* VirtualMachine::read_int() {
    auto bytes = read(4);
    DEBUG_OUT("read_int called and returned :" + *(uint32_t*)bytes);
    return (uint32_t*)bytes;
}
#undef DEBUG_OUT
