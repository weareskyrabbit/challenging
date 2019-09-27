#ifndef CHALLENGING_FRAME_H
#define CHALLENGING_FRAME_H

#include "value.h"
#include "instruction.h"

using namespace groupy;

typedef struct {
    value* local_variables;
    value this_;
    instruction* return_address;
} frame;

#endif //CHALLENGING_FRAME_H
