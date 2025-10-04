#include <dsalib/search/binary_search.h>

#include <assert.h>
#include <stdio.h>

void test_lower_bound() {
    printf("Testing lower_bound...\n");

    // Test 1: Normal case - target exists
    int arr1[] = {1, 3, 5, 7, 9, 11, 13};
    assert(dsalib_lower_bound(arr1, 7, 7) == 3);
    printf("  ✓ Test 1 passed: Found exact match in middle\n");

    // Test 2: Target smaller than all
    assert(dsalib_lower_bound(arr1, 7, 0) == 0);
    printf("  ✓ Test 2 passed: Target smaller than all elements\n");

    // Test 3: Target larger than all
    assert(dsalib_lower_bound(arr1, 7, 20) == 7);
    printf("  ✓ Test 3 passed: Target larger than all elements (returns size)\n");

    // Test 4: Target not found - between elements
    assert(dsalib_lower_bound(arr1, 7, 6) == 3); // should point to 7
    printf("  ✓ Test 4 passed: Target not present, returns insertion point\n");

    // Test 5: Empty array
    int arr2[] = {};
    assert(dsalib_lower_bound(arr2, 0, 5) == 0);
    printf("  ✓ Test 5 passed: Empty array\n");

    // Test 6: NULL pointer
    assert(dsalib_lower_bound(NULL, 5, 5) == 0);
    printf("  ✓ Test 6 passed: NULL pointer handled\n");

    // Test 7: Single element - equal
    int arr3[] = {42};
    assert(dsalib_lower_bound(arr3, 1, 42) == 0);
    printf("  ✓ Test 7 passed: Single element equal\n");

    // Test 8: Single element - smaller
    assert(dsalib_lower_bound(arr3, 1, 10) == 0);
    printf("  ✓ Test 8 passed: Single element larger than target\n");

    // Test 9: Single element - larger
    assert(dsalib_lower_bound(arr3, 1, 50) == 1);
    printf("  ✓ Test 9 passed: Single element smaller than target\n");

    // Test 10: Duplicates - should return first occurrence
    int arr4[] = {1, 3, 3, 3, 5};
    assert(dsalib_lower_bound(arr4, 5, 3) == 1);
    printf("  ✓ Test 10 passed: Duplicates handled (first occurrence)\n");

    // Test 11: Negative numbers
    int arr5[] = {-10, -5, 0, 5, 10};
    assert(dsalib_lower_bound(arr5, 5, -5) == 1);
    assert(dsalib_lower_bound(arr5, 5, -7) == 1); // should point to -5
    assert(dsalib_lower_bound(arr5, 5, -11) == 0); // before all
    assert(dsalib_lower_bound(arr5, 5, 11) == 5); // after all
    printf("  ✓ Test 11 passed: Handles negative numbers\n");

    printf("All lower_bound tests passed!\n\n");
}

void test_binary_search() {
    printf("Testing binary_search...\n");

    // Test 1: Normal case - target found (sorted array)
    int arr1[] = {1, 3, 5, 7, 9, 11, 13};
    assert(dsalib_binary_search(arr1, 7, 7) == 3);
    printf("  ✓ Test 1 passed: Found target in middle\n");

    // Test 2: Target at beginning
    assert(dsalib_binary_search(arr1, 7, 1) == 0);
    printf("  ✓ Test 2 passed: Found target at beginning\n");

    // Test 3: Target at end
    assert(dsalib_binary_search(arr1, 7, 13) == 6);
    printf("  ✓ Test 3 passed: Found target at end\n");

    // Test 4: Target not found - too small
    assert(dsalib_binary_search(arr1, 7, 0) == -1);
    printf("  ✓ Test 4 passed: Target smaller than all elements\n");

    // Test 5: Target not found - too large
    assert(dsalib_binary_search(arr1, 7, 20) == -1);
    printf("  ✓ Test 5 passed: Target larger than all elements\n");

    // Test 6: Target not found - in range
    assert(dsalib_binary_search(arr1, 7, 6) == -1);
    printf("  ✓ Test 6 passed: Target not in sorted array\n");

    // Test 7: Empty array
    int arr2[] = {};
    assert(dsalib_binary_search(arr2, 0, 5) == -1);
    printf("  ✓ Test 7 passed: Empty array\n");

    // Test 8: NULL pointer
    assert(dsalib_binary_search(NULL, 5, 5) == -1);
    printf("  ✓ Test 8 passed: NULL pointer handled\n");

    // Test 9: Single element - found
    int arr3[] = {42};
    assert(dsalib_binary_search(arr3, 1, 42) == 0);
    printf("  ✓ Test 9 passed: Single element found\n");

    // Test 10: Single element - not found
    assert(dsalib_binary_search(arr3, 1, 10) == -1);
    printf("  ✓ Test 10 passed: Single element not found\n");

    // Test 11: Two elements
    int arr4[] = {5, 10};
    assert(dsalib_binary_search(arr4, 2, 5) == 0);
    assert(dsalib_binary_search(arr4, 2, 10) == 1);
    printf("  ✓ Test 11 passed: Two elements\n");

    // Test 12: Even number of elements
    int arr5[] = {2, 4, 6, 8};
    assert(dsalib_binary_search(arr5, 4, 6) == 2);
    printf("  ✓ Test 12 passed: Even number of elements\n");

    // Test 13: Negative numbers
    int arr6[] = {-10, -5, 0, 5, 10};
    assert(dsalib_binary_search(arr6, 5, -5) == 1);
    printf("  ✓ Test 13 passed: Handles negative numbers\n");

    // Test 14: Large sorted array
    int arr7[100];
    for (int i = 0; i < 100; i++) {
        arr7[i] = i * 2; // 0, 2, 4, 6, ..., 198
    }
    assert(dsalib_binary_search(arr7, 100, 50) == 25);
    assert(dsalib_binary_search(arr7, 100, 51) == -1);
    printf("  ✓ Test 14 passed: Large array\n");

    printf("All binary_search tests passed!\n\n");
}

void test_binary_search_recursive() {
    printf("Testing binary_search_recursive...\n");

    // Test 1: Normal case
    int arr1[] = {1, 3, 5, 7, 9, 11, 13};
    assert(dsalib_binary_search_recursive(arr1, 0, 6, 7) == 3);
    printf("  ✓ Test 1 passed: Found target in middle\n");

    // Test 2: Target at beginning
    assert(dsalib_binary_search_recursive(arr1, 0, 6, 1) == 0);
    printf("  ✓ Test 2 passed: Found target at beginning\n");

    // Test 3: Target at end
    assert(dsalib_binary_search_recursive(arr1, 0, 6, 13) == 6);
    printf("  ✓ Test 3 passed: Found target at end\n");

    // Test 4: Target not found
    assert(dsalib_binary_search_recursive(arr1, 0, 6, 6) == -1);
    printf("  ✓ Test 4 passed: Target not found\n");

    // Test 5: Empty range (left > right)
    assert(dsalib_binary_search_recursive(arr1, 5, 2, 5) == -1);
    printf("  ✓ Test 5 passed: Empty range\n");

    // Test 6: Single element - found
    int arr2[] = {42};
    assert(dsalib_binary_search_recursive(arr2, 0, 0, 42) == 0);
    printf("  ✓ Test 6 passed: Single element found\n");

    // Test 7: Single element - not found
    assert(dsalib_binary_search_recursive(arr2, 0, 0, 10) == -1);
    printf("  ✓ Test 7 passed: Single element not found\n");

    // Test 8: Search in subrange
    int arr3[] = {1, 3, 5, 7, 9};
    assert(dsalib_binary_search_recursive(arr3, 1, 3, 5) == 2);
    printf("  ✓ Test 8 passed: Search in subrange\n");

    // Test 9: Negative numbers
    int arr4[] = {-10, -5, 0, 5, 10};
    assert(dsalib_binary_search_recursive(arr4, 0, 4, -5) == 1);
    printf("  ✓ Test 9 passed: Handles negative numbers\n");

    printf("All binary_search_recursive tests passed!\n\n");
}

int main() {
    printf("================================\n");
    printf("Search Algorithms Test Suite\n");
    printf("================================\n\n");

    test_lower_bound();
    test_binary_search();
    test_binary_search_recursive();

    printf("================================\n");
    printf("All tests passed successfully!\n");
    printf("================================\n");

    return 0;
}
