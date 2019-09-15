//
// Created by mirro on 2019/09/14.
//

#ifndef CHALLENGING_FRAME_H
#define CHALLENGING_FRAME_H


#include "Structures/instruction.h"

class Frame {
public:
    instruction* return_address;
    Frame(instruction* return_address) {
        this->return_address = return_address;
    }
};


#endif //CHALLENGING_FRAME_H
