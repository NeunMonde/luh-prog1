#include "base.h"

typedef struct dynamic_stack_s {

    int length;
    int value[];

} DynamicStack;

DynamicStack * stack_new() {
    
    DynamicStack * stack = xcalloc(1, sizeof(DynamicStack));

    return stack;
}

void stack_free(DynamicStack * stack) {

    free(stack);

}

void stack_push(DynamicStack * stack, int value) {
    
    stack->value[stack->length] = value;
    stack = realloc(stack, sizeof(DynamicStack) + sizeof(int) * (stack->length + 1));
    stack->length++;

}

int stack_pop(DynamicStack * stack) {
    
    if (stack->length == 0) {
        return 0;
    }
    else {
        int value = stack->value[stack->length - 1];
        stack = realloc(stack, sizeof(DynamicStack) + sizeof(int) * (stack->length - 1));
        stack->length--;
        return value;
    }
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
    report_memory_leaks(true);
    
    DynamicStack * stack = stack_new();
    test_stack_ops(stack);

    stack_free(stack);

    DynamicStack * stack2 = stack_new();
    stack_free(stack2);
}
