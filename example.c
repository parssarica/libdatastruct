#include "libdatastruct.h"
#include <stdio.h>

int main()
{
    linkedlist *l = create_linkedlist();

    /* Let's add some variables */
    int var1 = 1;
    int var2 = 2;
    int var3 = 3;
    linkedlist_add(l, &var1);
    linkedlist_add(l, &var2);
    linkedlist_add(l, &var3);
    linkedlist_add_int(l, 12);
    linkedlist_add_string(l, "Hi!");
    linkedlist_add_double(l, 3.14);

    // 	/* Let's list them with a loop! */
    // 	void* i;
    // 	int j;
    // 	for(j = 0; j < linkedlist_length(l); j++)
    // 	{
    // 		printf("%d. value of linked list: %d\n", j, linkedlist_get(l,
    // j));
    // 	}

    // 	/* Let's delete an element */
    // 	linkedlist_delete(l, 1);
    // 	printf("After deleting:\n");
    // 	for(j = 0; j < linkedlist_length(l); j++)
    // 	{
    // 		printf("%d. value of linked list: %d\n", j, linkedlist_get(l,
    // j));
    // 	}

    // 	/* Let's update an element */
    // 	char* newvar = "A new value.";
    // 	linkedlist_update(l, 1, &newvar);

    // 	/* Getting the length */

    // 	printf("This is the final length of the list: %d\n",
    // linkedlist_length(l));

    // 	linkedlist_free(l);
}
