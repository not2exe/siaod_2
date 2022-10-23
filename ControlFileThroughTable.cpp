//
// Created by da on 20.10.2022.
//

#include "ControlFileThroughTable.h"

int ControlFileThroughTable::fromFileToTable(int pos) {
    Schedule schedule{};
    if (FilesBin::getScheduleByNumber(pos, fileName, schedule) != 0) {
        return -1;
    }

    hashTable.put(Key(schedule.key), pos);
    return 0;
}

int ControlFileThroughTable::remove(Key key) {
    auto begin = std::chrono::steady_clock::now();
    int pos = hashTable.get(key);
    if (pos == 0)return -2;
    if (!hashTable.remove(key))return -2;
    if (FilesBin::deleteByPos(pos, fileName) != 0)return -1;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    cout<<"Время выполнение операции: "<<elapsed_ms.count()<<endl;
    return 0;
}

int ControlFileThroughTable::getFromFile(Schedule &schedule, Key key) {
    auto begin = std::chrono::steady_clock::now();
    int pos = hashTable.get(key);
    if (pos == 0)return -2;
    if (FilesBin::getScheduleByNumber(pos, fileName, schedule) != 0)return -1;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    cout<<"Время выполнение операции: "<<elapsed_ms.count()<<endl;
    return 0;
}

ControlFileThroughTable::ControlFileThroughTable(string fileName) {
    this->fileName = fileName;
    int size = FilesBin::getSize(fileName);
    for (int i = 1; i <= size; i++) {
        fromFileToTable(i);
    }
}
