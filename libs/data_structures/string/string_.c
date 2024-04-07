#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

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


/* возвращает указатель на последний пробельный символ,
   расположенный на ленте памяти между адресами start и end,
   не включая start */
char* findLastSpaceChr(char* end, const char* start)
{
    while (!isspace(*end) && *start != '\0')
        end--;

    return end;
}


int strcmp(const char* lhs, const char* rhs)
{
    while (*lhs && *lhs == *rhs)
        lhs++, rhs++;

    return *lhs - *rhs;
}


/* записывает по адресу destination фрагмент памяти,
   начиная с адреса source_start до source_end;
   возвращает указатель на следующий свободный фрагмент памяти в
   destination */
char* copy(const char* source_start, const char* source_end, char* destination)
{
    size_t len = source_end - source_start;

    memcpy(destination, source_start, sizeof(char) * len);

    return destination + sizeof(char) * len;
}


/* возвращает 1, если латинская буква прописная, и 0 в противном случае */
int is_lowercase(int chr)
{
    return chr >= 0x61 && chr <= 0x7a;
}


/* записывает по адресу destination элементы из фрагмента памяти,
   начиная с source_start и заканчивая source_end,
   удовлетворяющие функции-предикату;
   возвращает указатель на следующий свободный для записи фрагмент в памяти */
char* copyBasedOnCondition(char* source_start, const char* source_end, char* destination, int (*condition)(int))
{
    char* destination_end = destination;

    while (*source_start != *source_end)
    {
        if (condition(*(source_start)))
        {
            memcpy(destination_end, source_start, sizeof(char));
            destination_end++;
        }

        source_start++;
    }

    *destination_end = '\0';
    size_t len = destination_end - destination;

    destination = realloc(destination, sizeof(char) * len);

    return destination;
}


/* записывает по адресу destination элементы из фрагмента памяти,
   начиная с source_end и заканчивая source_start,
   удовлетворяющие функции-предикату;
   возвращает указатель на следующий свободный для записи фрагмент в памяти */
char* copyReversedBasedOnCondition(char* source_end, const char* source_start,
                    char* destination, int (*condition)(int))
{
    char* destination_end = destination;

    while (*source_end != *source_start)
    {
        if (condition(*(source_end)))
        {
            memcpy(destination_end, source_end, sizeof(char));
            destination_end++;
        }

        source_end--;
    }

    *destination_end = '\0';
    size_t len = destination_end - destination;

    destination = realloc(destination, sizeof(char) * len);

    return destination;
}