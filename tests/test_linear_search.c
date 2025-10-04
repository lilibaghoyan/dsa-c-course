#include <dsalib/search/linear_search.h>

#include <assert.h>
#include <stdio.h>

void test_linear_search() {
    printf("Testing linear_search...\n");

    // Test 1: Normal case - target found
    int arr1[] = {5, 2, 8, 1, 9};
    assert(dsalib_linear_search(arr1, 5, 8) == 2);
    printf("  ✓ Test 1 passed: Found target in middle\n");

    // Test 2: Target at beginning
    assert(dsalib_linear_search(arr1, 5, 5) == 0);
    printf("  ✓ Test 2 passed: Found target at beginning\n");

    // Test 3: Target at end
    assert(dsalib_linear_search(arr1, 5, 9) == 4);
    printf("  ✓ Test 3 passed: Found target at end\n");

    // Test 4: Target not found
    assert(dsalib_linear_search(arr1, 5, 100) == -1);
    printf("  ✓ Test 4 passed: Target not found\n");

    // Test 5: Empty array
    int arr2[] = {};
    assert(dsalib_linear_search(arr2, 0, 5) == -1);
    printf("  ✓ Test 5 passed: Empty array\n");

    // Test 6: NULL pointer
    assert(dsalib_linear_search(NULL, 5, 5) == -1);
    printf("  ✓ Test 6 passed: NULL pointer handled\n");

    // Test 7: Single element - found
    int arr3[] = {42};
    assert(dsalib_linear_search(arr3, 1, 42) == 0);
    printf("  ✓ Test 7 passed: Single element found\n");

    // Test 8: Single element - not found
    assert(dsalib_linear_search(arr3, 1, 10) == -1);
    printf("  ✓ Test 8 passed: Single element not found\n");

    // Test 9: Duplicate values - returns first occurrence
    int arr4[] = {3, 7, 7, 7, 9};
    assert(dsalib_linear_search(arr4, 5, 7) == 1);
    printf("  ✓ Test 9 passed: Returns first occurrence of duplicate\n");

    // Test 10: Negative numbers
    int arr5[] = {-5, -2, 0, 3, 7};
    assert(dsalib_linear_search(arr5, 5, -2) == 1);
    printf("  ✓ Test 10 passed: Handles negative numbers\n");

    printf("All linear_search tests passed!\n\n");
}

int main() {
    printf("================================\n");
    printf("Search Algorithms Test Suite\n");
    printf("================================\n\n");

    test_linear_search();

    printf("================================\n");
    printf("All tests passed successfully!\n");
    printf("================================\n");

    return 0;
}
