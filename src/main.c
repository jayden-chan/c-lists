#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"
#include "vector.h"
#include "panic.h"

#define LIST_SIZE 10000000
#define NUM_FETCH 1000

int main() {
        srand(time(0));

        Vector v = vector_create(0);
        /* LinkedList l = list_create(); */

        printf("Pushing %d, random items...\n", LIST_SIZE);
        for (int i = 0; i < LIST_SIZE; i++) {
                vector_push(&v, rand());
                /* list_push(&l, rand()); */
        }

        int sum = 0;
        printf("Summing %d items from random indexes...\n", NUM_FETCH);
        for (int i = 0; i < NUM_FETCH; i++) {
                int idx = (rand() % (LIST_SIZE - 1 - 0 + 1)) + 0;
                sum += vector_get(&v, idx);
                /* sum += list_get(&l, idx); */
        }

        printf("Freeing list...\n");
        vector_free(&v);
        /* list_free(&l); */
        return EXIT_SUCCESS;
}
