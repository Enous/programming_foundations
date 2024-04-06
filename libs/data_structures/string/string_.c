#include <stdio.h>
#include "string_.h"

/* возвращает кол-во символов в строке, не считая нуль-символ */
size_t get_strlen(const char* start)
{
    char* end = start;

    while (*end != '\0')
        end++;

    return end - start;
}