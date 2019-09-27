//
// Created by mirro on 2019/09/13.
//

#ifndef UNTITLED7_GARBAGECOLLECTION_H
#define UNTITLED7_GARBAGECOLLECTION_H


#include "Object_.h"

class GarbageCollection {
public:
    Object_* new_();
    void collect();
    void mark_from_roots();
    void mark();
};


#endif //UNTITLED7_GARBAGECOLLECTION_H
