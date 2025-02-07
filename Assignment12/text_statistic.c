#include "base.h"

typedef struct text_statistic_s {
    int chars;
    int letters;
    int digits;
    int linebreaks;
    int sentences;
} TextStatistic;

typedef bool (*CharacterTestFunction)(char);

bool is_valid_char(char c) {
    if ((c >= 32 && c <= 126 )|| c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        return true;
    }
    return false;
}

bool is_letter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }
    return false;
}

bool is_digit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

bool is_sentence(char c) {
    if (c == '.' || c == '?' || c == '!') {
        return true;
    }
    return false;
}

bool is_newline(char c) {
    if (c == '\n') {
        return true;
    }
    return false;
}

int calculate_statistic(const char * text, CharacterTestFunction test_function) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (test_function(text[i])) {
            count++;
        }
    }
    return count;
    
}

TextStatistic make_text_statistic(String text) {
    TextStatistic statistic = {};
    statistic.chars = calculate_statistic(text, is_valid_char);
    statistic.letters = calculate_statistic(text, is_letter);
    statistic.digits = calculate_statistic(text, is_digit);
    statistic.linebreaks = calculate_statistic(text, is_newline);
    statistic.sentences = calculate_statistic(text, is_sentence);

    return statistic;
}

void print_text_statistic(TextStatistic statistic) {
    printf("\n\n");
    printf(".chars = %d\n", statistic.chars);
    printf(".letters = %d\n", statistic.letters);
    printf(".digits = %d\n", statistic.digits);
    printf(".linebreaks = %d\n", statistic.linebreaks);
    printf(".sentences = %d\n", statistic.sentences);
}

void test_text_statistic(String text, int chars, int letters, int digits, int linebreaks, int sentences) {
    TextStatistic s = make_text_statistic(text);
    test_equal_i(s.chars, chars);
    test_equal_i(s.letters, letters);
    test_equal_i(s.digits, digits);
    test_equal_i(s.linebreaks, linebreaks);
    test_equal_i(s.sentences, sentences);
}

int main(void) {
    test_text_statistic("", 0, 0, 0, 0, 0);
    test_text_statistic("Hello World.", 12, 10, 0, 0, 1);
    test_text_statistic("Number 12. Number 11?", 21, 12, 4, 0, 2);
    test_text_statistic("This is another text\nwith linebreaks. And sentences!", 52, 43, 0, 1, 2);
    return 0;
}
