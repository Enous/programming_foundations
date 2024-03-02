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
        v->capacity = 0;
    }
    else if (new_capacity != 0)
    {
        if (v->capacity == 0)
        {
            int* data = malloc(new_capacity * sizeof(int));

            if (data)
            {
                v->data = data;
                v->size = new_capacity;
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
