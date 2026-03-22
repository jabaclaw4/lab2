#include "../src/test_utils.h"
#include <iostream>

int total = 0;
int passed = 0;

void check(bool condition, const char* test_name) {
    total++;
    if (condition) {
        passed++;
        std::cout << "✓ " << test_name << std::endl;
    } else {
        std::cout << "✗ " << test_name << " FAILED" << std::endl;
    }
}

void reset_counters() {
    total = 0;
    passed = 0;
}

void print_results() {
    std::cout << "\nResults: " << passed << "/" << total << " passed" << std::endl;
    if (passed == total) {
        std::cout << "ALL TESTS PASSED" << std::endl;
    } else {
        std::cout << "SOME TESTS FAILED" << std::endl;
    }
}