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
    if (x->next != NULL)
        x->prev->next = x->next;

    if (x->prev != NULL)
        x->next->prev = x->prev;
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
    while (1)
    {
        tmp = ll;
        ll = ll->next;
        if (ll == NULL)
        {
            break;
        }
        if (tmp->data != NULL)
        {
            free(tmp->data);
        }
        free(tmp);
    }
}
