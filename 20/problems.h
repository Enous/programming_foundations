#ifndef INC_20_PROBLEMS_H
#define INC_20_PROBLEMS_H

#define MAX_SIZE 20

#define SUBMAT_CORNER_COORDS 4

void matrixAdd(matrix*, int**, int);
matrix gameOfLife(matrix);
void medianFilter(matrix*, int);
int getArrMedian(matrix, int, int, int);
//char** subdomainVisits(char**, int, int*);
void shuffleStr(char*, int*, int);
int* binaryTree(int*, int, int*);
int submatricesThatContainOnlyDigit1(matrix);
char** subdomainVisits(char**, int, int*);

#endif //INC_20_PROBLEMS_H
