#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"

void test_swapRows()
{
    int rows_count = 3;
    int cols_count = 2;

    matrix mx = getMemMatrix(rows_count, cols_count);

    mx.values[0][0] = 1;
    mx.values[0][1] = 2;

    mx.values[1][0] = 3;
    mx.values[1][1] = 4;

    mx.values[2][0] = 5;
    mx.values[2][1] = 6;

    int i1 = 0;
    int i2 = 2;

    swapRows(mx, i1, i2);

    assert(mx.values[i1][0] == 5);
    assert(mx.values[i1][1] == 6);
    assert(mx.values[i2][0] == 1);
    assert(mx.values[i2][1] == 2);

    freeMemMatrix(&mx);
}


void test_swapCols()
{
    int rows_count = 2;
    int cols_count = 3;

    matrix mx = getMemMatrix(rows_count, cols_count);

    mx.values[0][0] = 1;
    mx.values[0][1] = 2;
    mx.values[0][2] = 3;

    mx.values[1][0] = 4;
    mx.values[1][1] = 5;
    mx.values[1][2] = 6;

    int j1 = 0;
    int j2 = 2;

    swapCols(mx, j1, j2);

    assert(mx.values[0][j1] == 3);
    assert(mx.values[1][j1] == 6);
    assert(mx.values[0][j2] == 1);
    assert(mx.values[1][j2] == 4);

    freeMemMatrix(&mx);
}


void test()
{
    test_swapRows();
    test_swapCols();
}


int main()
{
    test();
}
