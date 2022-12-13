//
// Created by da on 06.11.2022.
//

#ifndef SIAOD_2_BINARYSEARCHTREE_H
#define SIAOD_2_BINARYSEARCHTREE_H

#include "AbstractStruct.h"

struct Node {
    Node *right;
    Node *left;
    Key key;
    int pos;

    Node(Key _key, int _pos) : key(_key), left(nullptr), right(nullptr), pos(_pos) {}
};

class BinarySearchTree : public Abstract {
    Node *root = nullptr;
public:
    Node *insert(Node *, Key, int);

    void insert(Key, int) override;

    int get(Node *, Key);

    int get(Key) override;

    Node *remove(Node *, Key);

    void remove(Key) override;

    void print();

    void print(Node *, string, bool);

    Node *findMinRightElem(Node *node);

    int getSize() override { return 1; }

    int getRotates() override { return 0; }
};


#endif //SIAOD_2_BINARYSEARCHTREE_H
