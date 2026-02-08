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
}
