//
// Created by da on 20.10.2022.
//

#include "ControlFileThroughTree.h"

int ControlFileThroughTree::fromFileToTable(int pos) {
    Schedule schedule{};
    if (FilesBin::getScheduleByNumber(pos, fileName, schedule) != 0) {
        return -1;
    }

    tree->insert(Key(schedule.key), pos);
    return 0;
}

int ControlFileThroughTree::remove(Key key) {
    auto begin = std::chrono::steady_clock::now();
    int pos = tree->get(key);
    if (pos == 0)return -2;
    tree->remove(key);
    if (FilesBin::deleteByPos(pos, fileName) != 0)return -1;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    cout << "Время выполнение операции: " << elapsed_ms.count() << endl;
    return 0;
}

int ControlFileThroughTree::getFromFile(Schedule &schedule, Key key) {
    auto begin = std::chrono::steady_clock::now();
    int pos = tree->get(key);
    if (pos == 0)return -2;
    if (FilesBin::getScheduleByNumber(pos, fileName, schedule) != 0)return -1;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    cout << "Время выполнение операции: " << elapsed_ms.count() << endl;
    return 0;
}

ControlFileThroughTree::ControlFileThroughTree(string fileName, int mode) {
    if (mode == 1) {
        tree = new BinarySearchTree;
    } else {
        tree = new AVL_tree;
    }
    this->fileName = fileName;
    int size = FilesBin::getSize(fileName);
    for (int i = 1; i <= size; i++) {
        fromFileToTable(i);
    }
    cout << "Среднее количество поворотов " << (double)tree->getRotates() / (double)tree->getSize();
}

