#include <dsalib/containers/stack.h>

#include <assert.h>
#include <stdio.h>

void test_stack_create_destroy() {
    printf("Testing stack_create and stack_destroy...\n");

    // Test 1: Create with default capacity
    dsalib_stack_t* stack1 = dsalib_stack_create(0);
    assert(stack1 != NULL);
    assert(dsalib_stack_size(stack1) == 0);
    assert(dsalib_stack_capacity(stack1) == 4); // Default capacity
    assert(dsalib_stack_is_empty(stack1));
    dsalib_stack_destroy(stack1);
    printf("  ✓ Test 1 passed: Create with default capacity\n");

    // Test 2: Create with custom capacity
    dsalib_stack_t* stack2 = dsalib_stack_create(10);
    assert(stack2 != NULL);
    assert(dsalib_stack_size(stack2) == 0);
    assert(dsalib_stack_capacity(stack2) == 10);
    dsalib_stack_destroy(stack2);
    printf("  ✓ Test 2 passed: Create with custom capacity\n");

    // Test 3: Destroy NULL pointer (should not crash)
    dsalib_stack_destroy(NULL);
    printf("  ✓ Test 3 passed: Destroy NULL pointer\n");

    printf("All stack_create/destroy tests passed!\n\n");
}

void test_stack_push() {
    printf("Testing stack_push...\n");

    dsalib_stack_t* stack = dsalib_stack_create(2);
    assert(stack != NULL);

    // Test 1: Push single element
    assert(dsalib_stack_push(stack, 10));
    assert(dsalib_stack_size(stack) == 1);
    assert(!dsalib_stack_is_empty(stack));
    printf("  ✓ Test 1 passed: Push single element\n");

    // Test 2: Push multiple elements
    assert(dsalib_stack_push(stack, 20));
    assert(dsalib_stack_push(stack, 30));
    assert(dsalib_stack_size(stack) == 3);
    printf("  ✓ Test 2 passed: Push multiple elements\n");

    // Test 3: Verify capacity increased (started at 2, now should be 4)
    assert(dsalib_stack_capacity(stack) >= 3);
    printf("  ✓ Test 3 passed: Capacity increased automatically\n");

    // Test 4: Push many elements to test multiple resizes
    for (int i = 0; i < 100; i++) {
        assert(dsalib_stack_push(stack, i));
    }
    assert(dsalib_stack_size(stack) == 103);
    printf("  ✓ Test 4 passed: Multiple resizes work correctly\n");

    // Test 5: Push to NULL stack
    assert(!dsalib_stack_push(NULL, 10));
    printf("  ✓ Test 5 passed: Push to NULL stack returns false\n");

    dsalib_stack_destroy(stack);
    printf("All stack_push tests passed!\n\n");
}

void test_stack_pop() {
    printf("Testing stack_pop...\n");

    dsalib_stack_t* stack = dsalib_stack_create(0);
    assert(stack != NULL);

    // Test 1: Pop from empty stack
    int value;
    assert(!dsalib_stack_pop(stack, &value));
    printf("  ✓ Test 1 passed: Pop from empty stack returns false\n");

    // Test 2: Push and pop single element
    dsalib_stack_push(stack, 42);
    assert(dsalib_stack_pop(stack, &value));
    assert(value == 42);
    assert(dsalib_stack_size(stack) == 0);
    assert(dsalib_stack_is_empty(stack));
    printf("  ✓ Test 2 passed: Push and pop single element\n");

    // Test 3: LIFO order (Last In First Out)
    dsalib_stack_push(stack, 10);
    dsalib_stack_push(stack, 20);
    dsalib_stack_push(stack, 30);

    assert(dsalib_stack_pop(stack, &value));
    assert(value == 30);
    assert(dsalib_stack_pop(stack, &value));
    assert(value == 20);
    assert(dsalib_stack_pop(stack, &value));
    assert(value == 10);
    assert(dsalib_stack_is_empty(stack));
    printf("  ✓ Test 3 passed: LIFO order maintained\n");

    // Test 4: Pop from NULL stack
    assert(!dsalib_stack_pop(NULL, &value));
    printf("  ✓ Test 4 passed: Pop from NULL stack returns false\n");

    // Test 5: Multiple push/pop cycles
    for (int i = 0; i < 50; i++) {
        dsalib_stack_push(stack, i);
    }
    for (int i = 49; i >= 0; i--) {
        assert(dsalib_stack_pop(stack, &value));
        assert(value == i);
    }
    assert(dsalib_stack_is_empty(stack));
    printf("  ✓ Test 5 passed: Multiple push/pop cycles\n");

    dsalib_stack_destroy(stack);
    printf("All stack_pop tests passed!\n\n");
}

void test_stack_peek() {
    printf("Testing stack_peek...\n");

    dsalib_stack_t* stack = dsalib_stack_create(0);
    assert(stack != NULL);

    // Test 1: Peek empty stack
    int value;
    assert(!dsalib_stack_peek(stack, &value));
    printf("  ✓ Test 1 passed: Peek empty stack returns false\n");

    // Test 2: Peek doesn't remove element
    dsalib_stack_push(stack, 100);
    assert(dsalib_stack_peek(stack, &value));
    assert(value == 100);
    assert(dsalib_stack_size(stack) == 1); // Size unchanged
    assert(dsalib_stack_peek(stack, &value));
    assert(value == 100); // Can peek multiple times
    printf("  ✓ Test 2 passed: Peek doesn't remove element\n");

    // Test 3: Peek after multiple pushes
    dsalib_stack_push(stack, 200);
    dsalib_stack_push(stack, 300);
    assert(dsalib_stack_peek(stack, &value));
    assert(value == 300); // Returns top element
    printf("  ✓ Test 3 passed: Peek returns top element\n");

    // Test 4: Peek NULL stack
    assert(!dsalib_stack_peek(NULL, &value));
    printf("  ✓ Test 4 passed: Peek NULL stack returns false\n");

    dsalib_stack_destroy(stack);
    printf("All stack_peek tests passed!\n\n");
}

void test_stack_utility_functions() {
    printf("Testing stack utility functions...\n");

    dsalib_stack_t* stack = dsalib_stack_create(0);
    assert(stack != NULL);

    // Test 1: is_empty
    assert(dsalib_stack_is_empty(stack));
    dsalib_stack_push(stack, 10);
    assert(!dsalib_stack_is_empty(stack));
    printf("  ✓ Test 1 passed: is_empty works correctly\n");

    // Test 2: size
    assert(dsalib_stack_size(stack) == 1);
    dsalib_stack_push(stack, 20);
    dsalib_stack_push(stack, 30);
    assert(dsalib_stack_size(stack) == 3);
    printf("  ✓ Test 2 passed: size works correctly\n");

    // Test 3: capacity
    size_t cap = dsalib_stack_capacity(stack);
    assert(cap >= 3);
    printf("  ✓ Test 3 passed: capacity works correctly\n");

    // Test 4: clear
    dsalib_stack_clear(stack);
    assert(dsalib_stack_size(stack) == 0);
    assert(dsalib_stack_is_empty(stack));
    assert(dsalib_stack_capacity(stack) == cap); // Capacity unchanged
    printf("  ✓ Test 4 passed: clear works correctly\n");

    // Test 5: NULL checks
    assert(dsalib_stack_is_empty(NULL));
    assert(dsalib_stack_size(NULL) == 0);
    assert(dsalib_stack_capacity(NULL) == 0);
    dsalib_stack_clear(NULL); // Should not crash
    printf("  ✓ Test 5 passed: NULL pointer handling\n");

    dsalib_stack_destroy(stack);
    printf("All utility function tests passed!\n\n");
}

void test_stack_stress() {
    printf("Testing stack stress scenarios...\n");

    dsalib_stack_t* stack = dsalib_stack_create(2);
    assert(stack != NULL);

    // Test 1: Large number of operations
    const int OPERATIONS = 10000;
    for (int i = 0; i < OPERATIONS; i++) {
        assert(dsalib_stack_push(stack, i));
    }
    assert(dsalib_stack_size(stack) == OPERATIONS);

    for (int i = OPERATIONS - 1; i >= 0; i--) {
        int value;
        assert(dsalib_stack_pop(stack, &value));
        assert(value == i);
    }
    assert(dsalib_stack_is_empty(stack));
    printf("  ✓ Test 1 passed: %d operations\n", OPERATIONS * 2);

    // Test 2: Alternating push/pop
    for (int i = 0; i < 1000; i++) {
        dsalib_stack_push(stack, i);
        dsalib_stack_push(stack, i + 1);
        int value;
        dsalib_stack_pop(stack, &value);
    }
    assert(dsalib_stack_size(stack) == 1000);
    printf("  ✓ Test 2 passed: Alternating push/pop\n");

    // Test 3: Negative numbers
    dsalib_stack_clear(stack);
    dsalib_stack_push(stack, -100);
    dsalib_stack_push(stack, -50);
    dsalib_stack_push(stack, 0);
    dsalib_stack_push(stack, 50);

    int value;
    dsalib_stack_pop(stack, &value);
    assert(value == 50);
    dsalib_stack_pop(stack, &value);
    assert(value == 0);
    dsalib_stack_pop(stack, &value);
    assert(value == -50);
    dsalib_stack_pop(stack, &value);
    assert(value == -100);
    printf("  ✓ Test 3 passed: Negative numbers\n");

    dsalib_stack_destroy(stack);
    printf("All stress tests passed!\n\n");
}

void demonstrate_stack_usage() {
    printf("Stack Usage Example: Reversing Numbers\n");
    printf("======================================\n");

    dsalib_stack_t* stack = dsalib_stack_create(0);

    printf("Original: ");
    int numbers[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
        dsalib_stack_push(stack, numbers[i]);
    }

    printf("\nReversed: ");
    int value;
    while (!dsalib_stack_is_empty(stack)) {
        dsalib_stack_pop(stack, &value);
        printf("%d ", value);
    }
    printf("\n\n");

    dsalib_stack_destroy(stack);
}

int main() {
    printf("================================\n");
    printf("Stack Test Suite\n");
    printf("================================\n\n");

    test_stack_create_destroy();
    test_stack_push();
    test_stack_pop();
    test_stack_peek();
    test_stack_utility_functions();
    test_stack_stress();
    demonstrate_stack_usage();

    printf("================================\n");
    printf("All stack tests passed!\n");
    printf("================================\n");

    return 0;
}
