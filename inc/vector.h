/**
 * List ADT implemented with contiguous chunk of
 * heap allocated memory
 *
 * Operations:
 * push: O(1)
 * get: O(1)
 * free: O(1)
 */
#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    size_t len;
    size_t cap;
    int *data;
} Vector;

Vector vector_create(size_t cap);
void vector_push(Vector *v, int value);
void vector_print(Vector *v);
int vector_get(Vector *v, size_t idx);
void vector_free(Vector *v);

#endif // VECTOR_H
