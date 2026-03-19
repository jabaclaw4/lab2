#include <iostream>
#include "../src/all_tests.h"

using namespace std;

void run_all_tests() {
    cout << "\n=====================================" << endl;
    cout << "  RUNNING ALL TESTS" << endl;
    cout << "=====================================" << endl;

    cout << "\n[1/6] DynamicArray tests:" << endl;
    run_test_dynamic_array();

    cout << "\n[2/6] LinkedList tests:" << endl;
    run_test_linked_list();

    cout << "\n[3/6] MutableArraySequence tests:" << endl;
    run_test_mutable_array();

    cout << "\n[4/6] MutableListSequence tests:" << endl;
    run_test_mutable_list();

    cout << "\n[5/6] Operators tests:" << endl;
    run_test_operators();

    cout << "\n[6/6] ResultInfo tests:" << endl;
    run_test_result_info();

    cout << "\n=====================================" << endl;
    cout << "  ALL TESTS COMPLETED!" << endl;
    cout << "=====================================" << endl;
}