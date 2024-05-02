#ifndef INC_19_PROBLEMS_H
#define INC_19_PROBLEMS_H

#include "problems.h"
#include "matrix.h"

#define MAX_STR_SIZE 100
#define MAX_SIZE 20
#define WARES_FIELDS_COUNT 4

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

/* преобразовывает файл, оставляя в каждой строке
   только самое длинное слово */
void fsaveOnlyLongestWordInEveryLine(FILE*, char*);

/* преобразовывает файл таким образом, чтобы сначала были
   целые положительные числа, а затем отрицательные;
   порядок следования как положительных,
   так и отрицательных чисел сохраняется */
void fsortPosAndNeg(FILE*, char*);

/* транспонирует матрицу в файле, если она не симметрична */
void ftransposeIfNonSymmetric(FILE*, char*);

/* преобразовывает файл, сохранив в нем
   информацию только о лучших n членах команды */
void fileFormSportsTeam(FILE*, char*, int);

void fwares(FILE*, char*, FILE*, char*);

#endif //INC_19_PROBLEMS_H
