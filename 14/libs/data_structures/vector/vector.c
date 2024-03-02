#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "vector.h"


// возвращает структуру-дескриптор вектор из n значений
vector createVector(size_t n)
{
    int* data = malloc(n * sizeof(int));

    if (data)
        return (vector) {data, 0, n};

    fprintf(stderr, "bad alloc");
    exit(1);
}


// изменяет количество
// памяти, выделенное под хранение элементов вектора
void reserve(vector* v, size_t new_capacity)
{
    if (v->capacity != 0 && new_capacity == 0)
    {
        deleteVector(v);
        clear(v);
        v->data = NULL;
        v->capacity = new_capacity;
    }
    else if (new_capacity != 0)
    {
        if (v->capacity == 0)
        {
            int* data = malloc(new_capacity * sizeof(int));

            if (data)
            {
                v->data = data;
                v->capacity = new_capacity;
            }
            else
            {
                fprintf(stderr, "bad alloc");
                exit(1);
            }
        }
        else
        {
            int* data = realloc(v->data, new_capacity);

            if (data)
            {
                v->data = data;
                v->capacity = new_capacity;

                if (v->size > v->capacity)
                    shrinkToFit(v);
            }
            else
            {
                fprintf(stderr, "bad alloc");
                exit(1);
            }
        }
    }
}


// удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector* v)
{
    v->size = 0;
}


// освобождает память, выделенную под неиспользуемые элементы
void shrinkToFit(vector* v)
{
    v->size = v->capacity;
}


//  освобождает память, выделенную вектору
void deleteVector(vector* v)
{
    free(v->data);
}


// возвращает true, если вектор пустой,
// и false в противном случае
bool isEmpty(vector* v)
{
    return v->size == 0;
}


// возвращает true, если вектор полный,
// и false в противном случае
bool isFull(vector* v)
{
    return v->size == v->capacity;
}


// возвращает i-й элемент вектора
int getVectorValue(vector* v, size_t idx)
{
    return v->data[idx];
}


// добавляет элемент x в конец вектора v
void pushBack(vector* v, int x)
{
    if (isFull(v))
    {
        size_t new_capacity = 0;

        if (v->capacity == 0)
            new_capacity = 1;
        else
            new_capacity = v->capacity * 2;

        reserve(v, new_capacity);
    }

    v->data[(v->size)++] = x;
}


// удаляет последний элемент из вектора
void popBack(vector* v)
{
    assert(!isEmpty(v));

    (v->size)--;
    v->data = realloc(v->data, v->size);
}


// возвращает указатель на idx-ый элемент вектора
int* getPointerToVectorElem(vector* v, size_t idx)
{
    if (idx < v->size)
        return v->data + idx;

    fprintf(stderr, "IndexError: Index (%lld) out of range", idx);
    exit(1);
}


// возвращает указатель на последний элемент вектора
int* back(vector* v)
{
    return v->data + v->size - 1;
}


// возвращает указатель на нулевой элемент вектора
int* front(vector* v)
{
    return v->data;
}