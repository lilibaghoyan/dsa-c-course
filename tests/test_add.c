#include "dsalib/add.h"
#include <assert.h>

int main(void) {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    return 0; // success
}
