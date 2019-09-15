//
// Created by mirro on 2019/09/14.
//

#ifndef CHALLENGING_FRAME_H
#define CHALLENGING_FRAME_H


class Frame {
public:
    int* return_address;
    Frame(int* return_address) {
        this->return_address = return_address;
    }
};


#endif //CHALLENGING_FRAME_H
