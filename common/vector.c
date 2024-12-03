#include <stdio.h>
#include "vector.h"

Vector*
vector_create(){
     Vector* vector = malloc(sizeof(Vector));
     vector->length = 0;
     vector->reserved = INITIAL_SIZE;
     vector->data = malloc(vector->reserved * sizeof(void*));
     return vector;
}

void
vector_insert_into(Vector* vector, void* element) {
     if (vector->length == vector->reserved) {
          vector->reserved *= 2;
          vector->data = realloc(vector->data, vector->reserved * sizeof(void*));
     }
     vector->data[vector->length++] = element;
}

void*
vector_element_at(const Vector* vector, const size_t  index){
     if(index >= vector->length){
          return nullptr;
     }

     return vector->data[index];
}

void*
vector_remove_element_at(Vector* vector, size_t index){
    void* element = vector_element_at(vector, index);
    for(size_t i = index; i < vector->length - 1; ++i){
        vector->data[i] = vector->data[i + 1];
    }

   --vector->length;
    if(vector->length > INITIAL_SIZE && vector->length <= vector->reserved / 2){
        vector->reserved /= 2;
        vector->data = realloc(vector->data, vector->reserved * sizeof(void*));
    }

    return element;
}

void
vector_destroy(Vector* vector) {
     free(vector->data);
     vector->data = nullptr;
     vector->length = 0;
     vector->reserved = 0;
}
