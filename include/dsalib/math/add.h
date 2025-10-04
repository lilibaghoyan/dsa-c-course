#ifndef DSALIB_MATH_ADD_H
#define DSALIB_MATH_ADD_H

/**
 * @brief Performs an integer addition without any safety checks.
 */
int unsafe_add(int a, int b);

/**
 * @brief Performs an integer addition with safety checks for overflow/underflow.
 *
 * Requirements for implementation:
 * - Detect if (a + b) would cause signed integer overflow or underflow.
 * - If safe: return the correct sum.
 * - If unsafe: signal an error.
 *
 * - The current API (`int safe_add(int a, int b)`) does not provide a way
 *   to signal errors properly (since it only returns an int).
 */
int safe_add(int a, int b);

#endif // DSALIB_MATH_ADD_H
