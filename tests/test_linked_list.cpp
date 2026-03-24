#include <iostream>
#include "../src/LinkedList.h"
#include "../src/test_utils.h"

using namespace std;

void run_test_linked_list() {
    reset_counters();

    cout << "=== LinkedList Tests ===" << endl;

    //пустой список
    LinkedList<int>* list1 = new LinkedList<int>();
    check(list1->GetLength() == 0, "empty list");
    delete list1;

    //один элемент
    int one[] = {42};
    LinkedList<int>* list2 = new LinkedList<int>(one, 1);
    check(list2->GetLength() == 1, "single: length");
    check(list2->GetFirst() == 42, "single: first");
    check(list2->GetLast() == 42, "single: last");
    check(list2->Get(0) == 42, "single: get(0)");
    delete list2;

    //экстремальные значения
    int extreme[] = {-2147483648, 0, 2147483647};
    LinkedList<int>* list3 = new LinkedList<int>(extreme, 3);
    check(list3->GetFirst() == -2147483648, "int_min");
    check(list3->Get(1) == 0, "zero");
    check(list3->GetLast() == 2147483647, "int_max");
    delete list3;

    //append к пустому
    LinkedList<int>* list4 = new LinkedList<int>();
    list4->Append(10);
    check(list4->GetLength() == 1, "append to empty: length");
    check(list4->GetFirst() == 10, "append to empty: element");
    check(list4->GetLast() == 10, "append to empty: first=last");
    delete list4;

    //prepend к пустому
    LinkedList<int>* list5 = new LinkedList<int>();
    list5->Prepend(20);
    check(list5->GetLength() == 1, "prepend to empty: length");
    check(list5->GetFirst() == 20, "prepend to empty: element");
    delete list5;

    //append несколько
    LinkedList<int>* list6 = new LinkedList<int>();
    list6->Append(1);
    list6->Append(2);
    list6->Append(3);
    check(list6->GetLength() == 3, "append x3: length");
    check(list6->Get(0) == 1, "append x3: first");
    check(list6->Get(2) == 3, "append x3: last");
    delete list6;

    //prepend несколько
    LinkedList<int>* list7 = new LinkedList<int>();
    list7->Prepend(1);
    list7->Prepend(2);
    list7->Prepend(3);
    check(list7->Get(0) == 3, "prepend x3: reverse order");
    delete list7;

    //insertAt позиция 0
    int data[] = {10, 20, 30};
    LinkedList<int>* list8 = new LinkedList<int>(data, 3);
    list8->InsertAt(99, 0);
    check(list8->GetFirst() == 99, "insertAt(0): new first");
    check(list8->Get(1) == 10, "insertAt(0): shift");
    check(list8->GetLength() == 4, "insertAt(0): length");
    delete list8;

    //insertAt середина
    LinkedList<int>* list9 = new LinkedList<int>(data, 3);
    list9->InsertAt(99, 1);
    check(list9->Get(0) == 10, "insertAt(1): element 0");
    check(list9->Get(1) == 99, "insertAt(1): inserted");
    check(list9->Get(2) == 20, "insertAt(1): shift");
    check(list9->GetLength() == 4, "insertAt(1): length");
    delete list9;

    //insertAt конец
    LinkedList<int>* list10 = new LinkedList<int>(data, 3);
    list10->InsertAt(99, 3);
    check(list10->GetLast() == 99, "insertAt(end): new last");
    check(list10->GetLength() == 4, "insertAt(end): length");
    delete list10;

    //getSubList
    int data2[] = {1, 2, 3, 4, 5};
    LinkedList<int>* list11 = new LinkedList<int>(data2, 5);
    LinkedList<int>* sub = list11->GetSubList(1, 3);
    check(sub->GetLength() == 3, "getSubList: length");
    check(sub->Get(0) == 2, "getSubList: first");
    check(sub->Get(2) == 4, "getSubList: last");
    delete list11;
    delete sub;

    //concat
    LinkedList<int>* list12 = new LinkedList<int>(data, 2);
    LinkedList<int>* list13 = new LinkedList<int>(data + 2, 1);
    LinkedList<int>* result = list12->Concat(list13);
    check(result->GetLength() == 3, "concat: length");
    check(result->Get(0) == 10, "concat: from first");
    check(result->Get(2) == 30, "concat: from second");
    delete list12;
    delete list13;
    delete result;

    //копирование
    LinkedList<int>* list14 = new LinkedList<int>(data, 3);
    LinkedList<int>* list15 = new LinkedList<int>(*list14);
    check(list15->GetLength() == 3, "copy: length");
    check(list15->Get(0) == 10, "copy: data");
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
    check(caught, "exception: getFirst on empty");

    print_results();
}