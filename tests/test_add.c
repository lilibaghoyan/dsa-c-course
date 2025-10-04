#include "dsalib/math/add.h"
#include <assert.h>

int main(void) {
    assert(unsafe_add(2, 3) == 5);
    assert(unsafe_add(-1, 1) == 0);
    return 0; // success
}
