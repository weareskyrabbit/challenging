#ifndef UNTITLED7_VIRTUALMACHINE_H
#define UNTITLED7_VIRTUALMACHINE_H

#include <iostream>
#include <stack>
#include <vector>
#include <iterator>

#include "Object_.h"
#include "Structures/instruction.h"
#include "Structures/class.h"
#include "Structures/frame.h"
#include "Structures/object.h"

using namespace std;

class VirtualMachine {
private:
    /* system area */ 
    value* register_;
    vector<uint8_t> input;
    uint32_t position;
    instruction* instructions;
    Object_** constant_pool;
    uint32_t counter; // program counter
    Object_** registers; // TODO remove
    uint32_t* functions;
    /* stack area */
    stack<frame*> runtime_stack;
    /* heap area */
    Object_* heap;
public:
    VirtualMachine() {
        this->position = 0;
        this->counter = 0;
    }
    VirtualMachine(Object_** registers, uint32_t* functions, instruction* instructions,
            Object_** constant_pool) {
        this->registers = registers;
        this->functions = functions;
        this->instructions = instructions;
        this->constant_pool = constant_pool;
    }
    uint32_t load(string file_name);
    void execute(uint32_t entry_point);
private:
    uint8_t* read(int32_t length);
    uint32_t* read_int();
};


#endif //UNTITLED7_VIRTUALMACHINE_H
