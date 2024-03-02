#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include <stdbool.h>
#include <assert.h>

void test_pushBack_emptyVector()
{
    size_t capacity = 0;
    vector v = createVector(capacity);

    int value = 1;
    pushBack(&v, value);

    assert(v.data[0] == 1);
    assert(v.size == 1);
    assert(v.capacity == 1);

    deleteVector(&v);
}


void test_pushBack_fullVector()
{
    size_t capacity = 3;
    size_t size = 3;
    vector v = createVector(capacity);
    v.data[0] = 1;
    v.data[1] = 2;
    v.data[2] = 3;
    v.size = size;

    int value = 1;
    pushBack(&v, value);

    assert(v.capacity == capacity * 2);
    assert(v.size = (size + 1));
    assert(v.data[v.size - 1] == value);

    deleteVector(&v);
}


void test_popBack_notEmptyVector()
{
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}


void test()
{
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
}


int main()
{
    test();

    return 0;
}