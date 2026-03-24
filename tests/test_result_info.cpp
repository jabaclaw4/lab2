#include <iostream>
#include <cassert>
#include <string>
#include "../src/ResultInfo.h"
#include "../src/MutableArraySequence.h"
#include "../src/test_utils.h"

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

int g_successCount = 0;
int g_failureCount = 0;

void CountSuccess(int val) {
    g_successCount++;
}

void CountFailure(const char* err) {
    g_failureCount++;
}

void test_result_info_success() {
    ResultInfo<int> result = ResultInfo<int>::Success(42);

    check(result.IsSuccess(), "result_info_success: IsSuccess");
    check(!result.IsFailure(), "result_info_success: not IsFailure");
    check(result.GetValue() == 42, "result_info_success: value");
}

void test_result_info_failure() {
    ResultInfo<int> result = ResultInfo<int>::Failure("error message");

    check(!result.IsSuccess(), "result_info_failure: not IsSuccess");
    check(result.IsFailure(), "result_info_failure: IsFailure");
}

void test_try_get_first() {
    Sequence<int>* empty = new MutableArraySequence<int>();
    ResultInfo<int> result1 = empty->TryGetFirst();
    check(result1.IsFailure(), "try_get_first: empty fails");

    empty = empty->Append(10);
    ResultInfo<int> result2 = empty->TryGetFirst();
    check(result2.IsSuccess(), "try_get_first: success");
    check(result2.GetValue() == 10, "try_get_first: value");

    delete empty;
}

void test_try_get() {
    Sequence<int>* seq = new MutableArraySequence<int>();
    seq = seq->Append(5)->Append(10)->Append(15);

    ResultInfo<int> result1 = seq->TryGet(1);
    check(result1.IsSuccess(), "try_get: success");
    check(result1.GetValue() == 10, "try_get: value");

    ResultInfo<int> result2 = seq->TryGet(100);
    check(result2.IsFailure(), "try_get: out of range fails");

    delete seq;
}

void test_map() {
    ResultInfo<int> result = ResultInfo<int>::Success(10);

    ResultInfo<int> doubled = result.Map(Double);
    check(doubled.IsSuccess(), "map: success");
    check(doubled.GetValue() == 20, "map: doubled value");

    ResultInfo<int> error = ResultInfo<int>::Failure("oops");
    ResultInfo<int> processed = error.Map(Double);
    check(processed.IsFailure(), "map: error propagates");
}

void test_filter() {
    ResultInfo<int> result = ResultInfo<int>::Success(10);
    ResultInfo<int> filtered = result.Filter(IsPositive, "must be positive");
    check(filtered.IsSuccess(), "filter: positive passes");

    ResultInfo<int> result2 = ResultInfo<int>::Success(-5);
    ResultInfo<int> filtered2 = result2.Filter(IsPositive, "must be positive");
    check(filtered2.IsFailure(), "filter: negative fails");
}

void test_match() {
    g_successCount = 0;
    g_failureCount = 0;

    ResultInfo<int>::Success(42).Match(CountSuccess, CountFailure);
    check(g_successCount == 1, "match: success called");
    check(g_failureCount == 0, "match: failure not called");

    ResultInfo<int>::Failure("error").Match(CountSuccess, CountFailure);
    check(g_successCount == 1, "match: success count unchanged");
    check(g_failureCount == 1, "match: failure called");
}

void test_try_find() {
    Sequence<int>* seq = new MutableArraySequence<int>();
    seq = seq->Append(5)->Append(10)->Append(20)->Append(25);

    ResultInfo<int> found = seq->TryFind(IsGreaterThan15);
    check(found.IsSuccess(), "try_find: found");
    check(found.GetValue() == 20, "try_find: correct value");

    delete seq;
}

void test_try_find_index() {
    Sequence<int>* seq = new MutableArraySequence<int>();
    seq = seq->Append(5)->Append(10)->Append(20)->Append(25);

    ResultInfo<int> index = seq->TryFindIndex(Equals20);
    check(index.IsSuccess(), "try_find_index: found");
    check(index.GetValue() == 2, "try_find_index: correct index");

    delete seq;
}

void run_test_result_info() {
    reset_counters();

    cout << "=== ResultInfo Tests ===" << endl;

    test_result_info_success();
    test_result_info_failure();
    test_try_get_first();
    test_try_get();
    test_map();
    test_filter();
    test_match();
    test_try_find();
    test_try_find_index();

    print_results();
}