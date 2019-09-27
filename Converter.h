//
// Created by mirro on 2019/09/16.
//

#ifndef CHALLENGING_CONVERTER_H
#define CHALLENGING_CONVERTER_H

#include <vector>

#include "VirtualMachine.h"

using namespace std;

class Converter {
private:
    vector<uint8_t> input;
    uint32_t position;
    uint8_t* read(int32_t length);
    uint32_t* read_int();
public:
    void IRtoWC(string const& file_name);
    VirtualMachine* IRtoMemory(string const& file_name);
    VirtualMachine* WCtoMemory(string const& file_name);
};

#endif //CHALLENGING_CONVERTER_H
