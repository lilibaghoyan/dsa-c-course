#include "dsalib/containers/stack.h"

#include <stdlib.h>
#include <string.h>

dsalib_stack_t* dsalib_stack_create(size_t initial_capacity) {
    return NULL;
}

void dsalib_stack_destroy(dsalib_stack_t* stack) {}

bool dsalib_stack_push(dsalib_stack_t* stack, int value) {
    return false;
}

bool dsalib_stack_pop(dsalib_stack_t* stack, int* value) {
    return false;
}

bool dsalib_stack_peek(const dsalib_stack_t* stack, int* value) {
    return false;
}

bool dsalib_stack_is_empty(const dsalib_stack_t* stack) {
    return false;
}

size_t dsalib_stack_size(const dsalib_stack_t* stack) {
    return 0;
}

size_t dsalib_stack_capacity(const dsalib_stack_t* stack) {
    return 0;
}

void dsalib_stack_clear(dsalib_stack_t* stack) {}
