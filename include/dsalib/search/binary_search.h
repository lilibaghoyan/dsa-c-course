#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stddef.h>

/**
 * @brief Finds the first position where target can be inserted
 *        without violating the order (lower_bound).
 *
 * This function returns the smallest index i such that arr[i] >= target.
 * If all elements in the array are less than target, it returns size.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 *
 * @param arr Pointer to the SORTED array (must not be NULL)
 * @param size Number of elements in the array
 * @param target The value to search for
 * @return The index of the first element >= target, or size if none
 *
 * Requirements:
 * - Array MUST be sorted in ascending order
 * - Handle empty arrays (size = 0) by returning 0
 * - Handle NULL pointer by returning 0
 * - Iterative approach only
 */
size_t dsalib_lower_bound(const int* arr, size_t size, int target);

/**
 * @brief Performs a binary search on a SORTED array to find a target value.
 *
 * This function uses the divide-and-conquer approach to efficiently search
 * a sorted array by repeatedly dividing the search interval in half.
 *
 * Time Complexity: O(log n) - where n is the size of the array
 * Space Complexity: O(1) - iterative implementation required
 *
 * @param arr Pointer to the SORTED array to search (must not be NULL)
 * @param size Number of elements in the array
 * @param target The value to search for
 * @return Index of the target if found, -1 if not found
 *
 * Requirements:
 * - Array MUST be sorted in ascending order
 * - Handle empty arrays (size = 0) by returning -1
 * - Handle NULL pointer by returning -1
 * - Use iterative approach (no recursion)
 * - If target appears multiple times, return ANY valid index
 * - Use integer division and avoid overflow in midpoint calculation
 */
int dsalib_binary_search(const int* arr, size_t size, int target);

/**
 * @brief Performs a recursive binary search on a SORTED array.
 *
 * This is a recursive implementation of binary search for students to
 * understand the recursive approach to divide-and-conquer algorithms.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) - due to recursion call stack
 *
 * @param arr Pointer to the SORTED array to search (must not be NULL)
 * @param left Starting index of the search range (inclusive)
 * @param right Ending index of the search range (inclusive)
 * @param target The value to search for
 * @return Index of the target if found, -1 if not found
 *
 * Requirements:
 * - Array MUST be sorted in ascending order
 * - Use recursive approach
 * - Base case: when left > right, return -1
 * - Avoid overflow in midpoint calculation
 */
int dsalib_binary_search_recursive(const int* arr, int left, int right, int target);

#endif // SEARCH_ALGORITHMS_H