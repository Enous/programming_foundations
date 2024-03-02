#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "vectorVoid.h"

// возвращает структуру-дескриптор вектор из n значений
vectorVoid createVectorV(size_t n, size_t base_type_size)
{
    int* data = malloc(n * sizeof(base_type_size));

    if (data)
        return (vectorVoid) {data, 0, n, base_type_size};

    fprintf(stderr, "bad alloc");
    exit(1);
}


// изменяет количество
// памяти, выделенное под хранение элементов вектора
void reserveV(vectorVoid* v, size_t new_capacity)
{
    if (v->capacity != 0 && new_capacity == 0)
    {
        deleteVectorV(v);
        clearV(v);
        v->data = NULL;
        v->capacity = new_capacity;
    }
    else if (new_capacity != 0)
    {
        if (v->capacity == 0)
        {
            int* data = malloc(new_capacity * sizeof(v->base_type_size));

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
                    shrinkToFitV(v);
            }
            else
            {
                fprintf(stderr, "bad alloc");
                exit(1);
            }
        }
    }
}


// освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vectorVoid* v)
{
    v->size = v->capacity;
}


// удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vectorVoid* v)
{
    v->size = 0;
}


//  освобождает память, выделенную вектору
void deleteVectorV(vectorVoid* v)
{
    free(v->data);
}