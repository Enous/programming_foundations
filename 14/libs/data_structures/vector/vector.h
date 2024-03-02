#ifndef INC_14_VECTOR_H
#define INC_14_VECTOR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct vector
{
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;


// возвращает структуру-дескриптор вектор из n значений
vector createVector(size_t);

// изменяет количество
// памяти, выделенное под хранение элементов вектора
void reserve(vector*, size_t);

// удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector*);

// освобождает память, выделенную под неиспользуемые элементы
void shrinkToFit(vector*);

//  освобождает память, выделенную вектору
void deleteVector(vector*);

// возвращает true, если вектор пустой,
// и false в противном случае
bool isEmpty(vector* v);

// возвращает true, если вектор полный,
// и false в противном случае
bool isFull(vector* v);

// возвращает i-й элемент вектора
int getVectorValue(vector*, size_t);

// добавляет элемент x в конец вектора v
void pushBack(vector*, int);

// удаляет последний элемент из вектора
void popBack(vector*);

// возвращает указатель на idx-ый элемент вектора
int* getPointerToVectorElem(vector*, size_t);

// возвращает указатель на последний элемент вектора
int* back(vector*);

// возвращает указатель на нулевой элемент вектора
int* front(vector*);

#endif //INC_14_VECTOR_H
