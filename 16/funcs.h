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

/* заменяет квадратную матрицу ее квадратом, если она симметрична */
void raiseMatrixToTheSecondPowerIfSymmetric(matrix*);

/* возвращает true, если все элементы целочисленного массива уникальны,
   и false в противном случае */
bool ifAllElemsAreUnique(int*, int);

/* транспонирует квадратную матрицу, если суммы элементов её строк различны */
void transposeMatrixIfThereAreNoEqualRowElemSums(matrix);

/* возвращает true, если две квадратные матрицы взаимно обратные,
   и false в противном случае */
bool twoSquareMatricesAreInversesOfEachOther(matrix mx1, matrix mx2);

/* возвращает сумму максимальных элементов псевдодиагоналей */
long long getSumOfPseudoDiagonalsMaxElems(matrix);

/* возвращает минимальный элемент матрицы в выделенной области */
int getMinElemInSelectedArea(matrix);

/* находит расстояние от данной точки до начала координат */
float getDistance(int*, int);

/* упорядочивает ряды матрицы по неубыванию их
   расстояний до начала координат */
void insertionSortMatrixRowsFloatCondition(matrix, float (*)(int*, int));

/* упорядочивает элементы матрицы (точки) по неубыванию их
   расстояний до начала координат */
void sortByDistances(matrix);

int cmp_longlong(const void* pa, const void* pb);

/* подсчитывает количество уникальных сумм элементов рядов матрицы */
int countUniqueRowElemSums(long long* arr, int size);

/* подсчитывает количество классов эквивалентных строк данной матрицы */
int countRowClassesWithEqualRowElemsSums(matrix m);

/* подсчитывает количество элементов матрицы, если они больше суммы остальных
   элементов своего столбца */
int countSpecialElems(matrix);

/* возвращает позицию первого минимального элемента матрицы (слева направо) */
position getFirstMinPos(matrix);

/* заменяет предпоследнюю строку матрицы первым
   из столбцов, в котором находится минимальный элемент матрицы */
void swapPenultimateRowWithFirstColWithMinElemInMatrix(matrix);

/* возвращает true, если массив отсортирован в порядке неубывания,
   и false в противном случае */
bool isSortedInNonDescendingOrder(int*, int);

/* возвращает true, если элементы всех рядов матрицы отсортированы в порядке неубывания,
   и false в противном случае */
bool elemsInAllRowsAreSortedInNonDescendingOrder(matrix);

/* подсчитывает количество матриц, строки которых упорядочены по неубыванию элементов */
int countMatricesWithRowElemsSortedInNonDescendingOrder(matrix*, int);

/* подсчитывает ряды матрицы, состоящие только из нулей */
int countRowsThatContainOnlyZeroes(matrix);

/* выводит матрицы с наибольшим числом нулевых строк */
void printMatricesWithMaxRowsThatContainOnlyZeroes(matrix*, int);

/* возвращает максимум абсолютных значений элементов матрицы */
int getMaxAbsoluteValue(matrix);

/* выводит матрицы с наименьшей нормой */
void printMatrixWithMinMaxAbsoluteValues(matrix*, int);

/* подсчитывает количество элементов в матрице, слева от которых
   только меньшие элементы, а справа - только большие */
int countSpecialMatrixElems(matrix);

#endif //INC_16_FUNCS_H
