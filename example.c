#include "libdatastruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tree_bfs(lds_tree *);
void print_bintree_bfs(lds_bintree *);

int main()
{
    lds_linkedlist *l = lds_create_linkedlist();

    /* Checking linked list is empty whether not */
    printf("Is linkedlist empty: %d\n", lds_linkedlist_is_empty(l));

    /* Let's add some variables */
    int var1 = 1;
    int var2 = 2;
    int var3 = 3;
    lds_linkedlist_add(l, &var1, sizeof(int));
    lds_linkedlist_add(l, &var2, sizeof(int));
    lds_linkedlist_add(l, &var3, sizeof(int));

    /* Checking linked list is empty whether not */
    printf("Is linkedlist empty: %d\n", lds_linkedlist_is_empty(l));

    /* Let's list them with a loop! */
    size_t j = 0;
    void *ptr;
    lds_linkedlist_for_each(l, ptr)
    {
        printf("%ld. value of linked list: %d\n", ++j, *(int *)ptr);
    }

    /* Let's delete an element */
    lds_linkedlist_delete(l, 1);
    printf("After deleting:\n");
    j = 0;
    lds_linkedlist_for_each(l, ptr)
    {
        printf("%ld. value of linked list: %d\n", ++j, *(int *)ptr);
    }

    /* Let's update an element */
    char *newvar = "A new value.";
    lds_linkedlist_update(l, 1, newvar, strlen(newvar) + 1);
    printf("After updating:\n");
    j = 0;
    lds_linkedlist_for_each(l, ptr)
    {
        if (j == 1)
        {
            printf("%ld. value of linked list: %s\n", ++j, (char *)ptr);
        }
        else
        {
            printf("%ld. value of linked list: %d\n", ++j, *(int *)ptr);
        }
    }

    /* Inserting an element */
    double pi = 3.14;
    lds_linkedlist_insert(l, &pi, sizeof(double), 1);
    printf("After inserting:\n");
    j = 0;
    lds_linkedlist_for_each(l, ptr)
    {
        if (j == 2)
        {
            printf("%ld. value of linked list: %s\n", ++j, (char *)ptr);
        }
        else if (j == 1)
        {
            printf("%ld. value of linked list: %f\n", ++j, *(double *)ptr);
        }
        else
        {
            printf("%ld. value of linked list: %d\n", ++j, *(int *)ptr);
        }
    }

    /* Popping an item */
    char ll_popped_item[16];
    lds_linkedlist_pop(l, &ll_popped_item);
    printf("Popped value from linked list: %s\n", ll_popped_item);

    /* Getting the length */

    printf("This is the length of the list: %ld\n", lds_linkedlist_length(l));

    /* Extending the linked list with another linkedlist */
    lds_linkedlist *l2 =
        lds_create_linkedlist(); /* Creating a second linked list in order to
                                    extend the first */
    lds_linkedlist_add(l2, &var1, sizeof(int));
    lds_linkedlist_add(l2, &var2, sizeof(int));
    lds_linkedlist_add(l2, &var3, sizeof(int));

    lds_linkedlist_extend(l, l2);

    /* Printing list after extending */
    j = 0;
    lds_linkedlist_for_each(l, ptr)
    {
        if (j == 1)
        {
            printf("%ld. value of linked list: %f\n", ++j, *(double *)ptr);
        }
        else
        {
            printf("%ld. value of linked list: %d\n", ++j, *(int *)ptr);
        }
    }

    /* Reversing a list */
    lds_linkedlist_reverse(l);

    /* Printing list after reversing */
    j = 0;
    lds_linkedlist_for_each(l, ptr)
    {
        if (j == 3)
        {
            printf("%ld. value of linked list: %f\n", ++j, *(double *)ptr);
        }
        else
        {
            printf("%ld. value of linked list: %d\n", ++j, *(int *)ptr);
        }
    }

    /* Finding the index of item */
    printf("Index of the first item that has value 3.14: %ld\n",
           lds_linkedlist_index(l, &pi, sizeof(double)));

    /* Getting data size of items */
    printf("Data size of second element: %ld\n",
           lds_linkedlist_data_size(lds_linkedlist_get_node(l, 1)));

    /* Finding the item */
    printf(
        "Size of the first item that has value 2: %ld\n",
        lds_linkedlist_data_size(lds_linkedlist_find(l, &var2, sizeof(int))));

    /* Getting the next item of a node */
    printf("The size of the next item of the third item: %ld\n",
           lds_linkedlist_data_size(
               lds_linkedlist_next(lds_linkedlist_get_node(l, 2))));

    /* Getting the previous item of a node */
    printf("The size of the previous item of the fifth item: %ld\n",
           lds_linkedlist_data_size(
               lds_linkedlist_prev(lds_linkedlist_get_node(l, 4))));

    /* Accessing the head node, if only have a node in middle of the linked list
     */
    lds_linkedlist *middle_node = lds_linkedlist_get_node(
        l, 3); /* Simulating the case we only have a middle node */
    printf("Size of head of linked list: %ld\n",
           lds_linkedlist_data_size(lds_linkedlist_head(middle_node)));

    /* Accessing the tail node, if you don't have */
    printf("Size of tail of the linked list: %ld\n",
           lds_linkedlist_data_size(lds_linkedlist_tail(middle_node)));

    /* Getting the data of an lds_linkedlist* object */
    printf("The data of the fourth node: %f\n",
           *(double *)lds_linkedlist_data(middle_node));

    /* Cleaning up */
    lds_linkedlist_free(l);
    lds_linkedlist_free(l2);

    /* Let's create a map! */
    lds_map *m = lds_create_map();
    int key1 = 1;
    int value1 = 2;
    int key2 = 3;
    int value2 = 4;
    int key3 = 5;
    int value3 = 6;

    /* Checking map is empty whether not */
    printf("Is map empty: %d\n", lds_map_is_empty(m));

    /* Reserving some space in order to increase performance */
    lds_map_reserve(m, 3);

    /* Checking capacity */
    printf("Capacity of map: %ld\n", lds_map_capacity(m));

    /* Adding values to map */
    lds_map_add(m, &key1, sizeof(int), &value1, sizeof(int));
    lds_map_add(m, &key2, sizeof(int), &value2, sizeof(int));
    lds_map_add(m, &key3, sizeof(int), &value3, sizeof(int));

    /* Retrieving the length of map */
    printf("Map length: %ld\n", lds_map_length(m));

    /* Getting some values from keys */
    printf("Value of key1: %d\n", *(int *)lds_map_get(m, &key1, sizeof(int)));

    /* Looping through map */
    void *key;
    void *value;
    j = 0;

    lds_map_for_each(m, key, value)
    {
        printf("%ld. key: %d\n", ++j, *(int *)key);
        printf("%ld. value: %d\n", j, *(int *)value);
    }

    /* Let's delete a key from map! */
    lds_map_delete(m, &key1, sizeof(int));

    printf("After deleting:\n");
    j = 0;
    lds_map_for_each(m, key, value)
    {
        printf("%ld. key: %d\n", ++j, *(int *)key);
        printf("%ld. value: %d\n", j, *(int *)value);
    }

    /* Updating first key */

    int new_key = 314;
    int new_value = 314159;

    lds_map_update_key(m, &key2, sizeof(int), &new_key, sizeof(int));
    lds_map_update_value(m, &key3, sizeof(int), &new_value, sizeof(int));
    printf("After updating:\n");
    j = 0;

    /* Minimizing the map */
    lds_map_minimize(m);

    lds_map_for_each(m, key, value)
    {
        printf("%ld. key: %d\n", ++j, *(int *)key);
        printf("%ld. value: %d\n", j, *(int *)value);
    }

    /* Checking map is empty whether not */
    printf("Is map empty: %d\n", lds_map_is_empty(m));

    /* Freeing map */

    lds_map_free(m);

    /* Creating a stack */

    lds_stack *s = lds_create_stack();

    /* Reserving some space in stack before pushes in order to increase
     * performance */
    lds_stack_reserve(s, 4);

    /* Checking capacity */
    printf("Stack capacity: %ld\n", lds_stack_capacity(s));

    /* Checking is stack empty */
    printf("Is stack empty: %d\n", lds_stack_is_empty(s));

    /* Pushing values to stack */

    int stack_val1 = 1;
    int stack_val2 = 2;
    int stack_val3 = 3;
    int stack_val4 = 4;

    lds_stack_push(s, &stack_val1, sizeof(int));
    lds_stack_push(s, &stack_val2, sizeof(int));
    lds_stack_push(s, &stack_val3, sizeof(int));
    lds_stack_push(s, &stack_val4, sizeof(int));

    /* Checking is stack empty */
    printf("Is stack empty: %d\n", lds_stack_is_empty(s));

    /* Popping some values from stack */
    int popped_val1;
    int popped_val2;
    int popped_val3;
    int popped_val4;

    lds_stack_pop(s, &popped_val1);
    lds_stack_pop(s, &popped_val2);
    lds_stack_pop(s, &popped_val3);
    lds_stack_pop(s, &popped_val4);
    printf("Popped: %d\n", popped_val1);
    printf("Popped: %d\n", popped_val2);
    printf("Popped: %d\n", popped_val3);
    printf("Popped: %d\n", popped_val4);

    /* Peeking a value from stack */

    int popped_val5;
    lds_stack_push(s, &stack_val1, sizeof(int));
    printf("Peeked: %d\n", *(int *)lds_stack_peek(s));

    lds_stack_pop(s, &popped_val5);
    printf("Popped: %d\n", popped_val5);

    /* Minimizing stack */
    lds_stack_minimize(s);

    /* Freeing stack */
    lds_stack_free(s);

    /* Creating a new queue */

    lds_queue *q = lds_create_queue();

    /* Reserving some space before enqueueing */
    lds_queue_reserve(q, 5);

    /* Checking the capacity of queue */
    printf("Capacity of queue: %ld\n", lds_queue_capacity(q));

    int queue_val1 = 1;
    int queue_val2 = 2;
    int queue_val3 = 3;
    int queue_val4 = 4;
    int queue_val5 = 5;

    /* Putting some values to our queue, via enqueueing */

    lds_queue_enqueue(q, &queue_val1, sizeof(int));
    lds_queue_enqueue(q, &queue_val2, sizeof(int));
    lds_queue_enqueue(q, &queue_val3, sizeof(int));
    lds_queue_enqueue(q, &queue_val4, sizeof(int));
    lds_queue_enqueue(q, &queue_val5, sizeof(int));

    /* Dequeueing them to access them again */

    int dequeued_val1;
    int dequeued_val2;
    int dequeued_val3;
    int dequeued_val4;
    int dequeued_val5;

    lds_queue_dequeue(q, &dequeued_val1);
    lds_queue_dequeue(q, &dequeued_val2);
    lds_queue_dequeue(q, &dequeued_val3);
    lds_queue_dequeue(q, &dequeued_val4);

    /* Checking is queue empty */
    printf("Is queue empty: %s\n", lds_queue_is_empty(q) ? "Yes" : "No");

    printf("Value dequeued: %d\n", dequeued_val1);
    printf("Value dequeued: %d\n", dequeued_val2);
    printf("Value dequeued: %d\n", dequeued_val3);
    printf("Value dequeued: %d\n", dequeued_val4);
    printf("Value to be dequeued: %d\n", *(int *)lds_queue_front(q));
    lds_queue_dequeue(q, &dequeued_val5);

    /* Dequeue returns an error code, so you can detect failures */
    if (!lds_queue_dequeue(q, &dequeued_val5))
    {
        printf("Dequeue failed (expected)\n");
    }

    printf("Value dequeued: %d\n", dequeued_val5);

    /* Checking is queue empty */
    printf("Is queue empty: %s\n", lds_queue_is_empty(q) ? "Yes" : "No");

    /* Minimizing queue */
    lds_queue_minimize(q);

    /* Freeing our queue */
    lds_queue_free(q);

    /* Creating a binary tree */

    lds_bintree *b = lds_create_bintree();

    /* Checking is binary tree empty whether not */
    printf("Is binary tree empty: %d\n", lds_bintree_is_empty(b));

    /* Setting values */
    int bintree_val1 = 1;
    int bintree_val2 = 2;
    int bintree_val3 = 3;
    int bintree_val4 = 4;
    int bintree_val5 = 5;
    int bintree_val6 = 6;
    int bintree_val7 = 7;

    /* Putting values */
    lds_bintree_insert_left(b, &bintree_val2, sizeof(int));
    lds_bintree_insert_right(b, &bintree_val3, sizeof(int));
    lds_bintree_insert_left(lds_bintree_left(b), &bintree_val4, sizeof(int));
    lds_bintree_insert_right(lds_bintree_left(b), &bintree_val5, sizeof(int));
    lds_bintree_insert_left(lds_bintree_right(b), &bintree_val6, sizeof(int));
    lds_bintree_insert_right(lds_bintree_right(b), &bintree_val7, sizeof(int));

    /* Changing values */
    lds_bintree_set(b, &bintree_val1, sizeof(int));

    /* Checking is binary tree empty whether not */
    printf("Is binary tree empty: %d\n", lds_bintree_is_empty(b));

    /* Accessing values */

    printf("Value of tree's left node: %d\n",
           *(int *)lds_bintree_get(lds_bintree_left(b)));
    printf("Value of tree's left node's right node: %d\n",
           *(int *)lds_bintree_get(lds_bintree_right(lds_bintree_left(b))));
    printf("Value of tree's right node's left node: %d\n",
           *(int *)lds_bintree_get(lds_bintree_left(lds_bintree_right(b))));

    /* Checking nodes have left children */

    printf("Does tree have a left child: %s\n",
           lds_bintree_has_left(b) ? "Yes" : "No");
    printf("Does tree's left child have a left child: %s\n",
           lds_bintree_has_left(lds_bintree_left(b)) ? "Yes" : "No");
    printf("Does tree's right child have a left child: %s\n",
           lds_bintree_has_left(lds_bintree_right(b)) ? "Yes" : "No");
    printf("Does tree's right child's left child have a left child: %s\n",
           lds_bintree_has_left(lds_bintree_left(lds_bintree_right(b))) ? "Yes"
                                                                        : "No");
    printf("Does tree's left child's left child have a left child: %s\n",
           lds_bintree_has_left(lds_bintree_left(lds_bintree_left(b))) ? "Yes"
                                                                       : "No");

    /* Checking nodes have right children */

    printf("Does tree have a right child: %s\n",
           lds_bintree_has_right(b) ? "Yes" : "No");
    printf("Does tree's left child have a right child: %s\n",
           lds_bintree_has_right(lds_bintree_left(b)) ? "Yes" : "No");
    printf("Does tree's right child have a right child: %s\n",
           lds_bintree_has_right(lds_bintree_right(b)) ? "Yes" : "No");
    printf("Does tree's right child's left child have a right child: %s\n",
           lds_bintree_has_right(lds_bintree_left(lds_bintree_right(b)))
               ? "Yes"
               : "No");
    printf("Does tree's left child's left child have a right child: %s\n",
           lds_bintree_has_right(lds_bintree_left(lds_bintree_left(b))) ? "Yes"
                                                                        : "No");

    /* Getting size of nodes */
    printf("Size of root node: %ld\n", lds_bintree_data_size(b));

    /* Deleting the left child */
    lds_bintree_delete_left(b);
    lds_bintree_insert_left(
        b, &bintree_val1,
        sizeof(int)); // Putting a dummy value so destroy function doesn't fail

    /* Deleting the right child */
    lds_bintree_delete_right(b);
    lds_bintree_insert_right(
        b, &bintree_val1,
        sizeof(int)); // Putting a dummy value so destroy function doesn't fail

    /* Looping through binary tree using BFS algorithm */
    lds_bintree_bfs(b, print_bintree_bfs);
    printf("\n");

    /* Cleaning up */
    lds_bintree_free(b);

    /* Creating a vector */
    lds_vector *v = lds_create_vector();

    /* Checking is vector empty whether not */
    printf("Is the vector empty: %d\n", lds_vector_is_empty(v));

    /* Reserving some space before multiple allocations, which can lead to
     * performance increase */
    lds_vector_reserve(v, 7);

    /* Adding variables */
    int vector_var1 = 1;
    int vector_var2 = 2;
    int vector_var3 = 3;
    int vector_var4 = 4;
    int vector_var5 = 5;
    int vector_var6 = 6;
    int vector_var7 = 7;

    lds_vector_add(v, &vector_var1, sizeof(int));
    lds_vector_add(v, &vector_var2, sizeof(int));
    lds_vector_add(v, &vector_var3, sizeof(int));
    lds_vector_add(v, &vector_var4, sizeof(int));
    lds_vector_add(v, &vector_var5, sizeof(int));
    lds_vector_add(v, &vector_var6, sizeof(int));
    lds_vector_add(v, &vector_var7, sizeof(int));
    lds_vector_minimize(v);

    /* Checking is vector empty whether not */
    printf("Is the vector empty: %d\n", lds_vector_is_empty(v));

    /* Looping through the vector */

    void *i;
    j = 1;

    lds_vector_for_each(v, i)
    {
        printf("%ld. value of vector: %d\n", j++, *(int *)i);
    }

    /* Deleting items */
    lds_vector_delete(v, 3);

    printf("Vector after deletion:\n");

    j = 1;
    lds_vector_for_each(v, i)
    {
        printf("%ld. value of vector: %d\n", j++, *(int *)i);
    }

    /* Inserting item */
    lds_vector_insert(v, 3, &vector_var4, sizeof(int));
    lds_vector_insert(v, 3, &vector_var7, sizeof(int));

    printf("Vector after insertions:\n");

    j = 1;
    lds_vector_for_each(v, i)
    {
        printf("%ld. value of vector: %d\n", j++, *(int *)i);
    }

    /* Getting the length */

    printf("Vector length: %ld\n", lds_vector_length(v));

    /* Accessing by index */
    printf("Vector's third item: %d\n", *(int *)lds_vector_get(v, 2));

    /* Popping a value */
    int vector_popped_val;
    lds_vector_pop(v, &vector_popped_val);
    printf("Popped value from vector: %d\n", vector_popped_val);

    /* Extending a vector with another vector */
    lds_vector *v2 = lds_create_vector();

    lds_vector_add(v2, &vector_var1, sizeof(int));
    lds_vector_add(v2, &vector_var2, sizeof(int));
    lds_vector_add(v2, &vector_var3, sizeof(int));

    lds_vector_extend(v, v2);

    /* Finding indexes of items */
    printf("Index of the first item that has value 6: %ld\n",
           lds_vector_index(v, &vector_var6, sizeof(int)));

    /* Printing vector after extending */
    printf("Vector after extending:\n");
    j = 1;
    lds_vector_for_each(v, i)
    {
        printf("%ld. value of vector: %d\n", j++, *(int *)i);
    }

    /* Reversing a vector */
    lds_vector_reverse(v);

    /* Printing it after reversing */
    printf("Vector after reversing:\n");
    j = 1;
    lds_vector_for_each(v, i)
    {
        printf("%ld. value of vector: %d\n", j++, *(int *)i);
    }

    /* Accessing vector capacity */
    printf("Vector capacity: %ld\n", lds_vector_capacity(v));

    /* Cleaning up */
    lds_vector_free(v);
    lds_vector_free(v2);

    /* Initializing a trie */

    lds_trie *trie_obj = lds_trie_create();

    /* Checking is trie empty whether not */
    printf("Is trie empty: %d\n", lds_trie_is_empty(trie_obj));

    /* Inserting some words */

    lds_trie_insert(trie_obj, "ace");
    lds_trie_insert(trie_obj, "ant");
    lds_trie_insert(trie_obj, "cat");
    lds_trie_insert(trie_obj, "pet");
    lds_trie_insert(trie_obj, "pen");

    /* Checking is trie empty whether not */
    printf("Is trie empty: %d\n", lds_trie_is_empty(trie_obj));

    /* Searching words in trie */

    printf("Is 'ace' in trie: %s\n",
           lds_trie_search(trie_obj, "ace") ? "Yes" : "No");
    printf("Is 'ant' in trie: %s\n",
           lds_trie_search(trie_obj, "ant") ? "Yes" : "No");
    printf("Is 'cat' in trie: %s\n",
           lds_trie_search(trie_obj, "cat") ? "Yes" : "No");
    printf("Is 'pet' in trie: %s\n",
           lds_trie_search(trie_obj, "pet") ? "Yes" : "No");
    printf("Is 'pen' in trie: %s\n",
           lds_trie_search(trie_obj, "pen") ? "Yes" : "No");
    printf("Is 'hello' in trie: %s\n",
           lds_trie_search(trie_obj, "hello") ? "Yes" : "No");
    printf("Is 'hi' in trie: %s\n",
           lds_trie_search(trie_obj, "hi") ? "Yes" : "No");
    printf("Is 'dog' in trie: %s\n",
           lds_trie_search(trie_obj, "dog") ? "Yes" : "No");

    /* Cleaning up */
    lds_trie_free(trie_obj);

    /* Creating a tree */
    lds_tree *t = lds_create_tree();
    lds_tree *n1;
    lds_tree *n2;

    int tree_val1 = 1;
    int tree_val2 = 2;
    int tree_val3 = 3;
    int tree_val4 = 4;
    int tree_val5 = 5;
    int tree_val6 = 6;
    int tree_val7 = 7;
    int tree_val8 = 8;

    /* Checking is tree empty whether not */
    printf("Is tree empty: %d\n", lds_tree_is_empty(t));

    /* Setting a value for root */
    lds_tree_set(t, &tree_val1, sizeof(int));

    /* Creating children nodes */
    n1 = lds_tree_add(t, &tree_val2, sizeof(int));
    n2 = lds_tree_add(t, &tree_val3, sizeof(int));
    lds_tree_add(n1, &tree_val4, sizeof(int));
    lds_tree_add(n1, &tree_val5, sizeof(int));
    lds_tree_add(n2, &tree_val6, sizeof(int));
    lds_tree_add(n2, &tree_val7, sizeof(int));

    /* Checking is tree empty whether not */
    printf("Is tree empty: %d\n", lds_tree_is_empty(t));

    /* Changing a node's value, as we did in root */
    lds_tree_set(n1, &tree_val8, sizeof(int));

    /* Accessing values */
    printf("Node value: %d\n", *(int *)lds_tree_get(n1));
    printf("Node value size: %ld\n", lds_tree_data_size(n1));
    printf("Node child count: %d\n", lds_tree_child_count(n1));

    /* Getting the nth child */
    lds_tree *n3 = lds_tree_child(t, 0);
    printf("Value of tree's first child: %d\n", *(int *)lds_tree_get(n3));

    /* Getting the parent */
    lds_tree *n4 = lds_tree_parent(n3);
    printf("Value of the previous node's parent: %d\n",
           *(int *)lds_tree_get(n4));

    /* Looping through the tree */
    lds_tree_bfs(t, print_tree_bfs);
    printf("\n");

    /* Cleaning up */
    lds_tree_free(t);

    /* Creating a graph */
    lds_graph *g = lds_create_graph();
    lds_graph *g_n1;
    lds_graph *g_n2;
    lds_graph *g_n3;

    /* Putting some new values */
    int graph_val1 = 1;
    int graph_val2 = 2;
    int graph_val3 = 3;
    int graph_val4 = 4;
    int graph_val5 = 5;
    int graph_val6 = 6;
    int graph_val7 = 7;
    int graph_val8 = 8;

    g_n1 = lds_graph_add(g, &graph_val2, sizeof(int));
    g_n2 = lds_graph_add(g, &graph_val3, sizeof(int));
    lds_graph_add(g_n1, &graph_val4, sizeof(int));
    lds_graph_add_weighted(g_n1, &graph_val5, sizeof(int), 5);
    lds_graph_add(g_n2, &graph_val6, sizeof(int));
    lds_graph_add_weighted(g_n2, &graph_val7, sizeof(int), 7);

    /* Changing node data */
    lds_graph_set(g, &graph_val1, sizeof(int));
    lds_graph_set(g_n1, &graph_val8, sizeof(int));

    /* Changing weight of edge */
    lds_graph_set_weight(g_n1, 0, 3);

    /* Getting nth child */
    g_n3 = lds_graph_child(g_n1, 1);

    /* Accessing values */
    printf("Value of root's first node's second child: %d\n",
           *(int *)lds_graph_get(g_n3));

    /* Accessing edge weights */
    printf("Weight of edge between graph's root's first child and its second "
           "child: %d\n",
           lds_graph_get_weight(g_n1, 1));

    /* Accessing node data size */
    printf("Size of root's first child's data size: %ld\n",
           lds_graph_data_size(g_n1));

    /* Getting child count */
    printf("Child count of root: %d\n", lds_graph_child_count(g));

    /* Linking root and root's grand child */
    lds_graph_link(g, lds_graph_child(g_n1, 1));

    /* Linking root and root's another grand child with weight */
    lds_graph_link_weighted(g, lds_graph_child(g_n2, 0), 314);

    /* Cleaning up */
    lds_graph_free(g);

    /* Creating a string */
    lds_string *str = lds_create_string();

    /* Pushing some values to string */
    lds_string_append(str, "Hello, ");
    lds_string_append(str, "world!");

    /* Getting value */
    printf("Value of string: %s\n", lds_string_cstr(str));

    /* Getting the length */
    printf("Length of the string: %ld\n", lds_string_len(str));

    /* Creating another string from a char* string */
    lds_string *str2 = lds_string_from("C is awesome!");

    /* Pushing values to front of string */
    lds_string_push_front(str2, "Simon says: ");
    printf("Value of string after pushing back: %s\n", lds_string_cstr(str2));

    /* Appending values with specific length */
    lds_string_append_len(
        str,
        " What a nice day! -SomeRandomDataThatIsNotSupposedToBeInTheString-",
        17);
    printf("Value of first string: %s\n", lds_string_cstr(str));

    /* Copying a string to lds_string */
    printf("Value of str2 before copying: %s\n", lds_string_cstr(str2));
    lds_string_copy(str2, "A string");
    printf("Value of str2 after copying: %s\n", lds_string_cstr(str2));

    /* Copying a string to lds_string with specified length */

    printf("Value of str before copying: %s\n", lds_string_cstr(str));
    lds_string_copy_len(str, "3.14 - This part shouldn't be in the string -",
                        4);
    printf("Value of str after copying: %s\n", lds_string_cstr(str));

    /* Transfering ownership between strings */
    lds_string_move(str, str2);

    /* Reserving some space for performance */
    lds_string_reserve(str, 1000);

    /* Checking capacity of string */
    printf("Capacity of string: %ld\n", lds_string_capacity(str));

    /* Inserting data */
    lds_string_insert(str, 1, "n amazing");

    /* Inserting data with specific length */
    lds_string_insert_len(str, 10, " and powerful -randomdata-", 13);

    printf("Value of string after insertions: %s\n", lds_string_cstr(str));

    /* Erasing some data */
    lds_string_erase(str, 1, 22);

    printf("Value of string after deletions: %s\n", lds_string_cstr(str));

    /* Compaing lds_strings */
    lds_string *str3 = lds_string_from("A string");
    lds_string *str4 = lds_string_from("A different string");

    printf("Is the string same with string \"A string\": %s\n",
           lds_string_compare(str, str3) ? "Yes" : "No");
    printf("Is the string same with string \"A different string\": %s\n",
           lds_string_compare(str, str4) ? "Yes" : "No");

    /* Using find function */
    printf("From which index does the 'str' substring start: %ld\n",
           lds_string_find(str, "str"));
    printf("From which index does the 'ing' substring start: %ld\n",
           lds_string_find(str, "ing"));
    printf("From which index does the 'hi' substring start: %ld\n",
           lds_string_find(str, "hi"));

    /* Checking strings containing sub-strings */
    printf("Does the string contain substring 'str': %s\n",
           lds_string_contains(str, "str") ? "Yes" : "No");
    printf("Does the string contain substring 'ing': %s\n",
           lds_string_contains(str, "ing") ? "Yes" : "No");
    printf("Does the string contain substring 'cat': %s\n",
           lds_string_contains(str, "cat") ? "Yes" : "No");
    printf("Does the string contain substring 'dog': %s\n",
           lds_string_contains(str, "dog") ? "Yes" : "No");

    /* Toggling the case of string */
    printf("String before toggling casing: <%s>\n", lds_string_cstr(str));
    lds_string_toggle_case(str);
    printf("String after toggling casing: <%s>\n", lds_string_cstr(str));

    /* Lower casing the string variable */
    printf("String before lower casing: <%s>\n", lds_string_cstr(str));
    lds_string_lower(str);
    printf("String after lower casing: <%s>\n", lds_string_cstr(str));

    /* Upper casing the string variable */
    printf("String before upper casing: <%s>\n", lds_string_cstr(str));
    lds_string_upper(str);
    printf("String after upper casing: <%s>\n", lds_string_cstr(str));

    /* Replacing a substring */
    printf("String before replacing: <%s>\n", lds_string_cstr(str));
    lds_string_replace(str, 2, "structure");
    printf("String after replacing: <%s>\n", lds_string_cstr(str));

    /* Splitting strings */
    lds_vector *splitted = lds_string_split(str, " ");
    lds_string **spart;
    j = 0;

    lds_vector_for_each(splitted, spart)
    {
        printf("%ld. part: %s\n", ++j, lds_string_cstr(*spart));
    }

    /* Reversing strings */
    printf("String before reversing: <%s>\n", lds_string_cstr(str));
    lds_string_reverse(str);
    printf("String after reversing: <%s>\n", lds_string_cstr(str));

    /* Cleaning the string */
    printf("String before cleaning: <%s>\n", lds_string_cstr(str));
    lds_string_clear(str);
    printf("String after cleaning: <%s>\n", lds_string_cstr(str));

    /* Cleaning up */
    lds_string_free(str);
    lds_string_free(str2); /* You should still clean up str2, even its ownership
                              is transfered */
    lds_string_free(str3);
    lds_string_free(str4);
    lds_string_split_free(splitted); /* You should also clean up the vector
                                  returned by lds_string_split function */
}

void print_tree_bfs(lds_tree *t)
{
    /* Print function for lds_tree_dfs function */
    printf("%d ", *(int *)lds_tree_get(t));
}

void print_bintree_bfs(lds_bintree *b)
{
    /* Print function for lds_bintree_bfs function */
    printf("%d ", *(int *)lds_bintree_get(b));
}
