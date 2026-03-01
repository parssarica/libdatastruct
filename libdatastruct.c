/*
Pars SARICA <pars@parssarica.com>
*/

#include "libdatastruct.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

lds_linkedlist *lds_create_linkedlist(void)
{
    lds_linkedlist *llist = malloc(sizeof(lds_linkedlist));
    if (llist == NULL)
    {
        return NULL;
    }

    llist->data = NULL;
    llist->prev = NULL;
    llist->next = NULL;
    return llist;
}

int lds_linkedlist_add(lds_linkedlist *ll, const void *data,
                       size_t datatype_size)
{
    lds_linkedlist *obj = ll;
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

    obj->next = malloc(sizeof(lds_linkedlist));
    if (obj->next == NULL)
    {
        return 0;
    }

    obj->next->data = malloc(datatype_size);
    obj->next->prev = obj;
    obj->next->next = NULL;

    memcpy(obj->next->data, data, datatype_size);

    return 1;
}

int lds_linkedlist_length(lds_linkedlist *ll)
{
    int length = 0;
    lds_linkedlist *x = ll;

    if (ll == NULL)
    {
        return 0;
    }

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

const void *lds_linkedlist_get(lds_linkedlist *ll, int index)
{
    int length = 0;
    lds_linkedlist *x = ll;

    if (ll == NULL)
    {
        return NULL;
    }

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

int lds_linkedlist_delete(lds_linkedlist *ll, int index)
{
    int length = 0;
    lds_linkedlist *x = ll;

    if (ll == NULL)
    {
        return 0;
    }

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

    lds_safefree(x->data);
    if (x->next != NULL && x->prev != NULL)
    {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    lds_safefree(x);

    return 1;
}

int lds_linkedlist_update(lds_linkedlist *ll, int index, const void *newvar,
                          size_t datatype_size)
{
    int length = 0;
    lds_linkedlist *x = ll;

    index++;

    if (ll == NULL)
    {
        return 0;
    }

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

    lds_safefree(x->data);
    x->data = malloc(datatype_size);

    memcpy(x->data, newvar, datatype_size);

    return 1;
}

int lds_linkedlist_free(lds_linkedlist *ll)
{
    lds_linkedlist *tmp;
    int to_break = 0;

    if (ll == NULL)
    {
        return 0;
    }

    while (1)
    {
        tmp = ll;
        if (tmp->data != NULL)
        {
            lds_safefree(tmp->data);
        }
        if (ll->next == NULL)
        {
            to_break = 1;
        }
        else
        {
            ll = ll->next;
        }

        lds_safefree(tmp);
        if (to_break)
        {
            break;
        }
    }

    return 1;
}

int lds_linkedlist_insert(lds_linkedlist *ll, const void *data,
                          size_t datatype_size, int index)
{
    lds_linkedlist *previous;
    int length = 0;

    if (ll == NULL)
    {
        return 0;
    }

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
    previous->next = malloc(sizeof(lds_linkedlist));
    if (previous->next == NULL)
    {
        return 0;
    }

    previous->next->data = malloc(datatype_size);
    if (previous->next->data == NULL)
    {
        lds_safefree(previous->next);
        return 0;
    }

    previous->next->prev = previous;
    previous->next->next = ll;
    memcpy(previous->next->data, data, datatype_size);

    return 1;
}

lds_map *lds_create_map(void)
{
    lds_map *table = malloc(sizeof(lds_map));

    if (table == NULL)
    {
        return NULL;
    }

    table->node_count = 0;
    table->capacity = 0;
    table->items = NULL;

    return table;
}

int lds_map_add(lds_map *table, const void *key, size_t keysize,
                const void *value, size_t valuesize)
{
    if (table == NULL)
    {
        return 0;
    }

    size_t i = 0;
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
        lds_safefree(table->items[i].key);
        lds_safefree(table->items[i].value);
        table->items[i].key = malloc(keysize);
        table->items[i].value = malloc(valuesize);

        if (table->items[i].key == NULL || table->items[i].value == NULL)
        {
            return 0;
        }
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
                realloc(table->items, sizeof(lds_mapitem) * table->capacity);
            if (table->items == NULL)
            {
                return 0;
            }
        }
        table->items[table->node_count].key = malloc(keysize);
        table->items[table->node_count].value = malloc(valuesize);

        if (table->items[i].key == NULL || table->items[i].value == NULL)
        {
            return 0;
        }
        table->items[table->node_count].keysize = keysize;
        table->items[table->node_count].valuesize = valuesize;
        table->items[table->node_count].deleted = 0;

        memcpy(table->items[table->node_count].key, key, keysize);
        memcpy(table->items[table->node_count].value, value, valuesize);

        table->node_count++;
    }

    return 1;
}

int lds_map_length(const lds_map *table)
{
    if (table != NULL)
    {
        return table->node_count;
    }
    else
    {
        return 0;
    }
}

static int lds_map_get_index(lds_map *table, const void *key, size_t keysize)
{
    if (table->items == NULL)
        return -1;

    size_t i;

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

const void *lds_map_get(lds_map *table, const void *key, size_t keysize)
{
    if (table->items == NULL)
        return NULL;

    int i = lds_map_get_index(table, key, keysize);
    if (i != -1)
    {
        return table->items[i].value;
    }

    return NULL;
}

int lds_map_delete(lds_map *table, const void *key, size_t keysize)
{
    if (table->items == NULL)
        return 0;

    int i = lds_map_get_index(table, key, keysize);
    if (i == -1)
    {
        return 0;
    }

    table->items[i].deleted = 1;

    return 1;
}

int lds_map_update_key(lds_map *table, const void *key_old, size_t old_keysize,
                       const void *key_new, size_t new_keysize)
{
    if (table->items == NULL)
        return 0;

    int i = lds_map_get_index(table, key_old, old_keysize);
    if (i == -1)
    {
        return 0;
    }

    lds_safefree(table->items[i].key);
    table->items[i].key = malloc(new_keysize);
    if (table->items[i].key == NULL)
    {
        return 0;
    }

    memcpy(table->items[i].key, key_new, new_keysize);

    return 1;
}

int lds_map_update_value(lds_map *table, const void *key, size_t keysize,
                         const void *newvalue, size_t new_valuesize)
{
    if (table->items == NULL)
        return 0;

    int i = lds_map_get_index(table, key, keysize);
    if (i == -1)
    {
        return 0;
    }
    lds_safefree(table->items[i].value);
    table->items[i].value = malloc(new_valuesize);
    if (table->items[i].value == NULL)
    {
        return 0;
    }

    memcpy(table->items[i].value, newvalue, new_valuesize);

    return 1;
}

int lds_map_free(lds_map *table)
{
    size_t i = 0;

    if (table == NULL)
    {
        return 0;
    }

    if (table->items != NULL)
    {
        for (i = 0; i < table->node_count; i++)
        {
            lds_safefree(table->items[i].key);
            lds_safefree(table->items[i].value);
        }
        lds_safefree(table->items);
    }
    else
    {
        lds_safefree(table);
        return 0;
    }

    lds_safefree(table);
    return 1;
}

int lds_map_minimize(lds_map *table)
{
    if (table == NULL || table->items == NULL || table->node_count <= 0)
    {
        return 0;
    }

    table->items =
        realloc(table->items, sizeof(lds_mapitem) * table->node_count);
    if (table->items == NULL)
    {
        return 0;
    }
    table->capacity = table->node_count;

    return 1;
}

lds_stack *lds_create_stack(void)
{
    lds_stack *s = malloc(sizeof(lds_stack));

    if (s == NULL)
    {
        return NULL;
    }

    s->node_count = 0;
    s->capacity = 0;
    s->items = NULL;

    return s;
}

int lds_stack_push(lds_stack *s, const void *value, size_t valuesize)
{
    if (s == NULL)
    {
        return 0;
    }

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

        s->items = realloc(s->items, s->capacity * (sizeof(lds_stackitem)));
        if (s->items == NULL)
        {
            return 0;
        }
    }

    s->items[s->node_count].item = malloc(valuesize);
    if (s->items[s->node_count].item == NULL)
    {
        return 0;
    }

    s->items[s->node_count].size = valuesize;
    memcpy(s->items[s->node_count].item, value, valuesize);

    s->node_count++;

    return 1;
}

int lds_stack_pop(lds_stack *s, void *out)
{
    if (s->items == NULL || s->node_count < 1)
        return 0;

    s->node_count--;
    memcpy(out, s->items[s->node_count].item, s->items[s->node_count].size);
    lds_safefree(s->items[s->node_count].item);

    return 1;
}

const void *lds_stack_peek(const lds_stack *s)
{
    if (s == NULL || s->items == NULL || s->node_count <= 0)
    {
        return NULL;
    }

    return s->items[s->node_count - 1].item;
}

int lds_stack_free(lds_stack *s)
{
    if (s == NULL)
    {
        return 0;
    }

    size_t i = 0;
    if (s->items != NULL)
    {
        for (i = 0; i < s->node_count; i++)
        {
            lds_safefree(s->items[i].item);
        }

        lds_safefree(s->items);
    }
    else
    {
        lds_safefree(s);
    }

    lds_safefree(s);

    return 1;
}

int lds_stack_minimize(lds_stack *s)
{
    if (s->items == NULL || s->node_count <= 0)
    {
        return 0;
    }

    if (s->node_count == 0)
    {
        lds_safefree(s->items);
    }
    else
    {
        s->items = realloc(s->items, sizeof(lds_stackitem) * s->node_count);
        if (s->items == NULL)
        {
            return 0;
        }
    }
    s->capacity = s->node_count;

    return 1;
}

int lds_stack_empty(const lds_stack *s)
{
    if (s == NULL)
    {
        return 0;
    }

    return s->node_count == 0;
}

lds_queue *lds_create_queue(void)
{
    lds_queue *q = malloc(sizeof(lds_queue));

    if (q == NULL)
    {
        return NULL;
    }

    q->node_count = 0;
    q->capacity = 0;
    q->items = NULL;

    return q;
}

int lds_queue_enqueue(lds_queue *q, const void *data, size_t datasize)
{
    if (q == NULL)
    {
        return 0;
    }

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

        q->items = realloc(q->items, sizeof(lds_queueitem) * q->capacity);
        if (q->items == NULL)
        {
            return 0;
        }
    }

    q->items[q->node_count].item = malloc(datasize);
    if (q->items[q->node_count].item == NULL)
    {
        return 0;
    }

    q->items[q->node_count].size = datasize;
    memcpy(q->items[q->node_count].item, data, datasize);

    q->node_count++;

    return 1;
}

int lds_queue_dequeue(lds_queue *q, void *out)
{
    if (q->items == NULL || q->node_count <= 0)
        return 0;

    q->node_count--;
    memcpy(out, q->items[0].item, q->items[0].size);
    lds_safefree(q->items[0].item);

    if (q->node_count > 0)
    {
        memmove(&q->items[0], &q->items[1],
                sizeof(lds_queueitem) * q->node_count);
    }

    return 1;
}

int lds_queue_free(lds_queue *q)
{
    size_t i = 0;

    if (q == NULL)
    {
        return 0;
    }

    if (q->items != NULL)
    {
        for (i = 0; i < q->node_count; i++)
        {
            lds_safefree(q->items[i].item);
        }

        lds_safefree(q->items);
    }
    else
    {
        lds_safefree(q);
        return 0;
    }

    lds_safefree(q);

    return 1;
}

int lds_queue_minimize(lds_queue *q)
{
    if (q->items == NULL)
        return 0;

    if (q->node_count == 0)
    {
        lds_safefree(q->items);
        q->items = NULL;
    }
    else
    {
        q->items = realloc(q->items, sizeof(lds_queueitem) * q->node_count);
    }

    q->capacity = q->node_count;

    return 1;
}

int lds_queue_is_empty(const lds_queue *q)
{
    if (q == NULL)
    {
        return 0;
    }

    return q->node_count == 0;
}

const void *lds_queue_front(const lds_queue *q)
{
    if (q->items == NULL || q->node_count <= 0)
        return NULL;

    return q->items[q->node_count - 1].item;
}

lds_bintree *lds_create_bintree(void)
{
    lds_bintree *b = malloc(sizeof(lds_bintree));

    if (b == NULL)
    {
        return NULL;
    }

    b->data = NULL;
    b->size = 0;
    b->left = NULL;
    b->right = NULL;

    return b;
}

int lds_bintree_set_nodes(lds_bintree *b)
{
    b->left = malloc(sizeof(lds_bintree));
    b->right = malloc(sizeof(lds_bintree));

    if (b->left == NULL || b->right == NULL)
    {
        return 0;
    }

    b->left->data = NULL;
    b->left->size = 0;
    b->left->left = NULL;
    b->left->right = NULL;
    b->right->data = NULL;
    b->right->size = 0;
    b->right->left = NULL;
    b->right->right = NULL;

    return 1;
}

int lds_bintree_set(lds_bintree *b, const void *data, size_t datasize)
{
    b->data = malloc(datasize);
    b->size = datasize;

    if (b->data == NULL)
    {
        return 0;
    }

    memcpy(b->data, data, datasize);

    return 1;
}

void *lds_bintree_get(const lds_bintree *b)
{
    if (b == NULL)
    {
        return NULL;
    }

    return b->data;
}

lds_bintree *lds_bintree_left(const lds_bintree *b)
{
    if (b == NULL)
    {
        return NULL;
    }

    return b->left;
}

lds_bintree *lds_bintree_right(const lds_bintree *b)
{
    if (b == NULL)
    {
        return NULL;
    }

    return b->right;
}

lds_bintree *lds_bintree_insert_left(lds_bintree *b, const void *data,
                                     size_t datasize)
{
    if (b == NULL || b->left != NULL)
        return NULL;

    b->left = lds_create_bintree();
    if (b->left == NULL)
    {
        return NULL;
    }

    b->left->data = malloc(datasize);
    if (b->left->data == NULL)
    {
        return NULL;
    }

    b->left->size = datasize;

    memcpy(b->left->data, data, datasize);

    return b->left;
}

lds_bintree *lds_bintree_insert_right(lds_bintree *b, const void *data,
                                      size_t datasize)
{
    if (b == NULL || b->right != NULL)
        return NULL;

    b->right = lds_create_bintree();
    if (b->right == NULL)
    {
        return NULL;
    }

    b->right->data = malloc(datasize);
    if (b->right->data == NULL)
    {
        return NULL;
    }

    b->right->size = datasize;

    memcpy(b->right->data, data, datasize);

    return b->right;
}

int lds_bintree_has_left(const lds_bintree *b)
{
    if (b == NULL)
    {
        return 0;
    }

    return b->left != NULL;
}

int lds_bintree_has_right(const lds_bintree *b)
{
    if (b == NULL)
    {
        return 0;
    }

    return b->right != NULL;
}

size_t lds_bintree_size(const lds_bintree *b)
{
    if (b == NULL)
    {
        return 0;
    }

    return b->size;
}

int lds_bintree_bfs(lds_bintree *b, void (*visit)(lds_bintree *))
{
    lds_bintree **b_null_checker;
    lds_vector *to_visit = lds_create_vector();

    if (b == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!lds_vector_add(to_visit, &b, sizeof(lds_bintree **)))
    {
        lds_vector_free(to_visit);
        return 0;
    }

    while (lds_vector_length(to_visit) != 0)
    {
        if (b->left != NULL)
        {
            if (!lds_vector_add(to_visit, &b->left, sizeof(lds_bintree **)))
            {
                lds_vector_free(to_visit);
                return 0;
            }
        }

        if (b->right != NULL)
        {
            if (!lds_vector_add(to_visit, &b->right, sizeof(lds_bintree **)))
            {
                lds_vector_free(to_visit);
                return 0;
            }
        }
        visit(b);

        if (to_visit->node_count > 0)
        {
            if (!lds_vector_delete(to_visit, 0))
            {
                lds_vector_free(to_visit);
                return 0;
            }
        }

        if (to_visit->node_count > 0)
        {
            b_null_checker = (lds_bintree **)lds_vector_get(to_visit, 0);
        }
        else
        {
            b_null_checker = NULL;
        }

        if (b_null_checker != NULL)
        {
            b = *b_null_checker;
        }
        else
        {
            break;
        }
    }

    lds_vector_free(to_visit);

    return 1;
}

static void lds_bintree_node_destroy(lds_bintree *b)
{
    if (b == NULL)
        return;

    if (b->data != NULL)
    {
        lds_safefree(b->data);
    }

    lds_safefree(b);
}

int lds_bintree_destroy(lds_bintree *b)
{
    return lds_bintree_bfs(b, lds_bintree_node_destroy);
}

int lds_bintree_remove_left(lds_bintree *b)
{
    int i = lds_bintree_destroy(b->left);

    if (i != 1)
    {
        return 0;
    }

    b->left = NULL;

    return 1;
}

int lds_bintree_remove_right(lds_bintree *b)
{
    int i = lds_bintree_destroy(b->right);

    if (i != 1)
    {
        return 0;
    }

    b->right = NULL;

    return 1;
}

lds_vector *lds_create_vector(void)
{
    lds_vector *v = malloc(sizeof(lds_vector));

    if (v == NULL)
    {
        return NULL;
    }

    v->node_count = 0;
    v->capacity = 0;
    v->items = NULL;

    return v;
}

int lds_vector_add(lds_vector *v, const void *data, int datasize)
{
    size_t i;

    if (v == NULL)
    {
        return 0;
    }

    i = v->node_count;

    if (i >= v->capacity)
    {
        while (i >= v->capacity)
        {
            if (v->capacity == 0)
            {
                v->capacity = 1;
            }
            else
            {
                v->capacity *= 2;
            }
        }
        v->items = realloc(v->items, sizeof(lds_vectoritem) * v->capacity);
        if (v->items == NULL)
        {
            return 0;
        }
    }

    v->items[i].item = malloc(datasize);
    v->items[i].size = datasize;

    if (v->items[i].item == NULL)
    {
        return 0;
    }

    memcpy(v->items[i].item, data, datasize);

    v->node_count++;

    return 1;
}

int lds_vector_delete(lds_vector *v, size_t index)
{
    lds_vectoritem *items;
    size_t i;
    int skipped = 0;

    if (v == NULL || v->items == NULL)
    {
        return 0;
    }

    if (index >= v->node_count)
    {
        return 0;
    }

    items = malloc(sizeof(lds_vectoritem) * v->capacity);
    if (items == NULL)
    {
        return 0;
    }

    for (i = 0; i < v->node_count; i++)
    {
        if (i == index)
        {
            lds_safefree(v->items[i].item);
            skipped++;
        }

        if (i + skipped < v->node_count)
        {
            items[i].item = v->items[i + skipped].item;
            items[i].size = v->items[i + skipped].size;
        }
    }

    lds_safefree(v->items);

    v->items = items;
    v->node_count--;

    return 1;
}

int lds_vector_insert(lds_vector *v, size_t index, const void *data,
                      size_t datasize)
{
    lds_vectoritem *items;
    size_t i;
    int skipped = 0;

    if (v == NULL || v->items == NULL)
    {
        return 0;
    }

    while (v->node_count + 1 >= v->capacity)
    {
        if (v->capacity == 0)
        {
            v->capacity = 1;
        }
        else
        {
            v->capacity *= 2;
        }
    }
    items = malloc(sizeof(lds_vectoritem) * v->capacity);
    if (items == NULL)
    {
        return 0;
    }

    v->node_count++;

    for (i = 0; i < v->node_count; i++)
    {
        if (i == index)
        {
            items[i].item = malloc(datasize);
            items[i].size = datasize;
            memcpy(items[i].item, data, datasize);
            skipped++;
        }
        else
        {
            items[i].item = v->items[i - skipped].item;
            items[i].size = v->items[i - skipped].size;
        }
    }

    lds_safefree(v->items);

    v->items = items;

    return 1;
}

size_t lds_vector_length(const lds_vector *v)
{
    if (v == NULL)
    {
        return 0;
    }

    return v->node_count;
}

int lds_vector_free(lds_vector *v)
{
    size_t j;

    if (v == NULL)
    {
        return 0;
    }

    if (v->items != NULL)
    {
        for (j = 0; j < v->node_count; j++)
        {
            if (v->items[j].item != NULL)
            {
                lds_safefree(v->items[j].item);
            }
        }
        lds_safefree(v->items);
    }
    else
    {
        lds_safefree(v);
        return 0;
    }

    lds_safefree(v);

    return 1;
}

int lds_vector_minimize(lds_vector *v)
{
    if (v->items == NULL)
    {
        return 0;
    }

    if (v->node_count == 0)
    {
        lds_safefree(v->items);
    }
    else
    {
        v->items = realloc(v->items, sizeof(lds_vectoritem) * v->node_count);
        if (v->items == NULL)
        {
            return 0;
        }
    }

    v->capacity = v->node_count;

    return 1;
}

const void *lds_vector_get(const lds_vector *v, size_t index)
{
    if (v == NULL || v->items == NULL || index >= v->capacity)
        return NULL;

    return v->items[index].item;
}

lds_trie *lds_trie_create(void)
{
    lds_trie *t = malloc(sizeof(lds_trie));

    if (t == NULL)
    {
        return NULL;
    }

    t->character = 0;
    t->child_count = 0;
    t->children = NULL;

    return t;
}

static int lds_trie_find(const lds_trie *t, char character)
{
    int found = -1;
    size_t i;

    if (t == NULL || t->children == NULL)
    {
        return -1;
    }

    for (i = 0; i < t->child_count; i++)
    {
        if (t->children[i]->character == character)
        {
            found = i;
            break;
        }
    }

    return found;
}

int lds_trie_insert(lds_trie *t, const char *word)
{
    int i = 0;
    int j = 0;

    if (t == NULL)
    {
        return 0;
    }

    while (1)
    {
        i = lds_trie_find(t, word[j++]);
        if (i == -1)
            break;
        t = t->children[i];
    }

    j--;
    while (1)
    {
        t->children =
            realloc(t->children, sizeof(lds_trie *) * ++(t->child_count));
        if (t->children == NULL)
        {
            return 0;
        }

        t->children[t->child_count - 1] = lds_trie_create();
        if (t->children[t->child_count - 1] == NULL)
        {
            return 0;
        }

        t->children[t->child_count - 1]->character = word[j++];
        if (word[j] == '\0')
            break;
        t = t->children[t->child_count - 1];
    }

    return 1;
}

int lds_trie_search(const lds_trie *t, const char *word)
{
    int i = 0;
    size_t j = 0;

    if (t == NULL || t->children == NULL)
    {
        return 0;
    }

    while (1)
    {
        i = lds_trie_find(t, word[j++]);
        if (i == -1)
            break;
        t = t->children[i];
    }

    return strlen(word) == --j;
}

int lds_trie_free(lds_trie *t)
{
    lds_trie **t_null_checker;
    lds_vector *to_visit = lds_create_vector();
    size_t i;

    if (t == NULL || t->children == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!lds_vector_add(to_visit, &t, sizeof(lds_trie **)))
    {
        return 0;
    }

    while (lds_vector_length(to_visit) != 0)
    {
        for (i = 0; i < t->child_count; i++)
        {
            if (!lds_vector_add(to_visit, &t->children[i], sizeof(lds_trie **)))
            {
                return 0;
            }
        }

        if (t->children != NULL)
        {
            lds_safefree(t->children);
        }

        lds_safefree(t);

        if (to_visit->node_count > 0)
        {
            if (!lds_vector_delete(to_visit, 0))
            {
                return 0;
            }
        }

        if (to_visit->node_count > 0)
        {
            t_null_checker = (lds_trie **)lds_vector_get(to_visit, 0);
        }
        else
        {
            t_null_checker = NULL;
        }

        if (t_null_checker != NULL)
        {
            t = *t_null_checker;
        }
        else
        {
            break;
        }
    }

    lds_vector_free(to_visit);

    return 1;
}

lds_tree *lds_create_tree(void)
{
    lds_tree *t = malloc(sizeof(lds_tree));

    if (t == NULL)
    {
        return NULL;
    }

    t->data = NULL;
    t->children = NULL;
    t->parent = NULL;
    t->datasize = 0;
    t->child_count = 0;

    return t;
}

int lds_tree_set(lds_tree *t, const void *data, size_t datasize)
{
    if (t == NULL)
    {
        return 0;
    }

    if (t->data != NULL)
    {
        lds_safefree(t->data);
    }

    t->data = malloc(datasize);
    if (t->data == NULL)
    {
        return 0;
    }

    t->datasize = datasize;

    memcpy(t->data, data, datasize);

    return 1;
}

lds_tree *lds_tree_add(lds_tree *t, const void *data, size_t datasize)
{
    if (t == NULL)
    {
        return NULL;
    }

    t->child_count++;
    t->children = realloc(t->children, sizeof(lds_tree *) * t->child_count);
    if (t->children == NULL)
    {
        return NULL;
    }

    t->children[t->child_count - 1] = malloc(sizeof(lds_tree));
    if (t->children[t->child_count - 1] == NULL)
    {
        lds_safefree(t->children);
        return NULL;
    }

    t->children[t->child_count - 1]->data = malloc(datasize);
    if (t->children[t->child_count - 1]->data == NULL)
    {
        lds_safefree(t->children);
        lds_safefree(t->children[t->child_count - 1]);
        return NULL;
    }
    t->children[t->child_count - 1]->datasize = datasize;
    memcpy(t->children[t->child_count - 1]->data, data, datasize);

    t->children[t->child_count - 1]->child_count = 0;
    t->children[t->child_count - 1]->children = NULL;
    t->children[t->child_count - 1]->parent = t;

    return t->children[t->child_count - 1];
}

void *lds_tree_get(const lds_tree *t)
{
    if (t == NULL)
        return NULL;

    return t->data;
}

size_t lds_tree_size(const lds_tree *t)
{
    if (t == NULL)
        return 0;

    return t->datasize;
}

int lds_tree_child_count(const lds_tree *t)
{
    if (t == NULL)
        return 0;

    return t->child_count;
}

lds_tree *lds_tree_child(const lds_tree *t, size_t child)
{
    if (t == NULL || child >= t->child_count || t->children == NULL)
        return NULL;

    return t->children[child];
}

lds_tree *lds_tree_parent(const lds_tree *t)
{
    if (t == NULL)
        return NULL;

    return t->parent;
}

int lds_tree_bfs(lds_tree *t, void (*visit)(lds_tree *))
{
    lds_tree **t_null_checker;
    lds_vector *to_visit = lds_create_vector();
    size_t i;

    if (t == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!lds_vector_add(to_visit, &t, sizeof(lds_tree **)))
    {
        lds_vector_free(to_visit);
        return 0;
    }

    while (lds_vector_length(to_visit) != 0)
    {
        for (i = 0; i < t->child_count; i++)
        {
            if (!lds_vector_add(to_visit, &t->children[i], sizeof(lds_tree **)))
            {
                lds_vector_free(to_visit);
                return 0;
            }
        }

        visit(t);

        if (to_visit->node_count > 0)
        {
            if (!lds_vector_delete(to_visit, 0))
            {
                lds_vector_free(to_visit);
                return 0;
            }
        }

        if (to_visit->node_count > 0)
        {
            t_null_checker = (lds_tree **)lds_vector_get(to_visit, 0);
        }
        else
        {
            t_null_checker = NULL;
        }

        if (t_null_checker != NULL)
        {
            t = *t_null_checker;
        }
        else
        {
            break;
        }
    }

    lds_vector_free(to_visit);

    return 1;
}

static void lds_tree_node_destroy(lds_tree *t)
{
    if (t == NULL)
        return;

    if (t->data != NULL)
    {
        lds_safefree(t->data);
    }

    if (t->children != NULL)
    {
        lds_safefree(t->children);
    }

    lds_safefree(t);
}

int lds_tree_destroy(lds_tree *t)
{
    return lds_tree_bfs(t, lds_tree_node_destroy);
}

lds_graph *lds_create_graph(void)
{
    lds_graph *g = malloc(sizeof(lds_graph));

    if (g == NULL)
    {
        return NULL;
    }

    g->data = NULL;
    g->datasize = 0;
    g->child_count_from = 0;
    g->child_count_to = 0;
    g->edges_from = NULL;
    g->edges_to = NULL;

    return g;
}

lds_graph *lds_graph_add(lds_graph *g, const void *data, size_t datasize)
{
    g->child_count_from++;
    g->edges_from =
        realloc(g->edges_from, sizeof(lds_graphedge) * g->child_count_from);
    if (g->edges_from == NULL)
    {
        return NULL;
    }

    g->edges_from[g->child_count_from - 1] = malloc(sizeof(lds_graphedge));
    if (g->edges_from[g->child_count_from - 1] == NULL)
    {
        lds_safefree(g->edges_from);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->parent = g;
    g->edges_from[g->child_count_from - 1]->child = lds_create_graph();
    if (g->edges_from[g->child_count_from - 1]->child == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        return NULL;
    }

    g->edges_from[g->child_count_from - 1]->weight = 0;

    g->edges_from[g->child_count_from - 1]->child->data = malloc(datasize);
    if (g->edges_from[g->child_count_from - 1]->child->data == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child);
        return NULL;
    }

    g->edges_from[g->child_count_from - 1]->child->datasize = datasize;
    g->edges_from[g->child_count_from - 1]->child->child_count_from = 0;
    g->edges_from[g->child_count_from - 1]->child->child_count_to = 1;
    g->edges_from[g->child_count_from - 1]->child->edges_from = NULL;
    g->edges_from[g->child_count_from - 1]->child->edges_to =
        malloc(sizeof(lds_graphedge *));
    if (g->edges_from[g->child_count_from - 1]->child->edges_to == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child->data);
        return NULL;
    }

    g->edges_from[g->child_count_from - 1]->child->edges_to[0] =
        malloc(sizeof(lds_graphedge));

    if (g->edges_from[g->child_count_from - 1]->child->edges_to[0] == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child->data);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child->edges_to);
        return NULL;
    }

    memcpy(g->edges_from[g->child_count_from - 1]->child->data, data, datasize);
    memcpy(g->edges_from[g->child_count_from - 1]->child->edges_to[0],
           g->edges_from[g->child_count_from - 1], sizeof(lds_graphedge));
    return g->edges_from[g->child_count_from - 1]->child;
}

lds_graph *lds_graph_add_weighted(lds_graph *g, const void *data,
                                  size_t datasize, int weight)
{
    g->child_count_from++;
    g->edges_from =
        realloc(g->edges_from, sizeof(lds_graphedge) * g->child_count_from);
    if (g->edges_from == NULL)
    {
        return NULL;
    }
    g->edges_from[g->child_count_from - 1] = malloc(sizeof(lds_graphedge));
    if (g->edges_from[g->child_count_from - 1] == NULL)
    {
        lds_safefree(g->edges_from);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->parent = g;
    g->edges_from[g->child_count_from - 1]->child = lds_create_graph();
    if (g->edges_from[g->child_count_from - 1]->child == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->weight = weight;

    g->edges_from[g->child_count_from - 1]->child->data = malloc(datasize);
    if (g->edges_from[g->child_count_from - 1]->child->data == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->child->datasize = datasize;
    g->edges_from[g->child_count_from - 1]->child->child_count_from = 0;
    g->edges_from[g->child_count_from - 1]->child->child_count_to = 1;
    g->edges_from[g->child_count_from - 1]->child->edges_from = NULL;
    g->edges_from[g->child_count_from - 1]->child->edges_to =
        malloc(sizeof(lds_graphedge *));
    if (g->edges_from[g->child_count_from - 1]->child->edges_to == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child->data);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->child->edges_to[0] =
        malloc(sizeof(lds_graphedge));
    if (g->edges_from[g->child_count_from - 1]->child->edges_to[0] == NULL)
    {
        lds_safefree(g->edges_from);
        lds_safefree(g->edges_from[g->child_count_from - 1]);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child->data);
        lds_safefree(g->edges_from[g->child_count_from - 1]->child->edges_to);
        return NULL;
    }

    memcpy(g->edges_from[g->child_count_from - 1]->child->data, data, datasize);
    memcpy(g->edges_from[g->child_count_from - 1]->child->edges_to[0],
           g->edges_from[g->child_count_from - 1], sizeof(lds_graphedge));
    return g->edges_from[g->child_count_from - 1]->child;
}

int lds_graph_set(lds_graph *g, void *data, size_t datasize)
{
    if (g == NULL)
    {
        return 0;
    }

    if (g->data != NULL)
    {
        lds_safefree(g->data);
    }

    g->data = malloc(datasize);
    if (g->data == NULL)
    {
        return 0;
    }
    g->datasize = datasize;

    memcpy(g->data, data, datasize);

    return 1;
}

int lds_graph_set_weight(const lds_graph *g, size_t edge_num, int new_weight)
{
    if (g == NULL || g->edges_from == NULL || g->child_count_from <= edge_num ||
        g->edges_from[edge_num] == NULL)
    {
        return 0;
    }
    g->edges_from[edge_num]->weight = new_weight;

    return 1;
}

lds_graph *lds_graph_child(lds_graph *g, size_t child)
{
    if (g == NULL || child >= g->child_count_from || g->edges_from == NULL ||
        g->edges_from[child] == NULL)
    {
        return NULL;
    }

    return g->edges_from[child]->child;
}

const void *lds_graph_get(const lds_graph *g)
{
    if (g == NULL)
    {
        return NULL;
    }

    return g->data;
}

int lds_graph_get_weight(lds_graph *g, size_t edge_number)
{
    if (g == NULL || g->edges_from == NULL ||
        edge_number >= g->child_count_from ||
        g->edges_from[edge_number] == NULL)
    {
        return 0;
    }

    return g->edges_from[edge_number]->weight;
}

size_t lds_graph_size(const lds_graph *g)
{
    if (g == NULL)
    {
        return 0;
    }

    return g->datasize;
}

int lds_graph_child_count(const lds_graph *g)
{
    if (g == NULL)
    {
        return 0;
    }

    return g->child_count_from;
}

int lds_graph_link(lds_graph *g1, lds_graph *g2)
{
    if (g1 == NULL || g2 == NULL)
    {
        return 0;
    }

    g1->child_count_from++;
    g1->edges_from =
        realloc(g1->edges_from, sizeof(lds_graphedge *) * g1->child_count_from);
    if (g1->edges_from == NULL)
    {
        return 0;
    }
    g1->edges_from[g1->child_count_from - 1] = malloc(sizeof(lds_graphedge));
    if (g1->edges_from[g1->child_count_from - 1] == NULL)
    {
        lds_safefree(g1->edges_from);
        return 0;
    }
    g1->edges_from[g1->child_count_from - 1]->parent = g1;
    g1->edges_from[g1->child_count_from - 1]->child = g2;
    g1->edges_from[g1->child_count_from - 1]->weight = 0;
    g2->child_count_to++;
    g2->edges_to =
        realloc(g2->edges_to, sizeof(lds_graphedge *) * g2->child_count_to);
    if (g2->edges_to == NULL)
    {
        lds_safefree(g1->edges_from);
        lds_safefree(g2->edges_to);
        return 0;
    }
    g2->edges_to[g2->child_count_to - 1] = malloc(sizeof(lds_graphedge));
    if (g2->edges_to[g2->child_count_to - 1] == NULL)
    {
        lds_safefree(g1->edges_from);
        lds_safefree(g2->edges_to);
        lds_safefree(g2->edges_to);
        return 0;
    }
    g2->edges_to[g2->child_count_to - 1]->parent = g1;
    g2->edges_to[g2->child_count_to - 1]->child = g2;
    g2->edges_to[g2->child_count_to - 1]->weight = 0;

    return 1;
}

int lds_graph_link_weighted(lds_graph *g1, lds_graph *g2, int weight)
{
    if (g1 == NULL || g2 == NULL)
        return 0;

    lds_graph_link(g1, g2);

    g1->edges_from[g1->child_count_from - 1]->weight = weight;
    g2->edges_to[g2->child_count_to - 1]->weight = weight;

    return 1;
}

int lds_graph_destroy(lds_graph *g)
{
    lds_graph **g_null_checker;
    lds_vector *visited = lds_create_vector();
    lds_vector *to_visit = lds_create_vector();
    size_t i;

    if (g == NULL || visited == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!lds_vector_add(to_visit, &g, sizeof(lds_graph **)))
    {
        lds_vector_free(to_visit);
        lds_vector_free(visited);
        return 0;
    }

    while (lds_vector_length(to_visit) != 0)
    {
        for (i = 0; i < lds_vector_length(visited); i++)
        {
            if (*(lds_graph **)lds_vector_get(visited, i) == g)
            {
                if (!lds_vector_delete(to_visit, 0))
                {
                    lds_vector_free(to_visit);
                    lds_vector_free(visited);
                    return 0;
                }
                if (to_visit->node_count > 0)
                {
                    g = *(lds_graph **)lds_vector_get(to_visit, 0);
                    if (g == NULL)
                    {
                        lds_vector_free(to_visit);
                        lds_vector_free(visited);
                        return 0;
                    }
                }
                else
                {
                    break;
                }
                continue;
            }
        }

        for (i = 0; i < g->child_count_from; i++)
        {
            if (!lds_vector_add(to_visit, &g->edges_from[i]->child,
                                sizeof(lds_graph **)))
            {
                lds_vector_free(to_visit);
                lds_vector_free(visited);
                return 0;
            }
        }

        if (g->data)
        {
            lds_safefree(g->data);
        }

        if (g->edges_from)
        {
            for (i = 0; i < g->child_count_from; i++)
            {
                lds_safefree(g->edges_from[i]);
            }
            lds_safefree(g->edges_from);
        }

        if (g->edges_to)
        {
            for (i = 0; i < g->child_count_to; i++)
            {
                lds_safefree(g->edges_to[i]);
            }
            lds_safefree(g->edges_to);
        }

        if (!lds_vector_add(visited, &g, sizeof(lds_graph **)))
        {
            lds_vector_free(to_visit);
            lds_vector_free(visited);
            return 0;
        }

        if (to_visit->node_count > 0)
        {
            if (!lds_vector_delete(to_visit, 0))
            {
                lds_vector_free(to_visit);
                lds_vector_free(visited);
                return 0;
            }
        }

        lds_safefree(g);

        if (to_visit->node_count > 0)
        {
            g_null_checker = (lds_graph **)lds_vector_get(to_visit, 0);
        }
        else
        {
            g_null_checker = NULL;
        }

        if (g_null_checker != NULL)
        {
            g = *g_null_checker;
        }
        else
        {
            break;
        }
    }

    lds_vector_free(visited);
    lds_vector_free(to_visit);

    return 1;
}

lds_string *lds_create_string(void)
{
    lds_string *s = malloc(sizeof(lds_string));

    if (s == NULL)
    {
        return NULL;
    }

    s->data = NULL;
    s->len = 0;
    s->capacity = 0;

    return s;
}

int lds_string_append(lds_string *s, const char *newstr)
{
    if (s == NULL)
    {
        return 0;
    }

    return lds_string_append_len(s, newstr, strlen(newstr));
}

int lds_string_append_len(lds_string *s, const char *newstr, size_t len)
{
    if (s == NULL)
    {
        return 0;
    }

    if (s->len + len + 1 >= s->capacity)
    {
        while (s->len + len + 1 >= s->capacity)
        {
            if (s->capacity == 0)
            {
                s->capacity = 1;
            }
            else
            {
                s->capacity *= 2;
            }
        }

        s->data = realloc(s->data, s->capacity);
        if (s->data == NULL)
        {
            return 0;
        }
    }

    memcpy(s->data + s->len, newstr, len);

    s->len += len;

    s->data[s->len] = 0;

    return 1;
}

const char *lds_string_cstr(const lds_string *s) { return s->data; }

size_t lds_string_len(const lds_string *s) { return s->len; }

lds_string *lds_string_from(const char *new_str)
{
    lds_string *s = lds_create_string();

    if (s == NULL)
    {
        return NULL;
    }

    if (!lds_string_append(s, new_str))
    {
        return NULL;
    }

    return s;
}

int lds_string_push_front_len(lds_string *s, const char *newstr, size_t len)
{
    if (s == NULL)
    {
        return 0;
    }

    if (s->len + len + 1 >= s->capacity)
    {
        while (s->len + len + 1 >= s->capacity)
        {
            if (s->capacity == 0)
            {
                s->capacity = 1;
            }
            else
            {
                s->capacity *= 2;
            }
        }

        s->data = realloc(s->data, s->capacity);
        if (s->data == NULL)
        {
            return 0;
        }
    }

    memmove(s->data + len, s->data, s->len);
    memcpy(s->data, newstr, len);

    s->len += len;

    s->data[s->len] = 0;

    return 1;
}

int lds_string_push_front(lds_string *s, const char *newstr)
{
    if (s == NULL)
    {
        return 0;
    }

    return lds_string_push_front_len(s, newstr, strlen(newstr));
}

int lds_string_copy_len(lds_string *s, const char *newstr, size_t length)
{
    if (length + 1 >= s->capacity)
    {
        while (s->len + strlen(newstr) + 1 >= s->capacity)
        {
            if (s->capacity == 0)
            {
                s->capacity = 1;
            }
            else
            {
                s->capacity *= 2;
            }
        }

        s->data = realloc(s->data, s->capacity);
        if (s->data == NULL)
        {
            return 0;
        }
    }

    memcpy(s->data, newstr, length);

    s->len = length;
    s->data[length] = 0;

    return 1;
}

int lds_string_copy(lds_string *s, const char *newstr)
{
    if (s == NULL)
    {
        return 0;
    }

    return lds_string_copy_len(s, newstr, strlen(newstr));
}

int lds_string_free(lds_string *s)
{
    if (s == NULL)
    {
        return 0;
    }

    if (s->data != NULL)
    {
        lds_safefree(s->data);
    }

    lds_safefree(s);

    return 1;
}

int lds_string_move(lds_string *s1, lds_string *s2)
{
    if (s1 == NULL || s2 == NULL || s1 == s2)
    {
        return 0;
    }

    if (s1->data != NULL)
    {
        lds_safefree(s1->data);
    }

    s1->data = s2->data;
    s1->len = s2->len;
    s1->capacity = s2->capacity;

    s2->data = NULL;
    s2->len = 0;
    s2->capacity = 0;

    return 1;
}

int lds_string_reserve(lds_string *s1, size_t newcap)
{
    if (s1 == NULL || s1->capacity >= newcap)
    {
        return 0;
    }

    s1->capacity = newcap;
    s1->data = realloc(s1->data, newcap);

    return 1;
}

int lds_string_insert_len(lds_string *s, size_t pos, const char *newstr,
                          size_t newstrlen)
{
    if (s == NULL || pos > s->len || newstr == NULL)
    {
        return 0;
    }

    if (s->len + newstrlen + 1 >= s->capacity)
    {
        while (s->len + newstrlen + 1 >= s->capacity)
        {
            if (s->capacity == 0)
            {
                s->capacity = 1;
            }
            else
            {
                s->capacity *= 2;
            }
        }

        s->data = realloc(s->data, s->capacity);
        if (s->data == NULL)
        {
            return 0;
        }
    }

    memmove(s->data + pos + newstrlen, s->data + pos, newstrlen);
    memcpy(s->data + pos, newstr, newstrlen);

    s->len += newstrlen;

    return 1;
}

int lds_string_insert(lds_string *s, size_t pos, const char *newstr)
{
    if (s == NULL || pos > s->len || newstr == NULL)
    {
        return 0;
    }

    return lds_string_insert_len(s, pos, newstr, strlen(newstr));
}

int lds_string_erase(lds_string *s, size_t pos, size_t len)
{
    if (s == NULL || pos > s->len || pos + len > s->len)
    {
        return 0;
    }

    memmove(s->data + pos, s->data + pos + len, len);
    s->data[pos + len] = 0;
    s->len -= len;

    return 1;
}

int lds_string_compare(const lds_string *s1, const lds_string *s2)
{
    if (s1 == NULL || s2 == NULL || s1->data == NULL || s2->data == NULL ||
        s1->len != s2->len)
    {
        return 0;
    }

    if (memcmp(s1->data, s2->data, s1->len) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int lds_string_clear(lds_string *s)
{
    if (s == NULL || s->data == NULL)
    {
        return 0;
    }

    s->len = 0;
    s->data[0] = 0;

    return 1;
}

int lds_string_reverse(lds_string *s)
{
    int left;
    int right;
    char k;

    if (s == NULL || s->data == NULL)
    {
        return 0;
    }

    left = 0;
    right = s->len - 1;

    while (left < right)
    {
        k = s->data[left];
        s->data[left] = s->data[right];
        s->data[right] = k;

        left++;
        right--;
    }

    return 1;
}

ssize_t lds_string_find_len(const lds_string *s, const char *pattern,
                            size_t size_pattern)
{
    if (s == NULL || s->data == NULL)
    {
        return -1;
    }

    size_t n = s->len;
    size_t m = size_pattern;
    int matched = 0;
    size_t i;
    size_t j;

    for (i = 0; i < (n - m + 1); i++)
    {
        matched = 1;
        for (j = 0; j < m; j++)
        {
            if (s->data[i + j] != pattern[j])
            {
                matched = 0;
                break;
            }
        }

        if (matched)
        {
            return (ssize_t)i;
        }
    }

    return -1;
}

ssize_t lds_string_find(const lds_string *s, const char *pattern)
{
    if (s == NULL || s->data == NULL)
    {
        return -1;
    }

    return lds_string_find_len(s, pattern, strlen(pattern));
}

int lds_string_contains_len(const lds_string *s, const char *pattern,
                            size_t len)
{
    if (s == NULL || s->data == NULL)
    {
        return 0;
    }

    return lds_string_find_len(s, pattern, len) != -1;
}

int lds_string_contains(const lds_string *s, const char *pattern)
{
    if (s == NULL || s->data == NULL)
    {
        return 0;
    }

    return lds_string_contains_len(s, pattern, strlen(pattern));
}

int lds_string_lower(lds_string *s)
{
    size_t i;

    if (s == NULL || s->data == NULL)
    {
        return 0;
    }

    for (i = 0; i < s->len; i++)
    {
        if (s->data[i] >= 'A' && s->data[i] <= 'Z')
        {
            s->data[i] += 32;
        }
    }

    return 1;
}

int lds_string_upper(lds_string *s)
{
    size_t i;

    if (s == NULL || s->data == NULL)
    {
        return 0;
    }

    for (i = 0; i < s->len; i++)
    {
        if (s->data[i] >= 'a' && s->data[i] <= 'z')
        {
            s->data[i] -= 32;
        }
    }

    return 1;
}

int lds_string_toggle_case(lds_string *s)
{
    size_t i;

    if (s == NULL || s->data == NULL)
    {
        return 0;
    }

    for (i = 0; i < s->len; i++)
    {
        if (s->data[i] >= 'A' && s->data[i] <= 'Z')
        {
            s->data[i] += 32;
        }
        else if (s->data[i] >= 'a' && s->data[i] <= 'z')
        {
            s->data[i] -= 32;
        }
    }

    return 1;
}

int lds_string_replace_len(lds_string *s, size_t pos, const char *newstr,
                           size_t newstr_len)
{
    if (s == NULL || s->data == NULL || newstr == NULL)
    {
        return 0;
    }

    if (pos + newstr_len + 1 >= s->capacity)
    {
        while (pos + newstr_len + 1 >= s->capacity)
        {
            if (s->capacity == 0)
            {
                s->capacity = 1;
            }
            else
            {
                s->capacity *= 2;
            }
        }

        s->data = realloc(s->data, s->capacity);
        if (s->data == NULL)
        {
            return 0;
        }
    }

    memcpy(s->data + pos, newstr, newstr_len);
    s->data[pos + newstr_len] = 0;
    s->len = pos + newstr_len;

    return 1;
}

int lds_string_replace(lds_string *s, size_t pos, const char *newstr)
{
    if (s == NULL || s->data == NULL || newstr == NULL)
    {
        return 0;
    }

    return lds_string_replace_len(s, pos, newstr, strlen(newstr));
}
