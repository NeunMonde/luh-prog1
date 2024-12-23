#include "base.h"

typedef struct dynamic_stack_s {
    // todo
} DynamicStack;

DynamicStack * stack_new() {
    // todo
    return NULL;
}

void stack_free(DynamicStack * stack) {
    // todo
}

void stack_push(DynamicStack * stack, int value) {
    // todo
}

int stack_pop(DynamicStack * stack) {
    // todo
    return 0;
}

void test_stack_ops(DynamicStack * stack) {
    stack_push(stack, 42);
    stack_push(stack, 1);
    stack_push(stack, 13);
    test_equal_i(stack_pop(stack), 13);
    test_equal_i(stack_pop(stack), 1);
    stack_push(stack, 400);
    stack_push(stack, 500);
    stack_push(stack, 600);
    stack_push(stack, 700);
    test_equal_i(stack_pop(stack), 700);
    test_equal_i(stack_pop(stack), 600);
    test_equal_i(stack_pop(stack), 500);
    test_equal_i(stack_pop(stack), 400);
    test_equal_i(stack_pop(stack), 42);
    test_equal_i(stack_pop(stack), 0);
}

int main(void) {
    DynamicStack * stack = stack_new();
    test_stack_ops(stack);

    stack_free(stack);

    DynamicStack * stack2 = stack_new();
    stack_free(stack2);
}
