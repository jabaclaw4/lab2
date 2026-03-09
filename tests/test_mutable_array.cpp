#include <iostream>
#include "../src/MutableArraySequence.h"
#include "../src/ImmutableArraySequence.h"

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

int main() {
    cout << "=== тесты MutableArraySequence ===" << endl;

    //пустая последовательность
    MutableArraySequence<int>* seq1 = new MutableArraySequence<int>();
    check(seq1->GetLength() == 0, "пустая: length = 0");
    delete seq1;

    //создание из массива
    int data[] = {10, 20, 30};
    MutableArraySequence<int>* seq2 = new MutableArraySequence<int>(data, 3);
    check(seq2->GetLength() == 3, "из массива: length = 3");
    check(seq2->Get(0) == 10, "из массива: первый элемент");
    check(seq2->Get(2) == 30, "из массива: последний элемент");
    delete seq2;

    //append
    MutableArraySequence<int>* seq3 = new MutableArraySequence<int>();
    seq3->Append(10);
    seq3->Append(20);
    check(seq3->GetLength() == 2, "append: length = 2");
    check(seq3->GetFirst() == 10, "append: первый");
    check(seq3->GetLast() == 20, "append: последний");
    delete seq3;

    //prepend
    MutableArraySequence<int>* seq4 = new MutableArraySequence<int>();
    seq4->Prepend(10);
    seq4->Prepend(20);
    seq4->Prepend(30);
    check(seq4->GetFirst() == 30, "prepend: первый = 30");
    check(seq4->Get(1) == 20, "prepend: средний = 20");
    check(seq4->GetLast() == 10, "prepend: последний = 10");
    delete seq4;

    //insertAt в начало
    MutableArraySequence<int>* seq5 = new MutableArraySequence<int>(data, 3);
    seq5->InsertAt(99, 0);
    check(seq5->Get(0) == 99, "insertAt(0): вставлен");
    check(seq5->Get(1) == 10, "insertAt(0): сдвиг");
    check(seq5->GetLength() == 4, "insertAt(0): length");
    delete seq5;

    //insertAt в середину
    MutableArraySequence<int>* seq6 = new MutableArraySequence<int>(data, 3);
    seq6->InsertAt(99, 1);
    check(seq6->Get(0) == 10, "insertAt(1): элемент 0");
    check(seq6->Get(1) == 99, "insertAt(1): вставлен");
    check(seq6->Get(2) == 20, "insertAt(1): сдвиг");
    delete seq6;

    //insertAt в конец
    MutableArraySequence<int>* seq7 = new MutableArraySequence<int>(data, 3);
    seq7->InsertAt(99, 3);
    check(seq7->GetLast() == 99, "insertAt(end): вставлен");
    check(seq7->GetLength() == 4, "insertAt(end): length");
    delete seq7;

    //getSubsequence
    int data2[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int>* seq8 = new MutableArraySequence<int>(data2, 5);
    Sequence<int>* sub = seq8->GetSubsequence(1, 3);
    check(sub->GetLength() == 3, "getSubsequence: length");
    check(sub->Get(0) == 2, "getSubsequence: первый");
    check(sub->Get(2) == 4, "getSubsequence: последний");
    delete seq8;
    delete sub;

    //concat
    MutableArraySequence<int>* seq9 = new MutableArraySequence<int>(data, 2);
    MutableArraySequence<int>* seq10 = new MutableArraySequence<int>(data + 2, 1);
    Sequence<int>* concat = seq9->Concat(seq10);
    check(concat->GetLength() == 3, "concat: length");
    check(concat->Get(0) == 10, "concat: из первого");
    check(concat->Get(2) == 30, "concat: из второго");
    delete seq9;
    delete seq10;
    delete concat;

    //экстремальные значения
    MutableArraySequence<int>* seq11 = new MutableArraySequence<int>();
    seq11->Append(-2147483648);
    seq11->Append(0);
    seq11->Append(2147483647);
    check(seq11->Get(0) == -2147483648, "экстремум: int_min");
    check(seq11->Get(1) == 0, "экстремум: ноль");
    check(seq11->Get(2) == 2147483647, "экстремум: int_max");
    delete seq11;

    //копирование
    MutableArraySequence<int>* seq12 = new MutableArraySequence<int>(data, 3);
    MutableArraySequence<int>* seq13 = new MutableArraySequence<int>(*seq12);
    check(seq13->GetLength() == 3, "копирование: length");
    check(seq13->Get(0) == 10, "копирование: данные");
    delete seq12;
    delete seq13;

    cout << "\n=== тесты ImmutableArraySequence ===" << endl;

    //пустая
    ImmutableArraySequence<int>* imm1 = new ImmutableArraySequence<int>();
    check(imm1->GetLength() == 0, "immutable пустая: length = 0");
    delete imm1;

    //append
    ImmutableArraySequence<int>* imm2 = new ImmutableArraySequence<int>();
    imm2->Append(10);
    imm2->Append(20);
    check(imm2->GetLength() == 2, "immutable append: length");
    check(imm2->GetFirst() == 10, "immutable append: первый");
    check(imm2->GetLast() == 20, "immutable append: последний");
    delete imm2;

    //prepend
    ImmutableArraySequence<int>* imm3 = new ImmutableArraySequence<int>();
    imm3->Prepend(10);
    imm3->Prepend(20);
    check(imm3->GetFirst() == 20, "immutable prepend: первый");
    check(imm3->GetLast() == 10, "immutable prepend: последний");
    delete imm3;

    //insertAt
    ImmutableArraySequence<int>* imm4 = new ImmutableArraySequence<int>(data, 3);
    imm4->InsertAt(99, 1);
    check(imm4->Get(1) == 99, "immutable insertAt: вставлен");
    check(imm4->GetLength() == 4, "immutable insertAt: length");
    delete imm4;

    cout << "\nитог: " << passed << " / " << total << " OK" << endl;
    return (passed == total) ? 0 : 1;
}