#include <iostream>
#include "../src/all_tests.h"

using namespace std;

void run_all_tests() {
    cout << "  RUNNING ALL TESTS" << endl;
    cout << "\n[1/8] DynamicArray tests:" << endl;
    run_test_dynamic_array();

    cout << "\n[2/8] LinkedList tests:" << endl;
    run_test_linked_list();

    cout << "\n[3/8] MutableArraySequence tests:" << endl;
    run_test_mutable_array();

    cout << "\n[4/8] MutableListSequence tests:" << endl;
    run_test_mutable_list();

    cout << "\n[5/8] Operators tests:" << endl;
    run_test_operators();

    cout << "\n[6/8] ResultInfo tests:" << endl;
    run_test_result_info();

    cout << "\n[7/8] BitSequence tests:" << endl;
    run_test_bit_sequence();

    cout << "\n[7/8] BitSequence tests:" << endl;
    test_matrix_2x2();
}