/*
Pars SARICA <pars@parssarica.com>
*/

#include <stddef.h>

#define safefree(x) free(x); x=NULL

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
    int deleted;
} vectoritem;

typedef struct
{
    int node_count;
    int capacity;
    int deleted_nodes;
    vectoritem *items;
} vector;

typedef struct _trie
{
    char character;
    int child_count;
    struct _trie **children;
} trie;

typedef struct _tree
{
    void *data;
    size_t datasize;
    int child_count;
    struct _tree **children;
    struct _tree *parent;
} tree;

typedef struct _graph graph;

typedef struct
{
    graph *parent;
    graph *child;
    int weight;
} graphedge;

struct _graph
{
    void *data;
    size_t datasize;
    int child_count_from;
    int child_count_to;
    graphedge **edges_from;
    graphedge **edges_to;
};

#define loopMap(m, key, value)                                                 \
    for (int i = 0; i < m->node_count &&                                       \
                    (key = m->items[i].key, value = m->items[i].value, 1);     \
         i++)                                                                  \
        if (m->items[i].deleted)                                               \
            continue;                                                          \
        else

#define loopVector(v, out)                                                     \
    for (int _i = 0; _i < (v->node_count + v->deleted_nodes) &&                \
                     (out = v->items[_i].item, 1);                             \
         _i++)                                                                 \
        if (v->items[_i].deleted)                                              \
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
int stack_empty(stack *);
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
void vector_delete(vector *, int);
void vector_insert(vector *, int, void *, int);
int vector_length(vector *);
void vector_free(vector *);
void vector_minimize(vector *);
void *vector_get(vector *, int);
trie *trie_create(void);
void trie_insert(trie *, char *);
int trie_search(trie *, char *);
void trie_free(trie *);
tree *create_tree(void);
void tree_set(tree *, void *, size_t);
tree *tree_add(tree *, void *, size_t);
void *tree_get(tree *);
size_t tree_size(tree *);
int tree_child_count(tree *);
tree *tree_child(tree *, int);
tree *tree_parent(tree *);
void tree_dfs(tree *, void (*)(tree *));
void tree_destroy(tree *);
graph *create_graph(void);
graph *graph_add(graph *, void *, size_t);
graph *graph_add_weighted(graph *, void *, size_t, int);
void graph_set(graph *, void *, size_t);
void graph_set_weight(graph *, int, int);
graph *graph_child(graph *, int);
void *graph_get(graph *);
int graph_get_weight(graph *, int);
size_t graph_size(graph *);
int graph_child_count(graph *);
void graph_destroy(graph *);
