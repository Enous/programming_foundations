#ifndef LIBS_MATRIX_H
#define LIBS_MATRIX_H

typedef struct matrix
{
    int** values; // элементы матрицы
    int rows_count; // количество рядов
    int cols_count; // количество столбцов
} matrix;

typedef struct position
{
    int row_idx;
    int col_idx;
} position;

/* размещает в динамической памяти матрицу размером
   rows_count на cols_count и возвращает матрицу */
matrix getMemMatrix(int, int);

/* размещает в динамической памяти массив из matrices_count матриц
   размером rows_count на cols_count и возвращает указатель на нулевую матрицу */
matrix* getMemArrayOfMatrices(int, int, int);

/* освобождает память, выделенную под хранение матрицы mx */
void freeMemMatrix(matrix*);

/* освобождает память, выделенную под хранение массива mxs из matrices_count матриц */
void freeMemMatrices(matrix*, int);

/* ввод матрицы */
void inputMatrix(matrix* mx);

/* ввод массива из matrices_count матриц, хранящегося по адресу mxs */
void inputMatrices(matrix*, int);

/* вывод матрицы */
void outputMatrix(matrix);

/* вывод массива их matrices_count, хранящегося по адресу mxs */
void outputMatrices(matrix*, int);

#endif //LIBS_MATRIX_H
