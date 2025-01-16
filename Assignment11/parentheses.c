#include "base.h"

typedef struct dynamic_stack_s {
    int length;
    char *parentheses;
} DynamicStack;

DynamicStack * stack_new() {
    DynamicStack * stack = xcalloc(1, sizeof(DynamicStack));
    stack->parentheses = NULL;
    return stack;
}

void stack_free(DynamicStack * stack) {
    free(stack);
}

void stack_push(DynamicStack * stack, char character) {
    stack->length++;
    stack->parentheses = realloc(stack->parentheses, stack->length * sizeof(char));
    stack->parentheses[stack->length - 1] = character;
}

void stack_pop(DynamicStack * stack) {
    if (stack->length > 0) {
        stack->length--;
        stack->parentheses = realloc(stack->parentheses, stack->length * sizeof(char));
    }
}

bool verify_parentheses(String text) {
    DynamicStack * stack = stack_new();

    char* opening_parentheses = "({[<";
    char* closing_parentheses = ")}]>";


    for (int i = 0; i < strlen(text); i++) {
        if (strchr(opening_parentheses, text[i]) != NULL) {
            stack_push(stack, text[i]);
        }
        else if (strchr(closing_parentheses, text[i]) != NULL) {
            if (stack->length == 0) {
                stack_free(stack);
                return false;
            }
            else {
                char last_parentheses = stack->parentheses[stack->length - 1];
                if (strchr(opening_parentheses, last_parentheses) - opening_parentheses != strchr(closing_parentheses, text[i]) - closing_parentheses) {
                    stack_free(stack);
                    return false;
                }
                else {
                    stack_pop(stack);
                }
            }
        }
    }
    if (stack->length != 0) {
        stack_free(stack);
        return false;
    }
    stack_free(stack);
    return true;
        

}

int main(void) {
    report_memory_leaks(true);

    test_equal_i(verify_parentheses(""), true);
    test_equal_i(verify_parentheses("Hello World"), true);
    test_equal_i(verify_parentheses("()"), true);
    test_equal_i(verify_parentheses("<{[()]}>"), true);
    test_equal_i(verify_parentheses("<{[)]}>"), false);
    test_equal_i(verify_parentheses("( Test ) "), true);
    test_equal_i(verify_parentheses("(1+2)*[2+3+(1 + 6/5)]"), true);
    test_equal_i(verify_parentheses("(an unmatched left parenthesis creates an unresolved tension that will stay with you all day"), false);
    test_equal_i(verify_parentheses("< [ > ]"), false);
    test_equal_i(verify_parentheses("<{[()]}"), false);
    test_equal_i(verify_parentheses("(<<({[({<{<({<([[[<[{(<{(<{{<[{<{{{<<{([<<<{{[{<<[[(([{[[[([(({()}))])]]]}]))]]>>}]}}>>>])}>>}}}>}]>}}>)}>)}]>]]])>})>}>})]})>>)"), true);

    return 0;
}
