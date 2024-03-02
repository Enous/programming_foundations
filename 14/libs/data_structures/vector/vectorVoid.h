#ifndef INC_14_VECTORVOID_H
#define INC_14_VECTORVOID_H

#include <stdio.h>
#include <stdbool.h>

typedef struct vectorVoid
{
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t base_type_size; // размер базового типа:
                        // например, если вектор хранит int -
                        // то поле base_TypeSize = sizeof(int)
                        // если вектор хранит float -
                        // то поле base_TypeSize = sizeof(float)
} vectorVoid;


// возвращает структуру-дескриптор вектор из n значений
vectorVoid createVectorV(size_t, size_t);

// изменяет количество
// памяти, выделенное под хранение элементов вектора
void reserveV(vectorVoid*, size_t);

// освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vectorVoid*);

// удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vectorVoid*);

//  освобождает память, выделенную вектору
void deleteVectorV(vectorVoid*);


#endif //INC_14_VECTORVOID_H
