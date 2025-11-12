#include "dsalib/search/binary_search.h"

#include <limits.h>
#include <stddef.h>

size_t dsalib_lower_bound(const int* arr, size_t size, int target) {
    if (size == 0 || !arr)
    {
        return 0;
    }
    size_t left = 0, right = size;
    while (left < right)
    {
        size_t mid = left + (right  - left) / 2;
        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return left;
}

int dsalib_binary_search(const int* arr, size_t size, int target) {
    if (size == 0 || !arr)
        {
            return -1;
        }
    size_t left = 0, right = size;
    while (left < right)
    {
        size_t mid = left + (right  - left) / 2;
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return -1;
}

int dsalib_binary_search_recursive(const int* arr, int left, int right, int target) {
    if (!arr || left > right)
    {
        return -1;
    }
    int mid = left + (right  - left) / 2;
    if (arr[mid] == target)
    {
        return mid;
    }
    if (arr[mid] < target)
    {
        return dsalib_binary_search_recursive(arr, mid + 1, right, target);
    }
    else {
        return dsalib_binary_search_recursive(arr, left, mid - 1, target);
    }
}
