#include <iostream>
#include "../src/DynamicArray.h"
#include "../src/test_utils.h"

using namespace std;


void run_test_dynamic_array() {
    cout << "=== тесты DynamicArray ===" << endl;

    //граничные значения
    DynamicArray<int>* arr1 = new DynamicArray<int>(0);
    check(arr1->GetSize() == 0, "размер 0");
    delete arr1;

    DynamicArray<int>* arr2 = new DynamicArray<int>(1);
    check(arr2->GetSize() == 1, "размер 1");
    delete arr2;

    DynamicArray<int>* arr3 = new DynamicArray<int>(10000);
    check(arr3->GetSize() == 10000, "большой размер");
    delete arr3;

    //экстремальные значения
    int extreme[] = {-2147483648, 0, 2147483647};  //int_min, 0, int_max
    DynamicArray<int>* arr4 = new DynamicArray<int>(extreme, 3);
    check(arr4->Get(0) == -2147483648, "int_min");
    check(arr4->Get(1) == 0, "ноль");
    check(arr4->Get(2) == 2147483647, "int_max");
    delete arr4;

    //set/get
    DynamicArray<int>* arr5 = new DynamicArray<int>(5);
    arr5->Set(0, 100);
    arr5->Set(4, 500);
    check(arr5->Get(0) == 100, "set/get первый");
    check(arr5->Get(4) == 500, "set/get последний");
    delete arr5;

    //resize вверх
    int data[] = {1, 2, 3};
    DynamicArray<int>* arr6 = new DynamicArray<int>(data, 3);
    arr6->Resize(5);
    check(arr6->GetSize() == 5, "resize вверх: размер");
    check(arr6->Get(0) == 1, "resize вверх: данные сохранены");
    check(arr6->Get(2) == 3, "resize вверх: последний старый");
    delete arr6;

    //resize вниз
    DynamicArray<int>* arr7 = new DynamicArray<int>(data, 3);
    arr7->Resize(1);
    check(arr7->GetSize() == 1, "resize вниз: размер");
    check(arr7->Get(0) == 1, "resize вниз: данные сохранены");
    delete arr7;

    //resize в 0
    DynamicArray<int>* arr8 = new DynamicArray<int>(data, 3);
    arr8->Resize(0);
    check(arr8->GetSize() == 0, "resize в 0");
    delete arr8;

    //копирование
    DynamicArray<int>* arr9 = new DynamicArray<int>(data, 3);
    DynamicArray<int>* arr10 = new DynamicArray<int>(*arr9);
    check(arr10->GetSize() == 3, "копирование: размер");
    check(arr10->Get(0) == 1, "копирование: данные");
    arr9->Set(0, 999);
    check(arr10->Get(0) == 1, "копирование: независимость");
    delete arr9;
    delete arr10;

    //исключения
    bool caught = false;
    try {
        DynamicArray<int>* arr11 = new DynamicArray<int>(3);
        arr11->Get(5);
    } catch (...) {
        caught = true;
    }
    check(caught, "исключение: выход за границы");

    caught = false;
    try {
        DynamicArray<int>* arr12 = new DynamicArray<int>(-1);
    } catch (...) {
        caught = true;
    }
    check(caught, "исключение: отрицательный размер");

    cout << "\nитог: " << passed << " / " << total << " OK" << endl;
}