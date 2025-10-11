#ifndef DSALIB_STACK_H
#define DSALIB_STACK_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Stack data structure using dynamic array.
 *
 * A stack is a Last-In-First-Out (LIFO) data structure.
 * Elements are added and removed from the top only.
 *
 * Time Complexities:
 * - Push: O(1) amortized (O(n) when resizing)
 * - Pop: O(1)
 * - Peek: O(1)
 * - IsEmpty: O(1)
 * - Size: O(1)
 */
typedef struct {
    int* data; // Dynamic array to store elements
    size_t size; // Current number of elements
    size_t capacity; // Current capacity of the array
} dsalib_stack_t;

/**
 * @brief Creates and initializes a new stack.
 *
 * Allocates memory for the stack structure and initializes it with
 * a default capacity. The stack will automatically grow as needed.
 *
 * @param initial_capacity Starting capacity (use 0 for default of 4)
 * @return Pointer to newly created stack, or NULL if allocation fails
 *
 * Requirements:
 * - Allocate memory for Stack structure
 * - Allocate memory for data array with given capacity (default 4 if 0)
 * - Initialize size to 0
 * - Return NULL if any allocation fails
 * - User must call stack_destroy() when done
 */
dsalib_stack_t* dsalib_stack_create(size_t initial_capacity);

/**
 * @brief Destroys the stack and frees all memory.
 *
 * @param stack Pointer to the stack to destroy
 *
 * Requirements:
 * - Free the data array
 * - Free the stack structure itself
 * - Handle NULL pointer gracefully (do nothing)
 */
void dsalib_stack_destroy(dsalib_stack_t* stack);

/**
 * @brief Pushes an element onto the top of the stack.
 *
 * If the stack is full, it automatically resizes (doubles capacity).
 *
 * Time Complexity: O(1) amortized
 *
 * @param stack Pointer to the stack
 * @param value Value to push
 * @return true if successful, false if allocation fails or stack is NULL
 *
 * Requirements:
 * - Add element to top of stack
 * - Increment size
 * - If capacity reached, double the capacity before pushing
 * - Handle NULL stack pointer (return false)
 * - Return false if reallocation fails (but keep stack valid)
 */
bool dsalib_stack_push(dsalib_stack_t* stack, int value);

/**
 * @brief Removes and returns the top element from the stack.
 *
 * Time Complexity: O(1)
 *
 * @param stack Pointer to the stack
 * @param value Pointer to store the popped value
 * @return true if successful, false if stack is empty or NULL
 *
 * Requirements:
 * - Remove top element from stack
 * - Store removed value in *value
 * - Decrement size
 * - Return false if stack is empty or NULL
 * - Optional: Shrink capacity if size drops below capacity/4 (extra credit)
 */
bool dsalib_stack_pop(dsalib_stack_t* stack, int* value);

/**
 * @brief Returns the top element without removing it.
 *
 * Time Complexity: O(1)
 *
 * @param stack Pointer to the stack
 * @param value Pointer to store the top value
 * @return true if successful, false if stack is empty or NULL
 *
 * Requirements:
 * - Copy top element to *value without removing it
 * - Do not modify the stack
 * - Return false if stack is empty or NULL
 */
bool dsalib_stack_peek(const dsalib_stack_t* stack, int* value);

/**
 * @brief Checks if the stack is empty.
 *
 * Time Complexity: O(1)
 *
 * @param stack Pointer to the stack
 * @return true if stack is empty or NULL, false otherwise
 */
bool dsalib_stack_is_empty(const dsalib_stack_t* stack);

/**
 * @brief Returns the number of elements in the stack.
 *
 * Time Complexity: O(1)
 *
 * @param stack Pointer to the stack
 * @return Number of elements, or 0 if stack is NULL
 */
size_t dsalib_stack_size(const dsalib_stack_t* stack);

/**
 * @brief Returns the current capacity of the stack.
 *
 * Time Complexity: O(1)
 *
 * @param stack Pointer to the stack
 * @return Current capacity, or 0 if stack is NULL
 */
size_t dsalib_stack_capacity(const dsalib_stack_t* stack);

/**
 * @brief Removes all elements from the stack.
 *
 * Time Complexity: O(1)
 *
 * @param stack Pointer to the stack
 *
 * Requirements:
 * - Reset size to 0
 * - Keep the allocated capacity (don't free/reallocate)
 * - Handle NULL pointer gracefully
 */
void dsalib_stack_clear(dsalib_stack_t* stack);

#endif // DSALIB_STACK_H