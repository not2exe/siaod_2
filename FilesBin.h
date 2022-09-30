//
// Created by da on 24.09.2022.
//
#include <iostream>
#include <fstream>

#ifndef SIAOD_2_FILESBIN_H
#define SIAOD_2_FILESBIN_H

using namespace std;

class FilesBin {
    struct schedule {
        char key[50];
        char numberOfGroup[3];
        char disciplineName[50];
        char classNumber[1];
        char week[2];
        char dayOfTheWeek[1];
        char typeOfLesson[50];
        char numberOfTheAudience[5];
    };
public:
    static int createNewFile(string, string);

    static int readFile(string);


};


#endif //SIAOD_2_FILESBIN_H
