//
// Created by da on 16.10.2022.
//

#include "HashTable.h"


int HashTable::hash(Key key, const int keySupport) {
    int hash_result = 0;
    for (char i: key.key) {
        hash_result = (keySupport * hash_result + i) % bufferSize;
    }
    hash_result = (hash_result * 2 + 1) % bufferSize;
    return hash_result;
}


bool HashTable::put(Key key, int val) {
    if (size + 1 > int(rehashConst * bufferSize)) {
        resize();
        cout << "\nTable is resized\n";//Вывод для тестов
    } else if (sizeWithDeleted > 2 * size) {
        rehash();
        cout << "\nTable is rehashed\n";//Вывод для тестов
    }
    int hashCode = hash(key);

    Node *slow = arr[hashCode];
    Node *fast = slow == nullptr ? nullptr : slow->next;

    while (fast != nullptr) {
        if (fast->isDeleted) {
            fast = new Node(val, key, fast->next);
            slow->next = fast;
            size++;
            return true;
        } else if (fast->val == val) {
            return false;
        }
        slow = slow->next;
        fast = fast->next;
    }
    if (slow == nullptr) {
        arr[hashCode] = new Node(val, key, nullptr);
    } else {
        fast = new Node(val, key, nullptr);
        collisions++;
        slow->next = fast;
    }
    size++;
    sizeWithDeleted++;
    return true;
}

void HashTable::resize() {
    int pastBufferSize = bufferSize; // Нужно запомнить для обхода по старой таблице
    bufferSize <<= 1;
    swapTables(new Node *[bufferSize], pastBufferSize);
}


void HashTable::rehash() {
    swapTables(new Node *[bufferSize], bufferSize);
}

void HashTable::swapTables(Node **arrTemp, int pastSize) {
    sizeWithDeleted = 0;
    size = 0;
    fillWithNullptr(arrTemp, bufferSize);
    swap(arr, arrTemp);
    for (int i = 0; i < pastSize; ++i) {
        Node *node = arrTemp[i];
        while (node != nullptr) {
            if (!node->isDeleted) {
                put(node->key, node->val);
            }
            node = node->next;
        }
    }

    for (int i = 0; i < pastSize; ++i) {
        if (arrTemp[i]) {
            delete arrTemp[i];
        }
    }
    delete[] arrTemp;
}

void HashTable::fillWithNullptr(Node **arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = nullptr;
    }
}

bool HashTable::remove(Key key) {
    Node *node = arr[hash(key)];
    if (node == nullptr)return false;
    while (node != nullptr) {
        if (node->key == key) {
            if (!node->isDeleted) {
                node->isDeleted = true;
                size--;
                return true;
            };
            return false;
        }
        node = node->next;
    }
    return false;
}


int HashTable::get(Key key) {
    int hashCode = hash(key);
    Node *node = arr[hashCode];
    if (node == nullptr)return 0;
    while (node != nullptr) {
        if (node->key == key && !(node->isDeleted)) {
            return node->val;
        }
        node = node->next;
    }
    return 0;
}

HashTable::~HashTable() {
    for (int i = 0; i < bufferSize; ++i) {
        if (arr[i])
            delete arr[i];
    }
    delete[] arr;
}

HashTable::HashTable() {
    bufferSize = defaultSize;
    size = 0;
    sizeWithDeleted = 0;
    arr = new Node *[bufferSize];
    fillWithNullptr(arr,bufferSize);
}
