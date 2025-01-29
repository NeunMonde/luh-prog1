/*
Compile: make palindrome
Run: ./palindrome
make palindrome && ./palindrome
*/

#include "base.h"

/**
(a) Todo: Implement.
Return whether a character is in the alphabet
*/
bool is_in_alphabet(char c) {
    
    // TODO implement
    
    return false;
}

/**
(b) Todo: Implement.
Return whether a String is a palindrome
*/
bool is_palindrome(char* s) {
    
    // TODO implement
    
    return false;
}

/**
(c) Todo: Implement.
Return whether a String contains at least one palindrome of minimum size minimum_palindrome_size
*/
bool contains_palindrome(char* s, int minimum_palindrome_size) {    
    
    // TODO implement
    
    return false;
}




void test(void) {
    // (a)
    test_equal_b(is_in_alphabet('a'), true);
    test_equal_b(is_in_alphabet('y'), true);
    test_equal_b(is_in_alphabet('B'), true);
    test_equal_b(is_in_alphabet('X'), true);
    test_equal_b(is_in_alphabet(' '), false);
    test_equal_b(is_in_alphabet('.'), false);
    test_equal_b(is_in_alphabet('{'), false);
    
    // (b)
    test_equal_b(is_palindrome("hello world"), false);
    test_equal_b(is_palindrome("anna"), true);
    test_equal_b(is_palindrome(""), false);
    test_equal_b(is_palindrome("shower."), false);
    test_equal_b(is_palindrome("madam ?"), true);
    test_equal_b(is_palindrome("nurses run"), true);
    
    // (c)
    test_equal_b(contains_palindrome("hello world", 5), false);
    test_equal_b(contains_palindrome("hello world", 3), true);
    test_equal_b(contains_palindrome("anna", 3), true);
    test_equal_b(contains_palindrome("", 0), false);
    test_equal_b(contains_palindrome("shower thoughts by madam anna", 4), true);
    test_equal_b(contains_palindrome("madam anna is a nurse", 3), true);
    test_equal_b(contains_palindrome("nurses run", 4), true);
    
}

int main(void) {
    test();
    return 0;
}
