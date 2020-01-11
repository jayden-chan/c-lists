#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

LinkedList list_create() {
        LinkedList l;
        l.len = 0;
        l.head = NULL;
        l.tail = NULL;
        return l;
}

void list_push(LinkedList *list, int value) {
        if (list->head == NULL) {
                Node *new_node = malloc(sizeof(struct Node));
                new_node->value = value;
                new_node->next = NULL;
                new_node->prev = NULL;
                list->head = new_node;
                list->tail = new_node;
        } else {
                Node *new_node = malloc(sizeof(struct Node));
                new_node->value = value;
                new_node->next = NULL;
                new_node->prev = list->tail;
                list->tail->next = new_node;
                list->tail = new_node;
        }

        list->len += 1;
}

void list_print(LinkedList *list) {
        Node *curr = list->head;

        printf("[");
        while (curr->next != NULL) {
                printf("%d, ", curr->value);
                curr = curr->next;
        }
        printf("%d]\n", curr->value);
}

int list_get(LinkedList *list, size_t idx) {
        if (list->len <= idx) {
                return -1;
        }

        Node *curr = list->head;

        int i = 0;
        while (i < idx) {
                curr = curr->next;
                i += 1;
        }

        return curr->value;
}

void list_free(LinkedList *list) {
        Node *curr = list->head;

        while (curr != NULL) {
                Node *prev = curr;
                curr = curr->next;
                free(prev);
        }
}
