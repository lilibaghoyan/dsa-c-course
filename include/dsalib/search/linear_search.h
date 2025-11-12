#ifndef DSALIB_LINEAR_SEARCH_H
#define DSALIB_LINEAR_SEARCH_H

#include <stddef.h>

/**
 * @brief Performs a linear search on an array to find a target value.
 *
 * This function searches through the array sequentially from the beginning
 * to the end until it finds the target value or reaches the end of the array.
 *
 * Time Complexity: O(n) - where n is the size of the array
 * Space Complexity: O(1)
 *
 * @param arr Pointer to the array to search (must not be NULL)
 * @param size Number of elements in the array
 * @param target The value to search for
 * @return Index of the target if found, -1 if not found
 *
 * Requirements:
 * - Handle empty arrays (size = 0) by returning -1
 * - Handle NULL pointer by returning -1
 * - Return the index of the FIRST occurrence if target appears multiple times
 * - Array does not need to be sorted
 */
int dsalib_linear_search(const int* arr, size_t size, int target);

#endif // DSALIB_LINEAR_SEARCH_H
