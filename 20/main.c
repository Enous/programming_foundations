#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "string_.h"
#include "problems.h"

#define ASSERT(expected, got) assert(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line)
{
    if (strcmp(expected, got))
    {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    }
    else
        fprintf(stderr, "%s - OK\n", funcName);
}


void assert(const bool expected, bool got,
            char const *fileName, char const *funcName,
            int line)
{
    if (expected != got)
    {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%d\"\n", expected);
        fprintf(stderr, "Got: \"%d\"\n\n", got);
    }
    else
        fprintf(stderr, "%s - OK\n", funcName);
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


void test_subdomainVisits1()
{
    int size = 1;
    char** cpdomains = malloc(sizeof(char*) * size);

    for (int i = 0; i < size; i++)
        cpdomains[i] = malloc(sizeof(char) * MAX_STR_SIZE);

    cpdomains[0] = "9001 discuss.leetcode.com";

    int subdomains_size;
    char** subdomains;

    subdomains = subdomainVisits(cpdomains, size, &subdomains_size);

    for (int i = 0; i < subdomains_size; i++)
        printf("%s", subdomains[i]);
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


void test_numTree()
{

}


void test()
{
    test_gameOfLife1();
    test_gameOfLife2();

    test_medianFilter1();
    test_medianFilter2();
    test_medianFilter3();

    // test_subdomainVisits1;

    test_shuffleStr1();
    test_shuffleStr2();
}


int main()
{
    test();
}
