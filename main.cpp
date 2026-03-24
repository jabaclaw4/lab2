#include <iostream>
#include "src/all_tests.h"
#include "src/MutableArraySequence.h"
#include "src/ImmutableArraySequence.h"
#include "src/MutableListSequence.h"
#include "src/ImmutableListSequence.h"

//доразобраться с монадой и бит секуанс добавить в демо консоль бит секуанс с проверкой тестов на маски и тд

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
    cout << "7 - InsertAt element" << endl;
    cout << "8 - Get element by index" << endl;
    cout << "9 - GetFirst / GetLast" << endl;
    cout << "10 - GetSubsequence" << endl;
    cout << "11 - Concat with another sequence" << endl;
    cout << "12 - TryGet (safe get)" << endl;
    cout << "13 - Print sequence" << endl;
    cout << "14 - Test operators demo" << endl;
    cout << "15 - Run ALL tests" << endl;
    cout << "0 - Exit" << endl;
    cout << "Choice: ";
}

void test_operators_demo() {
    cout << "\n=== DEMO: Operators ===" << endl;

    Sequence<int>* seq1 = new MutableArraySequence<int>();
    seq1->Append(1)->Append(2)->Append(3);

    Sequence<int>* seq2 = new MutableArraySequence<int>();
    seq2->Append(4)->Append(5);

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
                g_seq = g_seq->Append(value);
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
                g_seq = g_seq->Prepend(value);
                cout << "Prepended " << value << endl;
                break;
            }
            case 7: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                int value, index;
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter index: ";
                cin >> index;
                try {
                    g_seq = g_seq->InsertAt(value, index);
                    cout << "Inserted " << value << " at index " << index << endl;
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
                try {
                    int value = g_seq->Get(index);
                    cout << "seq[" << index << "] = " << value << endl;
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 9: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                try {
                    cout << "First element: " << g_seq->GetFirst() << endl;
                    cout << "Last element: " << g_seq->GetLast() << endl;
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 10: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                int startIndex, endIndex;
                cout << "Enter start index: ";
                cin >> startIndex;
                cout << "Enter end index: ";
                cin >> endIndex;
                try {
                    Sequence<int>* subSeq = g_seq->GetSubsequence(startIndex, endIndex);
                    cout << "Subsequence [" << startIndex << ".." << endIndex << "]: " << *subSeq << endl;
                    delete subSeq;
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 11: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                cout << "Creating temporary sequence to concat..." << endl;
                Sequence<int>* temp = new MutableArraySequence<int>();
                int count;
                cout << "How many elements to add? ";
                cin >> count;
                for (int i = 0; i < count; i++) {
                    int value;
                    cout << "Element " << (i+1) << ": ";
                    cin >> value;
                    temp = temp->Append(value);
                }
                cout << "Current sequence: " << *g_seq << endl;
                cout << "Temp sequence: " << *temp << endl;

                Sequence<int>* result = g_seq->Concat(temp);
                cout << "Concatenated: " << *result << endl;

                char replace;
                cout << "Replace current sequence with result? (y/n): ";
                cin >> replace;
                if (replace == 'y' || replace == 'Y') {
                    delete g_seq;
                    g_seq = result;
                } else {
                    delete result;
                }
                delete temp;
                break;
            }
            case 12: {
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
            case 13: {
                if (g_seq == nullptr) {
                    cout << "Create sequence first!" << endl;
                    break;
                }
                cout << "Sequence: " << *g_seq << endl;
                cout << "Length: " << g_seq->GetLength() << endl;
                break;
            }
            case 14: {
                test_operators_demo();
                break;
            }
            case 15: {
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
    return 0;
}
