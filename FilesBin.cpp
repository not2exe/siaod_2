//
// Created by da on 24.09.2022.
//

#include "FilesBin.h"

using namespace std;


int FilesBin::createNewFile(string nameBin, int size, string nameText) {
    ifstream textFile(nameText);
    ofstream binFile(nameBin, ios::binary | ios::trunc);
    if (size > 10) {
        size = 10;
    }
    binFile.write(reinterpret_cast<char *>(&size), sizeof(int));
    if (!binFile.good() || !textFile.good()) return -1;
    Schedule schedule{};
    for (int i = 0; i < size; i++) {
        textFile.get();
        textFile.getline(schedule.key, sizeof(schedule.key), '\n');
        textFile.getline(schedule.disciplineName, sizeof(schedule.disciplineName), '\n');
        textFile.getline(schedule.typeOfLesson, sizeof(schedule.typeOfLesson), '\n');
        textFile.getline(schedule.numberOfTheAudience, sizeof(schedule.numberOfTheAudience), '\n');
        textFile >> schedule.numberOfGroup;
        textFile >> schedule.classNumber;
        textFile >> schedule.week;
        textFile >> schedule.dayOfTheWeek;
        binFile.write(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
    }

    textFile.clear();
    binFile.clear();
    textFile.close();
    binFile.close();
    return 0;
}

int FilesBin::readFile(string nameBin) {
    ifstream binFile(nameBin, ios::binary | ios::in);
    if (!binFile.good())return -1;

    int size;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    Schedule schedule{};
    for (int i = 0; i < size; i++) {
        binFile.read(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
        printOneSchedule(schedule);
    }
    binFile.clear();
    binFile.close();
    return 0;
}

int FilesBin::saveFromBinToText(string nameBin, string nameText) {
    ifstream binFile(nameBin, ios::binary | ios::in);
    ofstream textFile(nameText);
    Schedule schedule{};
    int size;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    if (!binFile.good() || !textFile.good()) return -1;
    for (int i = 0; i < size; i++) {
        binFile.read(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
        textFile << schedule.key << endl << schedule.disciplineName << endl << schedule.typeOfLesson << endl
                 << schedule.numberOfTheAudience << endl
                 << schedule.numberOfGroup << endl << schedule.classNumber << endl << schedule.week << endl
                 << schedule.dayOfTheWeek << endl;

    }
    textFile.clear();
    binFile.clear();
    textFile.close();
    binFile.close();
    return 0;
}

int FilesBin::getScheduleByNumber(int pos, string nameBin, Schedule &schedule) {

    ifstream binFile(nameBin, ios::binary | ios::in);
    int size;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    if (!binFile.good() || (pos > size) || (pos < 1))return -1;

    binFile.seekg(sizeof(Schedule) * (pos - 1) + sizeof(int), ios::beg);
    binFile.read(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
    binFile.clear();
    binFile.close();
    return 0;
}

int FilesBin::deleteByPos(int pos, string nameBin) {
    fstream binFile(nameBin, ios::binary | ios::out | ios::in);
    int size;
    Schedule last;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    if (!binFile.good() || (pos > size))return -1;
    binFile.seekg(sizeof(Schedule) * (size - 1) + sizeof(int), ios::beg);
    binFile.read(reinterpret_cast<char *>(&last), sizeof(Schedule));

    binFile.seekg(sizeof(Schedule) * (pos - 1) + sizeof(int), ios::beg);
    binFile.write(reinterpret_cast<char *>( &last), sizeof(Schedule));
    binFile.seekg(0, ios::beg);
    size--;
    binFile.write(reinterpret_cast<char *>( &size), sizeof(int));
    return 0;
}

int FilesBin::deleteByKey(string key, string nameBin) {
    fstream binFile(nameBin, ios::binary | ios::in | ios::out);
    if (!binFile.good())return -1;
    Schedule schedule{};
    int size;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    Schedule last{};
    getScheduleByNumber(size, nameBin, last);
    for (int i = 0; i < size; i++) {
        binFile.read(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
        if (schedule.key == key) {
            binFile.seekg(-sizeof(Schedule), ios::cur);
            binFile.write(reinterpret_cast<char *>( &last), sizeof(Schedule));
            binFile.seekg(0, ios::beg);
            size--;
            binFile.write(reinterpret_cast<char *>( &size), sizeof(int));
            return 0;
        }
    }

    binFile.clear();
    binFile.close();
    return -1;
}

int FilesBin::createFileWithScheduleForGroup(short group, string nameBin,
                                             string nameBinSchedule) {
    nameBinSchedule = nameBin + "ForGroup" + to_string(group);
    ifstream binFile(nameBin, ios::binary | ios::in);
    ofstream binGroupFile(nameBinSchedule, ios::binary | ios::out);

    vector<Schedule> arrayForNewFile;

    if (!binFile.good() || !binGroupFile.good())return -1;

    int size;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    Schedule schedule{};
    for (int i = 0; i < size; i++) {
        binFile.read(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
        if (schedule.numberOfGroup == group) {
            arrayForNewFile.push_back(schedule);
        }
    }

    int newSize = arrayForNewFile.size();
    binGroupFile.write(reinterpret_cast<char *>(&newSize), sizeof(int));
    for (Schedule scheduleTemp: arrayForNewFile) {
        binGroupFile.write(reinterpret_cast<char *>( &scheduleTemp), sizeof(Schedule));
    }

    binFile.clear();
    binFile.close();
    binGroupFile.clear();
    binGroupFile.close();
    cout << "Создан новый файл с названием: " << nameBinSchedule << endl;
    readFile(nameBinSchedule);
    return 0;
}

int FilesBin::updateSchedule(string nameBin) {
    fstream binFile(nameBin, ios::binary | ios::in | ios::out);
    if (!binFile.good())return -1;

    int size;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    Schedule schedule{};
    pair<int, string> pairTemp;
    set<pair<int, string>> setOfPair;
    int counter = 0;

    for (int i = 0; i < size; i++) {
        binFile.read(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
        pairTemp.first =
                schedule.classNumber + schedule.dayOfTheWeek * 100 +
                schedule.week * 10000;
        pairTemp.second = schedule.numberOfTheAudience;
        if (setOfPair.contains(pairTemp)) {
            while (setOfPair.contains(pairTemp)) {
                makeNewAudience(schedule.numberOfTheAudience);
                pairTemp.second = schedule.numberOfTheAudience;
            }
            binFile.seekg(-sizeof(Schedule), ios::cur);
            binFile.write(reinterpret_cast<char *>( &schedule), sizeof(Schedule));
            counter++;
        } else {
            setOfPair.insert(pairTemp);
        }
    }

    binFile.clear();
    binFile.close();
    cout << "\nОбновленное расписание, замен - " << counter << endl;
    readFile(nameBin);
    return 0;
}

void FilesBin::makeNewAudience(char *oldAudience) {
    oldAudience[0] = 'A' + rand() % 26;
    oldAudience[1] = '-';
    oldAudience[2] = '0' + rand() % 10;
    oldAudience[3] = '0' + rand() % 10;
    oldAudience[4] = '0' + rand() % 10;
}

void FilesBin::printOneSchedule(Schedule schedule) {
    cout << "\nКлюч : " << schedule.key
         << "\nГруппа : " << schedule.numberOfGroup
         << "\nНаименование дисциплины: " << schedule.disciplineName
         << "\nНомер класса: " << schedule.classNumber
         << "\nНеделя месяца: " << schedule.week
         << "\nДень недели: " << schedule.dayOfTheWeek
         << "\nВид занятия: " << schedule.typeOfLesson
         << "\nНомер аудитории: " << schedule.numberOfTheAudience << endl;
}

int FilesBin::createBinFileFromArray(vector<Schedule> schedules, string nameBin) {
    ofstream binFile(nameBin, ios::binary | ios::trunc);
    if (!binFile.good())return -1;
    int size = schedules.size();
    binFile.write(reinterpret_cast<char *>(&size), sizeof(int));
    for (int i = 0; i < schedules.size(); i++) {
        binFile.write(reinterpret_cast<char *>( &schedules[i]), sizeof(Schedule));
    }
    binFile.clear();
    binFile.close();
    return 0;
}

int FilesBin::getSize(string nameBin) {
    ifstream binFile(nameBin, ios::binary | ios::in);
    if (!binFile.good())return -1;
    int size;
    binFile.read(reinterpret_cast<char *>(&size), sizeof(int));
    binFile.clear();
    binFile.close();
    return size;
}






