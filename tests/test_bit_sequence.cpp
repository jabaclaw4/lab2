#include <iostream>
#include "../src/BitSequence.h"

using namespace std;

int total = 0;
int passed = 0;

void check(bool condition, const char* name) {
    total++;
    if (condition) {
        passed++;
        cout << "OK";
    } else {
        cout << "FAIL";
    }
    cout << " - " << name << endl;
}

int main() {
    cout << "=== тесты BitSequence ===" << endl;

    //создание пустой последовательности
    BitSequence* bs1 = new BitSequence(0);
    check(bs1->GetLength() == 0, "пустая: length = 0");
    delete bs1;

    //создание последовательности из 8 бит
    BitSequence* bs2 = new BitSequence(8);
    check(bs2->GetLength() == 8, "8 бит: length = 8");
    check(bs2->Get(0).GetValue() == false, "8 бит: все нули");
    delete bs2;

    //append
    BitSequence* bs3 = new BitSequence(0);
    bs3->Append(Bit(true));
    bs3->Append(Bit(false));
    bs3->Append(Bit(true));
    check(bs3->GetLength() == 3, "append: length = 3");
    check(bs3->Get(0).GetValue() == true, "append: бит 0 = 1");
    check(bs3->Get(1).GetValue() == false, "append: бит 1 = 0");
    check(bs3->Get(2).GetValue() == true, "append: бит 2 = 1");
    delete bs3;

    //побитовое AND
    Bit bits1[] = {Bit(true), Bit(true), Bit(false), Bit(true)};
    Bit bits2[] = {Bit(true), Bit(false), Bit(true), Bit(true)};
    BitSequence* bs4 = new BitSequence(bits1, 4);  //1101
    BitSequence* bs5 = new BitSequence(bits2, 4);  //1011
    BitSequence* andResult = bs4->BitwiseAnd(*bs5);  //1001
    check(andResult->Get(0).GetValue() == true, "AND: бит 0");
    check(andResult->Get(1).GetValue() == false, "AND: бит 1");
    check(andResult->Get(2).GetValue() == false, "AND: бит 2");
    check(andResult->Get(3).GetValue() == true, "AND: бит 3");
    delete bs4;
    delete bs5;
    delete andResult;

    //побитовое OR
    bs4 = new BitSequence(bits1, 4);  //1101
    bs5 = new BitSequence(bits2, 4);  //1011
    BitSequence* orResult = bs4->BitwiseOr(*bs5);  //1111
    check(orResult->Get(0).GetValue() == true, "OR: бит 0");
    check(orResult->Get(1).GetValue() == true, "OR: бит 1");
    check(orResult->Get(2).GetValue() == true, "OR: бит 2");
    check(orResult->Get(3).GetValue() == true, "OR: бит 3");
    delete bs4;
    delete bs5;
    delete orResult;

    //побитовое XOR
    bs4 = new BitSequence(bits1, 4);  //1101
    bs5 = new BitSequence(bits2, 4);  //1011
    BitSequence* xorResult = bs4->BitwiseXor(*bs5);  //0110
    check(xorResult->Get(0).GetValue() == false, "XOR: бит 0");
    check(xorResult->Get(1).GetValue() == true, "XOR: бит 1");
    check(xorResult->Get(2).GetValue() == true, "XOR: бит 2");
    check(xorResult->Get(3).GetValue() == false, "XOR: бит 3");
    delete bs4;
    delete bs5;
    delete xorResult;

    //побитовое NOT
    bs4 = new BitSequence(bits1, 4);  //1101
    BitSequence* notResult = bs4->BitwiseNot();  //0010
    check(notResult->Get(0).GetValue() == false, "NOT: бит 0");
    check(notResult->Get(1).GetValue() == true, "NOT: бит 1");
    check(notResult->Get(2).GetValue() == true, "NOT: бит 2");
    check(notResult->Get(3).GetValue() == false, "NOT: бит 3");
    delete bs4;
    delete notResult;

    //битовая маска (пример от препода)
    //права: read=1, write=1, execute=0 → маска 110
    Bit permissions[] = {Bit(false), Bit(true), Bit(true)};  //011 (execute, write, read)
    Bit mask[] = {Bit(false), Bit(true), Bit(true)};          //011 (проверяем write и read)
    BitSequence* perm = new BitSequence(permissions, 3);
    BitSequence* msk = new BitSequence(mask, 3);
    BitSequence* result = perm->BitwiseAnd(*msk);
    check(result->Get(0).GetValue() == false, "маска: execute = 0");
    check(result->Get(1).GetValue() == true, "маска: write = 1");
    check(result->Get(2).GetValue() == true, "маска: read = 1");
    delete perm;
    delete msk;
    delete result;

    cout << "\nитог: " << passed << " / " << total << " OK" << endl;
    return (passed == total) ? 0 : 1;
}