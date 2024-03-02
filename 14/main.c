#include <stdio.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/vector/vectorVoid.h"
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

    deleteVector(&v);
}


void test_getPointerToVectorElem_notEmptyVector()
{
    vector v = createVector(3);
    v.data[0] = 1;
    v.data[1] = 2;
    v.data[2] = 3;
    v.size = 3;

    size_t idx = 1;

    int* p = getPointerToVectorElem(&v, idx);

    assert(p == v.data + idx);
}


void test_getPointerToLastElem()
{
    vector v = createVector(3);
    v.data[0] = 1;
    v.data[1] = 2;
    v.data[2] = 3;
    v.size = 3;

    size_t idx = v.size - 1;

    int* p = getPointerToVectorElem(&v, idx);

    assert(p == v.data + v.size - 1);
}


void test_back()
{
    vector v = createVector(3);
    v.data[0] = 1;
    v.data[1] = 2;
    v.data[2] = 3;
    v.size = 3;

    int* p = back(&v);

    assert(p == v.data + v.size - 1);
}


void test_front()
{
    vector v = createVector(3);
    v.data[0] = 1;
    v.data[1] = 2;
    v.data[2] = 3;
    v.size = 3;

    int* p = front(&v);

    assert(p == v.data);
}


void test()
{
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_getPointerToVectorElem_notEmptyVector();
    test_getPointerToLastElem();
    test_back();
    test_front();
}


int main()
{
    vectorVoid v_void;

    return 0;
}