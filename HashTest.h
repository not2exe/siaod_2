//
// Created by da on 22.10.2022.
//
#include "HashTable.h"
#include "vector"

#ifndef SIAOD_2_HASHTEST_H
#define SIAOD_2_HASHTEST_H


int testHashT(vector<Schedule> schedules) {
    HashTable hashTable;
    for (int i = 0; i < schedules.size(); i++) {
        hashTable.put(schedules[i].key, i);
    }
    hashTable.remove(schedules[1].key);
    cout << hashTable.get(schedules[1].key) << endl;
    cout << hashTable.get(schedules[2].key) << endl;
    hashTable.remove(schedules[20].key);
    cout << hashTable.get(schedules[20].key) << endl;
    cout << hashTable.get(schedules[99].key)<<endl;
    cout<<"Кол-во коллизий "<<hashTable.getCollisions()<<endl;
    return 0;
}



#endif //SIAOD_2_HASHTEST_H
