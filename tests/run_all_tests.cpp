#include <iostream>

using namespace std;

//объявляем main из каждого теста как отдельную функцию
int test_dynamic_array_main();
int test_linked_list_main();
int test_mutable_array_main();
int test_mutable_list_main();
int test_operators_main();
int test_result_info_main();

int main() {
    cout << "  RUNNING ALL TESTS FOR LAB 2" << endl;
    int failed = 0;
    cout << "\n[1/6] Running DynamicArray tests..." << endl;
    if (test_dynamic_array_main() != 0) failed++;

    cout << "\n[2/6] Running LinkedList tests..." << endl;
    if (test_linked_list_main() != 0) failed++;

    cout << "\n[3/6] Running MutableArray tests..." << endl;
    if (test_mutable_array_main() != 0) failed++;

    cout << "\n[4/6] Running MutableList tests..." << endl;
    if (test_mutable_list_main() != 0) failed++;

    cout << "\n[5/6] Running Operators tests..." << endl;
    if (test_operators_main() != 0) failed++;

    cout << "\n[6/6] Running ResultInfo tests..." << endl;
    if (test_result_info_main() != 0) failed++;

    cout << "\n=====================================" << endl;
    if (failed == 0) {
        cout << "  ALL TESTS PASSED! ✓" << endl;
    } else {
        cout << "  " << failed << " TEST(S) FAILED! ✗" << endl;
    }
    return failed;
}