#ifndef TEST_UTILS_H
#define TEST_UTILS_H

extern int total;//extern = определено где то ещё
extern int passed;

void check(bool condition, const char* test_name);
void reset_counters();
void print_results();

#endif