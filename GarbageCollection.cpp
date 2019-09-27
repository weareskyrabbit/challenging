//
// Created by mirro on 2019/09/13.
//

#include <iostream>
#include <stdlib.h>
#include "GarbageCollection.h"

using namespace std;

Object_* GarbageCollection::new_() {
    Object_* reference = (Object_*)malloc(sizeof(Object_));
    if (!reference) {
        collect();
        reference = (Object_*)malloc(sizeof(Object_));
        if (!reference) {
            cout << "error : out of memory" << endl;
        }
    }
    return reference;
}
void GarbageCollection::collect() {
    /*
    mark_from_roots();
    sweep();
     */
}
void GarbageCollection::mark_from_roots() {
    /*
    initialize(worklist);
    for (Object_* field : roots) {
        Object_* reference = *field;
        if (reference && !is_marked(reference)) {
            set_marked(reference);
            add(worklist, reference);
            mark();
        }
    }
     */
}
void GarbageCollection::mark() {

}