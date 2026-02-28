/*
Pars SARICA <pars@parssarica.com>
*/

#include "libdatastruct.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

linkedlist *create_linkedlist(void)
{
    linkedlist *llist = malloc(sizeof(linkedlist));
    if (llist == NULL)
    {
        return NULL;
    }

    llist->data = NULL;
    llist->prev = NULL;
    llist->next = NULL;
    return llist;
}

int linkedlist_add(linkedlist *ll, void *data, size_t datatype_size)
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

int linkedlist_length(linkedlist *ll)
{
    int length = 0;
    linkedlist *x = ll;

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

void *linkedlist_get(linkedlist *ll, int index)
{
    int length = 0;
    linkedlist *x = ll;

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

int linkedlist_delete(linkedlist *ll, int index)
{
    int length = 0;
    linkedlist *x = ll;

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

    safefree(x->data);
    if (x->next != NULL && x->prev != NULL)
    {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    safefree(x);

    return 1;
}

int linkedlist_update(linkedlist *ll, int index, void *newvar,
                      size_t datatype_size)
{
    int length = 0;
    linkedlist *x = ll;

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

    safefree(x->data);
    x->data = malloc(datatype_size);

    memcpy(x->data, newvar, datatype_size);

    return 1;
}

int linkedlist_free(linkedlist *ll)
{
    linkedlist *tmp;
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
            safefree(tmp->data);
        }
        if (ll->next == NULL)
        {
            to_break = 1;
        }
        else
        {
            ll = ll->next;
        }

        safefree(tmp);
        if (to_break)
        {
            break;
        }
    }

    return 1;
}

int linkedlist_insert(linkedlist *ll, void *data, size_t datatype_size,
                      int index)
{
    linkedlist *previous;
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
    previous->next = malloc(sizeof(linkedlist));
    if (previous->next == NULL)
    {
        return 0;
    }

    previous->next->data = malloc(datatype_size);
    if (previous->next->data == NULL)
    {
        free(previous->next);
        return 0;
    }

    previous->next->prev = previous;
    previous->next->next = ll;
    memcpy(previous->next->data, data, datatype_size);

    return 1;
}

map *create_map(void)
{
    map *table = malloc(sizeof(map));

    if (table == NULL)
    {
        return NULL;
    }

    table->node_count = 0;
    table->capacity = 0;
    table->items = NULL;

    return table;
}

int map_add(map *table, void *key, size_t keysize, void *value,
            size_t valuesize)
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
        safefree(table->items[i].key);
        safefree(table->items[i].value);
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
                realloc(table->items, sizeof(mapitem) * table->capacity);
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

int map_length(map *table)
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

static int map_get_index(map *table, void *key, size_t keysize)
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

void *map_get(map *table, void *key, size_t keysize)
{
    if (table->items == NULL)
        return NULL;

    int i = map_get_index(table, key, keysize);
    if (i != -1)
    {
        return table->items[i].value;
    }

    return NULL;
}

int map_delete(map *table, void *key, size_t keysize)
{
    if (table->items == NULL)
        return 0;

    int i = map_get_index(table, key, keysize);
    if (i == -1)
    {
        return 0;
    }

    table->items[i].deleted = 1;

    return 1;
}

int map_update_key(map *table, void *key_old, size_t old_keysize, void *key_new,
                   size_t new_keysize)
{
    if (table->items == NULL)
        return 0;

    int i = map_get_index(table, key_old, old_keysize);
    if (i == -1)
    {
        return 0;
    }

    safefree(table->items[i].key);
    table->items[i].key = malloc(new_keysize);
    if (table->items[i].key == NULL)
    {
        return 0;
    }

    memcpy(table->items[i].key, key_new, new_keysize);

    return 1;
}

int map_update_value(map *table, void *key, size_t keysize, void *newvalue,
                     size_t new_valuesize)
{
    if (table->items == NULL)
        return 0;

    int i = map_get_index(table, key, keysize);
    if (i == -1)
    {
        return 0;
    }
    safefree(table->items[i].value);
    table->items[i].value = malloc(new_valuesize);
    if (table->items[i].value == NULL)
    {
        return 0;
    }

    memcpy(table->items[i].value, newvalue, new_valuesize);

    return 1;
}

int map_free(map *table)
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
            safefree(table->items[i].key);
            safefree(table->items[i].value);
        }
        safefree(table->items);
    }
    else
    {
        safefree(table);
        return 0;
    }

    safefree(table);
    return 1;
}

int map_minimize(map *table)
{
    if (table == NULL || table->items == NULL || table->node_count <= 0)
    {
        return 0;
    }

    table->items = realloc(table->items, sizeof(mapitem) * table->node_count);
    if (table->items == NULL)
    {
        return 0;
    }
    table->capacity = table->node_count;

    return 1;
}

stack *create_stack(void)
{
    stack *s = malloc(sizeof(stack));

    if (s == NULL)
    {
        return NULL;
    }

    s->node_count = 0;
    s->capacity = 0;
    s->items = NULL;

    return s;
}

int stack_push(stack *s, void *value, size_t valuesize)
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

        s->items = realloc(s->items, s->capacity * (sizeof(stackitem)));
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

int stack_pop(stack *s, void *out)
{
    if (s->items == NULL || s->node_count < 1)
        return 0;

    s->node_count--;
    memcpy(out, s->items[s->node_count].item, s->items[s->node_count].size);
    safefree(s->items[s->node_count].item);

    return 1;
}

void *stack_peek(stack *s)
{
    if (s == NULL || s->items == NULL || s->node_count <= 0)
    {
        return NULL;
    }

    return s->items[s->node_count - 1].item;
}

int stack_free(stack *s)
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
            safefree(s->items[i].item);
        }

        safefree(s->items);
    }
    else
    {
        safefree(s);
    }

    safefree(s);

    return 1;
}

int stack_minimize(stack *s)
{
    if (s->items == NULL || s->node_count <= 0)
    {
        return 0;
    }

    if (s->node_count == 0)
    {
        safefree(s->items);
    }
    else
    {
        s->items = realloc(s->items, sizeof(stackitem) * s->node_count);
        if (s->items == NULL)
        {
            return 0;
        }
    }
    s->capacity = s->node_count;

    return 1;
}

int stack_empty(stack *s)
{
    if (s == NULL)
    {
        return 0;
    }

    return s->node_count == 0;
}

queue *create_queue(void)
{
    queue *q = malloc(sizeof(queue));

    if (q == NULL)
    {
        return NULL;
    }

    q->node_count = 0;
    q->capacity = 0;
    q->items = NULL;

    return q;
}

int enqueue(queue *q, void *data, size_t datasize)
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

        q->items = realloc(q->items, sizeof(queueitem) * q->capacity);
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

int dequeue(queue *q, void *out)
{
    if (q->items == NULL || q->node_count <= 0)
        return 0;

    q->node_count--;
    memcpy(out, q->items[0].item, q->items[0].size);
    safefree(q->items[0].item);

    if (q->node_count > 0)
    {
        memmove(&q->items[0], &q->items[1], sizeof(queueitem) * q->node_count);
    }

    return 1;
}

int queue_free(queue *q)
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
            safefree(q->items[i].item);
        }

        safefree(q->items);
    }
    else
    {
        safefree(q);
        return 0;
    }

    safefree(q);

    return 1;
}

int queue_minimize(queue *q)
{
    if (q->items == NULL)
        return 0;

    if (q->node_count == 0)
    {
        safefree(q->items);
        q->items = NULL;
    }
    else
    {
        q->items = realloc(q->items, sizeof(stackitem) * q->node_count);
    }

    q->capacity = q->node_count;

    return 1;
}

int queue_is_empty(queue *q)
{
    if (q == NULL)
    {
        return 0;
    }

    return q->node_count == 0;
}

void *queue_front(queue *q)
{
    if (q->items == NULL || q->node_count <= 0)
        return NULL;

    return q->items[q->node_count - 1].item;
}

bintree *create_bintree(void)
{
    bintree *b = malloc(sizeof(bintree));

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

int bintree_set_nodes(bintree *b)
{
    b->left = malloc(sizeof(bintree));
    b->right = malloc(sizeof(bintree));

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

int bintree_set(bintree *b, void *data, size_t datasize)
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

void *bintree_get(bintree *b)
{
    if (b == NULL)
    {
        return NULL;
    }

    return b->data;
}

bintree *bintree_left(bintree *b)
{
    if (b == NULL)
    {
        return NULL;
    }

    return b->left;
}

bintree *bintree_right(bintree *b)
{
    if (b == NULL)
    {
        return NULL;
    }

    return b->right;
}

bintree *bintree_insert_left(bintree *b, void *data, size_t datasize)
{
    if (b == NULL || b->left != NULL)
        return NULL;

    b->left = create_bintree();
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

bintree *bintree_insert_right(bintree *b, void *data, size_t datasize)
{
    if (b == NULL || b->right != NULL)
        return NULL;

    b->right = create_bintree();
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

int bintree_has_left(bintree *b)
{
    if (b == NULL)
    {
        return 0;
    }

    return b->left != NULL;
}

int bintree_has_right(bintree *b)
{
    if (b == NULL)
    {
        return 0;
    }

    return b->right != NULL;
}

size_t bintree_size(bintree *b)
{
    if (b == NULL)
    {
        return 0;
    }

    return b->size;
}

int bintree_bfs(bintree *b, void (*visit)(bintree *))
{
    bintree **b_null_checker;
    vector *to_visit = create_vector();

    if (b == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!vector_add(to_visit, &b, sizeof(bintree **)))
    {
        vector_free(to_visit);
        return 0;
    }

    while (vector_length(to_visit) != 0)
    {
        if (b->left != NULL)
        {
            if (!vector_add(to_visit, &b->left, sizeof(bintree **)))
            {
                vector_free(to_visit);
                return 0;
            }
        }

        if (b->right != NULL)
        {
            if (!vector_add(to_visit, &b->right, sizeof(bintree **)))
            {
                vector_free(to_visit);
                return 0;
            }
        }
        visit(b);

        if (to_visit->node_count > 0)
        {
            if (!vector_delete(to_visit, 0))
            {
                vector_free(to_visit);
                return 0;
            }
        }

        if (to_visit->node_count > 0)
        {
            b_null_checker = (bintree **)vector_get(to_visit, 0);
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

    vector_free(to_visit);

    return 1;
}

static void bintree_node_destroy(bintree *b)
{
    if (b == NULL)
        return;

    if (b->data != NULL)
    {
        safefree(b->data);
    }

    safefree(b);
}

int bintree_destroy(bintree *b) { return bintree_bfs(b, bintree_node_destroy); }

int bintree_remove_left(bintree *b)
{
    int i = bintree_destroy(b->left);

    if (i != 1)
    {
        return 0;
    }

    b->left = NULL;

    return 1;
}

int bintree_remove_right(bintree *b)
{
    int i = bintree_destroy(b->right);

    if (i != 1)
    {
        return 0;
    }

    b->right = NULL;

    return 1;
}

vector *create_vector(void)
{
    vector *v = malloc(sizeof(vector));

    if (v == NULL)
    {
        return NULL;
    }

    v->node_count = 0;
    v->capacity = 0;
    v->items = NULL;

    return v;
}

int vector_add(vector *v, void *data, int datasize)
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
        v->items = realloc(v->items, sizeof(vectoritem) * v->capacity);
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

int vector_delete(vector *v, size_t index)
{
    vectoritem *items;
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

    items = malloc(sizeof(vectoritem) * v->capacity);
    if (items == NULL)
    {
        return 0;
    }

    for (i = 0; i < v->node_count; i++)
    {
        if (i == index)
        {
            safefree(v->items[i].item);
            skipped++;
        }

        if (i + skipped < v->node_count)
        {
            items[i].item = v->items[i + skipped].item;
            items[i].size = v->items[i + skipped].size;
        }
    }

    safefree(v->items);

    v->items = items;
    v->node_count--;

    return 1;
}

int vector_insert(vector *v, size_t index, void *data, size_t datasize)
{
    vectoritem *items;
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
    items = malloc(sizeof(vectoritem) * v->capacity);
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

    safefree(v->items);

    v->items = items;

    return 1;
}

size_t vector_length(vector *v)
{
    if (v == NULL)
    {
        return 0;
    }

    return v->node_count;
}

int vector_free(vector *v)
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
                safefree(v->items[j].item);
            }
        }
        safefree(v->items);
    }
    else
    {
        safefree(v);
        return 0;
    }

    safefree(v);

    return 1;
}

int vector_minimize(vector *v)
{
    if (v->items == NULL)
    {
        return 0;
    }

    if (v->node_count == 0)
    {
        safefree(v->items);
    }
    else
    {
        v->items = realloc(v->items, sizeof(vectoritem) * v->node_count);
        if (v->items == NULL)
        {
            return 0;
        }
    }

    v->capacity = v->node_count;

    return 1;
}

void *vector_get(vector *v, size_t index)
{
    if (v == NULL || v->items == NULL || index >= v->capacity)
        return NULL;

    return v->items[index].item;
}

trie *trie_create(void)
{
    trie *t = malloc(sizeof(trie));

    if (t == NULL)
    {
        return NULL;
    }

    t->character = 0;
    t->child_count = 0;
    t->children = NULL;

    return t;
}

static int trie_find(trie *t, char character)
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

int trie_insert(trie *t, char *word)
{
    int i = 0;
    int j = 0;

    if (t == NULL)
    {
        return 0;
    }

    while (1)
    {
        i = trie_find(t, word[j++]);
        if (i == -1)
            break;
        t = t->children[i];
    }

    j--;
    while (1)
    {
        t->children = realloc(t->children, sizeof(trie *) * ++(t->child_count));
        if (t->children == NULL)
        {
            return 0;
        }

        t->children[t->child_count - 1] = trie_create();
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

int trie_search(trie *t, char *word)
{
    int i = 0;
    size_t j = 0;

    if (t == NULL || t->children == NULL)
    {
        return 0;
    }

    while (1)
    {
        i = trie_find(t, word[j++]);
        if (i == -1)
            break;
        t = t->children[i];
    }

    return strlen(word) == --j;
}

int trie_free(trie *t)
{
    trie **t_null_checker;
    vector *to_visit = create_vector();
    size_t i;

    if (t == NULL || t->children == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!vector_add(to_visit, &t, sizeof(trie **)))
    {
        return 0;
    }

    while (vector_length(to_visit) != 0)
    {
        for (i = 0; i < t->child_count; i++)
        {
            if (!vector_add(to_visit, &t->children[i], sizeof(trie **)))
            {
                return 0;
            }
        }

        if (t->children != NULL)
        {
            safefree(t->children);
        }

        safefree(t);

        if (to_visit->node_count > 0)
        {
            if (!vector_delete(to_visit, 0))
            {
                return 0;
            }
        }

        if (to_visit->node_count > 0)
        {
            t_null_checker = (trie **)vector_get(to_visit, 0);
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

    vector_free(to_visit);

    return 1;
}

tree *create_tree(void)
{
    tree *t = malloc(sizeof(tree));

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

int tree_set(tree *t, void *data, size_t datasize)
{
    if (t == NULL)
    {
        return 0;
    }

    if (t->data != NULL)
    {
        safefree(t->data);
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

tree *tree_add(tree *t, void *data, size_t datasize)
{
    if (t == NULL)
    {
        return NULL;
    }

    t->child_count++;
    t->children = realloc(t->children, sizeof(tree *) * t->child_count);
    if (t->children == NULL)
    {
        return NULL;
    }

    t->children[t->child_count - 1] = malloc(sizeof(tree));
    if (t->children[t->child_count - 1] == NULL)
    {
        free(t->children);
        return NULL;
    }

    t->children[t->child_count - 1]->data = malloc(datasize);
    if (t->children[t->child_count - 1]->data == NULL)
    {
        free(t->children);
        free(t->children[t->child_count - 1]);
        return NULL;
    }
    t->children[t->child_count - 1]->datasize = datasize;
    memcpy(t->children[t->child_count - 1]->data, data, datasize);

    t->children[t->child_count - 1]->child_count = 0;
    t->children[t->child_count - 1]->children = NULL;
    t->children[t->child_count - 1]->parent = t;

    return t->children[t->child_count - 1];
}

void *tree_get(tree *t)
{
    if (t == NULL)
        return NULL;

    return t->data;
}

size_t tree_size(tree *t)
{
    if (t == NULL)
        return 0;

    return t->datasize;
}

int tree_child_count(tree *t)
{
    if (t == NULL)
        return 0;

    return t->child_count;
}

tree *tree_child(tree *t, size_t child)
{
    if (t == NULL || child >= t->child_count || t->children == NULL)
        return NULL;

    return t->children[child];
}

tree *tree_parent(tree *t)
{
    if (t == NULL)
        return NULL;

    return t->parent;
}

int tree_bfs(tree *t, void (*visit)(tree *))
{
    tree **t_null_checker;
    vector *to_visit = create_vector();
    size_t i;

    if (t == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!vector_add(to_visit, &t, sizeof(tree **)))
    {
        vector_free(to_visit);
        return 0;
    }

    while (vector_length(to_visit) != 0)
    {
        for (i = 0; i < t->child_count; i++)
        {
            if (!vector_add(to_visit, &t->children[i], sizeof(tree **)))
            {
                vector_free(to_visit);
                return 0;
            }
        }

        visit(t);

        if (to_visit->node_count > 0)
        {
            if (!vector_delete(to_visit, 0))
            {
                vector_free(to_visit);
                return 0;
            }
        }

        if (to_visit->node_count > 0)
        {
            t_null_checker = (tree **)vector_get(to_visit, 0);
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

    vector_free(to_visit);

    return 1;
}

static void tree_node_destroy(tree *t)
{
    if (t == NULL)
        return;

    if (t->data != NULL)
    {
        safefree(t->data);
    }

    if (t->children != NULL)
    {
        safefree(t->children);
    }

    safefree(t);
}

int tree_destroy(tree *t) { return tree_bfs(t, tree_node_destroy); }

graph *create_graph(void)
{
    graph *g = malloc(sizeof(graph));

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

graph *graph_add(graph *g, void *data, size_t datasize)
{
    g->child_count_from++;
    g->edges_from =
        realloc(g->edges_from, sizeof(graphedge) * g->child_count_from);
    if (g->edges_from == NULL)
    {
        return NULL;
    }

    g->edges_from[g->child_count_from - 1] = malloc(sizeof(graphedge));
    if (g->edges_from[g->child_count_from - 1] == NULL)
    {
        free(g->edges_from);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->parent = g;
    g->edges_from[g->child_count_from - 1]->child = create_graph();
    if (g->edges_from[g->child_count_from - 1]->child == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        return NULL;
    }

    g->edges_from[g->child_count_from - 1]->weight = 0;

    g->edges_from[g->child_count_from - 1]->child->data = malloc(datasize);
    if (g->edges_from[g->child_count_from - 1]->child->data == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        free(g->edges_from[g->child_count_from - 1]->child);
        return NULL;
    }

    g->edges_from[g->child_count_from - 1]->child->datasize = datasize;
    g->edges_from[g->child_count_from - 1]->child->child_count_from = 0;
    g->edges_from[g->child_count_from - 1]->child->child_count_to = 1;
    g->edges_from[g->child_count_from - 1]->child->edges_from = NULL;
    g->edges_from[g->child_count_from - 1]->child->edges_to =
        malloc(sizeof(graphedge *));
    if (g->edges_from[g->child_count_from - 1]->child->edges_to == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        free(g->edges_from[g->child_count_from - 1]->child);
        free(g->edges_from[g->child_count_from - 1]->child->data);
        return NULL;
    }

    g->edges_from[g->child_count_from - 1]->child->edges_to[0] =
        malloc(sizeof(graphedge));

    if (g->edges_from[g->child_count_from - 1]->child->edges_to[0] == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        free(g->edges_from[g->child_count_from - 1]->child);
        free(g->edges_from[g->child_count_from - 1]->child->data);
        free(g->edges_from[g->child_count_from - 1]->child->edges_to);
        return NULL;
    }

    memcpy(g->edges_from[g->child_count_from - 1]->child->data, data, datasize);
    memcpy(g->edges_from[g->child_count_from - 1]->child->edges_to[0],
           g->edges_from[g->child_count_from - 1], sizeof(graphedge));
    return g->edges_from[g->child_count_from - 1]->child;
}

graph *graph_add_weighted(graph *g, void *data, size_t datasize, int weight)
{
    g->child_count_from++;
    g->edges_from =
        realloc(g->edges_from, sizeof(graphedge) * g->child_count_from);
    if (g->edges_from == NULL)
    {
        return NULL;
    }
    g->edges_from[g->child_count_from - 1] = malloc(sizeof(graphedge));
    if (g->edges_from[g->child_count_from - 1] == NULL)
    {
        free(g->edges_from);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->parent = g;
    g->edges_from[g->child_count_from - 1]->child = create_graph();
    if (g->edges_from[g->child_count_from - 1]->child == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->weight = weight;

    g->edges_from[g->child_count_from - 1]->child->data = malloc(datasize);
    if (g->edges_from[g->child_count_from - 1]->child->data == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        free(g->edges_from[g->child_count_from - 1]->child);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->child->datasize = datasize;
    g->edges_from[g->child_count_from - 1]->child->child_count_from = 0;
    g->edges_from[g->child_count_from - 1]->child->child_count_to = 1;
    g->edges_from[g->child_count_from - 1]->child->edges_from = NULL;
    g->edges_from[g->child_count_from - 1]->child->edges_to =
        malloc(sizeof(graphedge *));
    if (g->edges_from[g->child_count_from - 1]->child->edges_to == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        free(g->edges_from[g->child_count_from - 1]->child);
        free(g->edges_from[g->child_count_from - 1]->child->data);
        return NULL;
    }
    g->edges_from[g->child_count_from - 1]->child->edges_to[0] =
        malloc(sizeof(graphedge));
    if (g->edges_from[g->child_count_from - 1]->child->edges_to[0] == NULL)
    {
        free(g->edges_from);
        free(g->edges_from[g->child_count_from - 1]);
        free(g->edges_from[g->child_count_from - 1]->child);
        free(g->edges_from[g->child_count_from - 1]->child->data);
        free(g->edges_from[g->child_count_from - 1]->child->edges_to);
        return NULL;
    }

    memcpy(g->edges_from[g->child_count_from - 1]->child->data, data, datasize);
    memcpy(g->edges_from[g->child_count_from - 1]->child->edges_to[0],
           g->edges_from[g->child_count_from - 1], sizeof(graphedge));
    return g->edges_from[g->child_count_from - 1]->child;
}

int graph_set(graph *g, void *data, size_t datasize)
{
    if (g == NULL)
    {
        return 0;
    }

    if (g->data != NULL)
    {
        safefree(g->data);
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

int graph_set_weight(graph *g, size_t edge_num, int new_weight)
{
    if (g == NULL || g->edges_from == NULL || g->child_count_from <= edge_num ||
        g->edges_from[edge_num] == NULL)
    {
        return 0;
    }
    g->edges_from[edge_num]->weight = new_weight;

    return 1;
}

graph *graph_child(graph *g, size_t child)
{
    if (g == NULL || child >= g->child_count_from || g->edges_from == NULL ||
        g->edges_from[child] == NULL)
    {
        return NULL;
    }

    return g->edges_from[child]->child;
}

void *graph_get(graph *g)
{
    if (g == NULL)
    {
        return NULL;
    }

    return g->data;
}

int graph_get_weight(graph *g, size_t edge_number)
{
    if (g == NULL || g->edges_from == NULL ||
        edge_number >= g->child_count_from ||
        g->edges_from[edge_number] == NULL)
    {
        return 0;
    }

    return g->edges_from[edge_number]->weight;
}

size_t graph_size(graph *g)
{
    if (g == NULL)
    {
        return 0;
    }

    return g->datasize;
}

int graph_child_count(graph *g)
{
    if (g == NULL)
    {
        return 0;
    }

    return g->child_count_from;
}

int graph_link(graph *g1, graph *g2)
{
    if (g1 == NULL || g2 == NULL)
    {
        return 0;
    }

    g1->child_count_from++;
    g1->edges_from =
        realloc(g1->edges_from, sizeof(graphedge *) * g1->child_count_from);
    if (g1->edges_from == NULL)
    {
        return 0;
    }
    g1->edges_from[g1->child_count_from - 1] = malloc(sizeof(graphedge));
    if (g1->edges_from[g1->child_count_from - 1] == NULL)
    {
        free(g1->edges_from);
        return 0;
    }
    g1->edges_from[g1->child_count_from - 1]->parent = g1;
    g1->edges_from[g1->child_count_from - 1]->child = g2;
    g1->edges_from[g1->child_count_from - 1]->weight = 0;
    g2->child_count_to++;
    g2->edges_to =
        realloc(g2->edges_to, sizeof(graphedge *) * g2->child_count_to);
    if (g2->edges_to == NULL)
    {
        free(g1->edges_from);
        free(g2->edges_to);
        return 0;
    }
    g2->edges_to[g2->child_count_to - 1] = malloc(sizeof(graphedge));
    if (g2->edges_to[g2->child_count_to - 1] == NULL)
    {
        free(g1->edges_from);
        free(g2->edges_to);
        free(g2->edges_to);
        return 0;
    }
    g2->edges_to[g2->child_count_to - 1]->parent = g1;
    g2->edges_to[g2->child_count_to - 1]->child = g2;
    g2->edges_to[g2->child_count_to - 1]->weight = 0;

    return 1;
}

int graph_link_weighted(graph *g1, graph *g2, int weight)
{
    if (g1 == NULL || g2 == NULL)
        return 0;

    graph_link(g1, g2);

    g1->edges_from[g1->child_count_from - 1]->weight = weight;
    g2->edges_to[g2->child_count_to - 1]->weight = weight;

    return 1;
}

int graph_destroy(graph *g)
{
    graph **g_null_checker;
    vector *visited = create_vector();
    vector *to_visit = create_vector();
    size_t i;

    if (g == NULL || visited == NULL || to_visit == NULL)
    {
        return 0;
    }

    if (!vector_add(to_visit, &g, sizeof(graph **)))
    {
        vector_free(to_visit);
        vector_free(visited);
        return 0;
    }

    while (vector_length(to_visit) != 0)
    {
        for (i = 0; i < vector_length(visited); i++)
        {
            if (*(graph **)vector_get(visited, i) == g)
            {
                if (!vector_delete(to_visit, 0))
                {
                    vector_free(to_visit);
                    vector_free(visited);
                    return 0;
                }
                if (to_visit->node_count > 0)
                {
                    g = *(graph **)vector_get(to_visit, 0);
                    if (g == NULL)
                    {
                        vector_free(to_visit);
                        vector_free(visited);
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
            if (!vector_add(to_visit, &g->edges_from[i]->child,
                            sizeof(graph **)))
            {
                vector_free(to_visit);
                vector_free(visited);
                return 0;
            }
        }

        if (g->data)
        {
            safefree(g->data);
        }

        if (g->edges_from)
        {
            for (i = 0; i < g->child_count_from; i++)
            {
                safefree(g->edges_from[i]);
            }
            safefree(g->edges_from);
        }

        if (g->edges_to)
        {
            for (i = 0; i < g->child_count_to; i++)
            {
                safefree(g->edges_to[i]);
            }
            safefree(g->edges_to);
        }

        if (!vector_add(visited, &g, sizeof(graph **)))
        {
            vector_free(to_visit);
            vector_free(visited);
            return 0;
        }

        if (to_visit->node_count > 0)
        {
            if (!vector_delete(to_visit, 0))
            {
                vector_free(to_visit);
                vector_free(visited);
                return 0;
            }
        }

        safefree(g);

        if (to_visit->node_count > 0)
        {
            g_null_checker = (graph **)vector_get(to_visit, 0);
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

    vector_free(visited);
    vector_free(to_visit);

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

int lds_string_append(lds_string *s, char *newstr)
{
    if (s == NULL)
    {
        return 0;
    }

    return lds_string_append_len(s, newstr, strlen(newstr));
}

int lds_string_append_len(lds_string *s, char *newstr, size_t len)
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

const char *lds_string_cstr(lds_string *s) { return s->data; }

size_t lds_string_len(lds_string *s) { return s->len; }

lds_string *lds_string_from(char *new_str)
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

int lds_string_push_back_len(lds_string *s, char *newstr, size_t len)
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

int lds_string_push_back(lds_string *s, char *newstr)
{
    if (s == NULL)
    {
        return 0;
    }

    return lds_string_push_back_len(s, newstr, strlen(newstr));
}

int lds_string_copy_len(lds_string *s, char *newstr, size_t length)
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

int lds_string_copy(lds_string *s, char *newstr)
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
        safefree(s->data);
    }

    safefree(s);

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
        safefree(s1->data);
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
