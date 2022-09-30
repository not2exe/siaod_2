#ifndef SIAOD_2_FILESFIRST_H
#define SIAOD_2_FILESFIRST_H
#include <iostream>
#include <fstream>
using namespace std;

class FilesFirst {
public:
    static int readFile(string name);

    static int addAnyToFile(string newAny,string name);

    static int countOfNumbers(string name);

    static int findNumber(int number,string name) ;

    static int ex22(int countForOneString,string name, string newFileName);

    static int createNewFile(string name,int mode);
};


#endif