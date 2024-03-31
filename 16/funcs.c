#include <stdio.h>
#include <limits.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>

#include "funcs.h"

/* меняет местами строки квадратной матрицы,
   в которых находятся максимальный и минимальный элементы */
void swapRowsWithMinAndMaxELems(matrix* mx)
{
    int row_with_min_elem_idx = ((position) getMinValuePos(*mx)).row_idx;
    int row_with_max_elem_idx = ((position) getMaxValuePos(*mx)).row_idx;

    if (row_with_min_elem_idx == row_with_max_elem_idx)
        return;

    swapRows(*mx, row_with_min_elem_idx, row_with_max_elem_idx);
}


/* возвращает наибольший элемент целочисленного массива */
int getMax(int* arr, int size)
{
    int max = 0;

    for (int i = 0; i < size; i++)
    {
        if (max < arr[i])
            max = arr[i];
    }

    return max;
}


/* упорядочивает строки матрицы по неубыванию наибольших элементов строк */
void sortMatrixRowsByMaxRowElem(matrix* mx)
{
    insertionSortMatrixRows(*mx, getMax);
}


/* возвращает наименьший элемент целочисленного массива */
int getMin(int* arr, int size)
{
    int min = INT_MAX;

    for (int i = 0; i < size; i++)
    {
        if (min > arr[i])
            min = arr[i];
    }

    return min;
}


/* упорядочивает столбцы матрицы по неубыванию минимальных элементов столбцов */
void sortMatrixColsByMinColElem(matrix* mx)
{
    selectionSortMatrixCols(*mx, getMin);
}


/* заменяет квадратную матрицу ее квадратом, если она симметрична */
void raiseMatrixToTheSecondPowerIfSymmetric(matrix* mx)
{
    if (!isSymmetricMatrix(mx))
        return;

    matrix mx_copy = *mx;

    *mx = multiplyMatrices(mx_copy, mx_copy);

    freeMemMatrix(&mx_copy);
}


/* возвращает true, если все элементы целочисленного массива уникальны,
   и false в противном случае */
bool ifAllElemsAreUnique(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
            if (arr[i] == arr[j])
                return false;
    }

    return true;
}


/* транспонирует квадратную матрицу, если суммы элементов её строк различны */
void transposeMatrixIfThereAreNoEqualRowElemSums(matrix mx)
{
    int* sums = malloc(sizeof(int) * mx.rows_count);

    for (int i = 0; i < mx.rows_count; i++)
    {
        sums[i] = getSum(mx.values[i], mx.cols_count);

        if (!ifAllElemsAreUnique(sums, i + 1))
            return;
    }

    transposeMatrix(&mx);

    free(sums);
}


/* возвращает true, если две квадратные матрицы взаимно обратные,
   и false в противном случае */
bool twoSquareMatricesAreInversesOfEachOther(matrix mx1, matrix mx2)
{
    matrix product = multiplyMatrices(mx1, mx2);

    bool res = isIdentityMatrix(&product);

    freeMemMatrix(&product);

    return res;
}


/* возвращает сумму максимальных элементов псевдодиагоналей */
long long getSumOfPseudoDiagonalsMaxElems(matrix mx)
{
    int i = mx.rows_count - 1;
    int j = 0;

    int sum = 0;
    int curr_step = 0;
    int total_elems = mx.rows_count + mx.cols_count - 1;

    while (curr_step < total_elems)
    {
        int k = i;
        int l = j;

        int max = mx.values[k++][l++];

        while (k + 1 <= mx.rows_count && l + 1 <= mx.cols_count)
        {
            if (mx.values[k][l] > max)
                max = mx.values[k][l];

            k++;
            l++;
        }

        if (i - 1 >= 0)
            i--;
        else
            j++;

        sum += max;

        curr_step++;
    }

    return sum;
}


/* возвращает минимальный элемент матрицы в выделенной области */
int getMinElemInSelectedArea(matrix mx)
{
    position border = getMaxValuePos(mx);

    int i = border.row_idx - 1;
    int j = border.col_idx;

    int k = j;
    int min = mx.values[i][j];

    while (1)
    {
        if (k + 1 < mx.cols_count)
            k++;

        if (j - 1 >= 0)
            j--;

        int l = j;

        while (l <= k)
        {
            if (min > mx.values[i][l])
                min = mx.values[i][l];

            l++;
        }

        if (i == 0 && j == 0)
            break;

        if (i - 1 >= 0)
            i--;
    }

    return min;
}


/* находит расстояние от данной точки до начала координат */
float getDistance(int* arr, int size)
{
    float distance = 0;

    for (int i = 0; i < size; i++)
        distance += (arr[i] * arr[i]);

    return sqrt(distance);
}


/* упорядочивает ряды матрицы по неубыванию их
   расстояний до начала координат */
void insertionSortMatrixRowsFloatCondition(matrix mx, float (*condition)(int*, int))
{
    int* condition_func_res = malloc(mx.rows_count * sizeof(float));
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


/* упорядочивает элементы матрицы (точки) по неубыванию их
   расстояний до начала координат */
void sortByDistances(matrix mx)
{
    insertionSortMatrixRowsFloatCondition(mx, getDistance);
}


int cmp_longlong(const void* pa, const void* pb)
{
    const long long a = *(const long long*) pa;
    const long long b = *(const long long*) pb;

    return (a > b) - (a < b);
}


/* подсчитывает количество уникальных сумм элементов рядов матрицы */
int countUniqueRowElemSums(long long* arr, int size)
{
    int count = 0;

    for (int i = 0; i < size - 1; i++)
        if (i == 0 || arr[i] != arr[i + 1])
            count++;

    return count;
}


/* подсчитывает количество классов эквивалентных строк данной матрицы */
int countRowClassesWithEqualRowElemsSums(matrix mx)
{
    long long* sums = calloc(mx.rows_count, sizeof(long long));

    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = 0; j < mx.cols_count; j++)
            sums[i] += mx.values[i][j];
    }

    qsort(sums, mx.rows_count, sizeof(long long), cmp_longlong);

    int count = countUniqueRowElemSums(sums, mx.rows_count);

    free(sums);

    return count;
}