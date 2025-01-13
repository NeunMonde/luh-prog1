#include "base.h"

typedef struct dynamic_stack_s {
    int size;
    int position;
    int *data;
    // todo
} DynamicStack;

DynamicStack * stack_new() {

    DynamicStack *stack = xmalloc(sizeof(DynamicStack));
    stack->size = 1;
    stack->position = 0;
    stack->data = xmalloc(1 * sizeof(int));
    return stack;
}

void stack_free(DynamicStack * stack) {
    free(stack->data);
    free(stack);
}

void stack_push(DynamicStack * stack, int value) {

    if(stack->position >= stack->size)
    {
        int *data = xmalloc((stack->size + 1) * sizeof(int));
        stack->size = stack->size + 1;

        for(int i = 0; i < stack->position; i++)
        {
            data[i] = stack->data[i];
        }

        free(stack->data);
        stack->data = data;
    }

    stack->data[stack->position] = value;
    stack->position = stack->position + 1;
}

int stack_pop(DynamicStack * stack) {

    if(stack->position > 0)
    {
        stack->position = stack->position - 1;
        return stack->data[stack->position];
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
