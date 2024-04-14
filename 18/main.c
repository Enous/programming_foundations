#include <stdio.h>

#include "string_.h"

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


void test_removeExtraSpaces()
{
    char s[] = "Just because you're  correct   doesn't mean you're   right!";
    removeExtraSpaces(s);
    ASSERT_STRING("Just because you're correct doesn't mean you're right!", s);
}


void test()
{
    test_removeExtraSpaces();
}


int main()
{
    test();
}
