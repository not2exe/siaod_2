
#include "FilesFirst.h"
#include "FilesBin.h"

string inputName() {
    string nameNew;
    cout << "\nВведите имя файла: ";
    cin >> nameNew;
    return nameNew;
}

string inputNewName() {
    string nameNew;
    cout << "\nВведите имя нового файла: ";
    cin >> nameNew;
    return nameNew;
}

int main() {

    int choose = 1;
    while (choose != 0) {
        cout << "\nСоздать новый двоичный файл - 1"
                "\nПрочитать и вывести содержимое двоичного файла - 2"
                "\nДобавить запись в конец файла - 3"
                "\nПрочитать значение числа, указав его порядковый номер в файле, и вернуть его значение - 4"
                "\nОпределить количество чисел в файле - 5"
                "\nСоздать новый файл из значений исходного, размещая на каждой строке заданное количество чисел, кроме, возможно, последней, где должны разместиться оставшиеся числа - 6"
                "\nВыход - 0\n";
        cin >> choose;
        switch (choose) {
            case 0: {
                break;
            }
            case 1: {
                if (FilesBin::createNewFile(inputName(), inputNewName()) == 0) {
                    cout << "\nФайл успешно создан";
                };
                break;
            }
            case 2: {
                FilesBin::readFile(inputName());
                break;
            }
            case 3: {
                string tempString;
                cout << "\nВведите значение для ввода: ";
                cin >> tempString;
                FilesFirst::addAnyToFile(tempString, inputName());
                break;
            }
            case 4: {
                int tempAny;
                cout << "\nВведите значение для поиска: ";
                cin >> tempAny;
                FilesFirst::findNumber(tempAny, inputName());
                break;
            }
            case 5: {
                cout << "\nКол-во чисел в файле: " << FilesFirst::countOfNumbers(inputName());
                break;
            }
            case 6: {
                int x;
                cout << "\nВведите кол-во чисел на одной строке: ";
                cin >> x;
                FilesFirst::ex22(x, inputName(), inputNewName());
                break;
            }
            default:
                cout << "\nНедопустимое значение";
                break;
        }
    }
    return 0;
}
