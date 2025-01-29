/*
Compile: make four_sorted_digits
Run: ./four_sorted_digits
Compile and run:
make four_sorted_digits && ./four_sorted_digits
*/

#include "base.h"
#include "string.h"

/* 
Returns true if s contains at least 4 incrementing digits right behind one another. Else it returns false.
*/ 
bool four_sorted_digits(String s) {
    return false; // todo: implement
}

void four_sorted_digits_test(void) {
    test_equal_i(four_sorted_digits(""), false);
    test_equal_i(four_sorted_digits("123"), false);
    test_equal_i(four_sorted_digits("abcd"), false);
    test_equal_i(four_sorted_digits("1234"), true);
    test_equal_i(four_sorted_digits("2479"), true);
    test_equal_i(four_sorted_digits("1111"), true);
    test_equal_i(four_sorted_digits("a123"), false);
    test_equal_i(four_sorted_digits("123a"), false);
    test_equal_i(four_sorted_digits("1234a"), true);
    test_equal_i(four_sorted_digits("xx1234y"), true);
    test_equal_i(four_sorted_digits("abc12345"), true);
    test_equal_i(four_sorted_digits("a 1 2 3 4 c"), false);
    test_equal_i(four_sorted_digits("a 3333 c"), true);
}

int main(void) {
    report_memory_leaks(true);
    four_sorted_digits_test();
    return 0;
}
