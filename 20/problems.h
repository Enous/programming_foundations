#ifndef INC_20_PROBLEMS_H
#define INC_20_PROBLEMS_H

#include "matrix.h"

#define MAX_SIZE 20
#define MAX_STR_SIZE 100
#define MAX_DIGIT 9

#define SUBMAT_CORNER_COORDS 4

#define ASSERT(expected, got) assert(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

typedef struct map
{
    size_t value;
    char key[MAX_STR_SIZE];
} map;

typedef struct query
{
    int pos;
    char* prefix;
} query;

typedef struct TreeNode
{
    int max;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
} TreeNode;

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
void buildTree(int*, int);
TreeNode* binaryTree(int*, int);
int submatricesThatContainOnlyDigit1(matrix);
char** subdomainVisits(char**, int, int*);
char* smallestNum(char*);
void createFileWithNumsSmallerThanN(FILE*, char*, char*, int);
void outputAns(char[MAX_SIZE][MAX_STR_SIZE], int, query*, int);
void putDigit(int, char*, char*, bool*, char*, int);

#endif //INC_20_PROBLEMS_H
