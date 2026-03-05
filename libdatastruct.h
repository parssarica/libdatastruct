/*
Pars SARICA <pars@parssarica.com>
*/

#include <stddef.h>
#include <sys/types.h>

#define lds_safefree(x)                                                        \
    free(x);                                                                   \
    x = NULL

typedef struct _linkedlist
{
    void *data;
    size_t datasize;
    struct _linkedlist *prev;
    struct _linkedlist *next;
} lds_linkedlist;

typedef struct
{
    void *key;
    void *value;
    size_t keysize;
    size_t valuesize;
    int deleted;
} lds_mapitem;

typedef struct
{
    size_t node_count;
    size_t capacity;
    lds_mapitem *items;
} lds_map;

typedef struct
{
    void *item;
    size_t size;
} lds_stackitem;

typedef struct
{
    size_t node_count;
    size_t capacity;
    lds_stackitem *items;
} lds_stack;

typedef struct
{
    void *item;
    size_t size;
} lds_queueitem;

typedef struct
{
    size_t node_count;
    size_t capacity;
    lds_queueitem *items;
} lds_queue;

typedef struct _bintree
{
    void *data;
    size_t size;
    struct _bintree *left;
    struct _bintree *right;
} lds_bintree;

typedef struct
{
    void *item;
    size_t size;
} lds_vectoritem;

typedef struct
{
    size_t node_count;
    size_t capacity;
    lds_vectoritem *items;
} lds_vector;

typedef struct _trie
{
    char character;
    size_t child_count;
    struct _trie **children;
} lds_trie;

typedef struct _tree
{
    void *data;
    size_t datasize;
    size_t child_count;
    struct _tree **children;
    struct _tree *parent;
} lds_tree;

typedef struct _graph lds_graph;

typedef struct
{
    lds_graph *parent;
    lds_graph *child;
    int weight;
} lds_graphedge;

struct _graph
{
    void *data;
    size_t datasize;
    size_t child_count_from;
    size_t child_count_to;
    lds_graphedge **edges_from;
    lds_graphedge **edges_to;
};

typedef struct
{
    char *data;
    size_t len;
    size_t capacity;
} lds_string;

#define lds_map_for_each(m, key, value)                                        \
    for (size_t lds__i = 0; lds__i < (m)->node_count; lds__i++)                \
        if ((m)->items[lds__i].deleted)                                        \
            continue;                                                          \
        else                                                                   \
            for (int lds__once = 1;                                            \
                 lds__once && ((key) = (m)->items[lds__i].key,                 \
                              (value) = (m)->items[lds__i].value, 1);          \
                 lds__once = 0)

#define lds_vector_for_each(v, out)                                            \
    for (size_t lds__i = 0;                                                    \
         lds__i < (v)->node_count && ((out) = (v)->items[lds__i].item, 1);     \
         lds__i++)

lds_linkedlist *lds_create_linkedlist(void);
int lds_linkedlist_add(lds_linkedlist *, const void *, size_t);
int lds_linkedlist_length(lds_linkedlist *);
const void *lds_linkedlist_get(lds_linkedlist *, size_t);
int lds_linkedlist_delete(lds_linkedlist *, size_t);
int lds_linkedlist_update(lds_linkedlist *, int, const void *, size_t);
int lds_linkedlist_insert(lds_linkedlist *, const void *, size_t, size_t);
int lds_linkedlist_free(lds_linkedlist *);
int lds_linkedlist_pop(lds_linkedlist *, void *);
lds_linkedlist *lds_linkedlist_get_node(lds_linkedlist *, size_t);
int lds_linkedlist_clear(lds_linkedlist *);
lds_map *lds_create_map(void);
int lds_map_add(lds_map *, const void *, size_t, const void *, size_t);
int lds_map_length(const lds_map *);
const void *lds_map_get(lds_map *, const void *, size_t);
int lds_map_delete(lds_map *, const void *, size_t);
int lds_map_update_key(lds_map *, const void *, size_t, const void *, size_t);
int lds_map_update_value(lds_map *, const void *, size_t, const void *, size_t);
int lds_map_free(lds_map *);
int lds_map_minimize(lds_map *);
int lds_map_clear(lds_map *);
lds_stack *lds_create_stack(void);
int lds_stack_push(lds_stack *, const void *, size_t);
int lds_stack_pop(lds_stack *, void *);
const void *lds_stack_peek(const lds_stack *);
int lds_stack_free(lds_stack *);
int lds_stack_minimize(lds_stack *);
int lds_stack_empty(const lds_stack *);
int lds_stack_clear(lds_stack *);
lds_queue *lds_create_queue(void);
int lds_queue_enqueue(lds_queue *, const void *, size_t);
int lds_queue_dequeue(lds_queue *, void *);
int lds_queue_free(lds_queue *);
int lds_queue_minimize(lds_queue *);
int lds_queue_clear(lds_queue *);
int lds_queue_is_empty(const lds_queue *);
const void *lds_queue_front(const lds_queue *);
lds_bintree *lds_create_bintree(void);
int lds_bintree_set_nodes(lds_bintree *);
int lds_bintree_set(lds_bintree *, const void *, size_t);
size_t lds_bintree_size(const lds_bintree *);
void *lds_bintree_get(const lds_bintree *);
lds_bintree *lds_bintree_left(const lds_bintree *);
lds_bintree *lds_bintree_right(const lds_bintree *);
lds_bintree *lds_bintree_insert_left(lds_bintree *, const void *, size_t);
lds_bintree *lds_bintree_insert_right(lds_bintree *, const void *, size_t);
int lds_bintree_has_left(const lds_bintree *);
int lds_bintree_has_right(const lds_bintree *);
int lds_bintree_bfs(lds_bintree *, void (*)(lds_bintree *));
int lds_bintree_destroy(lds_bintree *);
int lds_bintree_remove_left(lds_bintree *);
int lds_bintree_remove_right(lds_bintree *);
lds_vector *lds_create_vector(void);
int lds_vector_add(lds_vector *, const void *, int);
int lds_vector_delete(lds_vector *, size_t);
int lds_vector_insert(lds_vector *, size_t, const void *, size_t);
size_t lds_vector_length(const lds_vector *);
int lds_vector_reserve(lds_vector *, size_t);
int lds_vector_free(lds_vector *);
int lds_vector_minimize(lds_vector *);
const void *lds_vector_get(const lds_vector *, size_t);
int lds_vector_pop(lds_vector *, void *);
int lds_vector_clear(lds_vector *);
lds_trie *lds_trie_create(void);
int lds_trie_insert(lds_trie *, const char *);
int lds_trie_search(const lds_trie *, const char *);
int lds_trie_free(lds_trie *);
lds_tree *lds_create_tree(void);
int lds_tree_set(lds_tree *, const void *, size_t);
lds_tree *lds_tree_add(lds_tree *, const void *, size_t);
void *lds_tree_get(const lds_tree *);
size_t lds_tree_size(const lds_tree *);
int lds_tree_child_count(const lds_tree *);
lds_tree *lds_tree_child(const lds_tree *, size_t);
lds_tree *lds_tree_parent(const lds_tree *);
int lds_tree_bfs(lds_tree *, void (*)(lds_tree *));
int lds_tree_destroy(lds_tree *);
lds_graph *lds_create_graph(void);
lds_graph *lds_graph_add(lds_graph *, const void *, size_t);
lds_graph *lds_graph_add_weighted(lds_graph *, const void *, size_t, int);
int lds_graph_set(lds_graph *, void *, size_t);
int lds_graph_set_weight(const lds_graph *, size_t, int);
lds_graph *lds_graph_child(lds_graph *, size_t);
const void *lds_graph_get(const lds_graph *);
int lds_graph_get_weight(lds_graph *, size_t);
size_t lds_graph_size(const lds_graph *);
int lds_graph_child_count(const lds_graph *);
int lds_graph_link(lds_graph *, lds_graph *);
int lds_graph_link_weighted(lds_graph *, lds_graph *, int);
int lds_graph_destroy(lds_graph *);
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
int lds_string_reverse(lds_string *);
ssize_t lds_string_find_len(const lds_string *, const char *, size_t);
ssize_t lds_string_find(const lds_string *, const char *);
int lds_string_contains_len(const lds_string *, const char *, size_t);
int lds_string_contains(const lds_string *, const char *);
int lds_string_lower(lds_string *);
int lds_string_upper(lds_string *);
int lds_string_toggle_case(lds_string *);
int lds_string_replace_len(lds_string *, size_t, const char *, size_t);
int lds_string_replace(lds_string *, size_t, const char *);
lds_vector *lds_string_split_len(lds_string *, const char *, size_t);
lds_vector *lds_string_split(lds_string *, const char *);
int lds_string_split_free(lds_vector *);
