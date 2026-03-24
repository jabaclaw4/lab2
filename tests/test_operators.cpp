#include <iostream>
#include <sstream>
#include <cassert>
#include "../src/MutableArraySequence.h"
#include "../src/test_utils.h"

using namespace std;

void test_operator_bracket() {
    Sequence<int>* seq = new MutableArraySequence<int>();
    seq = seq->Append(10);
    seq = seq->Append(20);
    seq = seq->Append(30);

    check((*seq)[0] == 10, "operator[]: index 0");
    check((*seq)[1] == 20, "operator[]: index 1");
    check((*seq)[2] == 30, "operator[]: index 2");

    delete seq;
}

void test_operator_equals() {
    Sequence<int>* seq1 = new MutableArraySequence<int>();
    seq1 = seq1->Append(1)->Append(2)->Append(3);

    Sequence<int>* seq2 = new MutableArraySequence<int>();
    seq2 = seq2->Append(1)->Append(2)->Append(3);

    Sequence<int>* seq3 = new MutableArraySequence<int>();
    seq3 = seq3->Append(1)->Append(2)->Append(4);

    check(*seq1 == *seq2, "operator==: equal sequences");
    check(*seq1 != *seq3, "operator!=: different sequences");

    delete seq1;
    delete seq2;
    delete seq3;
}

void test_operator_plus() {
    Sequence<int>* seq1 = new MutableArraySequence<int>();
    seq1 = seq1->Append(1)->Append(2);

    Sequence<int>* seq2 = new MutableArraySequence<int>();
    seq2 = seq2->Append(3)->Append(4);

    Sequence<int>* result = *seq1 + *seq2;

    check(result->GetLength() == 4, "operator+: length");
    check((*result)[0] == 1, "operator+: element 0");
    check((*result)[1] == 2, "operator+: element 1");
    check((*result)[2] == 3, "operator+: element 2");
    check((*result)[3] == 4, "operator+: element 3");

    delete seq1;
    delete seq2;
    delete result;
}

void test_operator_output() {
    Sequence<int>* seq = new MutableArraySequence<int>();
    seq = seq->Append(1)->Append(2)->Append(3);

    stringstream ss;
    ss << *seq;

    check(ss.str() == "[1, 2, 3]", "operator<<: output format");

    delete seq;
}

void run_test_operators() {
    reset_counters();

    cout << "=== Operator Tests ===" << endl;

    test_operator_bracket();
    test_operator_equals();
    test_operator_plus();
    test_operator_output();

    print_results();
}