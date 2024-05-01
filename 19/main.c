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
    char ans[4][MAX_STR_SIZE] = {"4 1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16\n",
                                 "2 4 2 3 1\n",
                                 "3 3 2 3 1 4 1 3 8 7",
                                 ""};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
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
    char ans[4][MAX_STR_SIZE] = {"0.00\n",
                                 "3.00\n",
                                 "4.58\n",
                                 "-10.32"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fsolve()
{
    char fname[] = "problem_3-1.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s\n", "3 + 9");

    fclose(f);

    fsolve(f, fname);

    f = fopen(fname, "r");

    char ans[MAX_STR_SIZE] = {"12"};
    char buffer[MAX_STR_SIZE];
    int i = 0;

    fgets(buffer, sizeof(buffer), f);

    ASSERT_STRING(ans, buffer, i + 1);

    i++;
    *buffer = '\0';
    *ans = '\0';
}


void test_fsaveWordsWithSequence()
{
    char fname[] = "problem_4-1.txt";

    FILE* f = fopen(fname, "w");
    fprintf(f, "%s", "ab123cd ef12 3g 123hi jklm n o1p2q3 rs tuvw 1x 2y 123z");
    fclose(f);

    char sequence[] = "123";

    fsaveWordsWithSequence(f, fname, sequence);

    f = fopen(fname, "r");

    char ans[] = "ab123cd 123hi 123z";
    char buffer[MAX_STR_SIZE];
    int i = 1;

    fgets(buffer, sizeof(buffer), f);

    ASSERT_STRING(ans, buffer, i);

    i++;
    *buffer = '\0';
    *ans = '\0';
    *sequence = '\0';

    memcpy(fname, "problem_4-2", 11);

    f = fopen(fname, "w");
    fprintf(f, "%s", "");
    fclose(f);

    memcpy(sequence, "asd", 3);

    fsaveWordsWithSequence(f, fname, sequence);

    f = fopen(fname, "r");

    memcpy(ans, "", 0);

    fgets(buffer, sizeof(buffer), f);

    ASSERT_STRING(ans, buffer, i);
}


void test_fsaveOnlyLongestWordInEveryLine()
{
    char fname[] = "problem_5.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s\n", "asfe 1safj 8gfhslke 3smdf 00 ker");
    fprintf(f, "%s\n", "ohongeww lbl i");
    fprintf(f, "%s", "@#$%&! &$#$ $%$%#$@!&");

    fclose(f);

    fsaveOnlyLongestWordInEveryLine(f, fname);

    f = fopen(fname, "r");

    int size = 3;
    char ans[3][MAX_STR_SIZE] = {"8gfhslke\n",
                                 "ohongeww\n",
                                 "$%$%#$@!&"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }

    *buffer = '\0';
}


void test_fsortPosAndNeg()
{
    char fname[] = "problem_7.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s\n", "3 -7 -9 16 4 -22");
    fprintf(f, "%s\n", "3 4 5");
    fprintf(f, "%s", "-12 -5 4 4 2 -1 15");

    fclose(f);

    fsortPosAndNeg(f, fname);

    f = fopen(fname, "r");

    int size = 3;
    char ans[3][MAX_STR_SIZE] = {"3 16 4 -7 -9 -22\n",
                                 "3 4 5\n",
                                 "4 4 2 15 -12 -5 -1"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test()
{
    test_ftranspose();
    test_fileFixedToFloating();
    // test_fsolve();
    test_fsaveWordsWithSequence();
    test_fsaveOnlyLongestWordInEveryLine();
    test_fsortPosAndNeg();
}

int main()
{
    test();
}