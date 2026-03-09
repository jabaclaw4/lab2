#include <iostream>
#include "../src/ArraySequence.h"

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
    cout << "=== тесты ArraySequence ===" << endl;

    //пустая
    Sequence<int>* seq1 = new ArraySequence<int>();
    check(seq1->GetLength() == 0, "пустая последовательность");
    delete seq1;

    //один элемент через append
    Sequence<int>* seq2 = new ArraySequence<int>();
    seq2->Append(42);
    check(seq2->GetLength() == 1, "один элемент: длина");
    check(seq2->GetFirst() == 42, "один элемент: first");
    check(seq2->GetLast() == 42, "один элемент: last");
    delete seq2;

    //экстремальные значения
    Sequence<int>* seq3 = new ArraySequence<int>();
    seq3->Append(-2147483648);
    seq3->Append(0);
    seq3->Append(2147483647);
    check(seq3->Get(0) == -2147483648, "int_min");
    check(seq3->Get(1) == 0, "ноль");
    check(seq3->Get(2) == 2147483647, "int_max");
    delete seq3;

    //prepend
    Sequence<int>* seq4 = new ArraySequence<int>();
    seq4->Prepend(1);
    seq4->Prepend(2);
    seq4->Prepend(3);
    check(seq4->GetFirst() == 3, "prepend: первый");
    check(seq4->GetLast() == 1, "prepend: последний");
    delete seq4;

    //insertAt позиция 0
    int data[] = {10, 20, 30};
    Sequence<int>* seq5 = new ArraySequence<int>(data, 3);
    seq5->InsertAt(99, 0);
    check(seq5->Get(0) == 99, "insertAt(0): вставлен");
    check(seq5->Get(1) == 10, "insertAt(0): сдвиг");
    delete seq5;

    //insertAt середина
    Sequence<int>* seq6 = new ArraySequence<int>(data, 3);
    seq6->InsertAt(99, 1);
    check(seq6->Get(0) == 10, "insertAt(1): элемент 0");
    check(seq6->Get(1) == 99, "insertAt(1): вставлен");
    check(seq6->Get(2) == 20, "insertAt(1): элемент 1 сдвинут");
    check(seq6->Get(3) == 30, "insertAt(1): элемент 2 сдвинут");
    delete seq6;

    //insertAt конец
    Sequence<int>* seq7 = new ArraySequence<int>(data, 3);
    seq7->InsertAt(99, 3);
    check(seq7->GetLast() == 99, "insertAt(end): вставлен");
    delete seq7;

    //getSubsequence
    int data2[] = {1, 2, 3, 4, 5};
    Sequence<int>* seq8 = new ArraySequence<int>(data2, 5);
    Sequence<int>* sub = seq8->GetSubsequence(1, 3);
    check(sub->GetLength() == 3, "getSubsequence: длина");
    check(sub->Get(0) == 2, "getSubsequence: первый");
    check(sub->Get(2) == 4, "getSubsequence: последний");
    delete seq8;
    delete sub;

    //concat
    Sequence<int>* seq9 = new ArraySequence<int>(data, 2);
    Sequence<int>* seq10 = new ArraySequence<int>(data + 2, 1);
    Sequence<int>* concat = seq9->Concat(seq10);
    check(concat->GetLength() == 3, "concat: длина");
    check(concat->Get(0) == 10, "concat: из первого");
    check(concat->Get(2) == 30, "concat: из второго");
    delete seq9;
    delete seq10;
    delete concat;

    cout << "\nитог: " << passed << " / " << total << " OK" << endl;
    return (passed == total) ? 0 : 1;
}