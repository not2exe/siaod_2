//
// Created by da on 06.11.2022.
//

#ifndef SIAOD_2_SCHEDULE_H
#define SIAOD_2_SCHEDULE_H

#include <iostream>
using namespace std;
struct Schedule {
    char key[37];
    char disciplineName[50];
    char typeOfLesson[50];
    char numberOfTheAudience[50];
    short numberOfGroup;
    short classNumber;
    short week;
    short dayOfTheWeek;
};
#endif //SIAOD_2_SCHEDULE_H
