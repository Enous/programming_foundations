#ifndef INC_16_FUNCS_H
#define INC_16_FUNCS_H

#include "matrix.h"

/* меняет местами строки квадратной матрицы,
   в которых находятся максимальный и минимальный элементы */
void swapRowsWithMinAndMaxELems(matrix*);

int getMax(int*, int);

/* упорядочивает строки матрицы по неубыванию наибольших элементов строк */
void sortMatrixRowsByMaxRowElem(matrix*);

/* упорядочивает столбцы матрицы по неубыванию минимальных элементов столбцов */
void sortMatrixColsByMinColElem(matrix*);

#endif //INC_16_FUNCS_H
