#ifndef CHALLENGING_CLASS_H
#define CHALLENGING_CLASS_H

#include "value.h"
#include "function.h"

typedef struct {
    value* static_variable;
    function* static_function;
}  class_;

#endif //CHALLENGING_CLASS_H
