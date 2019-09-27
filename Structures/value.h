#ifndef CHALLENGING_VALUE_H
#define CHALLENGING_VALUE_H

#include "object.h"

typedef union {
    int32_t i;
    int8_t* s;
    object o;
} value;

#endif //CHALLENGING_VALUE_H
