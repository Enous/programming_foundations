#include <stdio.h>

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