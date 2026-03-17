#include <iostream>
#include "../src/LinkedList.h"

using namespace std;

int total = 0;
int passed = 0;

void check(bool condition, const char* name) {
    total++;
    if (condition) {
        passed++;
        cout << "OK";
    } else {
        cout << "FAIL";
    }
    cout << " - " << name << endl;
}

int test_linked_list_main() {
    cout << "=== тесты LinkedList ===" << endl;

    //пустой список
    LinkedList<int>* list1 = new LinkedList<int>();
    check(list1->GetLength() == 0, "пустой список");
    delete list1;

    //один элемент
    int one[] = {42};
    LinkedList<int>* list2 = new LinkedList<int>(one, 1);
    check(list2->GetLength() == 1, "один элемент: длина");
    check(list2->GetFirst() == 42, "один элемент: first");
    check(list2->GetLast() == 42, "один элемент: last");
    check(list2->Get(0) == 42, "один элемент: get(0)");
    delete list2;

    //экстремальные значения
    int extreme[] = {-2147483648, 0, 2147483647};
    LinkedList<int>* list3 = new LinkedList<int>(extreme, 3);
    check(list3->GetFirst() == -2147483648, "int_min");
    check(list3->Get(1) == 0, "ноль");
    check(list3->GetLast() == 2147483647, "int_max");
    delete list3;

    //append к пустому
    LinkedList<int>* list4 = new LinkedList<int>();
    list4->Append(10);
    check(list4->GetLength() == 1, "append к пустому: длина");
    check(list4->GetFirst() == 10, "append к пустому: элемент");
    check(list4->GetLast() == 10, "append к пустому: first=last");
    delete list4;

    //prepend к пустому
    LinkedList<int>* list5 = new LinkedList<int>();
    list5->Prepend(20);
    check(list5->GetLength() == 1, "prepend к пустому: длина");
    check(list5->GetFirst() == 20, "prepend к пустому: элемент");
    delete list5;

    //append несколько
    LinkedList<int>* list6 = new LinkedList<int>();
    list6->Append(1);
    list6->Append(2);
    list6->Append(3);
    check(list6->GetLength() == 3, "append x3: длина");
    check(list6->Get(0) == 1, "append x3: первый");
    check(list6->Get(2) == 3, "append x3: последний");
    delete list6;

    //prepend несколько
    LinkedList<int>* list7 = new LinkedList<int>();
    list7->Prepend(1);
    list7->Prepend(2);
    list7->Prepend(3);
    check(list7->Get(0) == 3, "prepend x3: обратный порядок");
    delete list7;

    //insertAt позиция 0
    int data[] = {10, 20, 30};
    LinkedList<int>* list8 = new LinkedList<int>(data, 3);
    list8->InsertAt(99, 0);
    check(list8->GetFirst() == 99, "insertAt(0): новый первый");
    check(list8->Get(1) == 10, "insertAt(0): сдвиг");
    check(list8->GetLength() == 4, "insertAt(0): длина");
    delete list8;

    //insertAt середина
    LinkedList<int>* list9 = new LinkedList<int>(data, 3);
    list9->InsertAt(99, 1);
    check(list9->Get(0) == 10, "insertAt(1): элемент 0");
    check(list9->Get(1) == 99, "insertAt(1): вставлен");
    check(list9->Get(2) == 20, "insertAt(1): сдвиг");
    check(list9->GetLength() == 4, "insertAt(1): длина");
    delete list9;

    //insertAt конец
    LinkedList<int>* list10 = new LinkedList<int>(data, 3);
    list10->InsertAt(99, 3);
    check(list10->GetLast() == 99, "insertAt(end): новый последний");
    check(list10->GetLength() == 4, "insertAt(end): длина");
    delete list10;

    //getSubList
    int data2[] = {1, 2, 3, 4, 5};
    LinkedList<int>* list11 = new LinkedList<int>(data2, 5);
    LinkedList<int>* sub = list11->GetSubList(1, 3);
    check(sub->GetLength() == 3, "getSubList: длина");
    check(sub->Get(0) == 2, "getSubList: первый");
    check(sub->Get(2) == 4, "getSubList: последний");
    delete list11;
    delete sub;

    //concat
    LinkedList<int>* list12 = new LinkedList<int>(data, 2);
    LinkedList<int>* list13 = new LinkedList<int>(data + 2, 1);
    LinkedList<int>* result = list12->Concat(list13);
    check(result->GetLength() == 3, "concat: длина");
    check(result->Get(0) == 10, "concat: из первого");
    check(result->Get(2) == 30, "concat: из второго");
    delete list12;
    delete list13;
    delete result;

    //копирование
    LinkedList<int>* list14 = new LinkedList<int>(data, 3);
    LinkedList<int>* list15 = new LinkedList<int>(*list14);
    check(list15->GetLength() == 3, "копирование: длина");
    check(list15->Get(0) == 10, "копирование: данные");
    delete list14;
    delete list15;

    //исключения
    bool caught = false;
    try {
        LinkedList<int>* list16 = new LinkedList<int>();
        list16->GetFirst();
    } catch (...) {
        caught = true;
    }
    check(caught, "исключение: getFirst на пустом");

    cout << "\nитог: " << passed << " / " << total << " OK" << endl;
    return (passed == total) ? 0 : 1;
}