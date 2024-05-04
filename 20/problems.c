#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix.h"
#include "string_.h"
#include "problems.h"

int countLiveCells(matrix mx, int row, int col)
{
    int count = 0;

    int row1, row2, col1, col2;
    row1 = row - 1;
    row2 = row + 1;
    col1 = col - 1;
    col2 = col + 1;

    for (int i = row1; i <= row2; i++)
    {
        if (i < 0)
            continue;

        for (int j = col1; j <= col2; j++)
        {
            if (j < 0 || (i >= mx.rows_count || j >= mx.cols_count) || i == row && j == col)
                continue;

            count += mx.values[i][j];
        }
    }

    return count;
}


matrix gameOfLife(matrix mx)
{
    matrix res_mx = getMemMatrix(mx.rows_count, mx.cols_count);

    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = 0; j < mx.cols_count; j++)
        {
            int total_live_neighbour_cells = countLiveCells(mx, i, j);
            int cell_state = mx.values[i][j];

            if (cell_state)
            {
                if (total_live_neighbour_cells < 2 || total_live_neighbour_cells > 3)
                    res_mx.values[i][j] = 0;
                else
                    res_mx.values[i][j] = 1;
            }
            else
            {
                if (total_live_neighbour_cells == 3)
                    res_mx.values[i][j] = 1;
                else
                    res_mx.values[i][j] = 0;
            }
        }
    }

    return res_mx;
}


int cmpfunc(const void* a, const void* b)
{
    int v1 = *(int*) a;
    int v2 = *(int*) b;

    if (v1 < v2)
        return -1;

    if (v1 == v2)
        return 0;

    return 1;
}


int getArrMedian(matrix mx, int row, int col, int arr_size)
{
    int arr[arr_size * arr_size];

    int shift = floor(arr_size / 2);
    int row1 = row - shift;
    int row2 = row + shift;
    int col1 = col - shift;
    int col2 = col + shift;

    int curr_size = 0;

    for (int i = row1; i <= row2; i++)
    {
        for (int j = col1; j <= col2; j++)
            arr[curr_size++] = mx.values[i][j];
    }

    qsort(arr, curr_size, sizeof(int), cmpfunc);

    return arr[(int) floor(curr_size / 2)];
}


void medianFilter(matrix* mx, int window_size)
{
    if (window_size > mx->rows_count || window_size > mx->cols_count)
        return;

    int shift = floor(window_size / 2);
    int r_border = mx->rows_count - shift;
    int c_border = mx->cols_count - shift;

    for (int i = shift; i < r_border; i++)
    {
        for (int j = shift; j < c_border; j++)
            mx->values[i][j] = getArrMedian(*mx, i, j, window_size);
    }
}


char** subdomainVisits(char** cpdomains, int size, int* return_size)
{
    char** subdomains = malloc(sizeof(char*) * MAX_SIZE);

    for (int i = 0; i < MAX_SIZE; i++)
        subdomains[i] = malloc(sizeof(char) * MAX_STR_SIZE);
}