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
    int size;
} stackitem;

typedef struct
{
    int node_count;
    int capacity;
    stackitem *items;
} stack;

typedef struct
{
    void *item;
    int size;
} queueitem;

typedef struct
{
    int node_count;
    int capacity;
    queueitem *items;
} queue;

typedef struct _bintree
{
    void *data;
    int size;
    struct _bintree *left;
    struct _bintree *right;
} bintree;

typedef struct
{
    void *item;
    int size;
} vectoritem;

typedef struct
{
    int node_count;
    int capacity;
    vectoritem *items;
} vector;

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
void map_minimize(map *);
stack *create_stack(void);
void stack_push(stack *, void *, size_t);
void *stack_pop(stack *);
void *stack_peek(stack *);
void stack_free(stack *);
void stack_minimize(stack *);
queue *create_queue(void);
void enqueue(queue *, void *, size_t);
void *dequeue(queue *);
void queue_free(queue *);
void queue_minimize(queue *);
void *queue_front(queue *);
bintree *create_bintree(void);
void bintree_set_nodes(bintree *);
void bintree_set(bintree *, void *, size_t);
void *bintree_get(bintree *);
void bintree_destroy(bintree *);
vector *create_vector(void);
void vector_add(vector *, void *, int);
