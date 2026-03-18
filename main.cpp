#include <iostream>
#include <cstdlib>  //для system()
#include "src/MutableArraySequence.h"
#include "src/ImmutableArraySequence.h"
#include "src/MutableListSequence.h"
#include "src/ImmutableListSequence.h"

using namespace std;

Sequence<int>* g_seq = nullptr;

void print_menu() {
    cout << "\n===== MENU =====" << endl;
    cout << "1 - Create MutableArraySequence" << endl;
    cout << "2 - Create ImmutableArraySequence" << endl;
    cout << "3 - Create MutableListSequence" << endl;
    cout << "4 - Create ImmutableListSequence" << endl;
    cout << "5 - Append element" << endl;
    cout << "6 - Prepend element" << endl;
    cout << "7 - Get element by index" << endl;
    cout << "8 - TryGet (safe get)" << endl;
    cout << "9 - Print sequence" << endl;
    cout << "10 - Test operators demo" << endl;
    cout << "11 - Run ALL tests" << endl;
    cout << "0 - Exit" << endl;
    cout << "Choice: ";
}

void test_operators_demo() {
    cout << "\n=== DEMO: Operators ===" << endl;

    Sequence<int>* seq1 = new MutableArraySequence<int>();
    seq1->Append(1);
    seq1->Append(2);
    seq1->Append(3);

    Sequence<int>* seq2 = new MutableArraySequence<int>();
    seq2->Append(4);
    seq2->Append(5);

    cout << "seq1 = " << *seq1 << endl;
    cout << "seq2 = " << *seq2 << endl;

    cout << "\nOperator []: seq1[1] = " << (*seq1)[1] << endl;

    cout << "\nOperator ==: seq1 == seq1? " << (*seq1 == *seq1 ? "true" : "false") << endl;
    cout << "Operator !=: seq1 != seq2? " << (*seq1 != *seq2 ? "true" : "false") << endl;

    Sequence<int>* seq3 = *seq1 + *seq2;
    cout << "\nOperator +: seq1 + seq2 = " << *seq3 << endl;

    delete seq1;
    delete seq2;
    delete seq3;
}

void run_all_tests() {
    cout << "\n=====================================" << endl;
    cout << "  RUNNING ALL TESTS..." << endl;
    cout << "=====================================" << endl;

    //запускаем скомпилированный файл all_tests
    int result = system("./all_tests");

    if (result != 0) {
        cout << "\nNote: Make sure 'all_tests' is compiled!" << endl;
        cout << "Compile with: g++ -std=c++17 all_tests.cpp -o all_tests" << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

//===== MAIN =====

int main() {
    int choice;

    cout << "LAB 2 - Sequence Demo" << endl;

    while (true) {
        print_menu();
        cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new MutableArraySequence<int>();
                cout << "Created MutableArraySequence" << endl;
                break;
            }
            case 2: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new ImmutableArraySequence<int>();
                cout << "Created ImmutableArraySequence" << endl;
                break;
            }
            case 3: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new MutableListSequence<int>();
                cout << "Created MutableListSequence" << endl;
                break;
            }
            case 4: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new ImmutableListSequence<int>();
                cout << "Created ImmutableListSequence" << endl;
                break;
            }
            case 5: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                int value;
                cout << "Enter value: ";
                cin >> value;
                g_seq->Append(value);
                cout << "Appended " << value << endl;
                break;
            }
            case 6: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                int value;
                cout << "Enter value: ";
                cin >> value;
                g_seq->Prepend(value);
                cout << "Prepended " << value << endl;
                break;
            }
            case 7: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                int index;
                cout << "Enter index: ";
                cin >> index;
                try {
                    int value = g_seq->Get(index);
                    cout << "seq[" << index << "] = " << value << endl;
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 8: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                int index;
                cout << "Enter index: ";
                cin >> index;
                ResultInfo<int> result = g_seq->TryGet(index);

                if (result.IsSuccess()) {
                    cout << "Success! seq[" << index << "] = " << result.GetValue() << endl;
                } else {
                    cout << "Error: " << result.GetError() << endl;
                }
                break;
            }
            case 9: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                cout << "Sequence: " << *g_seq << endl;
                cout << "Length: " << g_seq->GetLength() << endl;
                break;
            }
            case 10: {
                test_operators_demo();
                break;
            }
            case 11: {
                run_all_tests();
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    if (g_seq != nullptr) {
        delete g_seq;
    }

    cout << "Goodbye!" << endl;
    return 0;
}