#ifndef LINKED_VECTOR_H
#define LINKED_VECTOR_H

typedef struct LinkedVector {
    size_t cap;
    size_t len;
    size_t chunks;
    struct LVNode *head;
} LinkedVector;

typedef struct LVNode {
    int *data;
    size_t cap;
    size_t used;
    struct LVNode *next;
} LVNode;

LVNode* lv_node_create(size_t cap);
LinkedVector lv_create(size_t cap);
void lv_push(LinkedVector *v, int value);
void lv_print(LinkedVector *v);
int lv_get(LinkedVector *v, size_t idx);
void lv_free(LinkedVector *v);

#endif // LINKED_VECTOR_H
