#include <stdio.h>

#include "string_.h"

void problem5()
{
    char* s1 = "Hello, World!";
    char* s2 = "Hello";
    char* s3 = "Hello, World!";
    char* s4 = "Helli";

    printf("Problem 5_1: %d\n", strcmp(s1, s2));
    printf("Problem 5_2: %d\n", strcmp(s2, s1));
    printf("Problem 5_3: %d\n", strcmp(s1, s3));
    printf("Problem 5_4: %d\n", strcmp(s2, s4));

    printf("\n");
}
