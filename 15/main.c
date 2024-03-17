#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "matrix.h"

void test_swapRows()
{
    int rows_count1 = 3;
    int cols_count1 = 2;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    3, 4,
                    5, 6
                    }, rows_count1, cols_count1);

    int i1 = 0;
    int i2 = 2;

    swapRows(mx1, i1, i2);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    5, 6,
                    3, 4,
                    1, 2
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_swapCols()
{
    int rows_count1 = 2;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6
            }, rows_count1, cols_count1);

    int j1 = 0;
    int j2 = 2;

    swapCols(mx1, j1, j2);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    6, 5, 4
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_insertionSortMatrixRows()
{
    int rows_count1 = 3;
    int cols_count1 = 5;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 4, 3, 6,
                    7, 5, 5, 5, 8,
                    5, 3, 4, 3, 5
            }, rows_count1, cols_count1);

    insertionSortMatrixRows(mx1, getSum);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    5, 3, 4, 3, 5,
                    3, 5, 4, 3, 6,
                    7, 5, 5, 5, 8
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_selectionSortMatrixCols()
{
    int rows_count1 = 3;
    int cols_count1 = 5;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 4, 3, 6,
                    7, 5, 5, 5, 8,
                    5, 3, 4, 3, 5
            }, rows_count1, cols_count1);

    selectionSortMatrixCols(mx1, getSum);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    3, 5, 4, 3, 6,
                    5, 5, 5, 7, 8,
                    3, 3, 4, 5, 5
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_isSquareMatrix()
{
    int rows_count = 2;
    int cols_count = 3;

    matrix mx = getMemMatrix(rows_count, cols_count);

    bool res = isSquareMatrix(&mx);
    bool ans = false;

    assert(res == ans);

    freeMemMatrix(&mx);
}


void test_TwoMatricesAreEqual()
{
    int rows_count1 = 3;
    int cols_count1 = 5;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 4, 3, 6,
                    5, 5, 5, 7, 8,
                    3, 3, 4, 5, 5
            }, rows_count1, cols_count1);

    int rows_count2 = 3;
    int cols_count2 = 5;

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    3, 5, 4, 3, 6,
                    5, 5, 5, 7, 8,
                    3, 3, 4, 5, 5
            }, rows_count2, cols_count2);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_isIdentityMatrix1()
{
    int rows_count = 4;
    int cols_count = 4;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
            }, rows_count, cols_count);

    bool res = isIdentityMatrix(&mx);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx);
}


void test_isIdentityMatrix2()
{
    int rows_count = 4;
    int cols_count = 4;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    0, 0, 0, 1,
                    0, 0, 1, 0,
                    0, 1, 0, 0,
                    1, 0, 0, 0
            }, rows_count, cols_count);

    bool res = isIdentityMatrix(&mx);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx);
}


void test_isSymmetricMatrix()
{
    int rows_count = 3;
    int cols_count = 3;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    1, 7, 3,
                    7, 4, 5,
                    3, 5, 2,
            }, rows_count, cols_count);

    bool res = isSymmetricMatrix(&mx);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx);
}


void test_transposeSquareMatrix()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, rows_count1, cols_count1);

    int rows_count2 = 3;
    int cols_count2 = 3;

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9
            }, rows_count2, cols_count2);

    transposeSquareMatrix(&mx1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_transposeMatrix1()
{
    int rows_count1 = 3;
    int cols_count1 = 2;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 4,
                    2, 5,
                    3, 6
            }, rows_count1, cols_count1);

    int rows_count2 = 2;
    int cols_count2 = 3;

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6
            }, rows_count2, cols_count2);

    transposeMatrix(&mx1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);
    assert(mx1.rows_count == mx2.rows_count && mx1.cols_count == mx2.cols_count);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_transposeMatrix2()
{
    int rows_count1 = 2;
    int cols_count1 = 4;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 4,
                    5, 6, 7, 8
            }, rows_count1, cols_count1);

    int rows_count2 = 4;
    int cols_count2 = 2;

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    1, 5,
                    2, 6,
                    3, 7,
                    4, 8
            }, rows_count2, cols_count2);

    transposeMatrix(&mx1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    assert(res == ans);
    assert(mx1.rows_count == mx2.rows_count && mx1.cols_count == mx2.cols_count);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_getMinValuePos1()
{
    int rows_count = 3;
    int cols_count = 2;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    4, 5,
                    7, 8
            }, rows_count, cols_count);

    position res = getMinValuePos(mx);
    position ans = {0, 0};

    assert(res.row_idx == ans.row_idx && res.col_idx == ans.col_idx);

    freeMemMatrix(&mx);
}


void test_getMinValuePos2()
{
    int rows_count = 4;
    int cols_count = 2;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    3, 9,
                    11, 4,
                    2, 8,
                    7, 10
            }, rows_count, cols_count);

    position res = getMinValuePos(mx);
    position ans = {2, 0};

    assert(res.row_idx == ans.row_idx && res.col_idx == ans.col_idx);

    freeMemMatrix(&mx);
}


void test_getMinValuePos3()
{
    int rows_count = 4;
    int cols_count = 2;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    3, 9,
                    11, 4,
                    3, 8,
                    7, 2
            }, rows_count, cols_count);

    position res = getMinValuePos(mx);
    position ans = {3, 1};

    assert(res.row_idx == ans.row_idx && res.col_idx == ans.col_idx);

    freeMemMatrix(&mx);
}


void test_getMaxValuePos1()
{
    int rows_count = 3;
    int cols_count = 2;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    12, 9,
                    11, 4,
                    3, 8
            }, rows_count, cols_count);

    position res = getMaxValuePos(mx);
    position ans = {0, 0};

    assert(res.row_idx == ans.row_idx && res.col_idx == ans.col_idx);

    freeMemMatrix(&mx);
}


void test_getMaxValuePos2()
{
    int rows_count = 3;
    int cols_count = 2;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    3, 9,
                    4, 11,
                    3, 8
            }, rows_count, cols_count);

    position res = getMaxValuePos(mx);
    position ans = {1, 1};

    assert(res.row_idx == ans.row_idx && res.col_idx == ans.col_idx);

    freeMemMatrix(&mx);
}


void test_getMaxValuePos3()
{
    int rows_count = 3;
    int cols_count = 2;

    matrix mx = createMatrixFromArray(
            (int[]) {
                    3, 9,
                    4, 11,
                    3, 14
            }, rows_count, cols_count);

    position res = getMaxValuePos(mx);
    position ans = {2, 1};

    assert(res.row_idx == ans.row_idx && res.col_idx == ans.col_idx);

    freeMemMatrix(&mx);
}


void test()
{
    test_swapRows();
    test_swapCols();
    test_insertionSortMatrixRows();
    test_selectionSortMatrixCols();
    test_isSquareMatrix();
    test_TwoMatricesAreEqual();
    test_isIdentityMatrix1();
    test_isIdentityMatrix2();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();
    test_transposeMatrix1();
    test_transposeMatrix2();
    test_getMinValuePos1();
    test_getMinValuePos2();
    test_getMinValuePos3();
    test_getMaxValuePos1();
    test_getMaxValuePos2();
    test_getMaxValuePos3();
}


int main()
{
    test();
}
