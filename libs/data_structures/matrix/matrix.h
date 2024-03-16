#ifndef LIBS_MATRIX_H
#define LIBS_MATRIX_H

typedef struct matrix
{
    int **values; // элементы матрицы
    int rows_count; // количество рядов
    int cols_count; // количество столбцов
} matrix;

typedef struct position
{
    int row_idx;
    int col_idx;
} position;

#endif //LIBS_MATRIX_H
