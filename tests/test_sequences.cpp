#include <iostream>
#include "../src/ArraySequence.h"
#include "../src/ListSequence.h"

using namespace std;

int main() {
    cout << "=== тест ArraySequence ===" << endl;

    //создаём ArraySequence
    Sequence<int>* arr = new ArraySequence<int>();

    //добавляем элементы
    arr->Append(10);
    arr->Append(20);
    arr->Append(30);
    arr->Prepend(5);

    //выводим
    cout << "длина: " << arr->GetLength() << endl;  //4
    cout << "первый: " << arr->GetFirst() << endl;  //5
    cout << "последний: " << arr->GetLast() << endl;  //30

    cout << "элементы: ";
    for (int i = 0; i < arr->GetLength(); i++) {
        cout << arr->Get(i) << " ";  //5 10 20 30
    }
    cout << endl;

    delete arr;

    cout << endl << "=== тест ListSequence ===" << endl;

    //создаём ListSequence
    Sequence<int>* list = new ListSequence<int>();

    //добавляем элементы
    list->Append(100);
    list->Append(200);
    list->Append(300);
    list->Prepend(50);

    //выводим
    cout << "длина: " << list->GetLength() << endl;  //4
    cout << "первый: " << list->GetFirst() << endl;  //50
    cout << "последний: " << list->GetLast() << endl;  //300

    cout << "элементы: ";
    for (int i = 0; i < list->GetLength(); i++) {
        cout << list->Get(i) << " ";  //50 100 200 300
    }
    cout << endl;

    delete list;

    cout << endl << "=== тест полиморфизма ===" << endl;

    //функция работает с ЛЮБОЙ последовательностью!
    auto printSequence = [](Sequence<int>* seq, string name) {
        cout << name << ": ";
        for (int i = 0; i < seq->GetLength(); i++) {
            cout << seq->Get(i) << " ";
        }
        cout << endl;
    };

    Sequence<int>* arr2 = new ArraySequence<int>();
    arr2->Append(1);
    arr2->Append(2);
    arr2->Append(3);

    Sequence<int>* list2 = new ListSequence<int>();
    list2->Append(4);
    list2->Append(5);
    list2->Append(6);

    printSequence(arr2, "массив");  //массив: 1 2 3
    printSequence(list2, "список");  //список: 4 5 6

    delete arr2;
    delete list2;

    cout << endl << "=== все тесты пройдены! ===" << endl;

    return 0;
}