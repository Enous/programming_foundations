#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "problems.h"
#include "matrix.h"

#define ASSERT_STRING(expected, got, test) assertString(expected, got, test, \
__FILE__, __FUNCTION__, __LINE__)

#define ASSERT(expected, got) assert(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

void assertString(const char *expected, char *got, int test,
                  char const *fileName, char const *funcName,
                  int line)
{
    if (strcmp(expected, got))
    {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s test %d - failed on line %d\n", funcName, test, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    }
    else
        fprintf(stderr, "%s test %d - OK\n", funcName, test);
}


void test_ftranspose()
{
    char fname[] = "problem_1.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s\n", "4 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
    fprintf(f, "%s\n", "2 4 3 2 1");
    fprintf(f, "%s\n", "3 3 1 3 2 4 8 3 1 7");
    fprintf(f, "%s", "");

    fclose(f);

    ftranspose(f, fname);

    f = fopen(fname, "r");

    int size = 4;
    char arr[4][MAX_STR_SIZE] = {"4 1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16\n",
                                 "2 4 2 3 1\n",
                                 "3 3 2 3 1 4 1 3 8 7",
                                 ""};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(arr[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fileFixedToFloating()
{
    char fname[] = "problem_2.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s\n", "0.000000");
    fprintf(f, "%s\n", "3.000000");
    fprintf(f, "%s\n", "4.578000");
    fprintf(f, "%s\n", "-10.321111");
    fprintf(f, "%s", "");

    fclose(f);

    fileFixedToFloating(f, fname);

    f = fopen(fname, "r");

    int size = 4;
    char arr[4][MAX_STR_SIZE] = {"0.00\n",
                                 "3.00\n",
                                 "4.58\n",
                                 "-10.32"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(arr[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test()
{
    test_ftranspose();
    test_fileFixedToFloating();
}

int main()
{
    test();
}