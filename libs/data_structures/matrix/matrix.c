#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/* размещает в динамической памяти матрицу размером
   rows_count на cols_count и возвращает матрицу */
matrix getMemMatrix(int rows_count, int cols_count)
{
    int** values = (int**) malloc(sizeof(int*) * rows_count);

    for (int i = 0; i < rows_count; i++)
        values[i] = (int*) malloc(sizeof(int) * cols_count);

    return (matrix) {values, rows_count, cols_count};
}


/* размещает в динамической памяти массив из matrices_count матриц
   размером rows_count на cols_count и возвращает указатель на нулевую матрицу */
matrix* getMemArrayOfMatrices(int matrices_count, int rows_count, int cols_count)
{
    matrix *mxs = (matrix*) malloc(sizeof(matrix) * matrices_count);

    for (int i = 0; i < matrices_count; i++)
        mxs[i] = getMemMatrix(rows_count, cols_count);

    return mxs;
}


/* освобождает память, выделенную под хранение матрицы mx */
void freeMemMatrix(matrix* mx)
{
    for (int i = 0; i < mx->rows_count; i++)
        free(mx->values[i]);

    free(mx->values);
}


/* освобождает память, выделенную под хранение массива mxs из matrices_count матриц */
void freeMemMatrices(matrix* mxs, int matrices_count)
{
    for (int i = 0; i < matrices_count; i++)
        freeMemMatrix(&mxs[i]);

    free(mxs);
}


/* ввод матрицы */
void inputMatrix(matrix* mx)
{
    for (int i = 0; i < mx->rows_count; i++)
    {
        for (int j = 0; j < mx->cols_count; j++)
            scanf("%d", &mx->values[i][j]);
    }
}


/* ввод массива из matrices_count матриц, хранящегося по адресу mxs */
void inputMatrices(matrix* mxs, int matrices_count)
{
    for (int i = 0; i < matrices_count; i++)
        inputMatrix(&mxs[i]);
}


/* вывод матрицы */
void outputMatrix(matrix mx)
{
    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = 0; j < mx.cols_count; j++)
            printf("%d", mx.values[i][j]);

        printf("\n");
    }
}


/* вывод массива их matrices_count, хранящегося по адресу mxs */
void outputMatrices(matrix* mxs, int matrices_count)
{
    for (int i = 0; i < matrices_count; i++)
        outputMatrix(mxs[i]);
}