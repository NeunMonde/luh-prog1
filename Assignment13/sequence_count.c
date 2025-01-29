/*
Compile: make sequence_count
Run: ./sequence_count
make sequence_count && ./sequence_count
*/

#include "base.h"
#include "string.h"

/**
(a) Todo: Implement.
Returns number of positions at which t occurs in s.
*/
int sequence_count(String s, String t) {
    // ... s_length(s) ... s[i]
    return -1;
}

/**
(b) Todo: Fix the bug.
Returns true if (and only if) the parentheses in s match and form a 
correctly parenthesized expression. The function just checks the 
parentheses and ignores any other characters.
*/
bool parentheses_correct(String s) {
    int n = s_length(s);
    int p = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] >= '(') p++;
        if (s[i] <= ')') p--;
    }
    return p < 0;
}

void test(void) {
    // (a)
    test_equal_i(sequence_count("hello world", "l"), 3);
    test_equal_i(sequence_count("hello world", "w"), 1);
    test_equal_i(sequence_count("hello worlld", "ll"), 2);
    test_equal_i(sequence_count("hello world  ", " "), 3);
    test_equal_i(sequence_count("hello world hello", "hello"), 2);
    test_equal_i(sequence_count("hello world", "not"), 0);
    test_equal_i(sequence_count("hello world", "not in there..."), 0);
    test_equal_i(sequence_count("...", "..."), 1);
    test_equal_i(sequence_count("....", "..."), 2);
    test_equal_i(sequence_count(".....", "..."), 3);
    
    // (b)
    test_equal_i(parentheses_correct("(3"), false);
    test_equal_i(parentheses_correct("3)"), false);
    test_equal_i(parentheses_correct(")3("), false);
    test_equal_i(parentheses_correct("(3)"), true);
    test_equal_i(parentheses_correct("((3))"), true);
    test_equal_i(parentheses_correct("((3)"), false);
    test_equal_i(parentheses_correct("((3)))"), false);
    test_equal_i(parentheses_correct("()((3))"), true);
    test_equal_i(parentheses_correct("(1)+(2)"), true);
    test_equal_i(parentheses_correct(""), true);
}

int main(void) {
    test();
    return 0;
}
