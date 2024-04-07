#include <stdio.h>
#include <stdlib.h>

#include "string_.h"

void problem6()
{
    size_t len = 14;

    char* s1 = malloc(sizeof(char) * len);

    s1 = "Hello, World!";

    char* s2 = malloc(sizeof(char) * len);
    char* p = s1 + len;

    copy(s1, p, s2);

    printf("Problem 6_A: %s\n", s2);

    char* s3 = malloc(sizeof(char) * len);

    copyBasedOnCondition(s2, s2 + len, s3, is_lowercase);

    printf("Problem 6_B: %s\n", s3);

    char* s4 = malloc(sizeof(char) * len);

    copyReversedBasedOnCondition(s2 + len, s2, s4, is_lowercase);

    printf("Problem 6_B: %s\n", s4);

    printf("\n");
}
