#ifndef INC_20_PROBLEMS_H
#define INC_20_PROBLEMS_H

#define MAX_SIZE 20
#define MAX_STR_SIZE 100

#define SUBMAT_CORNER_COORDS 4

#define ASSERT(expected, got) assert(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

void assert(const int, int,
            char const*, char const*,
            int);
void assertString(const char*, char*,
                  char const*, char const*,
                  int);

void matrixAdd(matrix*, int**, int);
matrix gameOfLife(matrix);
void medianFilter(matrix*, int);
int getArrMedian(matrix, int, int, int);
//char** subdomainVisits(char**, int, int*);
void shuffleStr(char*, int*, int);
int* binaryTree(int*, int, int*);
int submatricesThatContainOnlyDigit1(matrix);
char** subdomainVisits(char**, int, int*);
void createFileWithNumsSmallerThanN1(FILE*, char*, char*, int);

#endif //INC_20_PROBLEMS_H
