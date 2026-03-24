#include <iostream>
#include "../src/DynamicArray.h"
#include "../src/test_utils.h"

using namespace std;

void test_matrix_2x2() {
    reset_counters();

    cout << "=== Matrix 2x2 Test ===" << endl;

    //создаём матрицу 2x2
    DynamicArray<DynamicArray<int>>* matrix = new DynamicArray<DynamicArray<int>>(2);

    //первая строка [1, 2]
    DynamicArray<int> row1(2);
    row1.Set(0, 1);
    row1.Set(1, 2);
    matrix->Set(0, row1);
    DynamicArray<int> row2(2);
    row2.Set(0, 3);
    row2.Set(1, 4);
    matrix->Set(1, row2);

    check(matrix->Get(0).Get(0) == 1, "matrix[0][0] = 1");
    check(matrix->Get(0).Get(1) == 2, "matrix[0][1] = 2");
    check(matrix->Get(1).Get(0) == 3, "matrix[1][0] = 3");
    check(matrix->Get(1).Get(1) == 4, "matrix[1][1] = 4");
    cout << "\nMatrix 2x2:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "[";
        for (int j = 0; j < 2; j++) {
            cout << matrix->Get(i).Get(j);
            if (j < 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    delete matrix;

    print_results();
}