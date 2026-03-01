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
int linkedlist_add(linkedlist *, const void *, size_t);
int linkedlist_length(linkedlist *);
const void *linkedlist_get(linkedlist *, int);
int linkedlist_delete(linkedlist *, int);
int linkedlist_update(linkedlist *, int, const void *, size_t);
int linkedlist_insert(linkedlist *, const void *, size_t, int);
int linkedlist_free(linkedlist *);
map *create_map(void);
int map_add(map *, const void *, size_t, const void *, size_t);
int map_length(const map *);
const void *map_get(map *, const void *, size_t);
int map_delete(map *, const void *, size_t);
int map_update_key(map *, const void *, size_t, const void *, size_t);
int map_update_value(map *, const void *, size_t, const void *, size_t);
int map_free(map *);
int map_minimize(map *);
stack *create_stack(void);
int stack_push(stack *, const void *, size_t);
int stack_pop(stack *, void *);
const void *stack_peek(const stack *);
int stack_free(stack *);
int stack_minimize(stack *);
int stack_empty(const stack *);
queue *create_queue(void);
int enqueue(queue *, const void *, size_t);
int dequeue(queue *, void *);
int queue_free(queue *);
int queue_minimize(queue *);
int queue_is_empty(const queue *);
const void *queue_front(const queue *);
bintree *create_bintree(void);
int bintree_set_nodes(bintree *);
int bintree_set(bintree *, const void *, size_t);
size_t bintree_size(const bintree *);
void *bintree_get(const bintree *);
bintree *bintree_left(const bintree *);
bintree *bintree_right(const bintree *);
bintree *bintree_insert_left(bintree *, const void *, size_t);
bintree *bintree_insert_right(bintree *, const void *, size_t);
int bintree_has_left(const bintree *);
int bintree_has_right(const bintree *);
int bintree_bfs(bintree *, void (*)(bintree *));
int bintree_destroy(bintree *);
int bintree_remove_left(bintree *);
int bintree_remove_right(bintree *);
vector *create_vector(void);
int vector_add(vector *, const void *, int);
int vector_delete(vector *, size_t);
int vector_insert(vector *, size_t, const void *, size_t);
size_t vector_length(const vector *);
int vector_free(vector *);
int vector_minimize(vector *);
const void *vector_get(const vector *, size_t);
trie *trie_create(void);
int trie_insert(trie *, const char *);
int trie_search(const trie *, const char *);
int trie_free(trie *);
tree *create_tree(void);
int tree_set(tree *, const void *, size_t);
tree *tree_add(tree *, const void *, size_t);
void *tree_get(const tree *);
size_t tree_size(const tree *);
int tree_child_count(const tree *);
tree *tree_child(const tree *, size_t);
tree *tree_parent(const tree *);
int tree_bfs(tree *, void (*)(tree *));
int tree_destroy(tree *);
graph *create_graph(void);
graph *graph_add(graph *, const void *, size_t);
graph *graph_add_weighted(graph *, const void *, size_t, int);
int graph_set(graph *, void *, size_t);
int graph_set_weight(const graph *, size_t, int);
graph *graph_child(graph *, size_t);
const void *graph_get(const graph *);
int graph_get_weight(graph *, size_t);
size_t graph_size(const graph *);
int graph_child_count(const graph *);
int graph_link(graph *, graph *);
int graph_link_weighted(graph *, graph *, int);
int graph_destroy(graph *);
lds_string *lds_create_string(void);
int lds_string_append(lds_string *, const char *);
int lds_string_append_len(lds_string *, const char *, size_t);
const char *lds_string_cstr(const lds_string *);
size_t lds_string_len(const lds_string *);
lds_string *lds_string_from(const char *);
int lds_string_push_front(lds_string *, const char *);
int lds_string_push_front_len(lds_string *, const char *, size_t);
int lds_string_copy_len(lds_string *, const char *, size_t);
int lds_string_copy(lds_string *, const char *);
int lds_string_free(lds_string *);
int lds_string_move(lds_string *, lds_string *);
int lds_string_reserve(lds_string *, size_t);
int lds_string_insert_len(lds_string *, size_t, const char *, size_t);
int lds_string_insert(lds_string *, size_t, const char *);
int lds_string_erase(lds_string *, size_t, size_t);
int lds_string_compare(const lds_string *, const lds_string *);
int lds_string_clear(lds_string *);
