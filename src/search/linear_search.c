#include "dsalib/search/linear_search.h"

#include <stddef.h>

int dsalib_linear_search(const int* arr, size_t size, int target) {
    for (int i = 0; i < size; i++)
    {
        if(arr[i] == target)
        {
            return i;
        }
    }
    if (size == 0 || !arr)
    {
        return -1;
    }
    return -1;
}
