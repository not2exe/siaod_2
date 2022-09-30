
#include "FilesFirst.h"

int FilesFirst::createNewFile(string name, int mode) {
    int temp;
    ofstream newFile(name);
    if (!newFile)return -1;
    if (mode == 1) {
        srand(time(NULL));
        for (int i = 0; i < 100; i++) {
            newFile << rand() % 100 << " ";
        }

    } else if (mode == 0) {
        ifstream testFile("first.txt");
        if (!testFile)return -1;
        while (!testFile.eof()) {
            testFile >> temp;
            newFile << temp << " ";
        }
        testFile.clear();
        if (!testFile.good())return -2;
        testFile.close();

    }

    newFile.clear();
    if (!newFile.good())return -2;
    newFile.close();
    return 0;
}

int FilesFirst::readFile(string name) {
    ifstream readFile(name);
    string line;

    if (!readFile) return -1;

    while (getline(readFile, line)) {
        cout << line << endl;
    }

    readFile.clear();
    if (!readFile.good())return -2;
    readFile.close();

    return 0;
}

int FilesFirst::addAnyToFile(string newAny, string name) {
    ofstream file(name, ios::app);
    if (!file)return -1;
    file << newAny << " ";
    file.clear();
    if (file.good()) {
        file.close();
    }
    if (!file.good())return -2;
    file.close();

    return 0;
}

int FilesFirst::countOfNumbers(string name) {
    int counter = 0, x;
    ifstream readFile(name);

    if (!readFile) return -1;

    while (!readFile.eof()) {
        readFile >> x;
        counter++;
    }
    readFile.clear();
    if (!readFile.good())return -2;
    readFile.close();

    return counter-1;
}

int FilesFirst::findNumber(int number, string name) {
    int counter = 0, x;
    ifstream readFile(name);

    if (!readFile) return -1;

    while (!readFile.eof()) {
        readFile >> x;
        counter++;
        if (x == number) {
            cout << "Номер числа: " << counter;
            if (!readFile.good())return -2;
            readFile.close();
            return number;
        }
    }
    readFile.clear();
    if (!readFile.good())return -2;
    readFile.close();

    return -1;
}

int FilesFirst::ex22(int countForOneString, string name, string newFileName) {
    if (countForOneString < 1)cout << "Некорректное значение\n";
    ifstream readFile(name);
    ofstream newFile(newFileName);

    int x = 0, temp;
    while (!readFile.eof()) {
        x++;
        readFile >> temp;
        newFile << temp << " ";
        if (x == countForOneString) {
            x = 0;
            newFile << "\n";
        }
    }
    readFile.clear();
    newFile.clear();
    if (!readFile.good() || !newFile.good())return -2;
    readFile.close();
    newFile.close();

    return -1;
}
