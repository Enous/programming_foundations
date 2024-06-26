#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

#include "string_.h"

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#define ASSERT(expected, got) assert(expected, got, \
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

    ASSERT(ans, res);
}


void test_wordsAreInLexicographicOrder2()
{
    char s[] = "apostrophe arbitrary assertion";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = true;

    ASSERT(ans, res);
}


void test_wordsAreInLexicographicOrder3()
{
    char s[] = "apostrophe assertion arbitrary";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = false;

    ASSERT(ans, res);
}


void test_wordsAreInLexicographicOrder4()
{
    char s[] = "";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = true;

    ASSERT(ans, res);
}


void test_wordsAreInLexicographicOrder5()
{
    char s[] = "string string string";

    bool res = wordsAreInLexicographicOrder(s);
    bool ans = true;

    ASSERT(ans, res);
}


void test_countPalindromeWords1()
{
    char s[] = "radar string level";

    int res = countPalindromeWords(s);
    int ans = 2;

    ASSERT(ans, res);
}


void test_countPalindromeWords2()
{
    char s[] = "   noon string ";

    int res = countPalindromeWords(s);
    int ans = 1;

    ASSERT(ans, res);
}


void test_countPalindromeWords3()
{
    char s[] = "  Just because you're  correct   doesn't mean you're   right";

    int res = countPalindromeWords(s);
    int ans = 0;

    ASSERT(ans, res);
}


void test_mixStrings1()
{
    char s1[] = "  Just you're  doesn't    you're  ";
    char s2[] = " because   correct mean  right   ";

    char* res = mixStrings(s1, s2);

    ASSERT_STRING("Just because you're correct doesn't mean you're right", res);

    free(res);
}


void test_mixStrings2()
{
    char s1[] = "  Just you're  doesn't    you're  ";
    char s2[] = " because";

    char* res = mixStrings(s1, s2);

    ASSERT_STRING("Just because you're doesn't you're", res);

    free(res);
}


void test_mixStrings3()
{
    char s1[] = "";
    char s2[] = " because   correct mean  right   ";

    char* res = mixStrings(s1, s2);

    ASSERT_STRING("because correct mean right", res);

    free(res);
}


void test_mixStrings4()
{
    char s1[] = "  Just you're  doesn't    you're  ";
    char s2[] = "";

    char* res = mixStrings(s1, s2);

    ASSERT_STRING("Just you're doesn't you're", res);

    free(res);
}


void test_mixStrings5()
{
    char s1[] = "";
    char s2[] = "";

    char* res = mixStrings(s1, s2);

    ASSERT_STRING("", res);

    free(res);
}


void test_reverseWordOrder1()
{
    char s[] = "  Just ";

    reverseWordOrder(s);

    ASSERT_STRING("Just", s);
}


void test_reverseWordOrder2()
{
    char s[] = "  Just because you're  correct   doesn't mean you're   right";

    reverseWordOrder(s);

    ASSERT_STRING("right you're mean doesn't correct you're because Just", s);
}


void test_reverseWordOrder3()
{
    char s[] = "";

    reverseWordOrder(s);

    ASSERT_STRING("", s);
}


void test_findLastS1WordThatS2Has1()
{
    char s1[] = "  Just because you're  correct   doesn't mean you're   right";
    char s2[] = "because you're correct";

    Word w = findLastS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("you're", s3);

    free(s3);
}


void test_findLastS1WordThatS2Has2()
{
    char s1[] = "  Just because you're  correct   doesn't mean you're   right";
    char s2[] = "";

    Word w = findLastS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("", s3);

    free(s3);
}


void test_findLastS1WordThatS2Has3()
{
    char s1[] = "";
    char s2[] = "  Just because you're  correct   doesn't mean you're   right";

    Word w = findLastS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("", s3);

    free(s3);
}


void test_findLastS1WordThatS2Has4()
{
    char s1[] = "";
    char s2[] = "";

    Word w = findLastS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("", s3);

    free(s3);
}


void test_stringHasSameWords1()
{
    char s[] = "Just because you're correct doesn't mean you're right";

    bool res = stringHasSameWords(s);
    bool ans = true;

    ASSERT(ans, res);
}


void test_stringHasSameWords2()
{
    char s[] = "Just because you're correct doesn't mean I'm right";

    bool res = stringHasSameWords(s);
    bool ans = false;

    ASSERT(ans, res);
}


void test_stringHasSameWords3()
{
    char s[] = "";

    bool res = stringHasSameWords(s);
    bool ans = false;

    ASSERT(ans, res);
}


void test_stringHasAnagrams1()
{
    char s[] = "race silent listen";

    bool res = stringHasAnagrams(s);
    bool ans = true;

    ASSERT(ans, res);
}


void test_stringHasAnagrams2()
{
    char s[] = "final";

    bool res = stringHasAnagrams(s);
    bool ans = false;

    ASSERT(ans, res);
}


void test_stringHasAnagrams3()
{
    char s[] = "";

    bool res = stringHasAnagrams(s);
    bool ans = false;

    ASSERT(ans, res);
}


void test_getStringWithoutWordsNotLikeLastWord1()
{
    char s1[] = "Just because you're right doesn't mean you're right";

    char* s2;

    s2 = getStringWithoutWordsNotLikeLastWord(s1);

    ASSERT_STRING("Just because you're doesn't mean you're", s2);

    free(s2);
}


void test_getStringWithoutWordsNotLikeLastWord2()
{
    char s1[] = "Just because you're correct doesn't mean you're right";

    char* s2;

    s2 = getStringWithoutWordsNotLikeLastWord(s1);

    ASSERT_STRING("Just because you're correct doesn't mean you're", s2);

    free(s2);
}


void test_getStringWithoutWordsNotLikeLastWord3()
{
    char s1[] = "right";

    char* s2;

    s2 = getStringWithoutWordsNotLikeLastWord(s1);

    ASSERT_STRING("", s2);

    free(s2);
}


void test_getStringWithoutWordsNotLikeLastWord4()
{
    char s1[] = "";

    char *s2;

    s2 = getStringWithoutWordsNotLikeLastWord(s1);

    ASSERT_STRING("", s2);
}


void test_findFirstS1WordThatPrecedesS1WordThatS2Has1()
{
    char s1[] = "Just because you're correct doesn't mean you're right";
    char s2[] = "because you're correct";

    Word w = findFirstS1WordThatPrecedesS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("Just", s3);

    free(s3);
}


void test_findFirstS1WordThatPrecedesS1WordThatS2Has2()
{
    char s1[] = "Just because you're correct doesn't mean you're right";
    char s2[] = "because you're Just";

    Word w = findFirstS1WordThatPrecedesS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("", s3);

    free(s3);
}


void test_findFirstS1WordThatPrecedesS1WordThatS2Has3()
{
    char s1[] = "Just because you're correct doesn't mean you're right";
    char s2[] = "thgir er'uoy naem t'nseod tcerroc er'uoy esuaceb tsuJ";

    Word w = findFirstS1WordThatPrecedesS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("", s3);

    free(s3);
}


void test_findFirstS1WordThatPrecedesS1WordThatS2Has4()
{
    char s1[] = "";
    char s2[] = "";

    Word w = findFirstS1WordThatPrecedesS1WordThatS2Has(s1, s2);

    char* s3 = malloc(sizeof(char) * ((w.end - w.beginning) + 1));

    wordToStr(w, s3);

    ASSERT_STRING("", s3);

    free(s3);
}


void test_deletePalindromes1()
{
    char s[] = "radar string level";

    deletePalindromes(s);

    ASSERT_STRING("string", s);
}


void test_deletePalindromes2()
{
    char s[] = "radar madam level";

    deletePalindromes(s);

    ASSERT_STRING("", s);
}


void test_deletePalindromes3()
{
    char s[] = "Just because you're correct doesn't mean you're right";

    deletePalindromes(s);

    ASSERT_STRING("Just because you're correct doesn't mean you're right", s);
}


void test_deletePalindromes4()
{
    char s[] = "";

    deletePalindromes(s);

    ASSERT_STRING("", s);
}


void test_addWordsToStrWithLesserWordCount1()
{
    char s1[] = "Just because you're correct";
    int n1 = 4;

    char s2[] = "Just because you're correct doesn't mean you're right";
    int n2 = 8;

    addWordsToStrWithLesserWordCount(s1, n1, s2, n2);

    ASSERT_STRING("Just because you're correct doesn't mean you're right", s1);
}


void test_addWordsToStrWithLesserWordCount2()
{
    char s1[] = "Just because you're correct doesn't mean you're right";
    int n1 = 8;

    char s2[] = "Just because you're correct";
    int n2 = 4;

    addWordsToStrWithLesserWordCount(s1, n1, s2, n2);

    ASSERT_STRING("Just because you're correct doesn't mean you're right", s2);
}


void test_addWordsToStrWithLesserWordCount3()
{
    char s1[] = "Just because you're correct";
    int n1 = 4;

    char s2[] = "Just because you're correct";
    int n2 = 4;

    addWordsToStrWithLesserWordCount(s1, n1, s2, n2);

    ASSERT_STRING("Just because you're correct", s1);
}


void test_addWordsToStrWithLesserWordCount4()
{
    char s1[MAX_STRING_SIZE] = "";
    int n1 = 0;

    char s2[] = "Just because you're correct doesn't mean you're right";
    int n2 = 8;

    addWordsToStrWithLesserWordCount(s1, n1, s2, n2);

    ASSERT_STRING("Just because you're correct doesn't mean you're right", s1);
}


void test_addWordsToStrWithLesserWordCount5()
{
    char s1[] = "";
    int n1 = 0;

    char s2[] = "";
    int n2 = 0;

    addWordsToStrWithLesserWordCount(s1, n1, s2, n2);

    ASSERT_STRING("", s1);
}


void test_stringContainsEveryLetterOfW1()
{
    char s1[] = "Just because you're correct doesn't mean you're right";
    char s2[] = "uer";

    bool res = stringContainsEveryLetterOfW(s1, s2);
    bool ans = true;

    ASSERT(ans, res);
}


void test_stringContainsEveryLetterOfW2()
{
    char s1[] = "Just because you're correct doesn't mean you're right";
    char s2[] = "uel";

    bool res = stringContainsEveryLetterOfW(s1, s2);
    bool ans = false;

    ASSERT(ans, res);
}


void test_stringContainsEveryLetterOfW3()
{
    char s1[] = "Just because you're correct doesn't mean you're right";
    char s2[] = "";

    bool res = stringContainsEveryLetterOfW(s1, s2);
    bool ans = true;

    ASSERT(ans, res);
}


void test_stringContainsEveryLetterOfW4()
{
    char s1[] = "";
    char s2[] = "";

    bool res = stringContainsEveryLetterOfW(s1, s2);
    bool ans = true;

    ASSERT(ans, res);
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

    test_countPalindromeWords1();
    test_countPalindromeWords2();
    test_countPalindromeWords3();

    test_mixStrings1();
    test_mixStrings2();
    test_mixStrings3();
    test_mixStrings4();
    test_mixStrings5();

    test_reverseWordOrder1();
    test_reverseWordOrder2();
    test_reverseWordOrder3();

    test_findLastS1WordThatS2Has1();
    test_findLastS1WordThatS2Has2();
    test_findLastS1WordThatS2Has3();
    test_findLastS1WordThatS2Has4();

    test_stringHasSameWords1();
    test_stringHasSameWords2();
    test_stringHasSameWords3();

    test_stringHasAnagrams1();
    test_stringHasAnagrams2();
    test_stringHasAnagrams3();

    test_getStringWithoutWordsNotLikeLastWord1();
    test_getStringWithoutWordsNotLikeLastWord2();
    test_getStringWithoutWordsNotLikeLastWord3();
    test_getStringWithoutWordsNotLikeLastWord4();

    test_findFirstS1WordThatPrecedesS1WordThatS2Has1();
    test_findFirstS1WordThatPrecedesS1WordThatS2Has2();
    test_findFirstS1WordThatPrecedesS1WordThatS2Has3();
    test_findFirstS1WordThatPrecedesS1WordThatS2Has4();

    test_deletePalindromes1();
    test_deletePalindromes2();
    test_deletePalindromes3();
    test_deletePalindromes4();

    test_addWordsToStrWithLesserWordCount1();
    test_addWordsToStrWithLesserWordCount2();
    test_addWordsToStrWithLesserWordCount3();
    test_addWordsToStrWithLesserWordCount4();
    test_addWordsToStrWithLesserWordCount5();

    test_stringContainsEveryLetterOfW1();
    test_stringContainsEveryLetterOfW2();
    test_stringContainsEveryLetterOfW3();
    test_stringContainsEveryLetterOfW4();
}


int main()
{
    test();
}