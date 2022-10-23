//
// Created by da on 20.10.2022.
//

#ifndef SIAOD_2_CONTROLFILETHROUGHTABLE_H
#define SIAOD_2_CONTROLFILETHROUGHTABLE_H

#include "HashTable.h"


class ControlFileThroughTable {
    string fileName;
    HashTable hashTable;
public:
    ControlFileThroughTable(string fileName);

    int fromFileToTable(int);

    int remove(Key);

    int getFromFile(Schedule &, Key);

    string getFileName() { return fileName; }

};


#endif //SIAOD_2_CONTROLFILETHROUGHTABLE_H
