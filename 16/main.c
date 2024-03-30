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
                    4, 5, 6,
                    3, 2, 1,
                    5, 3, 10,
                    1, 7, 4
            }, rows_count1, cols_count1);

    sortMatrixRowsByMaxRowElem(&mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    4, 5, 6,
                    1, 7, 4,
                    5, 3, 10
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_sortMatrixColsByMinColElem()
{
    int rows_count1 = 3;
    int cols_count1 = 6;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 2, 4, 3, 3,
                    2, 5, 1, 8, 2, 7,
                    6, 1, 4, 4, 8, 3
            }, rows_count1, cols_count1);

    sortMatrixColsByMinColElem(&mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    5, 2, 3, 3, 3, 4,
                    5, 1, 2, 2, 7, 8,
                    1, 4, 6, 8, 3, 4
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_raiseMatrixToTheSecondPowerIfSymmetric1()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    2, 3, 6,
                    3, 4, 5,
                    6, 5, 9
            }, rows_count1, cols_count1);

    raiseMatrixToTheSecondPowerIfSymmetric(&mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    49, 48, 81,
                    48, 50, 83,
                    81, 83, 142
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_raiseMatrixToTheSecondPowerIfSymmetric2()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    2, 3, 6,
                    7, 4, 5,
                    6, 5, 9
            }, rows_count1, cols_count1);

    raiseMatrixToTheSecondPowerIfSymmetric(&mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    61, 48, 81,
                    72, 62, 107,
                    101, 83, 142
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = false;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_transposeMatrixIfThereAreNoEqualRowElemSums1()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    2, 3, 6,
                    7, 4, 1,
                    8, 12, 9
            }, rows_count1, cols_count1);

    transposeMatrixIfThereAreNoEqualRowElemSums(mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    2, 7, 8,
                    3, 4, 12,
                    6, 1, 9
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_transposeMatrixIfThereAreNoEqualRowElemSums2()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    2, 3, 6,
                    6, 4, 1,
                    8, 12, 9
            }, rows_count1, cols_count1);

    transposeMatrixIfThereAreNoEqualRowElemSums(mx1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    2, 3, 6,
                    6, 4, 1,
                    8, 12, 9
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_twoSquareMatricesAreInversesOfEachOther()
{
    int rows_count1 = 2;
    int cols_count1 = 2;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    3, -2,
                    -1, 1
            }, rows_count1, cols_count1);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    1, 3
            }, rows_count1, cols_count1);

    bool res = twoSquareMatricesAreInversesOfEachOther(mx1, mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_getSumOfPseudoDiagonalsMaxElems1()
{
    int rows_count1 = 3;
    int cols_count1 = 4;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    3, 2, 5, 4,
                    1, 3, 6, 3,
                    3, 2, 1, 2
            }, rows_count1, cols_count1);

    long long res = getSumOfPseudoDiagonalsMaxElems(mx1);
    long long ans = 23;

    assert(res == ans);

    freeMemMatrix(&mx1);
}


void test_getSumOfPseudoDiagonalsMaxElems2()
{
    int rows_count1 = 1;
    int cols_count1 = 2;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    4, 6
            }, rows_count1, cols_count1);

    long long res = getSumOfPseudoDiagonalsMaxElems(mx1);
    long long ans = 10;

    assert(res == ans);

    freeMemMatrix(&mx1);
}


void test_getSumOfPseudoDiagonalsMaxElems3()
{
    int rows_count1 = 2;
    int cols_count1 = 1;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    4,
                    6
            }, rows_count1, cols_count1);

    long long res = getSumOfPseudoDiagonalsMaxElems(mx1);
    long long ans = 10;

    assert(res == ans);

    freeMemMatrix(&mx1);
}


void test()
{
    test_swapRowsWithMinAndMaxELems1();
    test_swapRowsWithMinAndMaxELems2();
    test_sortMatrixRowsByMaxRowElem();
    test_sortMatrixColsByMinColElem();
    test_raiseMatrixToTheSecondPowerIfSymmetric1();
    test_raiseMatrixToTheSecondPowerIfSymmetric2();
    test_transposeMatrixIfThereAreNoEqualRowElemSums1();
    test_transposeMatrixIfThereAreNoEqualRowElemSums2();
    test_twoSquareMatricesAreInversesOfEachOther();
    test_getSumOfPseudoDiagonalsMaxElems1();
    test_getSumOfPseudoDiagonalsMaxElems2();
    test_getSumOfPseudoDiagonalsMaxElems3();
}


int main()
{
    test();
}
