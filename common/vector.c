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
          void** nl = realloc(vector->data, vector->reserved * sizeof(void*));
          vector->data = nl;
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

void
vector_destroy(Vector* vector) {
     free(vector->data);
     vector->data = nullptr;
     vector->length = 0;
     vector->reserved = 0;
}
