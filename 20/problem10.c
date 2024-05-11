#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "matrix.h"
#include "problems.h"

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        FILE* f = fopen(argv[1], "w");

        fprintf(f, "%s\n", "abcd");
        fprintf(f, "%s\n", "efgh");
        fprintf(f, "%s\n", "ijklmnop");
        fprintf(f, "%s\n", "qrstuv");
        fprintf(f, "%s\n", "w");
        fprintf(f, "%s\n", "xy");
        fprintf(f, "%s\n", "z");

        fclose(f);

        int n = atoi(argv[3]);

        FILE* new_f = fopen(argv[2], "r");



        fclose(new_f);
    }

    return 0;
}