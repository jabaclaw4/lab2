#include <iostream>
#include <sstream>
#include <cassert>
#include "../src/MutableArraySequence.h"
#include "../src/test_utils.h"

using namespace std;

void test_operator_bracket() {
    cout << "test_operator_bracket... ";

    Sequence<int>* seq = new MutableArraySequence<int>();
    seq = seq->Append(10);
    seq = seq->Append(20);
    seq = seq->Append(30);

    assert((*seq)[0] == 10);
    assert((*seq)[1] == 20);
    assert((*seq)[2] == 30);

    delete seq;
    cout << "PASS" << endl;
}

void test_operator_equals() {
    cout << "test_operator_equals... ";

    Sequence<int>* seq1 = new MutableArraySequence<int>();
    seq1 = seq1->Append(1)->Append(2)->Append(3);

    Sequence<int>* seq2 = new MutableArraySequence<int>();
    seq2 = seq2->Append(1)->Append(2)->Append(3);

    Sequence<int>* seq3 = new MutableArraySequence<int>();
    seq3 = seq3->Append(1)->Append(2)->Append(4);

    assert(*seq1 == *seq2);
    assert(*seq1 != *seq3);

    delete seq1;
    delete seq2;
    delete seq3;
    cout << "PASS" << endl;
}

void test_operator_plus() {
    cout << "test_operator_plus... ";

    Sequence<int>* seq1 = new MutableArraySequence<int>();
    seq1 = seq1->Append(1)->Append(2);

    Sequence<int>* seq2 = new MutableArraySequence<int>();
    seq2 = seq2->Append(3)->Append(4);

    Sequence<int>* result = *seq1 + *seq2;

    assert(result->GetLength() == 4);
    assert((*result)[0] == 1);
    assert((*result)[1] == 2);
    assert((*result)[2] == 3);
    assert((*result)[3] == 4);

    delete seq1;
    delete seq2;
    delete result;
    cout << "PASS" << endl;
}

void test_operator_output() {
    cout << "test_operator_output... ";

    Sequence<int>* seq = new MutableArraySequence<int>();
    seq = seq->Append(1)->Append(2)->Append(3);

    stringstream ss;
    ss << *seq;

    assert(ss.str() == "[1, 2, 3]");

    delete seq;
    cout << "PASS" << endl;
}

void run_test_operators() {
    reset_counters();

    test_operator_bracket();
    test_operator_equals();
    test_operator_plus();
    test_operator_output();

    print_results();
}