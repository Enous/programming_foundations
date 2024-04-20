#include <stdio.h>
#include <memory.h>

#include "string_.h"

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#define ASSERT_BOOL(expected, got) assertBool(expected, got, \
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


void assertBool(const bool expected, bool got,
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


void test_removeExtraSpaces1()
{
    char s[] = "Just because you're  correct   doesn't mean you're   right!";
    removeExtraSpaces(s);
    ASSERT_STRING("Just because you're correct doesn't mean you're right!", s);
}


void test_removeExtraSpaces2()
{
    char s[] = "   Hello,  World!  ";
    removeExtraSpaces(s);
    ASSERT_STRING(" Hello, World! ", s);
}


void test_removeExtraSpaces3()
{
    char s[] = "";
    removeExtraSpaces(s);
    ASSERT_STRING("", s);
}


void test_moveDigitsToEnd1()
{
    char s[] = "H1e2l3l4o  8765World";
    Word w;
    char* start = s;

    while (getWord(start, &w))
    {
        moveDigitsToWordEnd(w);

        start = w.end;
    }

    ASSERT_STRING("Hello1234  World8765", s);
}


void test_moveDigitsToEnd2()
{
    char s[] = "";
    Word w;
    char* start = s;

    while (getWord(start, &w))
    {
        moveDigitsToWordEnd(w);

        start = w.end;
    }

    ASSERT_STRING("", s);
}


void test_moveDigitsToEnd3()
{
    char s[] = "   H1e2l3l4o  8765World ";
    Word w;
    char* start = s;

    while (getWord(start, &w))
    {
        moveDigitsToWordEnd(w);

        start = w.end;
    }

    ASSERT_STRING("   Hello1234  World8765 ", s);
}


void test_replaceDigitsWithDigitNumOfSpaces1()
{
    char s[] = "H1e2l3l4o";

    printf("%c", *(s + get_strlen(s)));

    replaceDigitsWithDigitNumOfSpaces(s);

    ASSERT_STRING("H e  l   l    o", s);
}


void test_replaceDigitsWithDigitNumOfSpaces2()
{
    char s[] = "12Hell34o";

    replaceDigitsWithDigitNumOfSpaces(s);

    ASSERT_STRING("   Hell       o", s);
}


void test_replaceDigitsWithDigitNumOfSpaces3()
{
    char s[] = "";

    replaceDigitsWithDigitNumOfSpaces(s);

    ASSERT_STRING("", s);
}


void test_replace1()
{
    char s[] = "Hell   o World";

    char w1[] = "Hell";
    char w2[] = "Heaven";

    replace(s, w1, w2);

    ASSERT_STRING("Heaven   o World", s);
}


void test_replace2()
{
    char s[] = "  Just because you're  correct   doesn't mean you're   right";

    char w1[] = "right";
    char w2[] = "correct";

    replace(s, w1, w2);

    ASSERT_STRING("  Just because you're  correct   doesn't mean you're   correct", s);
}


void test_replace3()
{
    char s[] = "  Just because you're  correct   doesn't mean you're   right";

    char w1[] = "correct";
    char w2[] = "right";

    replace(s, w1, w2);

    ASSERT_STRING("  Just because you're  right   doesn't mean you're   right", s);
}


void test_replace4()
{
    char s[] = "  Just because you're  correct   doesn't mean you're   right";

    char w1[] = "you're";
    char w2[] = "I'm";

    replace(s, w1, w2);

    ASSERT_STRING("  Just because I'm  correct   doesn't mean I'm   right", s);
}


void test_replace5()
{
    char s[] = "";

    char w1[] = "right";
    char w2[] = "correct";

    replace(s, w1, w2);

    ASSERT_STRING("", s);
}


void test_wordsAreInLexicographicOrder1()
{
    char s[] = "abcd acde aefg";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = true;

    ASSERT_BOOL(ans, res);
}


void test_wordsAreInLexicographicOrder2()
{
    char s[] = "apostrophe arbitrary assertion";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = true;

    ASSERT_BOOL(ans, res);
}


void test_wordsAreInLexicographicOrder3()
{
    char s[] = "apostrophe assertion arbitrary";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = false;

    ASSERT_BOOL(ans, res);
}


void test_wordsAreInLexicographicOrder4()
{
    char s[] = "";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = true;

    ASSERT_BOOL(ans, res);
}


void test_wordsAreInLexicographicOrder5()
{
    char s[] = "string string string";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = true;

    ASSERT_BOOL(ans, res);
}


void test()
{
    test_removeExtraSpaces1();
    test_removeExtraSpaces2();
    test_removeExtraSpaces3();

    test_moveDigitsToEnd1();
    test_moveDigitsToEnd2();
    test_moveDigitsToEnd3();

    test_replaceDigitsWithDigitNumOfSpaces1();
    test_replaceDigitsWithDigitNumOfSpaces2();
    test_replaceDigitsWithDigitNumOfSpaces3();

    test_replace1();
    test_replace2();
    test_replace3();
    test_replace4();
    test_replace5();

    test_wordsAreInLexicographicOrder1();
    test_wordsAreInLexicographicOrder2();
    test_wordsAreInLexicographicOrder3();
    test_wordsAreInLexicographicOrder4();
    test_wordsAreInLexicographicOrder5();
}


int main()
{
    test();
}
