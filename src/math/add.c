#include "dsalib/math/add.h"
#include <limits.h>

int unsafe_add(int a, int b) {
    return a + b;
}

int safe_add(int a, int b) {
    long long sum = (long long)a + (long long)b;
    if (sum > INT_MAX) return INT_MAX;
    if (sum < INT_MIN) return INT_MIN;
    return (int)sum;
}
