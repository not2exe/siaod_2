//
// Created by da on 24.09.2022.
//
#include <fstream>
#include <set>
#include <vector>
#include "Schedule.h"

#ifndef SIAOD_2_FILESBIN_H
#define SIAOD_2_FILESBIN_H



class FilesBin {
public:
    static int createNewFile(string, int= 10, string = "second.txt");

    static int saveFromBinToText(string, string);

    static int readFile(string);

    static int getScheduleByNumber(int, string, Schedule &);

    static int deleteByKey(string, string);

    static int createFileWithScheduleForGroup(short, string, string= "");

    static int updateSchedule(string);

    static void makeNewAudience(char *);

    static void printOneSchedule(Schedule);

    static int deleteByPos(int pos, string nameBin);

    static int createBinFileFromArray(vector<Schedule>, string nameBin);

    static int getSize(string nameBin);
};


#endif //SIAOD_2_FILESBIN_H
