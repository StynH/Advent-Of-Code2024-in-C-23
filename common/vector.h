#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define INITIAL_SIZE 10

typedef struct Vector{
    void** data;
    size_t length;
    size_t reserved;
} Vector;

Vector* vector_create();
void vector_insert_into(Vector* vector, void* element);
void* vector_element_at(const Vector* vector, size_t  index);
void vector_destroy(Vector* vector);

#endif //VECTOR_H
