#include <stdio.h>
#include <stdlib.h>

#include "linked_vector.h"
#include "panic.h"

int allocations = 0;

LinkedVector lv_create(size_t cap) {
        LinkedVector v;
        v.cap = cap;
        v.len = 0;
        v.chunks = 0;

        if (cap == 0) {
                v.head = NULL;
        } else {
                LVNode *head = lv_node_create(cap);
                v.head = head;
                v.chunks += 1;
        }

        return v;
}

LVNode* lv_node_create(size_t cap) {
        if (cap == 0) {
                panic("Cannot allocate LVNode with 0 capacity");
        }

        LVNode *n = malloc(sizeof(struct LVNode));
        if (!n) {
                panic("Failed to allocate memory for LVNode");
        }

        int *data = malloc(sizeof(int) * cap);
        if (!data) {
                panic("Failed to allocate buffer for LVNode");
        }

        n->data = data;
        n->cap = cap;
        n->used = 0;
        n->next = NULL;
        return n;
}

void lv_push(LinkedVector *v, int value) {
        LVNode *curr = v->head;
        while (curr->next != NULL) {
                curr = curr->next;
        }

        if (curr->used >= curr->cap) {
#ifdef DEBUG
                printf("Out of capacity, allocating new chunk\n");
#endif
                size_t new_cap = curr->cap * 2;
                LVNode *new_node = lv_node_create(new_cap);
                curr->next = new_node;
                curr = new_node;
                v->cap += new_cap;
                v->chunks += 1;
                allocations += 1;
        }

        *(curr->data + curr->used) = value;
        curr->used += 1;
        v->len += 1;
}

void lv_print(LinkedVector *v) {
        LVNode *curr = v->head;

        printf("[");
        while (curr != NULL) {
                size_t used = curr->used - 1;

                for (int i = 0; i < used; i++) {
                        printf("%d, ", *(curr->data + i));
                }

                if (curr->next == NULL) {
                        printf("%d]", *(curr->data + used));
                } else {
                        printf("%d, ", *(curr->data + used));
                }

                curr = curr->next;
        }
        printf("\n");
}

int lv_get(LinkedVector *v, size_t idx) {
        if (idx >= v->len) {
                return -1;
        }

        LVNode *curr = v->head;
        size_t curr_idx = curr->cap;

#ifdef DEBUG
        printf("current chunk size %zu\n", curr->cap);
#endif
        while (curr_idx <= idx) {
                curr = curr->next;
                curr_idx += curr->cap;
#ifdef DEBUG
                printf("current chunk size %zu\n", curr->cap);
#endif
        }

#ifdef DEBUG
        printf("\n");
        printf("idx = %zu curr_idx = %zu\n", idx, curr_idx);
#endif
        size_t offset = (curr->cap - (curr_idx - idx));
#ifdef DEBUG
        printf("offset %zu\n", offset);
#endif
        return *(curr->data + offset);
}

void lv_free(LinkedVector *v) {
        LVNode *curr = v->head;

#ifdef DEBUG
        printf("Reallocations: %d\n", allocations);
#endif

        while (curr != NULL) {
                LVNode *prev = curr;
                curr = curr->next;
                if (prev->data) {
                        free(prev->data);
                }
                free(prev);
        }
}
