/*
Pars SARICA <pars@parssarica.com>
*/

#include <stddef.h>

#define safefree(x)                                                            \
    free(x);                                                                   \
    x = NULL

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
    size_t node_count;
    size_t capacity;
    mapitem *items;
} map;

typedef struct
{
    void *item;
    size_t size;
} stackitem;

typedef struct
{
    size_t node_count;
    size_t capacity;
    stackitem *items;
} stack;

typedef struct
{
    void *item;
    size_t size;
} queueitem;

typedef struct
{
    size_t node_count;
    size_t capacity;
    queueitem *items;
} queue;

typedef struct _bintree
{
    void *data;
    size_t size;
    struct _bintree *left;
    struct _bintree *right;
} bintree;

typedef struct
{
    void *item;
    size_t size;
} vectoritem;

typedef struct
{
    size_t node_count;
    size_t capacity;
    vectoritem *items;
} vector;

typedef struct _trie
{
    char character;
    size_t child_count;
    struct _trie **children;
} trie;

typedef struct _tree
{
    void *data;
    size_t datasize;
    size_t child_count;
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
    size_t child_count_from;
    size_t child_count_to;
    graphedge **edges_from;
    graphedge **edges_to;
};

typedef struct
{
    char *data;
    size_t len;
    size_t capacity;
} lds_string;

#define loopMap(m, key, value)                                                 \
    for (size_t i = 0; i < m->node_count &&                                    \
                       (key = m->items[i].key, value = m->items[i].value, 1);  \
         i++)                                                                  \
        if (m->items[i].deleted)                                               \
            continue;                                                          \
        else

#define loopVector(v, out)                                                     \
    for (size_t _i = 0; _i < (v->node_count) && (out = v->items[_i].item, 1);  \
         _i++)

linkedlist *create_linkedlist(void);
int linkedlist_add(linkedlist *, void *, size_t);
int linkedlist_length(linkedlist *);
void *linkedlist_get(linkedlist *, int);
int linkedlist_delete(linkedlist *, int);
int linkedlist_update(linkedlist *, int, void *, size_t);
int linkedlist_insert(linkedlist *, void *, size_t, int);
int linkedlist_free(linkedlist *);
map *create_map(void);
int map_add(map *, void *, size_t, void *, size_t);
int map_length(map *);
void *map_get(map *, void *, size_t);
int map_delete(map *, void *, size_t);
int map_update_key(map *, void *, size_t, void *, size_t);
int map_update_value(map *, void *, size_t, void *, size_t);
int map_free(map *);
int map_minimize(map *);
stack *create_stack(void);
int stack_push(stack *, void *, size_t);
int stack_pop(stack *, void *);
void *stack_peek(stack *);
int stack_free(stack *);
int stack_minimize(stack *);
int stack_empty(stack *);
queue *create_queue(void);
int enqueue(queue *, void *, size_t);
int dequeue(queue *, void *);
int queue_free(queue *);
int queue_minimize(queue *);
int queue_is_empty(queue *);
void *queue_front(queue *);
bintree *create_bintree(void);
int bintree_set_nodes(bintree *);
int bintree_set(bintree *, void *, size_t);
size_t bintree_size(bintree *);
void *bintree_get(bintree *);
bintree *bintree_left(bintree *);
bintree *bintree_right(bintree *);
bintree *bintree_insert_left(bintree *, void *, size_t);
bintree *bintree_insert_right(bintree *, void *, size_t);
int bintree_has_left(bintree *);
int bintree_has_right(bintree *);
int bintree_bfs(bintree *, void (*)(bintree *));
int bintree_destroy(bintree *);
int bintree_remove_left(bintree *);
int bintree_remove_right(bintree *);
vector *create_vector(void);
int vector_add(vector *, void *, int);
int vector_delete(vector *, size_t);
int vector_insert(vector *, size_t, void *, size_t);
size_t vector_length(vector *);
int vector_free(vector *);
int vector_minimize(vector *);
void *vector_get(vector *, size_t);
trie *trie_create(void);
int trie_insert(trie *, char *);
int trie_search(trie *, char *);
int trie_free(trie *);
tree *create_tree(void);
int tree_set(tree *, void *, size_t);
tree *tree_add(tree *, void *, size_t);
void *tree_get(tree *);
size_t tree_size(tree *);
int tree_child_count(tree *);
tree *tree_child(tree *, size_t);
tree *tree_parent(tree *);
int tree_bfs(tree *, void (*)(tree *));
int tree_destroy(tree *);
graph *create_graph(void);
graph *graph_add(graph *, void *, size_t);
graph *graph_add_weighted(graph *, void *, size_t, int);
int graph_set(graph *, void *, size_t);
int graph_set_weight(graph *, size_t, int);
graph *graph_child(graph *, size_t);
void *graph_get(graph *);
int graph_get_weight(graph *, size_t);
size_t graph_size(graph *);
int graph_child_count(graph *);
int graph_link(graph *, graph *);
int graph_link_weighted(graph *, graph *, int);
int graph_destroy(graph *);
lds_string *lds_create_string(void);
int lds_string_append(lds_string *, char *);
int lds_string_append_len(lds_string *, char *, size_t);
const char *lds_string_cstr(lds_string *);
size_t lds_string_len(lds_string *);
lds_string *lds_string_from(char *);
int lds_string_push_back(lds_string *, char *);
