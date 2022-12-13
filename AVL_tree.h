//
// Created by da on 06.11.2022.
//

#ifndef SIAOD_2_AVL_TREE_H
#define SIAOD_2_AVL_TREE_H


#include "AbstractStruct.h"

class AVL_tree : public Abstract {
    int countOfRotates = 0;
    int size = 0;

    struct Node {
        Key key;
        int pos;
        Node *left;
        Node *right;
        int height;

        Node(Key _key, int _pos) : key(_key), pos(_pos), height(1), left(nullptr), right(nullptr) {}
    };
    Node *root = nullptr;
    int getHeight(Node *);
    int getBalance(Node *);
    Node *rightRotate(Node *);
    Node *leftRotate(Node *);
    Node *balance(Node *);
    void fixHeight(Node *node);

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
    int getSize() override { return size; }
    int getRotates() override { return countOfRotates; }
};


#endif //SIAOD_2_AVL_TREE_H
