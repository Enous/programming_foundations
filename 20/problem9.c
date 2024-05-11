#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "problems.h"


int main2(int argc, char* argv[])
{
    if (argc >= 2)
    {
        FILE* f = fopen(argv[1], "w");

        fprintf(f, "%s\n", "1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1");

        fclose(f);

        int x = atoi(argv[3]);

        createFileWithNumsSmallerThanN1(f, argv[1], argv[2], x);

        FILE* new_f = fopen(argv[2], "r");

        char ans[] = "1 2 3 4 5 5 4 3 2 1";

        char buffer[MAX_STR_SIZE];
        fgets(buffer, sizeof(buffer), new_f);

        ASSERT_STRING(ans, buffer);

        fclose(new_f);
    }

    return 0;
}