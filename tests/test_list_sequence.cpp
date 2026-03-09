#include <iostream>
#include "../src/ListSequence.h"

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
    cout << "=== тесты ListSequence ===" << endl;

    //пустая
    Sequence<int>* seq1 = new ListSequence<int>();
    check(seq1->GetLength() == 0, "пустая последовательность");
    delete seq1;

    //append
    Sequence<int>* seq2 = new ListSequence<int>();
    seq2->Append(10);
    seq2->Append(20);
    check(seq2->GetLength() == 2, "append: длина");
    check(seq2->GetFirst() == 10, "append: первый");
    check(seq2->GetLast() == 20, "append: последний");
    delete seq2;

    //prepend
    Sequence<int>* seq3 = new ListSequence<int>();
    seq3->Prepend(1);
    seq3->Prepend(2);
    check(seq3->GetFirst() == 2, "prepend: первый");
    delete seq3;

    //insertAt
    int data[] = {10, 20, 30};
    Sequence<int>* seq4 = new ListSequence<int>(data, 3);
    seq4->InsertAt(99, 1);
    check(seq4->Get(1) == 99, "insertAt: вставлен");
    check(seq4->GetLength() == 4, "insertAt: длина");
    delete seq4;

    cout << "\nитог: " << passed << " / " << total << " OK" << endl;
    return (passed == total) ? 0 : 1;
}