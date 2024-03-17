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

/* обмен строк матрицы по индексам */
void swapRows(matrix, int, int);

/* обмен столбцов матрицы по индексам */
void swapCols(matrix, int, int);

/* возвращает сумму элементов целочисленного массива */
int getSum(int*, int);

/* выполняет сортировку вставками строк
   матрицы по неубыванию значения функции,
   применяемой для строк */
void insertionSortMatrixRows(matrix, int (*)(int*, int));

/* выполняет сортировку выбором строк
   матрицы по неубыванию значения функции,
   применяемой для столбцов */
void selectionSortMatrixCols(matrix, int (*)(int*, int));

void swap(int*, int*);

/* возвращает true, если матрица является квадратной,
   и false в противном случае */
bool isSquareMatrix(matrix*);


/* возвращает true, если две матрицы равны,
   и false в противном случае */
bool TwoMatricesAreEqual(matrix*, matrix*);

/* возвращает true, если матрица является единичной,
   и false в противном случае */
bool isIdentityMatrix(matrix*);

/* возвращает значение true, если матрица является симметричной,
   и false в противном случае */
bool isSymmetricMatrix(matrix*);

/* транспонирует квадратную матрицу */
void transposeSquareMatrix(matrix*);

/* транспонирует матрицу */
void transposeMatrix(matrix*);

/* возвращает позицию минимального элемента матрицы */
position getMinValuePos(matrix);

/* возвращает позицию минимального элемента матрицы */
position getMaxValuePos(matrix);

/* возвращает матрицу, построенную из элементов данного массива */
matrix createMatrixFromArray(const int*, size_t, size_t);

/* возвращает указатель на нулевую матрицу массива из матриц, размещенных
   в динамической памяти, построенных из элементов данного массива */
matrix* createMatrixArrayFromArray(const int*, size_t, size_t, size_t);

#endif //LIBS_MATRIX_H
