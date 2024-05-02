#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "problems.h"
#include "matrix.h"
#include "string_.h"

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
        fprintf(stderr, "%s %d - failed on line %d\n", funcName, test, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    }
    else
        fprintf(stderr, "%s %d - OK\n", funcName, test);
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


void test_fsolve1()
{
    char fname[] = "problem_3-1.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s", "-3 / 9 * 2\n");

    fclose(f);

    fsolve(f, fname);

    f = fopen(fname, "r");

    int size = 2;
    char ans[2][MAX_STR_SIZE] = {"-3 / 9 * 2\n",
                                 "-0.67"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fsolve2()
{
    char fname[] = "problem_3-2.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s", "-3 + 9 * 2\n");

    fclose(f);

    fsolve(f, fname);

    f = fopen(fname, "r");

    int size = 2;
    char ans[2][MAX_STR_SIZE] = {"-3 + 9 * 2\n",
                                 "15"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fsolve3()
{
    char fname[] = "problem_3-3.txt";

    FILE* f = fopen(fname, "w");

    fprintf(f, "%s", "");

    fclose(f);

    fsolve(f, fname);

    f = fopen(fname, "r");

    int size = 1;
    char ans[1][MAX_STR_SIZE] = {""};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
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
    char fname[] = "problem_7.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("3 -7 -9 16 4 -22\n", sizeof(char), 17, f);
    fwrite("3 4 5\n", sizeof(char), 6, f);
    fwrite("-12 -5 4 4 2 -1 15\n", sizeof(char), 19, f);

    fclose(f);

    fsortPosAndNeg(f, fname);

    f = fopen(fname, "rb");

    int size = 3;
    char ans[3][MAX_STR_SIZE] = {"3 16 4 -7 -9 -22\n",
                                 "3 4 5\n",
                                 "4 4 2 15 -12 -5 -1\n"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_ftransposeIfSymmetric()
{
    char fname[] = "problem_8.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("4 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\n", sizeof(char), 41, f);
    fwrite("2 4 3 2 1\n", sizeof(char), 10, f);
    fwrite("3 3 -2 4 -2 6 2 4 2 3\n", sizeof(char), 22, f);

    fclose(f);

    ftransposeIfNonSymmetric(f, fname);

    f = fopen(fname, "rb");

    int size = 3;
    char ans[3][MAX_STR_SIZE] = {"4 1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16\n",
                                 "2 4 2 3 1\n",
                                 "3 3 -2 4 -2 6 2 4 2 3\n"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fileFormSportsTeam1()
{
    char fname[] = "problem_9-1.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("F I O 233\n", sizeof(char), 10, f);
    fwrite("I O F 546\n", sizeof(char), 10, f);
    fwrite("I F O 421\n", sizeof(char), 10, f);

    fclose(f);

    int n = 2;

    fileFormSportsTeam(f, fname, n);

    f = fopen(fname, "rb");

    int size = 2;
    char ans[2][MAX_STR_SIZE] = {"I O F 546\n",
                                 "I F O 421\n"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fileFormSportsTeam2()
{
    char fname[] = "problem_9-2.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("", sizeof(char), 1, f);

    fclose(f);

    int n = 2;

    fileFormSportsTeam(f, fname, n);

    f = fopen(fname, "rb");

    int size = 1;
    char ans[1][MAX_STR_SIZE] = {""};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fileFormSportsTeam3()
{
    char fname[] = "problem_9-3.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("F I O 233\n", sizeof(char), 10, f);
    fwrite("I O F 546\n", sizeof(char), 10, f);
    fwrite("I F O 421\n", sizeof(char), 10, f);

    fclose(f);

    int n = 4;

    fileFormSportsTeam(f, fname, n);

    f = fopen(fname, "rb");

    int size = 3;
    char ans[3][MAX_STR_SIZE] = {"I O F 546\n",
                                 "I F O 421\n",
                                 "F I O 233\n"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fwares1()
{
    char fname[] = "problem_10-1_f.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("asd 20 100 2000\n", sizeof(char), 16, f);
    fwrite("fgh 10 32 320\n", sizeof(char), 14, f);
    fwrite("jkl 5 14 70\n", sizeof(char), 12, f);

    fclose(f);

    char gname[] = "problem_10-1_g.bin";

    FILE* g = fopen(gname, "wb");

    fwrite("asd 10\n", sizeof(char), 7, g);
    fwrite("jkl 1\n", sizeof(char), 6, g);

    fclose(g);

    fwares(f, fname, g, gname);

    f = fopen(fname, "rb");

    int size = 3;
    char ans[3][MAX_STR_SIZE] = {"asd 20 90 1800\n",
                                 "fgh 10 32 320\n",
                                 "jkl 5 13 65\n"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fwares2()
{
    char fname[] = "problem_10-2_f.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("asd 20 100 2000\n", sizeof(char), 16, f);
    fwrite("fgh 10 32 320\n", sizeof(char), 14, f);
    fwrite("jkl 5 14 70\n", sizeof(char), 12, f);

    fclose(f);

    char gname[] = "problem_10-2_g.bin";

    FILE* g = fopen(gname, "wb");

    fwrite("asd 100\n", sizeof(char), 8, g);
    fwrite("jkl 14\n", sizeof(char), 7, g);

    fclose(g);

    fwares(f, fname, g, gname);

    f = fopen(fname, "rb");

    int size = 1;
    char ans[1][MAX_STR_SIZE] = {"fgh 10 32 320\n"};

    int i = 0;

    char buffer[MAX_STR_SIZE];

    while (fgets(buffer, sizeof(buffer), f) || i < size)
    {
        ASSERT_STRING(ans[i], buffer, i + 1);
        i++;
        *buffer = '\0';
    }
}


void test_fwares3()
{
    char fname[] = "problem_10-3_f.bin";

    FILE* f = fopen(fname, "wb");

    fwrite("", sizeof(char), 1, f);

    fclose(f);

    char gname[] = "problem_10-3_g.bin";

    FILE* g = fopen(gname, "wb");

    fwrite("asd 100\n", sizeof(char), 8, g);
    fwrite("jkl 14\n", sizeof(char), 7, g);

    fclose(g);

    fwares(f, fname, g, gname);

    f = fopen(fname, "rb");

    int size = 1;
    char ans[1][MAX_STR_SIZE] = {""};

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

    test_fsolve1();
    test_fsolve2();
    test_fsolve3();

    test_fsaveWordsWithSequence();

    test_fsaveOnlyLongestWordInEveryLine();

    test_fsortPosAndNeg();

    test_ftransposeIfSymmetric();

    test_fileFormSportsTeam1();
    test_fileFormSportsTeam2();
    test_fileFormSportsTeam3();

    test_fwares1();
    test_fwares2();
    test_fwares3();
}

int main()
{
    test();
}