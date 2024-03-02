#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include <stdbool.h>
#include <assert.h>

int main()
{
    vector v = createVector(14);
    v.size = 13;

    reserve(&v, 12);

    printf("%d", v.size);

    return 0;
}