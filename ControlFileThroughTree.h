//
// Created by da on 20.10.2022.
//

#ifndef SIAOD_2_CONTROLFILETHROUGHTREE_H
#define SIAOD_2_CONTROLFILETHROUGHTREE_H

#include "AbstractStruct.h"
#include "BinarySearchTree.h"
#include "AVL_tree.h"

class ControlFileThroughTree {
    string fileName;
    Abstract *tree;
public:
    ControlFileThroughTree(string fileName, int);

    int fromFileToTable(int);

    int remove(Key);

    int getFromFile(Schedule &, Key);

    string getFileName() { return fileName; }

};


#endif //SIAOD_2_CONTROLFILETHROUGHTREE_H
