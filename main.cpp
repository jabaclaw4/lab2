#include <iostream>
#include <limits>
#include "src/all_tests.h"
#include "src/SequenceUtils.h"
#include "src/MutableArraySequence.h"
#include "src/ImmutableArraySequence.h"
#include "src/MutableListSequence.h"
#include "src/ImmutableListSequence.h"
#include "src/BitSequence.h"

//доразобраться с монадой
//1 тест бит крашится

using namespace std;

Sequence<int>* g_seq = nullptr;
BitSequence* g_bitseq = nullptr;

void print_menu() {
    cout << "\n===== MENU =====" << endl;
    cout << "=== Integer Sequences ===" << endl;
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
    cout << "\n=== BitSequence ===" << endl;
    cout << "16 - Create BitSequence" << endl;
    cout << "17 - Append bit to BitSequence" << endl;
    cout << "18 - Print BitSequence" << endl;
    cout << "19 - Bitwise AND with another BitSequence" << endl;
    cout << "20 - Bitwise OR with another BitSequence" << endl;
    cout << "21 - Bitwise XOR with another BitSequence" << endl;
    cout << "22 - Bitwise NOT" << endl;
    cout << "\n=== Demos & Tests ===" << endl;
    cout << "14 - Test operators demo" << endl;
    cout << "15 - Run ALL tests" << endl;
    cout << "0 - Exit" << endl;
    cout << "Choice: ";
}

void test_operators_demo() {
    cout << "\n=== DEMO: Operators ===" << endl;

    Sequence<int>* seq1 = new MutableArraySequence<int>();
    seq1 = seq1->Append(1)->Append(2)->Append(3);

    Sequence<int>* seq2 = new MutableArraySequence<int>();
    seq2 = seq2->Append(4)->Append(5);

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

void print_bitsequence(BitSequence* bs) {
    cout << "BitSequence [length=" << bs->GetLength() << "]: ";
    for (int i = 0; i < bs->GetLength(); i++) {
        cout << (bs->Get(i).GetValue() ? "1" : "0");
    }
    cout << endl;
}

int main() {
    int choice;
    cout << "LAB 2 - Sequence Demo" << endl;

    while (true) {
        print_menu();

        //защита от неправильного ввода
        if (!(cin >> choice)) {
            cout << "\nERROR: Invalid input! Please enter a number." << endl;
            cin.clear();//очищаем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//очищаем буфер
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new MutableArraySequence<int>();
                cout << "OK: Created MutableArraySequence" << endl;
                break;
            }
            case 2: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new ImmutableArraySequence<int>();
                cout << "OK: Created ImmutableArraySequence" << endl;
                break;
            }
            case 3: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new MutableListSequence<int>();
                cout << "OK: Created MutableListSequence" << endl;
                break;
            }
            case 4: {
                if (g_seq != nullptr) delete g_seq;
                g_seq = new ImmutableListSequence<int>();
                cout << "OK: Created ImmutableListSequence" << endl;
                break;
            }
            case 5: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                int value;
                cout << "Enter value: ";
                if (!(cin >> value)) {
                    cout << "ERROR: Invalid input" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                g_seq = g_seq->Append(value);
                cout << "OK: Appended " << value << endl;
                break;
            }
            case 6: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                int value;
                cout << "Enter value: ";
                if (!(cin >> value)) {
                    cout << "ERROR: Invalid input" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                g_seq = g_seq->Prepend(value);
                cout << "OK: Prepended " << value << endl;
                break;
            }
            case 7: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                int value, index;
                cout << "Enter value: ";
                if (!(cin >> value)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter index: ";
                if (!(cin >> index)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                try {
                    g_seq = g_seq->InsertAt(value, index);
                    cout << "OK: Inserted " << value << " at index " << index << endl;
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }
            case 8: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                int index;
                cout << "Enter index: ";
                if (!(cin >> index)) {
                    cout << "ERROR: Invalid input" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                try {
                    int value = g_seq->Get(index);
                    cout << "seq[" << index << "] = " << value << endl;
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }
            case 9: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                try {
                    cout << "First element: " << g_seq->GetFirst() << endl;
                    cout << "Last element: " << g_seq->GetLast() << endl;
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }
            case 10: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                int startIndex, endIndex;
                cout << "Enter start index: ";
                if (!(cin >> startIndex)) {
                    cout << "ERROR: Invalid input" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter end index: ";
                if (!(cin >> endIndex)) {
                    cout << "ERROR: Invalid input" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                try {
                    Sequence<int>* subSeq = g_seq->GetSubsequence(startIndex, endIndex);
                    cout << "Subsequence [" << startIndex << ".." << endIndex << "]: " << *subSeq << endl;
                    delete subSeq;
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }
            case 11: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                Sequence<int>* temp = new MutableArraySequence<int>();
                int count;
                cout << "How many elements to add? ";
                if (!(cin >> count) || count < 0) {
                    cout << "ERROR: Invalid input" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    delete temp;
                    break;
                }
                for (int i = 0; i < count; i++) {
                    int value;
                    cout << "Element " << (i+1) << ": ";
                    if (!(cin >> value)) {
                        cout << "ERROR: Invalid input" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        delete temp;
                        break;
                    }
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
                    cout << "ERROR: Create sequence first" << endl;
                    break;
                }
                int index;
                cout << "Enter index: ";
                if (!(cin >> index)) {
                    cout << "ERROR: Invalid input" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                ResultInfo<int> result = g_seq->TryGet(index);

                if (result.IsSuccess()) {
                    cout << "OK: Success seq[" << index << "] = " << result.GetValue() << endl;
                } else {
                    cout << "ERROR: " << result.GetError() << endl;
                }
                break;
            }
            case 13: {
                if (g_seq == nullptr) {
                    cout << "ERROR: Create sequence first" << endl;
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
            case 16: {
                if (g_bitseq != nullptr) delete g_bitseq;
                int size;
                cout << "Enter number of bits: ";
                if (!(cin >> size) || size < 0) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                g_bitseq = new BitSequence(size);
                cout << "OK: Created BitSequence with " << size << " bits (all 0)" << endl;
                print_bitsequence(g_bitseq);
                break;
            }
            case 17: {
                if (g_bitseq == nullptr) {
                    cout << "ERROR: Create BitSequence first" << endl;
                    break;
                }
                int bit;
                cout << "Enter bit value (0 or 1): ";
                if (!(cin >> bit) || (bit != 0 && bit != 1)) {
                    cout << "ERROR: Invalid input! Enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                BitSequence* old = g_bitseq;
                g_bitseq = (BitSequence*)g_bitseq->Append(Bit(bit == 1));
                delete old;
                cout << "OK: Appended bit " << bit << endl;
                print_bitsequence(g_bitseq);
                break;
            }
            case 18: {
                if (g_bitseq == nullptr) {
                    cout << "ERROR: Create BitSequence first" << endl;
                    break;
                }
                print_bitsequence(g_bitseq);
                break;
            }
            case 19: {
                if (g_bitseq == nullptr) {
                    cout << "ERROR: Create BitSequence first" << endl;
                    break;
                }
                cout << "Enter bits for second BitSequence (same length=" << g_bitseq->GetLength() << "):" << endl;
                Bit* bits = new Bit[g_bitseq->GetLength()];
                for (int i = 0; i < g_bitseq->GetLength(); i++) {
                    int bit;
                    cout << "Bit " << i << " (0/1): ";
                    if (!(cin >> bit) || (bit != 0 && bit != 1)) {
                        cout << "ERROR: Invalid input!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        delete[] bits;
                        goto end_case_19;
                    }
                    bits[i] = Bit(bit == 1);
                }
                {
                    BitSequence* bs2 = new BitSequence(bits, g_bitseq->GetLength());
                    BitSequence* result = g_bitseq->BitwiseAnd(*bs2);
                    cout << "\nBitSequence 1: ";
                    print_bitsequence(g_bitseq);
                    cout << "BitSequence 2: ";
                    print_bitsequence(bs2);
                    cout << "AND result:    ";
                    print_bitsequence(result);
                    delete bs2;
                    delete result;
                }
                delete[] bits;
                end_case_19:
                break;
            }
            case 20: {
                if (g_bitseq == nullptr) {
                    cout << "ERROR: Create BitSequence first (menu option 16)" << endl;
                    break;
                }
                cout << "Enter bits for second BitSequence (same length=" << g_bitseq->GetLength() << "):" << endl;
                Bit* bits = new Bit[g_bitseq->GetLength()];
                for (int i = 0; i < g_bitseq->GetLength(); i++) {
                    int bit;
                    cout << "Bit " << i << " (0/1): ";
                    if (!(cin >> bit) || (bit != 0 && bit != 1)) {
                        cout << "ERROR: Invalid input!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        delete[] bits;
                        goto end_case_20;
                    }
                    bits[i] = Bit(bit == 1);
                }
                {
                    BitSequence* bs2 = new BitSequence(bits, g_bitseq->GetLength());
                    BitSequence* result = g_bitseq->BitwiseOr(*bs2);
                    cout << "\nBitSequence 1: ";
                    print_bitsequence(g_bitseq);
                    cout << "BitSequence 2: ";
                    print_bitsequence(bs2);
                    cout << "OR result:     ";
                    print_bitsequence(result);
                    delete bs2;
                    delete result;
                }
                delete[] bits;
                end_case_20:
                break;
            }
            case 21: {
                if (g_bitseq == nullptr) {
                    cout << "ERROR: Create BitSequence first (menu option 16)!" << endl;
                    break;
                }
                cout << "Enter bits for second BitSequence (same length=" << g_bitseq->GetLength() << "):" << endl;
                Bit* bits = new Bit[g_bitseq->GetLength()];
                for (int i = 0; i < g_bitseq->GetLength(); i++) {
                    int bit;
                    cout << "Bit " << i << " (0/1): ";
                    if (!(cin >> bit) || (bit != 0 && bit != 1)) {
                        cout << "ERROR: Invalid input!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        delete[] bits;
                        goto end_case_21;
                    }
                    bits[i] = Bit(bit == 1);
                }
                {
                    BitSequence* bs2 = new BitSequence(bits, g_bitseq->GetLength());
                    BitSequence* result = g_bitseq->BitwiseXor(*bs2);
                    cout << "\nBitSequence 1: ";
                    print_bitsequence(g_bitseq);
                    cout << "BitSequence 2: ";
                    print_bitsequence(bs2);
                    cout << "XOR result:    ";
                    print_bitsequence(result);
                    delete bs2;
                    delete result;
                }
                delete[] bits;
                end_case_21:
                break;
            }
            case 22: {
                if (g_bitseq == nullptr) {
                    cout << "ERROR: Create BitSequence first" << endl;
                    break;
                }
                BitSequence* result = g_bitseq->BitwiseNot();
                cout << "\nBitSequence: ";
                print_bitsequence(g_bitseq);
                cout << "NOT result:  ";
                print_bitsequence(result);
                delete result;
                break;
            }
            default:
                cout << "ERROR: Invalid choice! Please choose 0-22" << endl;
        }
    }

    if (g_seq != nullptr) {
        delete g_seq;
    }
    if (g_bitseq != nullptr) {
        delete g_bitseq;
    }

    cout << "\nGoodbye!" << endl;
    return 0;
}