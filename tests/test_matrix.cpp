#include <iostream>
#include "../src/DynamicArray.h"

using namespace std;

void test_matrix_2x2() {
    cout << "=== Test: DynamicArray<DynamicArray<int>> ===" << endl;

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

    cout << "Matrix 2x2:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "[";
        for (int j = 0; j < 2; j++) {
            cout << matrix->Get(i).Get(j);
            if (j < 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    delete matrix;
}

