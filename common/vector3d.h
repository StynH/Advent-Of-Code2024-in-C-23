#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <stdlib.h>

typedef struct Vector3d{
    struct Vector** data;
    size_t heigth;
} Vector3d;

Vector3d* vector3d_create();
void vector3d_insert_at(Vector3d* vector3d, size_t x, size_t y, void* element);
void* vector3d_element_at(const Vector3d* vector3d, size_t x, size_t y);
void* vector3d_remove_element_at(Vector3d* vector3d, size_t x, size_t y);
void vector3d_destroy(Vector3d* vector3d);

#endif //VECTOR3D_H
