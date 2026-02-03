/*
Pars SARICA <pars@parssarica.com>
*/

#include "libdatastruct.h"
#include <stddef.h>
#include <stdlib.h>

linkedlist *create_linkedlist(void)
{
    linkedlist *llist = malloc(sizeof(linkedlist));
    llist->data = NULL;
    llist->prev = NULL;
    llist->next = NULL;
}

void linkedlist_add(linkedlist *ll, void *data)
{
    linkedlist *obj = ll;
    while (1)
    {
        if (obj->next != NULL)
        {
            obj = obj->next;
        }
        else
        {
            break;
        }
    }

    obj->next = malloc(sizeof(linkedlist));
    obj->next->data = data;
    obj->next->prev = obj;
    obj->next->next = NULL;
}
