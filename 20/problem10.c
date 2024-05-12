#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "problems.h"

FILE* f;
int count;

void sigfunc(int sig)
{
    signal(SIGINT,sigfunc);

    char* buffer = malloc(sizeof(char) * MAX_STR_SIZE);

    if (sig == SIGINT)
    {
        for (int i = 0; i < count; i++)
        {
            if (fgets(buffer, MAX_STR_SIZE, f))
                printf("%s", buffer);
            else
            {
                free(buffer);
                exit(0);
            }
        }

        *buffer = '\0';
    }
}


int main10(int argc, char* argv[])
{
    if (argc >= 2)
    {
        f = fopen(argv[1], "w");

        fprintf(f, "%s\n", "abcd");
        fprintf(f, "%s\n", "efgh");
        fprintf(f, "%s\n", "ijklmnop");
        fprintf(f, "%s\n", "qrstuv");
        fprintf(f, "%s\n", "w");
        fprintf(f, "%s\n", "xy");
        fprintf(f, "%s\n", "z");

        fclose(f);

        f = fopen(argv[1], "r");

        count = atoi(argv[2]);

        signal(SIGINT,sigfunc);

        while (1)
        {
            sleep(10);
        }
    }
}