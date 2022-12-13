//
// Created by da on 26.11.2022.
//

#ifndef SIAOD_2_ABSTRACTSTRUCT_H
#define SIAOD_2_ABSTRACTSTRUCT_H

#include "Key.h"

struct Abstract {
    virtual int get(Key key) = 0;
    virtual void remove(Key key) = 0;
    virtual void insert(Key key,int pos) = 0;
    virtual int getSize() = 0;
    virtual int getRotates() = 0;
};

#endif //SIAOD_2_ABSTRACTSTRUCT_H
