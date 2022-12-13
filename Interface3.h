//
// Created by da on 06.11.2022.
//

#ifndef SIAOD_2_INTERFACE3_H
#define SIAOD_2_INTERFACE3_H

#include "FilesBin.h"
#include "HashTable.h"
#include "ControlFileThroughTree.h"
#include <random>

string input(string msg = "Введите имя двоичного файла") {
    string res;
    cout << msg << ": ";
    cin >> res;
    return res;
}

Schedule generateSchedule() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<> distribution(1, 1000000);
    Schedule schedule{};
    const string gen = "0123456789abcdef";
    string disciplineNames[3]{"Мат.анализ", "СИАОД", "Философия"};
    string typesOfLesson[3]{"Практика", "Лекция", "Лабораторная работа"};
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            schedule.key[i] = '-';
        } else {
            schedule.key[i] = gen[distribution(mt) % gen.size()];
        }
    }
    FilesBin::makeNewAudience(schedule.numberOfTheAudience);
    string randomDisc = disciplineNames[distribution(mt) % 3];
    for (int i = 0; i < randomDisc.size(); i++) {
        schedule.disciplineName[i] = randomDisc[i];
    }
    string typeOfLesson = typesOfLesson[distribution(mt) % 3];
    for (int i = 0; i < typeOfLesson.size(); i++) {
        schedule.typeOfLesson[i] = typeOfLesson[i];
    }
    schedule.dayOfTheWeek = distribution(mt) % 7 + 1;
    schedule.numberOfGroup = distribution(mt) % 1000 + 1;
    schedule.week = distribution(mt) % 4 + 1;
    schedule.classNumber = distribution(mt) % 7 + 1;
    return schedule;
}

vector<Schedule> getRandoms(int n) {
    vector<Schedule> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = generateSchedule();
    }
    return ans;
}

#endif //SIAOD_2_INTERFACE3_H

int interface3() {
    srand(NULL);
    int number,mode;
    string name = input();
    cout << "Введите количество записей: ";
    cin >> number;
    vector<Schedule> fileSchedules = getRandoms(number);
    FilesBin::createBinFileFromArray(fileSchedules, name);
    cout<<"Введите чем управлять, 1 - БДП, 2-... - Авл: ";
    cin>>mode;
    ControlFileThroughTree *controlFileThroughTable = new ControlFileThroughTree(name,mode);
    int choose = -1;
    while (choose != 0) {
        cout << "\nСменить имя двоичного файла и создать новую таблицу - 1"
                "\nПрочитать запись из файла и вставить элемент в таблицу - 2"
                "\nУдалить запись из таблицы при заданном значении ключа и соответственно из файла - 3"
                "\nНайти запись в файле по значению ключа - 4"
                "\nВывести содержимое двоичного файла - 5"
                "\nСоздать новый двоичный файл из тестовых значения - 6"
                "\nСоздать новый двоичный файл из случайных значений - 7"
                "\nВывести первую запись, по центру и в конце - 8\n";
        cin >> choose;
        char key[Key::keySize];
        Schedule schedule{};
        switch (choose) {
            case 1:
                cout<<"Введите чем управлять, 1 - БДП, 2-... - Авл: ";
                cin>>mode;
                controlFileThroughTable = new ControlFileThroughTree(input(),mode);
                break;
            case 2:
                int pos;
                cout << "\nВведите позицию элементов: ";
                cin >> pos;
                controlFileThroughTable->fromFileToTable(pos);
                break;
            case 3:
                cout << "\nВведите ключ: ";
                cin >> key;
                controlFileThroughTable->remove(key);
                break;
            case 4:
                cout << "\nВведите ключ: ";
                cin >> key;
                controlFileThroughTable->getFromFile(schedule, key);
                FilesBin::printOneSchedule(schedule);
                break;
            case 5:
                FilesBin::readFile(controlFileThroughTable->getFileName());
                break;
            case 6: {
                string name = input();
                FilesBin::createNewFile(name);
                controlFileThroughTable = new ControlFileThroughTree(name,mode);
                break;
            }
            case 7: {
                string name = input();
                int number;
                cout << "Введите количество записей: ";
                cin >> number;
                FilesBin::createBinFileFromArray(getRandoms(number), name);
                controlFileThroughTable = new ControlFileThroughTree(name,mode);
                break;
            }
            case 8:
                FilesBin::printOneSchedule(fileSchedules[0]);
                FilesBin::printOneSchedule(fileSchedules[fileSchedules.size() / 2]);
                FilesBin::printOneSchedule(fileSchedules[fileSchedules.size() - 1]);
                break;
        }
    }
    delete controlFileThroughTable;
    return 0;
}
