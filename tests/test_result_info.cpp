#include <iostream>
#include <cassert>
#include <string>
#include "../src/ResultInfo.h"
#include "../src/MutableArraySequence.h"

using namespace std;

int Double(int x) {
    return x * 2;
}

bool IsPositive(int x) {
    return x > 0;
}

bool IsEven(int x) {
    return x % 2 == 0;
}

bool IsGreaterThan15(int x) {
    return x > 15;
}

bool Equals20(int x) {
    return x == 20;
}

int RecoverValue(const char* error) {
    cout << "Recovering from: " << error << endl;
    return -1;
}

void PrintSuccess(int val) {
    cout << "Success! Value = " << val << endl;
}

void PrintError(const char* err) {
    cout << "Error: " << err << endl;
}

//глобальные счётчики для test_match
int g_successCount = 0;
int g_failureCount = 0;

void CountSuccess(int val) {
    g_successCount++;
}

void CountFailure(const char* err) {
    g_failureCount++;
}

void test_result_info_success() {
    cout << "test_result_info_success... ";

    ResultInfo<int> result = ResultInfo<int>::Success(42);

    assert(result.IsSuccess());
    assert(!result.IsFailure());
    assert(result.GetValue() == 42);

    cout << "PASS" << endl;
}

void test_result_info_failure() {
    cout << "test_result_info_failure... ";

    ResultInfo<int> result = ResultInfo<int>::Failure("error message");

    assert(!result.IsSuccess());
    assert(result.IsFailure());

    cout << "PASS" << endl;
}

void test_try_get_first() {
    cout << "test_try_get_first... ";

    Sequence<int>* empty = new MutableArraySequence<int>();
    ResultInfo<int> result1 = empty->TryGetFirst();
    assert(result1.IsFailure());

    empty->Append(10);
    ResultInfo<int> result2 = empty->TryGetFirst();
    assert(result2.IsSuccess());
    assert(result2.GetValue() == 10);

    delete empty;
    cout << "PASS" << endl;
}

void test_try_get() {
    cout << "test_try_get... ";

    Sequence<int>* seq = new MutableArraySequence<int>();
    seq->Append(5);
    seq->Append(10);
    seq->Append(15);

    ResultInfo<int> result1 = seq->TryGet(1);
    assert(result1.IsSuccess());
    assert(result1.GetValue() == 10);

    ResultInfo<int> result2 = seq->TryGet(100);
    assert(result2.IsFailure());

    delete seq;
    cout << "PASS" << endl;
}

void test_map() {
    cout << "test_map... ";

    ResultInfo<int> result = ResultInfo<int>::Success(10);

    ResultInfo<int> doubled = result.Map(Double);
    assert(doubled.IsSuccess());
    assert(doubled.GetValue() == 20);

    ResultInfo<int> error = ResultInfo<int>::Failure("oops");
    ResultInfo<int> processed = error.Map(Double);
    assert(processed.IsFailure());

    cout << "PASS" << endl;
}

void test_filter() {
    cout << "test_filter... ";

    ResultInfo<int> result = ResultInfo<int>::Success(10);
    ResultInfo<int> filtered = result.Filter(IsPositive, "must be positive");
    assert(filtered.IsSuccess());

    ResultInfo<int> result2 = ResultInfo<int>::Success(-5);
    ResultInfo<int> filtered2 = result2.Filter(IsPositive, "must be positive");
    assert(filtered2.IsFailure());

    cout << "PASS" << endl;
}

void test_match() {
    cout << "test_match... ";

    g_successCount = 0;
    g_failureCount = 0;

    ResultInfo<int>::Success(42).Match(CountSuccess, CountFailure);
    assert(g_successCount == 1);
    assert(g_failureCount == 0);

    ResultInfo<int>::Failure("error").Match(CountSuccess, CountFailure);
    assert(g_successCount == 1);
    assert(g_failureCount == 1);

    cout << "PASS" << endl;
}

void test_try_find() {
    cout << "test_try_find... ";

    Sequence<int>* seq = new MutableArraySequence<int>();
    seq->Append(5);
    seq->Append(10);
    seq->Append(20);
    seq->Append(25);

    ResultInfo<int> found = seq->TryFind(IsGreaterThan15);
    assert(found.IsSuccess());
    assert(found.GetValue() == 20);

    delete seq;
    cout << "PASS" << endl;
}

void test_try_find_index() {
    cout << "test_try_find_index... ";

    Sequence<int>* seq = new MutableArraySequence<int>();
    seq->Append(5);
    seq->Append(10);
    seq->Append(20);
    seq->Append(25);

    ResultInfo<int> index = seq->TryFindIndex(Equals20);
    assert(index.IsSuccess());
    assert(index.GetValue() == 2);

    delete seq;
    cout << "PASS" << endl;
}

int test_result_info_main() {
    cout << "Running ResultInfo tests..." << endl << endl;

    test_result_info_success();
    test_result_info_failure();
    test_try_get_first();
    test_try_get();
    test_map();
    test_filter();
    test_match();
    test_try_find();
    test_try_find_index();

    cout << endl << "All ResultInfo tests passed!" << endl;
    return 0;
}