#include "vector3d.h"
#include "vector.h"
#include <stdio.h>

Vector3d*
vector3d_create() {
    Vector3d* vector3d = malloc(sizeof(Vector3d));
    vector3d->data = malloc(sizeof(Vector*));
    vector3d->data[0] = vector_create();
    vector3d->heigth = 1;
    return vector3d;
}

void
vector3d_insert_at(Vector3d* vector3d, size_t x, size_t y, void* element) {
    size_t height_needed = y + 1;

    while (vector3d->heigth < height_needed) {
        Vector** temp = realloc(vector3d->data, height_needed * sizeof(Vector*));
        vector3d->data = temp;
        vector3d->data[vector3d->heigth] = vector_create();
        vector3d->heigth++;
    }

    vector_insert_into(vector3d->data[y], element);
}

void*
vector3d_element_at(const Vector3d* vector3d, size_t x, size_t y) {
    if (y >= vector3d->heigth || x >= vector3d->data[y]->length) {
        return nullptr;
    }
    return vector_element_at(vector3d->data[y], x);
}

void*
vector3d_remove_element_at(Vector3d* vector3d, size_t x, size_t y) {
    if (y >= vector3d->heigth || x >= vector3d->data[y]->length) {
        return nullptr;
    }

    void* element = vector_remove_element_at(vector3d->data[y], x);
    return element;
}

void
vector3d_destroy(Vector3d* vector3d) {
    if (vector3d->data) {
        for (size_t i = 0; i < vector3d->heigth; i++) {
            if (vector3d->data[i]) {
                vector_destroy(vector3d->data[i]);
            }
        }
        free(vector3d->data);
    }
    free(vector3d);
}
