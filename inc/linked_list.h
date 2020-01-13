/**
 * Doubly-linked list with head and tail pointers
 *
 * Operations:
 * push: O(1)
 * get: O(n)
 * free: O(n)
 */
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList {
        size_t len;
        struct LLNode *head;
        struct LLNode *tail;
} LinkedList;

typedef struct LLNode {
        int value;
        struct LLNode *next;
        struct LLNode *prev;
} LLNode;

LinkedList ll_create();
void ll_push(LinkedList *list, int value);
void ll_print(LinkedList *list);
int  ll_get(LinkedList *list, size_t idx);
void  ll_free(LinkedList *list);

#endif // LINKED_LIST_H
