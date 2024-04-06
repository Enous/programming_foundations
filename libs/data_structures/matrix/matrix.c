#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <memory.h>

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
            printf("%d ", mx.values[i][j]);

        printf("\n");
    }

    printf("\n");
}


/* вывод массива их matrices_count, хранящегося по адресу mxs */
void outputMatrices(matrix* mxs, int matrices_count)
{
    for (int i = 0; i < matrices_count; i++)
    {
        outputMatrix(mxs[i]);
        printf("\n");
    }
}


/* обмен строк матрицы по индексам */
void swapRows(matrix mx, int i1, int i2)
{
    assert(i1 >= 0 && i1 < mx.rows_count);
    assert(i2 >= 0 && i2 < mx.rows_count);

    int* temp = mx.values[i1];
    mx.values[i1] = mx.values[i2];
    mx.values[i2] = temp;
}


/* обмен столбцов матрицы по индексам */
void swapCols(matrix mx, int j1, int j2)
{
    assert(j1 >= 0 && j1 < mx.cols_count);
    assert(j2 >= 0 && j2 < mx.cols_count);

    for (int i = 0; i < mx.rows_count; i++)
    {
        int temp = mx.values[i][j1];
        mx.values[i][j1] = mx.values[i][j2];
        mx.values[i][j2] = temp;
    }
}


/* возвращает сумму элементов целочисленного массива */
int getSum(int* arr, int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
        sum += arr[i];

    return sum;
}


/* обменивает значение двух целочисленных переменных по адресам */
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* выполняет сортировку вставками строк
   матрицы по неубыванию значения функции,
   применяемой для строк */
void insertionSortMatrixRows(matrix mx, int (*condition)(int*, int))
{
    int* condition_func_res = malloc(mx.rows_count * sizeof(int));
    condition_func_res[0] = condition(mx.values[0], mx.cols_count);

    for (int i = 1; i < mx.rows_count; i++)
    {
        condition_func_res[i] = condition(mx.values[i], mx.cols_count);
        int temp = condition_func_res[i];
        int j = i;

        while (j > 0 && condition_func_res[j - 1] > temp)
        {
            condition_func_res[j] = condition_func_res[j - 1];
            swapRows(mx, j, j - 1);
            j--;
        }

        condition_func_res[j] = temp;
    }

    free(condition_func_res);
}


/* выполняет сортировку выбором строк
   матрицы по неубыванию значения функции,
   применяемой для столбцов */
void selectionSortMatrixCols(matrix mx, int (*condition)(int*, int))
{
    int* condition_func_res = malloc(mx.cols_count * sizeof(int));

    for (int i = 0; i < mx.cols_count; i++)
    {
        int* arr = malloc(mx.cols_count * sizeof(int));

        for (int j = 0; j < mx.rows_count; j++)
            arr[j] = mx.values[j][i];

        condition_func_res[i] = condition(arr, mx.rows_count);
    }

    for (int i = 0; i < mx.cols_count - 1; i++)
    {
        int min_idx = i;

        for (int j = i + 1; j < mx.cols_count; j++)
        {
            if (condition_func_res[j] < condition_func_res[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
        {
            swap(&condition_func_res[min_idx], &condition_func_res[i]);
            swapCols(mx, min_idx, i);
        }
    }
}


/* возвращает true, если матрица является квадратной,
   и false в противном случае */
bool isSquareMatrix(matrix* mx)
{
    return mx->cols_count == mx->rows_count;
}


/* возвращает true, если две матрицы равны,
   и false в противном случае */
bool TwoMatricesAreEqual(matrix* mx1, matrix* mx2)
{
    if (mx1->rows_count != mx2->rows_count || mx1->cols_count != mx2->cols_count)
        return false;

    for (int i = 0; i < mx1->rows_count; i++)
    {
        if (memcmp(mx1->values[i], mx2->values[i], sizeof(int) * mx1->cols_count) != 0)
            return false;
    }

    return true;
}


/* возвращает true, если матрица является единичной,
   и false в противном случае */
bool isIdentityMatrix(matrix* mx)
{
    if (mx->rows_count != mx->cols_count)
        return false;

    if (mx->values[0][0] == 1)
    {
        for (int i = 0; i < mx->rows_count; i++)
        {
            for (int j = 0; j < mx->cols_count; j++)
            {
                if (i == j)
                {
                    if (mx->values[i][j] != 1)
                        return false;
                }
                else
                {
                    if (mx->values[i][j] != 0)
                        return false;
                }
            }
        }
    }
    else if (mx->values[0][mx->cols_count - 1] == 1)
    {
        for (int i = 0; i < mx->rows_count; i++)
        {
            for (int j = 0; j < mx->cols_count; j++)
            {
                if (i == mx->cols_count - j - 1)
                {
                    if (mx->values[i][j] != 1)
                        return false;
                }
                else
                {
                    if (mx->values[i][j] != 0)
                        return false;
                }
            }
        }
    }
    else
        return false;

    return true;
}


/* возвращает значение true, если матрица является симметричной,
   и false в противном случае */
bool isSymmetricMatrix(matrix* mx)
{
    if (mx->rows_count != mx->cols_count)
        return false;

    for (int i = 0; i < mx->rows_count; i++)
    {
        for (int j = i + 1; j < mx->cols_count; j++)
        {
            if (mx->values[i][j] != mx->values[j][i])
                return false;
        }
    }

    return true;
}


/* транспонирует квадратную матрицу */
void transposeSquareMatrix(matrix* mx)
{
    for (int i = 0; i < mx->rows_count; i++)
    {
        for (int j = i + 1; j < mx->cols_count; j++)
            swap(&mx->values[i][j], &mx->values[j][i]);
    }
}


/* транспонирует матрицу */
void transposeMatrix(matrix* mx)
{
    if (mx->rows_count > mx->cols_count)
    {
        for (int i = 0; i < mx->rows_count; i++)
        {
            mx->values[i] = realloc(mx->values[i], sizeof(int) * mx->rows_count);

            for (int j = i + 1; j < mx->rows_count; j++)
                swap(&mx->values[i][j], &mx->values[j][i]);
        }

        swap(&mx->rows_count, &mx->cols_count);

        mx->values = realloc(mx->values, sizeof(int*) * mx->rows_count);
    }
    else if (mx->rows_count < mx->cols_count)
    {
        mx->values = realloc(mx->values, sizeof(int*) * mx->cols_count);

        for (int i = mx->rows_count; i < mx->cols_count; i++)
            mx->values[i] = malloc(sizeof(int) * mx->rows_count);

        for (int i = 0; i < mx->cols_count; i++)
        {
            for (int j = i + 1; j < mx->cols_count; j++)
                swap(&mx->values[i][j], &mx->values[j][i]);
        }

        swap(&mx->rows_count, &mx->cols_count);

        for (int i = 0; i < mx->cols_count; i++)
            mx->values[i] = realloc(mx->values[i], sizeof(int) * mx->cols_count);
    }
    else
    {
        for (int i = 0; i < mx->cols_count; i++)
        {
            for (int j = i + 1; j < mx->cols_count; j++)
                swap(&mx->values[i][j], &mx->values[j][i]);
        }

        swap(&mx->rows_count, &mx->cols_count);
    }
}


/* возвращает позицию минимального элемента матрицы */
position getMinValuePos(matrix mx)
{
    position min_elem_pos = {0, 0};

    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = 0; j < mx.cols_count; j++)
        {
            if (mx.values[i][j] < mx.values[min_elem_pos.row_idx][min_elem_pos.col_idx])
            {
                min_elem_pos.row_idx = i;
                min_elem_pos.col_idx = j;
            }
        }
    }

    return min_elem_pos;
}


/* возвращает позицию максимального элемента матрицы */
position getMaxValuePos(matrix mx)
{
    position max_elem_pos = {0, 0};

    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = 0; j < mx.cols_count; j++)
        {
            if (mx.values[i][j] > mx.values[max_elem_pos.row_idx][max_elem_pos.col_idx])
            {
                max_elem_pos.row_idx = i;
                max_elem_pos.col_idx = j;
            }
        }
    }

    return max_elem_pos;
}


/* возвращает матрицу, построенную из элементов данного массива */
matrix createMatrixFromArray(const int* arr, size_t rows_count, size_t cols_count)
{
    matrix m = getMemMatrix(rows_count, cols_count);

    int k = 0;

    for (int i = 0; i < rows_count; i++)
        for (int j = 0; j < cols_count; j++)
            m.values[i][j] = arr[k++];

    return m;
}


/* возвращает указатель на нулевую матрицу массива из матриц, размещенных
   в динамической памяти, построенных из элементов данного массива */
matrix* createMatrixArrayFromArray(const int* values, size_t matrices_count, size_t rows_count, size_t cols_count)
{
    matrix* mxs = getMemArrayOfMatrices(matrices_count, rows_count, cols_count);

    int l = 0;

    for (size_t k = 0; k < matrices_count; k++)
        for (size_t i = 0; i < rows_count; i++)
            for (size_t j = 0; j < cols_count; j++)
                mxs[k].values[i][j] = values[l++];

    return mxs;
}


/* возвращает произведение матриц */
matrix multiplyMatrices(matrix mx1, matrix mx2)
{
    matrix mx3 = getMemMatrix(mx1.rows_count, mx2.cols_count);

    for (int i = 0; i < mx1.rows_count; i++)
    {
        for (int j = 0; j < mx1.rows_count; j++)
        {
            int elem = 0;

            for (int k = 0; k < mx1.cols_count; k++)
                elem += (mx1.values[i][k] * mx2.values[k][j]);

            mx3.values[i][j] = elem;
        }
    }

    return mx3;
}


