//
// Created by mirro on 2019/09/13.
//

#pragma once

#include <string>

using namespace std;

union Object_ {
    // int
    int32_t* i;

    // string
    int8_t* s;
};
