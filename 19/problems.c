#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "problems.h"
#include "matrix.h"

void ftranspose(FILE* f, char* fname)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    char str_arr[MAX_SIZE][MAX_STR_SIZE];

    int j = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        char* buffer_ptr = buffer;

        char* token = strtok(buffer_ptr, " ");

        char* chr_order = token;
        char* chr_order_ptr = chr_order;

        int order = atoi(token);

        token = strtok(NULL, " ");

        int* arr = malloc(sizeof(int) * order * order);
        int i = 0;
        arr[i++] = order;

        while (token)
        {
            arr[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }

        matrix mx = createMatrixFromArray(arr + 1, order, order);
        transposeMatrix(&mx);

        int shift = 0;

        while (order > 0)
        {
            order /= 10;
            shift++;
        }

        chr_order_ptr += sizeof(char) * shift;
        *(chr_order_ptr++) = ' ';
        *chr_order_ptr = '\0';

        int str_size;

        char* res = matrixIntoCharArr(mx, &str_size);
        strcat(chr_order, res);

        strcpy(str_arr[j++], chr_order);

        *buffer = '\0';
    }

    fclose(f);

    f = fopen(fname, "w");

    for (int k = 0; k < j; k++)
    {
        if (k < j - 1)
            fprintf(f, "%s\n", str_arr[k]);
        else
            fprintf(f, "%s", str_arr[k]);
    }

    fclose(f);
}