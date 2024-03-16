#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>
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
            int* data = realloc(v->data, new_capacity * v->base_type_size);

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


// возвращает true, если вектор пустой,
// и false в противном случае
bool isEmptyV(vectorVoid* v)
{
    return v->size == 0;
}


// возвращает true, если вектор полный,
// и false в противном случае
bool isFullV(vectorVoid* v)
{
    return v->size == v->capacity;
}


// записывает по адресу destination idx-ый элемент вектора v
void getVectorValueV(vectorVoid* v, size_t idx, void* destination)
{
    assert(idx < v->size);

    memcpy(destination, v->data + idx * v->base_type_size, v->base_type_size);
}


// записывает на idx-ый элемент вектора v значение,
// расположенное по адресу source
void setVectorValueV(vectorVoid* v, size_t idx, void* source)
{
    assert(idx < v->size);

    memcpy(v->data + idx * v->base_type_size, source, v->base_type_size);
}


// удаляет последний элемент из вектора
void popBackV(vectorVoid* v)
{
    assert(!isEmptyV(v));

    (v->size)--;
    v->data = realloc(v->data, v->size);
}


// записывает по адресу пустой ячейки памяти, идущей после последней заполненной ячейки,
// значение, расположенное по адресу source
void pushBackV(vectorVoid* v, void* source)
{
    if (isFullV(v))
    {
        size_t new_capacity = 0;

        if (v->capacity == 0)
            new_capacity = 1;
        else
            new_capacity = v->capacity * 2;

        reserveV(v, new_capacity);
    }

    memcpy(v->data + v->size * v->base_type_size, source, v->base_type_size);

    (v->size)++;
}