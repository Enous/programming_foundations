#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "funcs.h"
#include "matrix.h"

void test_swapRowsWithMinAndMaxELems1()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, rows_count1, cols_count1);

    swapRowsWithMinAndMaxELems(&mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    7, 8, 9,
                    4, 5, 6,
                    1, 2, 3
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_swapRowsWithMinAndMaxELems2()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 9,
                    4, 5, 6,
                    7, 8, 7
            }, rows_count1, cols_count1);

    swapRowsWithMinAndMaxELems(&mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 9,
                    4, 5, 6,
                    7, 8, 7
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_sortMatrixRowsByMaxRowElem()
{
    int rows_count1 = 4;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    6, 5, 4,
                    3, 2, 1,
                    10, 3, 5,
                    7, 1, 4
            }, rows_count1, cols_count1);

    sortMatrixRowsByMaxRowElem(&mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    6, 5, 4,
                    7, 1, 4,
                    10, 3, 5
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test()
{
    test_swapRowsWithMinAndMaxELems1();
    test_swapRowsWithMinAndMaxELems2();
    test_sortMatrixRowsByMaxRowElem();
}


int main()
{
    test();
}
