//
// Created by da on 16.10.2022.
//
#include <list>
#include "Key.h"

#ifndef SIAOD_2_HASHTABLE_H
#define SIAOD_2_HASHTABLE_H



class HashTable {
    const int defaultSize = 8;
    const double rehashConst = 0.75;
    int collisions = 0;

    struct Node {
        int val;
        Key key;
        bool isDeleted;
        Node *next = nullptr;

        Node(int value, Key _key, Node *node) : val(value), key(_key), isDeleted(false), next(node) {}
    };

    Node **arr;
    int size;
    int bufferSize;
    int sizeWithDeleted;

    int hash(Key key, const int keySupport = 31);

    void resize();

    void rehash();

    void fillWithNullptr(Node **arr, int);

    void swapTables(Node **arrTemp, int pastSize);

public:
    HashTable();

    bool put(Key key, int val);

    bool remove(Key key);

    int get(Key key);

    int getCollisions() { return collisions; }

    ~HashTable();

};


#endif //SIAOD_2_HASHTABLE_H
