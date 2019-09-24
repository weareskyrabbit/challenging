//
// Created by mirro on 2019/09/13.
//

#include <fstream>
#include "VirtualMachine.h"

using namespace std;

// #define ON_DEBUG

#ifdef ON_DEBUG

#define DEBUG_OUT(message, target) cout << "debug | " << message << target << endl

#else

#define DEBUG_OUT(message, target)

#endif

uint32_t VirtualMachine::load(string file_name) {
    input.clear();
    position = 0;
    file_name += ".wc";
    ifstream fin;
    fin.open(file_name.c_str(), ios::in | ios::binary);
    if (!fin) {
        cout << "error | file `"<< file_name.c_str() <<"` didn't open" << endl;
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
    registers = new Object_*[registers_size];

    uint32_t references_size = *read_int();
    DEBUG_OUT("references size : ", references_size);

    uint32_t functions_size = *read_int();
    DEBUG_OUT("functions size : ", functions_size);
    functions = new uint32_t[functions_size];
    functions = (uint32_t*) read(sizeof(uint32_t) * functions_size);

    int32_t instructions_size = *read_int();
    DEBUG_OUT("instructions size : ", instructions_size);
    instructions = new instruction[instructions_size];
    instructions = (instruction*) read(sizeof(instruction) * instructions_size);

    uint32_t constant_pool_size = *read_int();
    DEBUG_OUT("constant pool size : ", constant_pool_size);
    constant_pool = new Object_*[constant_pool_size];

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
void VirtualMachine::execute(uint32_t entry_point) {
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
        &&L_LOAD0,
        &&L_LOAD1,
        &&L_STORE0,
        &&L_STORE1,
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
            DEBUG_OUT("nop called with instruction : ", (uint32_t) pc->type);
        } NEXT;
        CASE(STOP) {
            DEBUG_OUT("stop called with instruction : ", (uint32_t) pc->type);
        } return;
        CASE(CALL) {
            frame* f = new frame;
            f.frame_pointer = frame_pointer;
            f.this_ = this_;
            f.return_address = pc + 1;
            frame_pointer++;
            frame_pointer = f;
            pc = registers[i.operand0]->o.method_table[i.operand1];
        } JUMP;
        CASE(RETURN) {
            registers[0] = (Object_*) i.operand0;
            frame* f = frame_pointer;
            frame_pointer--;
            frame_pointer = f.frame_pointer;
            this_ = f.this_;
            pc = f.return_address;
        } JUMP;
        CASE(BR) {
            pc = instructions + i.operand0;
        } JUMP;
        CASE(BR_N) {

        } JUMP;
        CASE(COPY) {
            registers[i.operand0] = constant_pool[i.operand1];
        } NEXT;
        CASE(LOAD0) { // load from fields
            registers[i.operand0] = this_.fields[i.operand1];
        } NEXT;
        CASE(LOAD1) { // load from locals
            registers[i.operand0] = frame_pointer.locals[i.operand1];
        } NEXT;
        CASE(STORE0) { // store to fields
            this_.fields[i.operand1] = registers[i.operand0];
        } NEXT;
        CASE(STORE1) { // store to locals
            frame_pointer.locals[i.operand1] = registers[i.operand0];
        } NEXT;
        CASE(ADD0) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i + registers[i.operand2]->i);
        } NEXT;
        CASE(ADD1) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i + constant_pool[i.operand2]->i);
        } NEXT;
        CASE(ADD2) {
            registers[i.operand0] = (Object_*) (constant_pool[i.operand1]->i + constant_pool[i.operand2]->i);
        } NEXT;
        CASE(SUB0) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i - registers[i.operand2]->i);
        } NEXT;
        CASE(SUB1) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i - constant_pool[i.operand2]->i);
        } NEXT;
        CASE(SUB2) {
            registers[i.operand0] = (Object_*) (constant_pool[i.operand1]->i - constant_pool[i.operand2]->i);
        } NEXT;
        CASE(MUL0) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i * registers[i.operand2]->i);
        } NEXT;
        CASE(MUL1) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i * constant_pool[i.operand2]->i);
        } NEXT;
        CASE(MUL2) {
            registers[i.operand0] = (Object_*) (constant_pool[i.operand1]->i * constant_pool[i.operand2]->i);
        } NEXT;
        CASE(DIV0) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i / registers[i.operand2]->i);
        } NEXT;
        CASE(DIV1) {
            registers[i.operand0] = (Object_*) (registers[i.operand1]->i / constant_pool[i.operand2]->i);
        } NEXT;
        CASE(DIV2) {
            registers[i.operand0] = (Object_*) (constant_pool[i.operand1]->i / constant_pool[i.operand2]->i);
        } NEXT;
        CASE(PRINT0) {
            printf("%s", constant_pool[i.operand0]->s);
        } NEXT;
        CASE(PRINT1) {
            printf("%d", registers[i.operand0]->i);
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
    DEBUG_OUT("read_int called and returned : ", *(uint32_t*)bytes);
    return (uint32_t*)bytes;
}
#undef DEBUG_OUT
