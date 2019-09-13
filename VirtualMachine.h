//
// Created by mirro on 2019/09/13.
//

#ifndef UNTITLED7_VIRTUALMACHINE_H
#define UNTITLED7_VIRTUALMACHINE_H

#include <iostream>
#include <stack>
#include <vector>
#include <iterator>
#include "Object_.h"

using namespace std;

class VirtualMachine {
private:
    vector<uint8_t> input;
    int position;
    int* instructions;
    Object_** constant_pool;
    int counter; // program counter
    Object_** registers;
public:
    VirtualMachine(const vector<uint8_t> input) {
        this->input = input;
        this->position = 0;
        this->counter = 0;
    }
    void analyze();
    void execute();
private:
    vector<uint8_t> read(int length);
    unsigned int read_int();
    unsigned int type();
    unsigned int operand1();
    unsigned int operand2();
    unsigned int operand3();
};


#endif //UNTITLED7_VIRTUALMACHINE_H
