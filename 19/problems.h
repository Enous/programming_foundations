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

/* решает выражение из 2-3 операндов, находящееся в файле,
   и записывает в конец данного файла результат */
void fsolve(FILE* f, char* fname);

/* сохраняет в файле только те слова,
   которые содержат данную последовательность символов */
void fsaveWordsWithSequence(FILE*, char*, char*);

#endif //INC_19_PROBLEMS_H
