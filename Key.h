//
// Created by da on 23.10.2022.
//

#ifndef SIAOD_2_KEY_H
#define SIAOD_2_KEY_H

#include "FilesBin.h"
#include "chrono"

struct Key {
    static const int keySize = 37;
    char key[keySize]{};

    bool operator==(Key key2) {
        for (int i = 0; i < keySize; i++) {
            if (key2.key[i] != key[i])return false;
        }
        return true;
    }

    bool operator<(Key key2) {
        for (int i = 0; i < keySize; i++) {
            if (key[i] > key2.key[i])return false;
            if (key[i] < key2.key[i])return true;
        }
        return key[keySize - 1] != key[keySize - 1];
    }

    bool operator>(Key key2) {
        for (int i = 0; i < keySize; i++) {
            if (key[i] < key2.key[i])return false;
            if (key[i] > key2.key[i])return true;
        }
        return key[keySize - 1] != key[keySize - 1];
    }
    void print() {
        for (char i: key) {
            cout << i;
        }
    }

    Key(char key2[keySize]) {
        for (int i = 0; i < keySize; i++) {
            key[i] = key2[i];
        }
    }
};

#endif //SIAOD_2_KEY_H
