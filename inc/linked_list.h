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
        struct Node *head;
        struct Node *tail;
} LinkedList;

typedef struct Node {
        int value;
        struct Node *next;
        struct Node *prev;
} Node;

LinkedList list_create();
void list_push(LinkedList *list, int value);
void list_print(LinkedList *list);
int  list_get(LinkedList *list, size_t idx);
void  list_free(LinkedList *list);

#endif // LINKED_LIST_H
