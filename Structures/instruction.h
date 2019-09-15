#ifndef UNTITLED7_INSTRUCTION_H
#define UNTITLED7_INSTRUCTION_H

#include <cstdint>

using namespace std;

#pragma pack (1)

struct instruction {
    // little endian
    uint8_t operand2;
    uint8_t operand1;
    uint8_t operand0;
    uint8_t type;
};

#pragma pack (0)

#endif