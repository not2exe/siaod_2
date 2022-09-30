//
// Created by da on 24.09.2022.
//

#include "FilesBin.h"

using namespace std;


int FilesBin::createNewFile(string copyFrom, string nameNew) {
    ifstream textFile(copyFrom);
    ofstream binFile(nameNew, ios::binary);

    if (!binFile || !textFile) return -1;

    schedule schedule{};
    while (!textFile.getline(schedule.key,50,'\n')) {
        textFile.getline(schedule.numberOfGroup,3,'\n');
        textFile.getline(schedule.disciplineName,50,'\n');
        textFile.getline(schedule.classNumber,1,'\n');
        textFile.getline(schedule.week,2,'\n');
        textFile.getline(schedule.dayOfTheWeek,1,'\n');
        textFile.getline(schedule.typeOfLesson,50,'\n');
        textFile.getline(schedule.numberOfTheAudience,5,'\n');

        binFile.write((char *) &schedule, sizeof(schedule));
    }
    textFile.clear();
    binFile.clear();
    if (!textFile.good() || !binFile.good())return -1;

    textFile.close();
    binFile.close();
    return 0;
}

int FilesBin::readFile(string nameBin) {
    ifstream binFile(nameBin, ios::binary);
    if (!binFile)return -1;

    schedule schedule;
    while (!binFile.eof()) {
        binFile.read((char *) &schedule, sizeof(schedule));
        cout << schedule.key
             << "\nГруппа : " << schedule.numberOfGroup
             << "\nНаименование дисциплины: " << schedule.disciplineName
             << "\nНомер класса: " << schedule.classNumber
             << "\nНеделя месяца: " << schedule.week
             << "\nДень недели: " << schedule.dayOfTheWeek
             << "\nВид занятия: " << schedule.typeOfLesson
             << "\nНомер аудитории: " << schedule.numberOfTheAudience;
    }
    binFile.clear();
    if (!binFile.good())return -1;

    binFile.close();
    return 0;
}



//int writeToTF(string nameBin, string nameTF) {
//    fstream obf(nameBin, ios::in | ios::binary);
//    ofstream otf(nameTF, ios::app);
//    if (obf.is_open()) {
//        if (otf) {
//            record r;
//            obf.read((char *) &r, sizeof(record));
//            while (!obf.eof()) {
//                otf << r.key << ' ' << r.data << '\n';
//                obf.read((char *) &r, sizeof(record));
//            }
//            obf.close();
//            otf.close();
//            return 0;
//        } else { return -1; }
//    }
//    return -2;
//}
//
//int SearchBin(string nameBin, int FindKey) {
//    ifstream obf(nameBin, ios::in | ios::binary);
//    if (!obf) return -1;
//    record r;
//    int i;
//    obf.read((char *) &r, sizeof(record));
//    while (!obf.eof()) {
//        if (FindKey == r.key) {
//            obf.close();
//            return i;
//        }
//        obf.read((char *) &r, sizeof(record));
//        i++;
//    }
//    obf.close();
//    return -2;
//}
//
//int delByKey(string nameBin, int Key) {
//    fstream obf(nameBin, ios::binary | ios::in);
//    string BB = "BB.dat"; // Буферный файл
//    record RR; // Буферная структура с последней строкой
//    int keyBuff; //
//    char dataBuff[50]; // Элементы последней строки
//
//    if (obf.is_open()) { // Сохранение последних элементов
//        ofstream obfBuff(BB, ios::binary | ios::out); // Буферный файл
//        record r;
//        obf.read((char *) &r, sizeof(record));
//        while (!obf.eof()) {
//            for (int i = 0; i < 50; i++) { RR.data[i] = r.data[i]; } // Запись последней строки
//            RR.key = r.key; // -||-
//
//            obfBuff.write((char *) &r, sizeof(record)); // Записываю всё в буфер
//            obf.read((char *) &r, sizeof(record));
//        }
//        obfBuff.close();
//        obf.close();
//        //remove(BB.c_str());
//    } else { return -1; }
//
//    remove(nameBin.c_str()); // Удаляю файл
//    //cout<<"\n"<<RR.key<<endl;
//
//    ofstream obf2(nameBin, ios::out | ios::binary); // Создаю заново
//    fstream obfBuff2(BB, ios::in | ios::binary); // Читаю буферный файл
//    if (obfBuff2.is_open()) {
//        record r2;
//
//        obfBuff2.read((char *) &r2, sizeof(record)); // Читаю буфер
//        while (!obfBuff2.eof()) {
//            if (r2.key != Key) { obf2.write((char *) &r2, sizeof(record)); } // Key - это то что мне не надо записывать
//                // соответственно у чего остальные ключи, записываются
//            else { obf2.write((char *) &RR, sizeof(record)); } // на место удалённого ключа ставлю последнюю строку
//            obfBuff2.read((char *) &r2, sizeof(record)); //читаю дальше
//        }
//        obfBuff2.close();
//        obf2.close();
//        remove(BB.c_str()); // удаляю буфер
//    }
//    return 0;
//}
