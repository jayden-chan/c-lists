#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"
#include "panic.h"

int reallocations = 0;

Vector vector_create(size_t cap) {
        if (cap == 0) {
                Vector v;
                v.len = 0;
                v.cap = 0;
                v.data = NULL;
                return v;
        } else {
                int *data = malloc(sizeof(int) * cap);
                if (!data) {
#ifdef DEBUG
                        fprintf(stderr, "[vector_create] VECTOR ALLOCATION FAILED\n");
#endif
                        panic("Failed to allocate memory for vector");
                }
                Vector v;
                v.len = 0;
                v.cap = cap;
                v.data = data;
                return v;
        }
}

bool vector_realloc(Vector *v, size_t new_cap) {
        if (new_cap <= v->cap) {
                return false;
        }

        int *new_data = realloc(v->data, sizeof(int) * new_cap);
        if (new_data) {
                v->data = new_data;
                v->cap = new_cap;
                reallocations += 1;
                return true;
        } else {
#ifdef DEBUG
                fprintf(stderr, "[vector_realloc] VECTOR REALLOCATION FAILED\n");
#endif
                return false;
        }
}

void vector_push(Vector *v, int value) {
        if (v->len >= v->cap) {
#ifdef DEBUG
                printf("Reallocating...\n");
#endif
                bool success = vector_realloc(v, v->cap == 0 ? 10 : v->cap * 2);
                if (!success) {
#ifdef DEBUG
                        fprintf(stderr, "FAILED TO PUSH\n");
#endif
                        panic("Failed to push new value to vector");
                }
        } else if (v->data == NULL) {
                int *data = malloc(sizeof(int) * 10);
                if (!data) {
#ifdef DEBUG
                        fprintf(stderr, "VECTOR ALLOCATION FAILED\n");
#endif
                        panic("Failed to push new value to vector");
                }
                v->data = data;
        }

        *(v->data + v->len) = value;
        v->len += 1;
}

void vector_print(Vector *v) {
        printf("[");
        for (int i = 0; i < v->len - 1; i++) {
                printf("%d, ", *(v->data + i));
        }
        printf("%d]\n", *(v->data + v->len - 1));
}

int vector_get(Vector *v, size_t idx) {
        if (idx >= v->len) {
                return -1;
        }

        return *(v->data + idx);
}

void vector_free(Vector *v) {
#ifdef DEBUG
        printf("Reallocations: %d\n", reallocations);
#endif
        free(v->data);
        v->data = NULL;
}
