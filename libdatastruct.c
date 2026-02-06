/*
Pars SARICA <pars@parssarica.com>
*/

#include "libdatastruct.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

linkedlist *create_linkedlist(void)
{
    linkedlist *llist = malloc(sizeof(linkedlist));
    llist->data = NULL;
    llist->prev = NULL;
    llist->next = NULL;
    return llist;
}

void linkedlist_add(linkedlist *ll, void *data, size_t datatype_size)
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
    obj->next->data = malloc(datatype_size);
    obj->next->prev = obj;
    obj->next->next = NULL;

    memcpy(obj->next->data, data, datatype_size);
}

int linkedlist_length(linkedlist *ll)
{
    int length = 0;
    linkedlist *x = ll;

    while (1)
    {
        if (x->next == NULL)
        {
            break;
        }
        else
        {
            x = x->next;
        }
        length++;
    }

    return length;
}

void *linkedlist_get(linkedlist *ll, int index)
{
    int length = 0;
    linkedlist *x = ll;

    index++;

    while (1)
    {
        if (x->next == NULL || length == index)
        {
            break;
        }
        else
        {
            x = x->next;
        }
        length++;
    }

    return x->data;
}

void linkedlist_delete(linkedlist *ll, int index)
{
    int length = 0;
    linkedlist *x = ll;

    index++;

    while (1)
    {
        if (x->next == NULL || length == index)
        {
            break;
        }
        else
        {
            x = x->next;
        }
        length++;
    }

    free(x->data);
    if (x->next != NULL && x->prev != NULL)
    {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    free(x);
}

void linkedlist_update(linkedlist *ll, int index, void *newvar,
                       size_t datatype_size)
{
    int length = 0;
    linkedlist *x = ll;

    index++;

    while (1)
    {
        if (x->next == NULL || length == index)
        {
            break;
        }
        else
        {
            x = x->next;
        }
        length++;
    }

    free(x->data);
    x->data = malloc(datatype_size);

    memcpy(x->data, newvar, datatype_size);
}

void linkedlist_free(linkedlist *ll)
{
    linkedlist *tmp;
    int to_break = 0;

    while (1)
    {
        tmp = ll;
        if (tmp->data != NULL)
        {
            free(tmp->data);
        }
        if (ll->next == NULL)
        {
            to_break = 1;
        }
        else
        {
            ll = ll->next;
        }

        free(tmp);
        if (to_break)
        {
            break;
        }
    }
}

void linkedlist_insert(linkedlist *ll, void *data, size_t datatype_size,
                       int index)
{
    linkedlist *previous;
    int length = 0;

    index++;
    while (1)
    {
        if (ll->next == NULL || length == index)
        {
            break;
        }
        else
        {
            ll = ll->next;
        }
        length++;
    }
    previous = ll->prev;
    previous->next = malloc(sizeof(linkedlist));
    previous->next->data = malloc(datatype_size);
    previous->next->prev = previous;
    previous->next->next = ll;
    memcpy(previous->next->data, data, datatype_size);
}
