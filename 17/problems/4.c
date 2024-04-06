#include <stdio.h>

#include "string_.h"

void problem4()
{
    char* s1 = "Hello, World!";
    char* s2 = "Hello";

    size_t len1 = get_strlen(s1);
    size_t len2 = get_strlen(s2);

    char* s1_space_pt = s1 + 6;
    char* s2_space_pt = s2 + len2;

    printf("Problem 4A_1: %c\n", *find(s1, (s1 + len1 - 1), 111));
    printf("Problem 4A_2: %c\n", *find(s1, (s1 + len1 - 1), 85));

    printf("Problem 4B_1: %c\n", *findNonSpaceChr(s1));
    printf("Problem 4B_2: %d\n", *s2_space_pt == *findNonSpaceChr(s2));

    printf("Problem 4C_1: %d\n", *s1_space_pt == *findSpaceChr(s1));
    printf("Problem 4C_2: %d\n", *s2_space_pt == *findSpaceChr(s2));

    printf("Problem 4D: %c\n", *findLastNonSpaceChr(s1 + len1 - 1, s1));

    printf("Problem 4E: %d\n", *s1_space_pt == *findLastSpaceChr(s1 + len1 - 1, s1));
}
