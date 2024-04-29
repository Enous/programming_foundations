#ifndef INC_19_PROBLEMS_H
#define INC_19_PROBLEMS_H

#include "problems.h"
#include "matrix.h"

#define MAX_STR_SIZE 100
#define MAX_SIZE 20

/* транспонирует матрицу в файле */
void ftranspose(FILE*, char*);

/* представляет каждое вещественное число в файле
   в форме с плавающей точкой */
void fileFixedToFloating(FILE* f, char* fname);

#endif //INC_19_PROBLEMS_H
