//
// Created by mirro on 2019/09/14.
//

#ifndef CHALLENGING_FRAME_H
#define CHALLENGING_FRAME_H


#include "Structures/instruction.h"

struct frame {
    frame* frame_pointer;
    object* this_;
    instruction* return_address;
    Object_* locals;
};

#endif //CHALLENGING_FRAME_H
