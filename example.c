#include "libdatastruct.h"
#include <stdio.h>
#include <string.h>

int main()
{
    linkedlist *l = create_linkedlist();

    /* Let's add some variables */
    int var1 = 1;
    int var2 = 2;
    int var3 = 3;
    linkedlist_add(l, &var1, sizeof(int));
    linkedlist_add(l, &var2, sizeof(int));
    linkedlist_add(l, &var3, sizeof(int));

    /* Let's list them with a loop! */
    int j;
    for (j = 0; j < linkedlist_length(l); j++)
    {
        printf("%d. value of linked list: %d\n", j,
               *(int *)linkedlist_get(l, j));
    }

    /* Let's delete an element */
    linkedlist_delete(l, 1);
    printf("After deleting:\n");
    for (j = 0; j < linkedlist_length(l); j++)
    {
        printf("%d. value of linked list: %d\n", j,
               *(int *)linkedlist_get(l, j));
    }

    /* Let's update an element */
    char *newvar = "A new value.";
    linkedlist_update(l, 1, newvar, strlen(newvar) + 1);
    printf("After updating:\n");
    for (j = 0; j < linkedlist_length(l); j++)
    {
        if (j == 1)
        {
            printf("%d. value of linked list: %s\n", j,
                   (char *)linkedlist_get(l, j));
        }
        else
        {
            printf("%d. value of linked list: %d\n", j,
                   *(int *)linkedlist_get(l, j));
        }
    }

    /* Inserting an element */
    double pi = 3.14;
    linkedlist_insert(l, &pi, sizeof(double), 1);
    printf("After inserting:\n");
    for (j = 0; j < linkedlist_length(l); j++)
    {
        if (j == 2)
        {
            printf("%d. value of linked list: %s\n", j,
                   (char *)linkedlist_get(l, j));
        }
        else if (j == 1)
        {
            printf("%d. value of linked list: %f\n", j,
                   *(double *)linkedlist_get(l, j));
        }
        else
        {
            printf("%d. value of linked list: %d\n", j,
                   *(int *)linkedlist_get(l, j));
        }
    }

    /* Getting the length */

    printf("This is the final length of the list: %d\n", linkedlist_length(l));

    linkedlist_free(l);

    /* Let's create a map! */

    map *m = create_map();
    int key1 = 1;
    int value1 = 2;
    int key2 = 3;
    int value2 = 4;
    int key3 = 5;
    int value3 = 6;

    map_add(m, &key1, sizeof(int), &value1, sizeof(int));
    map_add(m, &key2, sizeof(int), &value2, sizeof(int));
    map_add(m, &key3, sizeof(int), &value3, sizeof(int));

    /* Retrieving the length of map */
    printf("Map length: %d\n", map_length(m));

    /* Getting some values from keys */
    printf("Value of key1: %d\n", *(int *)map_get(m, &key1, sizeof(int)));

    /* Looping through map */
    void *key;
    void *value;
    j = 0;

    loopMap(m, key, value)
    {
        printf("%d. key: %d\n", ++j, *(int *)key);
        printf("%d. value: %d\n", j, *(int *)value);
    }

    /* Let's delete a key from map! */
    map_delete(m, &key1, sizeof(int));

    printf("After deleting:\n");
    j = 0;
    loopMap(m, key, value)
    {
        printf("%d. key: %d\n", ++j, *(int *)key);
        printf("%d. value: %d\n", j, *(int *)value);
    }

    /* Updating first key */

    int new_key = 314;
    int new_value = 314159;

    map_update_key(m, &key2, sizeof(int), &new_key, sizeof(int));
    map_update_value(m, &key3, sizeof(int), &new_value, sizeof(int));
    printf("After updating:\n");
    j = 0;

    /* Minimizing the map */
    map_minimize(m);

    loopMap(m, key, value)
    {
        printf("%d. key: %d\n", ++j, *(int *)key);
        printf("%d. value: %d\n", j, *(int *)value);
    }

    /* Freeing map */

    map_free(m);

    /* Creating a stack */

    stack *s = create_stack();

    /* Pushing values to stack */

    int stack_val1 = 1;
    int stack_val2 = 2;
    int stack_val3 = 3;
    int stack_val4 = 4;

    stack_push(s, &stack_val1, sizeof(int));
    stack_push(s, &stack_val2, sizeof(int));
    stack_push(s, &stack_val3, sizeof(int));
    stack_push(s, &stack_val4, sizeof(int));

    /* Popping some values from stack */
    printf("Popped: %d\n", *(int *)stack_pop(s));
    printf("Popped: %d\n", *(int *)stack_pop(s));
    printf("Popped: %d\n", *(int *)stack_pop(s));
    printf("Popped: %d\n", *(int *)stack_pop(s));

    /* Peeking a value from stack */

    stack_push(s, &stack_val1, sizeof(int));
    printf("Peeked: %d\n", *(int *)stack_peek(s));
    printf("Popped: %d\n", *(int *)stack_pop(s));

    /* Minimizing stack */
    stack_minimize(s);

    /* Freeing stack */
    stack_free(s);

    /* Creating a new queue */

    queue *q = create_queue();

    int queue_val1 = 1;
    int queue_val2 = 2;
    int queue_val3 = 3;
    int queue_val4 = 4;
    int queue_val5 = 5;

    /* Putting some values to our queue, via enqueueing */

    enqueue(q, &queue_val1, sizeof(int));
    enqueue(q, &queue_val2, sizeof(int));
    enqueue(q, &queue_val3, sizeof(int));
    enqueue(q, &queue_val4, sizeof(int));
    enqueue(q, &queue_val5, sizeof(int));

    /* Dequeueing them to access them again */

    printf("Value dequeued: %d\n", *(int *)dequeue(q));
    printf("Value dequeued: %d\n", *(int *)dequeue(q));
    printf("Value dequeued: %d\n", *(int *)dequeue(q));
    printf("Value dequeued: %d\n", *(int *)dequeue(q));
    printf("Value to be dequeued: %d\n", *(int *)queue_front(q));
    printf("Value dequeued: %d\n", *(int *)dequeue(q));

    /* Minimizing queue */
    queue_minimize(q);

    /* Freeing our queue */
    queue_free(q);

    /* Creating a binary tree */

    bintree *b = create_bintree();

    /* Initializing some nodes */

    bintree_set_nodes(b);
    bintree_set_nodes(b->left);
    bintree_set_nodes(b->right);

    /* Setting values */
    int bintree_val1 = 1;
    int bintree_val2 = 2;
    int bintree_val3 = 3;
    int bintree_val4 = 4;
    int bintree_val5 = 5;
    int bintree_val6 = 6;
    int bintree_val7 = 7;

    bintree_set(b, &bintree_val1, sizeof(int));
    bintree_set(b->left, &bintree_val2, sizeof(int));
    bintree_set(b->right, &bintree_val3, sizeof(int));
    bintree_set(b->left->left, &bintree_val4, sizeof(int));
    bintree_set(b->left->right, &bintree_val5, sizeof(int));
    bintree_set(b->right->left, &bintree_val6, sizeof(int));
    bintree_set(b->right->right, &bintree_val7, sizeof(int));

    /* Accessing values */

    printf("Value of tree's left node: %d\n", *(int *)bintree_get(b->left));
    printf("Value of tree's left node's right node: %d\n",
           *(int *)bintree_get(b->left->right));
    printf("Value of tree's right node's left node: %d\n",
           *(int *)bintree_get(b->right->left));

    /* Cleaning up */
    bintree_destroy(b);

    /* Creating a vector */
    vector *v = create_vector();

    /* Adding variables */
    int vector_var1 = 1;
    int vector_var2 = 2;
    int vector_var3 = 3;
    int vector_var4 = 4;
    int vector_var5 = 5;
    int vector_var6 = 6;
    int vector_var7 = 7;

    vector_add(v, &vector_var1, sizeof(int));
    vector_add(v, &vector_var2, sizeof(int));
    vector_add(v, &vector_var3, sizeof(int));
    vector_add(v, &vector_var4, sizeof(int));
    vector_add(v, &vector_var5, sizeof(int));
    vector_add(v, &vector_var6, sizeof(int));
    vector_add(v, &vector_var7, sizeof(int));

    /* Looping through the vector */

    void *i;
    j = 1;

    loopVector(v, i) { printf("%d. value of vector: %d\n", j++, *(int *)i); }

    /* Deleting items */
    vector_delete(v, 3);

    printf("Vector after deletion:\n");

    j = 1;
    loopVector(v, i) { printf("%d. value of vector: %d\n", j++, *(int *)i); }

    /* Inserting item */
    vector_insert(v, 3, &vector_var4, sizeof(int));
    vector_insert(v, 3, &vector_var7, sizeof(int));

    printf("Vector after insertions:\n");

    j = 1;
    loopVector(v, i) { printf("%d. value of vector: %d\n", j++, *(int *)i); }

    /* Getting the length */

    printf("Vector length: %d\n", vector_length(v));

    /* Cleaning up */
    vector_free(v);

    /* Initializing a trie */

    trie *t = trie_create();

    /* Inserting some words */

    trie_insert(t, "ace");
    trie_insert(t, "ant");
    trie_insert(t, "cat");
    trie_insert(t, "pet");
    trie_insert(t, "pen");

    /* Searching words in trie */

    printf("Is 'ace' in trie: %s\n", trie_search(t, "ace") ? "Yes" : "No");
    printf("Is 'ant' in trie: %s\n", trie_search(t, "ant") ? "Yes" : "No");
    printf("Is 'cat' in trie: %s\n", trie_search(t, "cat") ? "Yes" : "No");
    printf("Is 'pet' in trie: %s\n", trie_search(t, "pet") ? "Yes" : "No");
    printf("Is 'pen' in trie: %s\n", trie_search(t, "pen") ? "Yes" : "No");
    printf("Is 'hello' in trie: %s\n", trie_search(t, "hello") ? "Yes" : "No");
    printf("Is 'hi' in trie: %s\n", trie_search(t, "hi") ? "Yes" : "No");
    printf("Is 'dog' in trie: %s\n", trie_search(t, "dog") ? "Yes" : "No");
}
