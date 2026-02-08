/*
Pars SARICA <pars@parssarica.com>
*/

#include "libdatastruct.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void **to_free_list;
int to_free_list_length;

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

map *create_map(void)
{
    map *table = malloc(sizeof(map));
    table->node_count = 0;
    table->capacity = 0;
    table->items = NULL;

    return table;
}

void map_add(map *table, void *key, size_t keysize, void *value,
             size_t valuesize)
{
    int i = 0;
    int found = 0;
    for (i = 0; i < table->node_count; i++)
    {
        if (table->items[i].deleted)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        free(table->items[i].key);
        free(table->items[i].value);
        table->items[i].key = malloc(keysize);
        table->items[i].value = malloc(valuesize);
        table->items[i].keysize = keysize;
        table->items[i].valuesize = valuesize;
        table->items[i].deleted = 0;

        memcpy(table->items[i].key, key, keysize);
        memcpy(table->items[i].value, value, valuesize);
    }
    else
    {
        if (table->node_count == table->capacity)
        {
            if (table->capacity == 0)
            {
                table->capacity = 1;
            }
            else
            {
                table->capacity *= 2;
            }
            table->items =
                realloc(table->items, sizeof(mapitem) * table->capacity);
        }
        table->items[table->node_count].key = malloc(keysize);
        table->items[table->node_count].value = malloc(valuesize);
        table->items[table->node_count].keysize = keysize;
        table->items[table->node_count].valuesize = valuesize;
        table->items[table->node_count].deleted = 0;

        memcpy(table->items[table->node_count].key, key, keysize);
        memcpy(table->items[table->node_count].value, value, valuesize);

        table->node_count++;
    }
}

int map_length(map *table) { return table->node_count; }

static int map_get_index(map *table, void *key, size_t keysize)
{
    int i;

    for (i = 0; i < table->node_count; i++)
    {
        if ((!table->items[i].deleted) &&
            (keysize == table->items[i].keysize) &&
            (memcmp(key, table->items[i].key, keysize) == 0))
        {
            return i;
        }
    }

    return -1;
}

void *map_get(map *table, void *key, size_t keysize)
{
    int i = map_get_index(table, key, keysize);
    if (i != -1)
    {
        return table->items[i].value;
    }

    return NULL;
}

void map_delete(map *table, void *key, size_t keysize)
{
    int i = map_get_index(table, key, keysize);
    if (i == -1)
        return;

    table->items[i].deleted = 1;
}

void map_update_key(map *table, void *key_old, size_t old_keysize,
                    void *key_new, size_t new_keysize)
{
    int i = map_get_index(table, key_old, old_keysize);
    if (i == -1)
        return;

    free(table->items[i].key);
    table->items[i].key = malloc(new_keysize);
    memcpy(table->items[i].key, key_new, new_keysize);
}

void map_update_value(map *table, void *key, size_t keysize, void *newvalue,
                      size_t new_valuesize)
{
    int i = map_get_index(table, key, keysize);
    if (i == -1)
        return;

    free(table->items[i].value);
    table->items[i].value = malloc(new_valuesize);
    memcpy(table->items[i].value, newvalue, new_valuesize);
}

void map_free(map *table)
{
    int i = 0;
    for (i = 0; i < table->node_count; i++)
    {
        free(table->items[i].key);
        free(table->items[i].value);
    }
    free(table->items);
    free(table);
}

stack *create_stack(void)
{
    stack *s = malloc(sizeof(stack));

    s->node_count = 0;
    s->capacity = 0;
    s->items = NULL;

    return s;
}

void stack_push(stack *s, void *value, size_t valuesize)
{
    if (s->node_count == s->capacity)
    {
        if (s->capacity == 0)
        {
            s->capacity = 1;
        }
        else
        {
            s->capacity *= 2;
        }

        s->items = realloc(s->items, s->capacity * (sizeof(stackitem)));
    }

    s->items[s->node_count].item = malloc(valuesize);
    s->items[s->node_count].size = valuesize;
    memcpy(s->items[s->node_count].item, value, valuesize);

    s->node_count++;
}

void *stack_pop(stack *s)
{
    void *val;

    s->node_count--;
    val = malloc(s->items[s->node_count].size);
    memcpy(val, s->items[s->node_count].item, s->items[s->node_count].size);
    free(s->items[s->node_count].item);

    to_free_list =
        realloc(to_free_list, sizeof(void *) * ++to_free_list_length);
    to_free_list[to_free_list_length - 1] = val;
    return val;
}

void *stack_peek(stack *s) { return s->items[s->node_count - 1].item; }

void stack_free(stack *s)
{
    int i = 0;
    for (i = 0; i < s->node_count; i++)
    {
        free(s->items[i].item);
    }

    free(s->items);

    free(s);

    for (i = 0; i < to_free_list_length; i++)
    {
        free(to_free_list[i]);
    }
    free(to_free_list);
    to_free_list_length = 0;
}

queue *create_queue(void)
{
    queue *q = malloc(sizeof(queue));

    q->node_count = 0;
    q->capacity = 0;
    q->items = NULL;

    return q;
}

void enqueue(queue *q, void *data, size_t datasize)
{
    if (q->node_count == q->capacity)
    {
        if (q->capacity == 0)
        {
            q->capacity = 1;
        }
        else
        {
            q->capacity *= 2;
        }

        q->items = realloc(q->items, sizeof(queueitem) * q->capacity);
    }

    q->items[q->node_count].item = malloc(datasize);
    memcpy(q->items[q->node_count].item, data, datasize);

    q->node_count++;
}
