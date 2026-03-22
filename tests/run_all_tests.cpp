#include <iostream>
#include "../src/all_tests.h"

using namespace std;

void run_all_tests() {
    cout << "  RUNNING ALL TESTS" << endl;
    cout << "\n[1/7] DynamicArray tests:" << endl;
    run_test_dynamic_array();

    cout << "\n[2/7] LinkedList tests:" << endl;
    run_test_linked_list();

    cout << "\n[3/7] MutableArraySequence tests:" << endl;
    run_test_mutable_array();

    cout << "\n[4/7] MutableListSequence tests:" << endl;
    run_test_mutable_list();

    cout << "\n[5/7] Operators tests:" << endl;
    run_test_operators();

    cout << "\n[6/7] ResultInfo tests:" << endl;
    run_test_result_info();

    cout << "\n[7/7] BitSequence tests:" << endl;
    run_test_bit_sequence();
}