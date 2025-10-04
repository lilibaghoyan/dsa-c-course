#include "dsalib/math/add.h"
#include <assert.h>

int main(void) {
    assert(dsalib_add(2, 3) == 5);
    assert(dsalib_add(-1, 1) == 0);
    return 0; // success
}
