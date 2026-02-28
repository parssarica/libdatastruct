#include "libdatastruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tree_bfs(tree *);
void print_bintree_bfs(bintree *);

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

    /* Checking is stack empty */
    printf("Is stack empty: %d\n", stack_empty(s));

    /* Pushing values to stack */

    int stack_val1 = 1;
    int stack_val2 = 2;
    int stack_val3 = 3;
    int stack_val4 = 4;

    stack_push(s, &stack_val1, sizeof(int));
    stack_push(s, &stack_val2, sizeof(int));
    stack_push(s, &stack_val3, sizeof(int));
    stack_push(s, &stack_val4, sizeof(int));

    /* Checking is stack empty */
    printf("Is stack empty: %d\n", stack_empty(s));

    /* Popping some values from stack */
    int popped_val1;
    int popped_val2;
    int popped_val3;
    int popped_val4;

    stack_pop(s, &popped_val1);
    stack_pop(s, &popped_val2);
    stack_pop(s, &popped_val3);
    stack_pop(s, &popped_val4);
    printf("Popped: %d\n", popped_val1);
    printf("Popped: %d\n", popped_val2);
    printf("Popped: %d\n", popped_val3);
    printf("Popped: %d\n", popped_val4);

    /* Peeking a value from stack */

    int popped_val5;
    stack_push(s, &stack_val1, sizeof(int));
    printf("Peeked: %d\n", *(int *)stack_peek(s));

    stack_pop(s, &popped_val5);
    printf("Popped: %d\n", popped_val5);

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

    int dequeued_val1;
    int dequeued_val2;
    int dequeued_val3;
    int dequeued_val4;
    int dequeued_val5;

    dequeue(q, &dequeued_val1);
    dequeue(q, &dequeued_val2);
    dequeue(q, &dequeued_val3);
    dequeue(q, &dequeued_val4);

    /* Checking is queue empty */
    printf("Is queue empty: %s\n", queue_is_empty(q) ? "Yes" : "No");

    printf("Value dequeued: %d\n", dequeued_val1);
    printf("Value dequeued: %d\n", dequeued_val2);
    printf("Value dequeued: %d\n", dequeued_val3);
    printf("Value dequeued: %d\n", dequeued_val4);
    printf("Value to be dequeued: %d\n", *(int *)queue_front(q));
    dequeue(q, &dequeued_val5);

    /* Dequeue returns an error code, so you can detect failures */
    if (!dequeue(q, &dequeued_val5))
    {
        printf("Dequeue failed (expected)\n");
    }

    printf("Value dequeued: %d\n", dequeued_val5);

    /* Checking is queue empty */
    printf("Is queue empty: %s\n", queue_is_empty(q) ? "Yes" : "No");

    /* Minimizing queue */
    queue_minimize(q);

    /* Freeing our queue */
    queue_free(q);

    /* Creating a binary tree */

    bintree *b = create_bintree();

    /* Setting values */
    int bintree_val1 = 1;
    int bintree_val2 = 2;
    int bintree_val3 = 3;
    int bintree_val4 = 4;
    int bintree_val5 = 5;
    int bintree_val6 = 6;
    int bintree_val7 = 7;

    /* Putting values */
    bintree_insert_left(b, &bintree_val2, sizeof(int));
    bintree_insert_right(b, &bintree_val3, sizeof(int));
    bintree_insert_left(bintree_left(b), &bintree_val4, sizeof(int));
    bintree_insert_right(bintree_left(b), &bintree_val5, sizeof(int));
    bintree_insert_left(bintree_right(b), &bintree_val6, sizeof(int));
    bintree_insert_right(bintree_right(b), &bintree_val7, sizeof(int));

    /* Changing values */
    bintree_set(b, &bintree_val1, sizeof(int));

    /* Accessing values */

    printf("Value of tree's left node: %d\n",
           *(int *)bintree_get(bintree_left(b)));
    printf("Value of tree's left node's right node: %d\n",
           *(int *)bintree_get(bintree_right(bintree_left(b))));
    printf("Value of tree's right node's left node: %d\n",
           *(int *)bintree_get(bintree_left(bintree_right(b))));

    /* Checking nodes have left children */

    printf("Does tree have a left child: %s\n",
           bintree_has_left(b) ? "Yes" : "No");
    printf("Does tree's left child have a left child: %s\n",
           bintree_has_left(bintree_left(b)) ? "Yes" : "No");
    printf("Does tree's right child have a left child: %s\n",
           bintree_has_left(bintree_right(b)) ? "Yes" : "No");
    printf("Does tree's right child's left child have a left child: %s\n",
           bintree_has_left(bintree_left(bintree_right(b))) ? "Yes" : "No");
    printf("Does tree's left child's left child have a left child: %s\n",
           bintree_has_left(bintree_left(bintree_left(b))) ? "Yes" : "No");

    /* Checking nodes have right children */

    printf("Does tree have a right child: %s\n",
           bintree_has_right(b) ? "Yes" : "No");
    printf("Does tree's left child have a right child: %s\n",
           bintree_has_right(bintree_left(b)) ? "Yes" : "No");
    printf("Does tree's right child have a right child: %s\n",
           bintree_has_right(bintree_right(b)) ? "Yes" : "No");
    printf("Does tree's right child's left child have a right child: %s\n",
           bintree_has_right(bintree_left(bintree_right(b))) ? "Yes" : "No");
    printf("Does tree's left child's left child have a right child: %s\n",
           bintree_has_right(bintree_left(bintree_left(b))) ? "Yes" : "No");

    /* Getting size of nodes */
    printf("Size of root node: %ld\n", bintree_size(b));

    /* Deleting the left child */
    bintree_remove_left(b);
    bintree_insert_left(
        b, &bintree_val1,
        sizeof(int)); // Putting a dummy value so destroy function doesn't fail

    /* Deleting the right child */
    bintree_remove_right(b);
    bintree_insert_right(
        b, &bintree_val1,
        sizeof(int)); // Putting a dummy value so destroy function doesn't fail

    /* Looping through binary tree using BFS algorithm */
    bintree_bfs(b, print_bintree_bfs);
    printf("\n");

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
    vector_minimize(v);

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

    printf("Vector length: %ld\n", vector_length(v));

    /* Accessing by index */
    printf("Vector's third item: %d\n", *(int *)vector_get(v, 2));

    /* Cleaning up */
    vector_free(v);

    /* Initializing a trie */

    trie *trie_obj = trie_create();

    /* Inserting some words */

    trie_insert(trie_obj, "ace");
    trie_insert(trie_obj, "ant");
    trie_insert(trie_obj, "cat");
    trie_insert(trie_obj, "pet");
    trie_insert(trie_obj, "pen");

    /* Searching words in trie */

    printf("Is 'ace' in trie: %s\n",
           trie_search(trie_obj, "ace") ? "Yes" : "No");
    printf("Is 'ant' in trie: %s\n",
           trie_search(trie_obj, "ant") ? "Yes" : "No");
    printf("Is 'cat' in trie: %s\n",
           trie_search(trie_obj, "cat") ? "Yes" : "No");
    printf("Is 'pet' in trie: %s\n",
           trie_search(trie_obj, "pet") ? "Yes" : "No");
    printf("Is 'pen' in trie: %s\n",
           trie_search(trie_obj, "pen") ? "Yes" : "No");
    printf("Is 'hello' in trie: %s\n",
           trie_search(trie_obj, "hello") ? "Yes" : "No");
    printf("Is 'hi' in trie: %s\n", trie_search(trie_obj, "hi") ? "Yes" : "No");
    printf("Is 'dog' in trie: %s\n",
           trie_search(trie_obj, "dog") ? "Yes" : "No");

    /* Cleaning up */
    trie_free(trie_obj);

    /* Creating a tree */
    tree *t = create_tree();
    tree *n1;
    tree *n2;

    int tree_val1 = 1;
    int tree_val2 = 2;
    int tree_val3 = 3;
    int tree_val4 = 4;
    int tree_val5 = 5;
    int tree_val6 = 6;
    int tree_val7 = 7;
    int tree_val8 = 8;

    /* Setting a value for root */
    tree_set(t, &tree_val1, sizeof(int));

    /* Creating children nodes */
    n1 = tree_add(t, &tree_val2, sizeof(int));
    n2 = tree_add(t, &tree_val3, sizeof(int));
    tree_add(n1, &tree_val4, sizeof(int));
    tree_add(n1, &tree_val5, sizeof(int));
    tree_add(n2, &tree_val6, sizeof(int));
    tree_add(n2, &tree_val7, sizeof(int));

    /* Changing a node's value, as we did in root */
    tree_set(n1, &tree_val8, sizeof(int));

    /* Accessing values */
    printf("Node value: %d\n", *(int *)tree_get(n1));
    printf("Node value size: %ld\n", tree_size(n1));
    printf("Node child count: %d\n", tree_child_count(n1));

    /* Getting the nth child */
    tree *n3 = tree_child(t, 0);
    printf("Value of tree's first child: %d\n", *(int *)tree_get(n3));

    /* Getting the parent */
    tree *n4 = tree_parent(n3);
    printf("Value of the previous node's parent: %d\n", *(int *)tree_get(n4));

    /* Looping through the tree */
    tree_bfs(t, print_tree_bfs);
    printf("\n");

    /* Cleaning up */
    tree_destroy(t);

    /* Creating a graph */
    graph *g = create_graph();
    graph *g_n1;
    graph *g_n2;
    graph *g_n3;

    /* Putting some new values */
    int graph_val1 = 1;
    int graph_val2 = 2;
    int graph_val3 = 3;
    int graph_val4 = 4;
    int graph_val5 = 5;
    int graph_val6 = 6;
    int graph_val7 = 7;
    int graph_val8 = 8;

    g_n1 = graph_add(g, &graph_val2, sizeof(int));
    g_n2 = graph_add(g, &graph_val3, sizeof(int));
    graph_add(g_n1, &graph_val4, sizeof(int));
    graph_add_weighted(g_n1, &graph_val5, sizeof(int), 5);
    graph_add(g_n2, &graph_val6, sizeof(int));
    graph_add_weighted(g_n2, &graph_val7, sizeof(int), 7);

    /* Changing node data */
    graph_set(g, &graph_val1, sizeof(int));
    graph_set(g_n1, &graph_val8, sizeof(int));

    /* Changing weight of edge */
    graph_set_weight(g_n1, 0, 3);

    /* Getting nth child */
    g_n3 = graph_child(g_n1, 1);

    /* Accessing values */
    printf("Value of root's first node's second child: %d\n",
           *(int *)graph_get(g_n3));

    /* Accessing edge weights */
    printf("Weight of edge between graph's root's first child and its second "
           "child: %d\n",
           graph_get_weight(g_n1, 1));

    /* Accessing node data size */
    printf("Size of root's first child's data size: %ld\n", graph_size(g_n1));

    /* Getting child count */
    printf("Child count of root: %d\n", graph_child_count(g));

    /* Linking root and root's grand child */
    graph_link(g, graph_child(g_n1, 1));

    /* Linking root and root's another grand child with weight */
    graph_link_weighted(g, graph_child(g_n2, 0), 314);

    /* Cleaning up */
    graph_destroy(g);

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

    /* Pushing values to back of string */
    lds_string_push_back(str2, "Simon says: ");
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

    /* Cleaning up */
    lds_string_free(str);
    lds_string_free(str2);
}

void print_tree_bfs(tree *t)
{
    /* Print function for tree_dfs function */
    printf("%d ", *(int *)tree_get(t));
}

void print_bintree_bfs(bintree *b)
{
    /* Print function for bintree_bfs function */
    printf("%d ", *(int *)bintree_get(b));
}
