#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "problems.h"


bool arraysAreEqual(int* arr1, int size1, int* arr2, int size2)
{
    if (size1 != size2)
        return false;

    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size1; j++)
        {
            if (arr1[i] != arr1[j])
                return false;
        }
    }

    return true;
}


void test_matrixAdd1()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0
            }, rows_count1, cols_count1);

    int size = 2;

    int arr1[2][SUBMAT_CORNER_COORDS] = {{1, 1, 2, 2}, {0, 0, 1, 1}};
    int** arr2 = malloc(sizeof(int*) * size);

    for (int i = 0; i < size; i++)
        arr2[i] = malloc(sizeof(int) * SUBMAT_CORNER_COORDS);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < SUBMAT_CORNER_COORDS; j++)
            arr2[i][j] = arr1[i][j];
    }

    matrixAdd(&mx1, arr2, size);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    1, 2, 1,
                    0, 1, 1
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    ASSERT(res, ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);

    for (int i = 0; i < size; i++)
        free(arr2[i]);

    free(arr2);
}


void test_matrixAdd2()
{
    int rows_count1 = 5;
    int cols_count1 = 5;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0
            }, rows_count1, cols_count1);

    int size = 3;

    int arr1[3][SUBMAT_CORNER_COORDS] = {{0, 3, 1, 4},
                                         {0, 0, 3, 3},
                                         {2, 0, 4, 2}};
    int** arr2 = malloc(sizeof(int*) * size);

    for (int i = 0; i < size; i++)
        arr2[i] = malloc(sizeof(int) * SUBMAT_CORNER_COORDS);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < SUBMAT_CORNER_COORDS; j++)
            arr2[i][j] = arr1[i][j];
    }

    matrixAdd(&mx1, arr2, size);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                1, 1, 1, 2, 1,
                1, 1, 1, 2, 1,
                2, 2, 2, 1, 0,
                2, 2, 2, 1, 0,
                1, 1, 1, 0, 0
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    ASSERT(res, ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);

    for (int i = 0; i < size; i++)
        free(arr2[i]);

    free(arr2);
}


void test_gameOfLife1()
{
    int rows_count1 = 4;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    0, 1, 0,
                    0, 0, 1,
                    1, 1, 1,
                    0, 0, 0
            }, rows_count1, cols_count1);

    matrix mx2 = gameOfLife(mx1);

    matrix mx3 = createMatrixFromArray(
            (int[]) {
                    0, 0, 0,
                    1, 0, 1,
                    0, 1, 1,
                    0, 1, 0
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx2, &mx3);
    bool ans = true;

    ASSERT(res, ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
    freeMemMatrix(&mx3);
}


void test_gameOfLife2()
{
    int rows_count1 = 4;
    int cols_count1 = 6;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    0, 1, 0, 1, 1, 0,
                    0, 0, 1, 0, 0, 1,
                    1, 1, 1, 1, 0, 0,
                    0, 0, 0, 0, 1, 1
            }, rows_count1, cols_count1);

    matrix mx2 = gameOfLife(mx1);

    matrix mx3 = createMatrixFromArray(
            (int[]) {
                    0, 0, 1, 1, 1, 0,
                    1, 0, 0, 0, 0, 0,
                    0, 1, 1, 1, 0, 1,
                    0, 1, 1, 1, 1, 0
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx2, &mx3);
    bool ans = true;

    ASSERT(res, ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
    freeMemMatrix(&mx3);
}


void test_medianFilter1()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30,
                    25, 35, 45,
                    15, 25, 35
            }, rows_count1, cols_count1);

    int window_size = 3;

    medianFilter(&mx1, window_size);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30,
                    25, 25, 45,
                    15, 25, 35
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    ASSERT(res, ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_medianFilter2()
{
    int rows_count1 = 6;
    int cols_count1 = 7;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30, 45, 40, 50, 50,
                    25, 35, 45, 30, 10, 55, 45,
                    15, 25, 35, 15, 20, 35, 25,
                    15, 15, 30, 45, 20, 50, 25,
                    40, 25, 30, 30, 15, 10, 45,
                    15, 40, 45, 50, 30, 55, 10
            }, rows_count1, cols_count1);

    int window_size = 5;

    medianFilter(&mx1, window_size);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30, 45, 40, 50, 50,
                    25, 35, 45, 30, 10, 55, 45,
                    15, 25, 25, 30, 30, 35, 25,
                    15, 15, 30, 30, 30, 50, 25,
                    40, 25, 30, 30, 15, 10, 45,
                    15, 40, 45, 50, 30, 55, 10
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    ASSERT(res, ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_medianFilter3()
{
    int rows_count1 = 6;
    int cols_count1 = 7;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30, 45, 40, 50, 50,
                    25, 35, 45, 30, 10, 55, 45,
                    15, 25, 35, 15, 20, 35, 25,
                    15, 15, 30, 45, 20, 50, 25,
                    40, 25, 30, 30, 15, 10, 45,
                    15, 40, 45, 50, 30, 55, 10
            }, rows_count1, cols_count1);

    int window_size = 7;

    medianFilter(&mx1, window_size);

    matrix mx2 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30, 45, 40, 50, 50,
                    25, 35, 45, 30, 10, 55, 45,
                    15, 25, 35, 15, 20, 35, 25,
                    15, 15, 30, 45, 20, 50, 25,
                    40, 25, 30, 30, 15, 10, 45,
                    15, 40, 45, 50, 30, 55, 10
            }, rows_count1, cols_count1);

    bool res = TwoMatricesAreEqual(&mx1, &mx2);
    bool ans = true;

    ASSERT(res, ans);

    freeMemMatrix(&mx1);
    freeMemMatrix(&mx2);
}


void test_buildTree1()
{

}


void test_shuffleStr1()
{
    int size = 3;
    char* s = malloc(sizeof(char) * (size + 1));
    strcpy(s, "abc");

    int* indices = malloc(sizeof(int) * size);
    memcpy(indices, (int[]) {0, 1, 2}, sizeof(int) * size);

    shuffleStr(s, indices, size);

    ASSERT_STRING("abc", s);

    free(s);
    free(indices);
}


void test_shuffleStr2()
{
    int size = 4;
    char* s = malloc(sizeof(char) * (size + 1));
    strcpy(s, "abap");

    int* indices = malloc(sizeof(int) * size);
    memcpy(indices, (int[]) {0, 3, 2, 1}, sizeof(int) * size);

    shuffleStr(s, indices, size);

    ASSERT_STRING("apab", s);

    free(s);
    free(indices);
}


void test_submatricesThatContainOnlyDigit1()
{
    int rows_count1 = 3;
    int cols_count1 = 3;

    matrix mx1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1,
                    1, 1, 0,
                    1, 1, 0
            }, rows_count1, cols_count1);

    int res = submatricesThatContainOnlyDigit1(mx1);
    int ans = 13;

    ASSERT(ans, res);

    freeMemMatrix(&mx1);
}


void test_outputAns()
{
    int n = 10;
    int q = 3;
    char dict[MAX_SIZE][MAX_STR_SIZE] = {"aa", "aaa", "aab",
                                      "ab", "abc", "ac",
                                      "ba", "daa", "dab", "dadba"};

    query queries[3] = {{4, "a"}, {2, "da"}, {4, "da"}};

    //outputAns(dict, n, queries, q);
}


void test_smallestNum1()
{
    char* pattern = malloc(sizeof(char) * (MAX_DIGIT + 1));
    strcpy(pattern, "IIIDIDDD");

    char* res = smallestNum(pattern);

    ASSERT_STRING("123549876", res);

    free(res);
    free(pattern);
}


void test_smallestNum2()
{
    char* pattern = malloc(sizeof(char) * (MAX_DIGIT + 1));
    strcpy(pattern, "DDD");

    char* res = smallestNum(pattern);

    ASSERT_STRING("4321", res);

    free(res);
    free(pattern);
}


void test_subdomainVisits1()
{
    char** d = malloc(sizeof(char*) * MAX_SIZE);
    int size = 1;

    for (int i = 0; i < size; i++)
        d[i] = malloc(sizeof(char) * MAX_STR_SIZE);

    strcpy(d[0], "9001 discuss.codeforces.com");

    int rsize;

    char** t = subdomainVisits(d, size, &rsize);

    char ans_size = 3;

    ASSERT(ans_size, rsize);

    for (int i = 0; i < rsize; i++)
    {
        printf("%s\n", t[i]);
        free(t[i]);
    }

    free(t);
}


void test_subdomainVisits2()
{
    char** d = malloc(sizeof(char*) * MAX_SIZE);
    int size = 4;

    for (int i = 0; i < size; i++)
        d[i] = malloc(sizeof(char) * MAX_STR_SIZE);

    strcpy(d[0], "900 google.mail.com");
    strcpy(d[1], "50 yahoo.com");
    strcpy(d[2], "1 intel.mail.com");
    strcpy(d[3], "5 wiki.org");

    int rsize;

    char** t = subdomainVisits(d, size, &rsize);

    char ans_size = 7;

    ASSERT(ans_size, rsize);

    for (int i = 0; i < rsize; i++)
    {
        printf("%s\n", t[i]);
        free(t[i]);
    }

    free(t);
}


void test()
{
    test_matrixAdd1();
    test_matrixAdd2();

    test_gameOfLife1();
    test_gameOfLife2();

    test_subdomainVisits1();
    test_subdomainVisits2();

    test_medianFilter1();
    test_medianFilter2();
    test_medianFilter3();

    test_submatricesThatContainOnlyDigit1();

    test_smallestNum1();
    test_smallestNum2();

    test_buildTree1();

    test_shuffleStr1();
    test_shuffleStr2();

    test_outputAns();
}


int main()
{
    test();
}
