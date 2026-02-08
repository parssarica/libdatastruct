/*
Pars SARICA <pars@parssarica.com>
*/

#include <stddef.h>

typedef struct _linkedlist
{
    void *data;
    struct _linkedlist *prev;
    struct _linkedlist *next;
} linkedlist;

typedef struct
{
    void *key;
    void *value;
    size_t keysize;
    size_t valuesize;
    int deleted;
} mapitem;

typedef struct
{
    int node_count;
    int capacity;
    mapitem *items;
} map;

typedef struct
{
    void *item;
} stackitem;

typedef struct
{
    int node_count;
    int capacity;
    stackitem *items;
} stack;

#define loopMap(m, key, value)                                                 \
    for (int i = 0; i < m->node_count &&                                       \
                    (key = m->items[i].key, value = m->items[i].value, 1);     \
         i++)                                                                  \
        if (m->items[i].deleted)                                               \
            continue;                                                          \
        else

linkedlist *create_linkedlist(void);
void linkedlist_add(linkedlist *, void *, size_t);
int linkedlist_length(linkedlist *);
void *linkedlist_get(linkedlist *, int);
void linkedlist_delete(linkedlist *, int);
void linkedlist_update(linkedlist *, int, void *, size_t);
void linkedlist_insert(linkedlist *, void *, size_t, int);
void linkedlist_free(linkedlist *);
map *create_map(void);
void map_add(map *, void *, size_t, void *, size_t);
int map_length(map *);
void *map_get(map *, void *, size_t);
void map_delete(map *, void *, size_t);
void map_update_key(map *, void *, size_t, void *, size_t);
void map_update_value(map *, void *, size_t, void *, size_t);
void map_free(map *);
stack *create_stack(void);
void stack_push(stack *, void *, size_t);
