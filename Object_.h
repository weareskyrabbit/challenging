//
// Created by mirro on 2019/09/13.
//

#ifndef UNTITLED7_OBJECT__H
#define UNTITLED7_OBJECT__H

using namespace std;

union Object_ {
    // int
    int32_t i;

    // string
    int8_t* s;

    // object
    object o;
};

#endif
