#include "class.h"
#include "frame.h"
#include "object.h"

using namespace groupy;

int main() {
    Class* system0;
    Instruction* pc;
    Value* system2;
    stack<Frame> stack;
    Object* heap;
    // call
    Frame f = new Frame;
    f.previous_this = system2[-1];
    f.return_address = pc;
    stack.push(f);
    /* system1 = .. */
    // return

    return 0;
}