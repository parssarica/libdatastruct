/*
Pars SARICA <pars@parssarica.com>
*/

#include "libdatastruct.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void **to_free_list_stack;
int to_free_list_stack_length;
void **to_free_list_queue;
int to_free_list_queue_length;

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
    if (table->items == NULL)
        return -1;

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
    if (table->items == NULL)
        return NULL;

    int i = map_get_index(table, key, keysize);
    if (i != -1)
    {
        return table->items[i].value;
    }

    return NULL;
}

void map_delete(map *table, void *key, size_t keysize)
{
    if (table->items == NULL)
        return;

    int i = map_get_index(table, key, keysize);
    if (i == -1)
        return;

    table->items[i].deleted = 1;
}

void map_update_key(map *table, void *key_old, size_t old_keysize,
                    void *key_new, size_t new_keysize)
{
    if (table->items == NULL)
        return;

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
    if (table->items == NULL)
        return;

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

    if (table->items != NULL)
    {
        for (i = 0; i < table->node_count; i++)
        {
            free(table->items[i].key);
            free(table->items[i].value);
        }
        free(table->items);
    }

    free(table);
}

void map_minimize(map *table)
{
    if (table->items == NULL)
        return;

    table->items = realloc(table->items, sizeof(mapitem) * table->node_count);
    table->capacity = table->node_count;
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
    if (s->items == NULL)
        return NULL;

    void *val;

    s->node_count--;
    val = malloc(s->items[s->node_count].size);
    memcpy(val, s->items[s->node_count].item, s->items[s->node_count].size);
    free(s->items[s->node_count].item);

    to_free_list_stack = realloc(to_free_list_stack,
                                 sizeof(void *) * ++to_free_list_stack_length);
    to_free_list_stack[to_free_list_stack_length - 1] = val;
    return val;
}

void *stack_peek(stack *s)
{
    if (s->items == NULL)
        return NULL;

    return s->items[s->node_count - 1].item;
}

void stack_free(stack *s)
{
    int i = 0;
    if (s->items != NULL)
    {
        for (i = 0; i < s->node_count; i++)
        {
            free(s->items[i].item);
        }

        free(s->items);
    }

    for (i = 0; i < to_free_list_stack_length; i++)
    {
        free(to_free_list_stack[i]);
    }
    free(to_free_list_stack);
    to_free_list_stack_length = 0;

    free(s);
}

void stack_minimize(stack *s)
{
    if (s->items == NULL)
        return;

    if (s->node_count == 0)
    {
        free(s->items);
        s->items = NULL;
    }
    else
    {
        s->items = realloc(s->items, sizeof(stackitem) * s->node_count);
    }
    s->capacity = s->node_count;
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
    q->items[q->node_count].size = datasize;
    memcpy(q->items[q->node_count].item, data, datasize);

    q->node_count++;
}

void *dequeue(queue *q)
{
    if (q->items == NULL)
        return NULL;

    void *val;
    int i;
    queueitem *items;

    q->node_count--;
    val = malloc(q->items[0].size);
    memcpy(val, q->items[0].item, q->items[0].size);

    items = malloc(sizeof(queueitem) * q->capacity);
    for (i = 0; i < q->node_count; i++)
    {
        items[i].item = malloc(q->items[i + 1].size);
        items[i].size = q->items[i + 1].size;
        memcpy(items[i].item, q->items[i + 1].item, q->items[i + 1].size);
    }

    for (i = 0; i <= q->node_count; i++)
    {
        free(q->items[i].item);
    }

    free(q->items);

    q->items = items;

    to_free_list_queue = realloc(to_free_list_queue,
                                 sizeof(void *) * ++to_free_list_queue_length);
    to_free_list_queue[to_free_list_queue_length - 1] = val;
    return val;
}

void queue_free(queue *q)
{
    int i = 0;
    if (q->items != NULL)
    {
        for (i = 0; i < q->node_count; i++)
        {
            free(q->items[i].item);
        }

        free(q->items);
    }

    for (i = 0; i < to_free_list_queue_length; i++)
    {
        free(to_free_list_queue[i]);
    }
    free(to_free_list_queue);
    to_free_list_queue_length = 0;

    free(q);
}

void queue_minimize(queue *q)
{
    if (q->items == NULL)
        return;

    if (q->node_count == 0)
    {
        free(q->items);
        q->items = NULL;
    }
    else
    {
        q->items = realloc(q->items, sizeof(stackitem) * q->node_count);
    }

    q->capacity = q->node_count;
}

void *queue_front(queue *q)
{
    if (q->items == NULL)
        return NULL;

    return q->items[q->node_count - 1].item;
}

bintree *create_bintree(void)
{
    bintree *b = malloc(sizeof(bintree));

    b->data = NULL;
    b->size = 0;
    b->left = NULL;
    b->right = NULL;

    return b;
}

void bintree_set_nodes(bintree *b)
{
    b->left = malloc(sizeof(bintree));
    b->right = malloc(sizeof(bintree));

    b->left->data = NULL;
    b->left->size = 0;
    b->left->left = NULL;
    b->left->right = NULL;
    b->right->data = NULL;
    b->right->size = 0;
    b->right->left = NULL;
    b->right->right = NULL;
}

void bintree_set(bintree *b, void *data, size_t datasize)
{
    b->data = malloc(datasize);
    b->size = datasize;

    memcpy(b->data, data, datasize);
}

void *bintree_get(bintree *b) { return b->data; }

void bintree_destroy(bintree *b)
{
    free(b->data);
    if (b->left != NULL)
    {
        bintree_destroy(b->left);
    }

    if (b->right != NULL)
    {
        bintree_destroy(b->right);
    }

    free(b);
}

vector *create_vector(void)
{
    vector *v = malloc(sizeof(vector));

    v->node_count = 0;
    v->capacity = 0;
    v->items = NULL;
    v->deleted_nodes = 0;

    return v;
}

void vector_add(vector *v, void *data, int datasize)
{
    if (v->node_count == v->capacity)
    {
        if (v->capacity == 0)
        {
            v->capacity = 1;
        }
        else
        {
            v->capacity *= 2;
        }
        v->items = realloc(v->items, sizeof(vectoritem) * v->capacity);
    }

    v->items[v->node_count].item = malloc(datasize);
    v->items[v->node_count].size = datasize;
    v->items[v->node_count].deleted = 0;

    memcpy(v->items[v->node_count].item, data, datasize);

    v->node_count++;
}

void vector_delete(vector *v, int index)
{
    int i;

    if (v->items == NULL)
    {
        return;
    }

    for (i = 0; i < v->capacity; i++)
    {
        if (i == index)
        {
            free(v->items[i].item);
            v->items[i].item = NULL;
            v->items[i].size = 0;
            v->items[i].deleted = 1;
            v->node_count--;
            v->deleted_nodes++;
        }
    }
}

void vector_insert(vector *v, int index, void *data, int datasize)
{
    vectoritem *items;
    int skipped = 0;
    int old_capacity;
    int i;

    if (v->items == NULL || index >= v->capacity)
    {
        return;
    }

    if (v->capacity > index && v->items[index].deleted == 1)
    {
        v->items[index].item = malloc(datasize);
        v->items[index].size = datasize;
        v->items[index].deleted = 0;
        v->deleted_nodes--;

        memcpy(v->items[index].item, data, datasize);

        v->node_count++;
        return;
    }

    old_capacity = v->capacity;
    if (v->capacity == v->node_count)
    {
        v->capacity *= 2;
    }
    items = malloc((v->capacity) * sizeof(vectoritem));
    for (i = 0; i < old_capacity + 1; i++)
    {
        if (i == index)
        {
            items[i].item = malloc(datasize);
            items[i].size = datasize;
            items[i].deleted = 0;

            memcpy(items[i].item, data, datasize);
            skipped++;
        }
        else
        {
            items[i].item = v->items[i - skipped].item;
            items[i].size = v->items[i - skipped].size;
            items[i].deleted = v->items[i - skipped].deleted;
        }
    }

    free(v->items);

    v->items = items;
    v->node_count++;
}

int vector_length(vector *v) { return v->node_count; }

void vector_free(vector *v)
{
    vectoritem *i;
    int j;

    if (v->items != NULL)
    {
        for (j = 0; j < v->node_count; j++)
        {
            i = &v->items[j];
            if (!i->deleted)
            {
                free(i->item);
            }
        }
        free(v->items);
    }

    free(v);
}

void vector_minimize(vector *v)
{
    if (v->items == NULL)
        return;

    if (v->node_count == 0)
    {
        free(v->items);
        v->items = NULL;
    }
    else
    {
        v->items = realloc(v->items, sizeof(vectoritem) * v->node_count);
    }

    v->capacity = v->node_count;
    v->deleted_nodes = 0;
}

trie *trie_create(void)
{
    trie *t = malloc(sizeof(trie));

    t->character = 0;
    t->child_count = 0;
    t->children = NULL;

    return t;
}

static int trie_find(trie *t, char character)
{
    int found = -1;
    int i;

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

void trie_insert(trie *t, char *word)
{
    int i = 0;
    int j = 0;

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
        t->children[t->child_count - 1] = trie_create();
        t->children[t->child_count - 1]->character = word[j++];
        if (word[j] == '\0')
            break;
        t = t->children[t->child_count - 1];
    }
}

int trie_search(trie *t, char *word)
{
    int i = 0;
    size_t j = 0;

    while (1)
    {
        i = trie_find(t, word[j++]);
        if (i == -1)
            break;
        t = t->children[i];
    }

    return strlen(word) == --j;
}

void trie_free(trie *t)
{
    int i;
    for (i = 0; i < t->child_count; i++)
    {
        trie_free(t->children[i]);
    }

    free(t->children);
    free(t);
}

tree *create_tree(void)
{
    tree *t = malloc(sizeof(tree));

    t->data = NULL;
    t->children = NULL;
    t->parent = NULL;
    t->datasize = 0;
    t->child_count = 0;

    return t;
}

void tree_set(tree *t, void *data, size_t datasize)
{
    if (t->data != NULL)
    {
        free(t->data);
    }

    t->data = malloc(datasize);
    t->datasize = datasize;

    memcpy(t->data, data, datasize);
}

tree *tree_add(tree *t, void *data, size_t datasize)
{
    t->child_count++;
    t->children = realloc(t->children, sizeof(tree *) * t->child_count);

    t->children[t->child_count - 1] = malloc(sizeof(tree));
    t->children[t->child_count - 1]->data = malloc(datasize);
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

tree *tree_child(tree *t, int child)
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

void tree_dfs(tree *t, void (*visit)(tree *))
{
    int i;

    if (t == NULL)
        return;

    visit(t);

    for (i = 0; i < t->child_count; i++)
    {
        tree_dfs(t->children[i], visit);
    }
}

void tree_destroy(tree *t)
{
    int i;

    if (t == NULL)
        return;

    if (t->data != NULL)
    {
        free(t->data);
    }

    for (i = 0; i < t->child_count; i++)
    {
        tree_destroy(t->children[i]);
    }

    free(t->children);
    free(t);
}

graph *create_graph(void)
{
    graph *g = malloc(sizeof(graph));

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
    g->edges_from[g->child_count_from - 1] = malloc(sizeof(graphedge));
    g->edges_from[g->child_count_from - 1]->parent = g;
    g->edges_from[g->child_count_from - 1]->child = create_graph();
    g->edges_from[g->child_count_from - 1]->weight = 0;

    g->edges_from[g->child_count_from - 1]->child->data = malloc(datasize);
    g->edges_from[g->child_count_from - 1]->child->datasize = datasize;
    g->edges_from[g->child_count_from - 1]->child->child_count_from = 0;
    g->edges_from[g->child_count_from - 1]->child->child_count_to = 1;
    g->edges_from[g->child_count_from - 1]->child->edges_from = NULL;
    g->edges_from[g->child_count_from - 1]->child->edges_to =
        malloc(sizeof(graphedge *));
    g->edges_from[g->child_count_from - 1]->child->edges_to[0] =
        malloc(sizeof(graphedge));

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
    g->edges_from[g->child_count_from - 1] = malloc(sizeof(graphedge));
    g->edges_from[g->child_count_from - 1]->parent = g;
    g->edges_from[g->child_count_from - 1]->child = create_graph();
    g->edges_from[g->child_count_from - 1]->weight = weight;

    g->edges_from[g->child_count_from - 1]->child->data = malloc(datasize);
    g->edges_from[g->child_count_from - 1]->child->datasize = datasize;
    g->edges_from[g->child_count_from - 1]->child->child_count_from = 0;
    g->edges_from[g->child_count_from - 1]->child->child_count_to = 1;
    g->edges_from[g->child_count_from - 1]->child->edges_from = NULL;
    g->edges_from[g->child_count_from - 1]->child->edges_to =
        malloc(sizeof(graphedge *));
    g->edges_from[g->child_count_from - 1]->child->edges_to[0] =
        malloc(sizeof(graphedge));

    memcpy(g->edges_from[g->child_count_from - 1]->child->data, data, datasize);
    memcpy(g->edges_from[g->child_count_from - 1]->child->edges_to[0],
           g->edges_from[g->child_count_from - 1], sizeof(graphedge));
    return g->edges_from[g->child_count_from - 1]->child;
}

void graph_set(graph *g, void *data, size_t datasize)
{
    if (g->data != NULL)
    {
        free(g->data);
    }

    g->data = malloc(datasize);
    g->datasize = datasize;

    memcpy(g->data, data, datasize);
}

void graph_set_weight(graph *g, int edge_num, int new_weight)
{
    g->edges_from[edge_num]->weight = new_weight;
}

graph *graph_child(graph *g, int child)
{
    if (child >= g->child_count_from)
        return NULL;
    return g->edges_from[child]->child;
}

void *graph_get(graph *g) { return g->data; }

int graph_get_weight(graph *g, int edge_number)
{
    return g->edges_from[edge_number]->weight;
}

size_t graph_size(graph *g) { return g->datasize; }
