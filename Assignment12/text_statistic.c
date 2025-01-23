#include "base.h"

typedef struct text_statistic_s {
    int chars;
    int letters;
    int digits;
    int linebreaks;
    int sentences;
} TextStatistic;

// TODO: typedef for CharacterTestFunction

// TODO: Implement predicate functions

int calculate_statistic(const char * text, CharacterTestFunction predicate) {
    // TODO
}

TextStatistic make_text_statistic(String text) {
    // TODO
    return (TextStatistic) {};
}

void print_text_statistic(TextStatistic statistic) {
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
