#include <stdio.h>
#include <ctype.h>

#include "string_.h"

/* возвращает кол-во символов в строке, не считая нуль-символ */
size_t get_strlen(const char* start)
{
    char* end = start;

    while (*end != '\0')
        end++;

    return end - start;
}


/* возвращает указатель на первый элемент с кодом chr,
   расположенном на ленте памяти между адресами start и end,
   не включая end */
char* find(char* start, char* end, int code)
{
    while (start != end && *start != code)
        start++;

    return start;
}


/* возвращает указатель на первый символ, отличный от пробельного,
   расположенный на ленте памяти между адресами start и end,
   не включая end */
char* findNonSpaceChr(char* start)
{
    while (!isspace(*(start + 1)) && *start != '\0')
        start++;

    return start;
}


/* возвращает указатель на первый пробельный символ,
   расположенный на ленте памяти между адресами start и end,
   не включая end */
char* findSpaceChr(char* start)
{
    while (!isspace(*start) && *start != '\0')
        start++;

    return start;
}


/* возвращает указатель на последний символ, отличный от пробельного,
   расположенный на ленте памяти между адресами start и end,
   не включая start */
char* findLastNonSpaceChr(char* end, const char* start)
{
    while (isspace(*(end)) && *end != *start)
        end--;

    return end;
}


char* findLastSpaceChr(char* end, const char* start)
{
    while (!isspace(*end) && *start != '\0')
        end--;

    return end;
}


