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
    obj->next->stored_in_heap = 0;
}

void linkedlist_add_int(linkedlist *ll, int value)
{
    int *x = malloc(sizeof(int));
    int i = 0;
    int length = 0;

    *x = value;
    linkedlist_add(ll, x);
    while (1)
    {
        if (ll->next == NULL || length == linkedlist_length(ll))
        {
            ll->stored_in_heap = 1;
            break;
        }
        else
        {
            ll = ll->next;
        }
        length++;
    }
}

void linkedlist_add_string(linkedlist *ll, char *value)
{
    char *x = malloc(strlen(value) + 1);
    int i = 0;
    int length = 0;

    x = memcpy(x, value, strlen(value));
    x[strlen(value)] = 0;

    linkedlist_add(ll, x);
    while (1)
    {
        if (ll->next == NULL || length == linkedlist_length(ll))
        {
            ll->stored_in_heap = 1;
            break;
        }
        else
        {
            ll = ll->next;
        }
        length++;
    }
}

void linkedlist_add_double(linkedlist *ll, double value)
{
    double *x = malloc(sizeof(double));
    int i = 0;
    int length = 0;

    *x = value;
    linkedlist_add(ll, x);
    while (1)
    {
        if (ll->next == NULL || length == linkedlist_length(ll))
        {
            ll->stored_in_heap = 1;
            break;
        }
        else
        {
            ll = ll->next;
        }
        length++;
    }
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
