#ifndef INC_14_VECTOR_H
#define INC_14_VECTOR_H

#include <stdio.h>

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

#endif //INC_14_VECTOR_H
