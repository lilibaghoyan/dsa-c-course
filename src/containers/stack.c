#include "dsalib/containers/stack.h"

#include <stdlib.h>
#include <string.h>

#define DEFEULT_CAPACITY 4

dsalib_stack_t* dsalib_stack_create(size_t initial_capacity) {
    if (initial_capacity == 0){
        initial_capacity = DEFEULT_CAPACITY;
    }
    dsalib_stack_t* stack = malloc(sizeof(dsalib_stack_t));
    
    if (!stack) {
        return NULL;
    }
    
    stack->data = malloc(initial_capacity*sizeof(int));
    stack->size = 0;
    stack->capacity = initial_capacity;
    return stack;
}


void dsalib_stack_destroy(dsalib_stack_t* stack) {
    if(!stack || stack->size == 0 || !stack->data) return;
    free(stack->data);
    free(stack);
}

bool dsalib_stack_push(dsalib_stack_t* stack, int value) {
    if(!stack || !stack->data){
        return false;
    }
    if(stack->size == stack->capacity){
        size_t new_capacity = stack->capacity * 2;
        int* new_data = realloc(stack->data, new_capacity*sizeof(int));
        if (!new_data){
            return false;
        }
        stack->capacity = new_capacity;
        stack->data = new_data;
    }
    stack->data[stack->size] = value;
    stack->size++;
    return true;
}

bool dsalib_stack_pop(dsalib_stack_t* stack, int* value) {
    if(!stack || stack->size == 0 || !stack->data){
        return false;
    }
    *value = stack->data[stack->size - 1];
    stack->size--;

    return true;
}

bool dsalib_stack_peek(const dsalib_stack_t* stack, int* value) {
    if(!stack || stack->size == 0 || !stack->data){
        return false;
    }
    *value = stack->data[stack->size - 1];
    return true;
}

bool dsalib_stack_is_empty(const dsalib_stack_t* stack) {
    if(!stack || stack->size == 0 || !stack->data){
        return true;
    }
    return false;
}

size_t dsalib_stack_size(const dsalib_stack_t* stack) {
    if(!stack){
        return 0;
    }
    return stack->size;
}

size_t dsalib_stack_capacity(const dsalib_stack_t* stack) {
    if(!stack){
        return 0;
    }
    return stack->capacity;
}

void dsalib_stack_clear(dsalib_stack_t* stack) {
    if(!stack || stack->size == 0 || !stack->data){
        return;
    }
    stack->size = 0;
}
