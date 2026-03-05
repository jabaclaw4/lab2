#include "../src/DynamicArray.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=== Тест DynamicArray ===" << endl;

    // Тест 1: Создание пустого массива
    DynamicArray<int>* arr1 = new DynamicArray<int>(0);
    cout << "Пустой массив, size = " << arr1->GetSize() << endl;  // 0

    // Тест 2: Создание массива с размером
    DynamicArray<int>* arr2 = new DynamicArray<int>(5);
    cout << "Массив из 5 элементов, size = " << arr2->GetSize() << endl;  // 5

    // Тест 3: Set и Get
    arr2->Set(0, 10);
    arr2->Set(1, 20);
    arr2->Set(2, 30);
    cout << "arr2[0] = " << arr2->Get(0) << endl;  // 10
    cout << "arr2[1] = " << arr2->Get(1) << endl;  // 20
    cout << "arr2[2] = " << arr2->Get(2) << endl;  // 30

    // Тест 4: Resize (увеличение)
    arr2->Resize(7);
    cout << "После Resize(7), size = " << arr2->GetSize() << endl;  // 7
    cout << "arr2[0] = " << arr2->Get(0) << endl;  // 10 (сохранился)
    cout << "arr2[5] = " << arr2->Get(5) << endl;  // 0 (новый элемент)

    // Тест 5: Resize (уменьшение)
    arr2->Resize(2);
    cout << "После Resize(2), size = " << arr2->GetSize() << endl;  // 2
    cout << "arr2[0] = " << arr2->Get(0) << endl;  // 10 (сохранился)

    // Тест 6: Создание из массива
    int numbers[] = {100, 200, 300};
    DynamicArray<int>* arr3 = new DynamicArray<int>(numbers, 3);
    cout << "Массив из {100,200,300}, arr3[1] = " << arr3->Get(1) << endl;  // 200

    // Тест 7: Копирующий конструктор
    DynamicArray<int>* arr4 = new DynamicArray<int>(*arr3);
    cout << "Копия arr3, arr4[1] = " << arr4->Get(1) << endl;  // 200

    // Тест 8: Проверка исключений
    try {
        arr2->Get(100);  // Индекс за пределами
    } catch (const std::out_of_range& e) {
        cout << "Поймали исключение: " << e.what() << endl;
    }

    // Освобождаем память
    delete arr1;
    delete arr2;
    delete arr3;
    delete arr4;

    cout << "=== Все тесты пройдены! ===" << endl;

    return 0;
}