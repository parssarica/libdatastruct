# libdatastruct

An easy to use C library providing linked lists, maps, stacks, queues, binary trees, vectors, tries, trees, graphs and strings.

---

## Table of Contents

- [Installation](#installation)
- [Documentation Note](#documentation-note)
- [Data structure list](#data-structure-list)
- [Lists](#lists)
  - [Linked lists](#linked-lists)
  - [Vectors](#vectors)
  - [Linked lists or vectors?](#linked-lists-or-vectors-)
- [Maps](#maps)
- [Stacks](#stacks)
- [Queues](#queues)
- [Binary trees](#binary-trees)
- [Tries](#tries)
- [Trees](#trees)
- [Graphs](#graphs)
- [Strings](#strings)

---


## Installation

Clone the repo and start developing:
```bash
git clone https://github.com/parssarica/libdatastruct.git
cd libdatastruct
```

---


---

## Documentation Note

This README provides an overview of the most commonly used features of **libdatastruct**.  
Not every function in the library is documented here.

For additional examples and a more complete overview of the available functionality,
please check the `example.c` file included in the repository.


## Data structure list
The following data structures are supported by libdatastruct:

- Linked lists
- Maps
- Stacks
- Queues
- Binary trees
- Vectors
- Tries
- Trees
- Graphs
- Strings

---

## Lists
You can use these two data structures as lists.

### Linked lists

Start by creating one:
```c
lds_linkedlist* l = lds_create_linkedlist();
if(l == NULL)
{
	return 0;
}
```

#### Adding items

To add some items, you should call `lds_linkedlist_add` function.
```c
int var1 = 1;
int var2 = 2;
int var3 = 3;

lds_linkedlist_add(l, &var1, sizeof(int));
lds_linkedlist_add(l, &var2, sizeof(int));
lds_linkedlist_add(l, &var3, sizeof(int));
```

You pass a pointer and a size because libdatastruct stores the data itself, not the pointer.

#### Deleting items

To delete some items, you should call `lds_linkedlist_delete` function.
```c
lds_linkedlist_delete(l, 1);
```

This deletes the second element (zero based index).

#### Updating an item

To update some items, you should call `lds_linkedlist_update` function.
```c
int new_variable = 5;

lds_linkedlist_update(l, 1, &new_variable, sizeof(int));
```

This makes the value of second element 5.

#### Inserting an item

To insert some items, you should call `lds_linkedlist_insert` function.
```c
int var4 = 4;

lds_linkedlist_insert(l, 1, &var4, sizeof(int));
```

After checking the second element, you will see 4, and the items from the second index before insertion will continue from third index.

#### Popping an item

To pop some items, which means getting the last item and deleting it, you should call `lds_linkedlist_pop` function.
```c
int popped_value;

lds_linkedlist_pop(l, &popped_value);
```

Now `popped_value` has the last item in the list.

#### Getting the length

You can use the `lds_linkedlist_length` function.
```c
size_t linked_list_length;

linked_list_length = lds_linkedlist_length(l);
```

#### Getting an item's value

You can use the `lds_linkedlist_get` function in order to get the nth item's value.
```c
int value;

value = lds_deref_int(lds_linkedlist_get(l, 1));
```

As the get function can not know which type does the user store in the list, it returns a `void *` pointer. `lds_deref_int` is a macro which dereferences `void *` pointers as they are pointing to an integer. There a few more macros like this:

- `lds_cast_char` -> Converts `void *` pointers to `char *` pointers so you can treat them as they are strings.
- `lds_deref_double` -> Dereferences `void *` pointers to `double` values.
- `lds_deref_type` -> Dereferences `void *` pointers to any type, but gets an argument specifying which type to dereference. It is used like `lds_deref_type(void_pointer, int)`

#### Extending the list with another one

Extending means, adding every item in the list 2 to list 1. To achieve this behaviour, you should use the `lds_linkedlist_extend` function.

```c
lds_linkedlist_extend(l1, l2);
```

Now `l1` contains the items of `l2`. Note that you shouldn't free `l2` after extending, because `l1` will contain items of `l2`.

#### Reversing the list

If you want to reverse the order of items in a list, you should call the `lds_linkedlist_reverse` function.
```c
lds_linkedlist_reverse(l);
```

#### Getting the index of item with the specific data

If you have the data and need to find the index of item that has the specific value, you should use the `lds_linkedlist_index` function.
```c
int data = 5;
ssize_t index = lds_linkedlist_index(l, &data, sizeof(int));
```

Also there is one more function like `lds_linkedlist_find`. It behaves almost same as `lds_linkedlist_index`, but instead it returns a node object.

```c
int data = 5;
lds_linkedlist_node* n = lds_linkedlist_find(l, &data, sizeof(int));
```

Now `n` is a raw node, which can be used with functions like `lds_linkedlist_data_size`, `lds_linkedlist_next`, etc.

#### Iterating over linked list

You can use the `lds_linkedlist_for_each` macro for iterating over linked list.
```c
void* ptr;

lds_linkedlist_for_each(l, ptr)
{
	printf("Value: %d\n", lds_deref_int(ptr));
}
```

#### Freeing the linked list

You can use the `lds_linkedlist_free` function in order to free the list.
```c
lds_linkedlist_free(l);
```

### Vectors

Start by creating one:
```c
lds_vector *v = lds_create_vector();
if(v == NULL)
{
	return 0;
}
```

#### Adding items

You can add items to a vector via `lds_vector_add` function:
```c
int var1 = 1;
int var2 = 2;
int var3 = 3;

lds_vector_add(v, &var1, sizeof(int));
lds_vector_add(v, &var2, sizeof(int));
lds_vector_add(v, &var3, sizeof(int));
```

#### Deleting items
You can delete items in a vector with `lds_vector_delete` function:
```c
lds_vector_delete(v, 1);
```

This deletes the second item.

#### Updating items
You can update an item in a vector by calling `lds_vector_update` function:
```c
int new_var1 = 5;
lds_vector_update(v, 1, &new_var, sizeof(int));
```

#### Inserting an item
You can insert an item via `lds_vector_insert`:
```c
int new_var2 = 10;
int new_var3 = 20;

lds_vector_insert(v, 1, &new_var2, sizeof(int));
lds_vector_insert(v, 1, &new_var3, sizeof(int));
```

After calling this functions, `new_var3` will be the second item and `new_var2` be the third.

#### Popping an item

You can pop from a vector by using `lds_vector_pop` function:
```c
int popped_val;
lds_vector_pop(v, &popped_val);
```

#### Retrieving the length of vector

You can get the length of a vector via `lds_vector_length` function:
```c
size_t length = lds_vector_length(v);
```

#### Getting items via index

You can get items from their indexes with `lds_vector_get` function:
```c
int second_value = lds_deref_int(lds_vector_get(v, 1));
```

#### Extending a vector with another vector

You can extend a vector with another with `lds_vector_extend` function:
```c
lds_vector_extend(v1, v2);
```

Unlike linked lists, you should free `v2` after extending.

#### Reversing a vector
You can reverse a vector with `lds_vector_reverse` function:
```c
lds_vector_reverse(v);
```

#### Reserving some space in vector

If you want to allocate some space in a vector, which can lead to performance increase, you should use `lds_vector_reserve` function:
```c
lds_vector_reserve(v, 10000);
```

Now `v` has capacity of holding 10.000 items, which means it won't do any allocation until 10.000 items are added to vector.

#### Finding the index of items

If you have some data and need to learn the index of item holding this data, you should use `lds_vector_index` function.
```c
int data = 10;
ssize_t index = lds_vector_index(v, &data, sizeof(int));
```

Now `index` will hold the index of item that holds 10.

#### Iterating over the vector

To iterate the vector, you should use `lds_vector_for_each` macro:
```c
void *ptr;
int i = 1;
lds_vector_for_each(v, ptr)
{
	printf("%d. value of vector is '%d'.\n", i, lds_deref_int(ptr));
	i++;
}
```

#### Cloning Vectors

To clone the vector, use `lds_vector_clone` function:
```c
lds_vector* v = lds_create_vector();
lds_vector* cloned = lds_vector_clone(v);
```

Try to avoid clone whenever possible because cloning is an expensive process. It duplicates every element in the source vector and allocates memory for each item. Note that you should free cloned vectors too.

#### Freeing vectors

You can free vectors via `lds_vector_free` function:
```c
lds_vector_free(v);
```

### Linked lists or vectors?

The choice is important, because linked lists are better solution for some problems and a vector being the better solution for another.

The difference relies in the design. Linked lists are consisting of nodes. Each node has pointers inside pointing to the next and previous nodes. This will require allocation every time when adding a node. But operations such as deleting, inserting are faster in linked lists, as it only needs to allocate a new node and modify a few pointers.

On the other hand, vectors have a large memory area. When you add an item, data is written to the remained part. This doesn't require allocation every time. When the memory area ends, it is doubled. But as all the items are side by side, every element has to be moved when an insertion or deletion is done. However, it is much faster than linked lists in adding an element, updating an element and especially accessing an element by index. Because it's `O(1)` in vectors, while it is `O(n)` in linked lists.

|                                              | Linked lists  | Vectors |
|----------------------------------------------|---------------|---------|
| Operations mostly require insertion          |       ✓       |         |
| Operations mostly require deletion           |       ✓       |         |
| Arrays with unknown size at compile time     |               |    ✓    |
| Operations mostly require accessing by index |               |    ✓    |
| Has a known maximum size                     |               |    ✓    |

## Maps
Maps are data structures consisting of key-value pairs. You can access the value if you have the key, but not the opposite.

### Creating maps
You should use `lds_create_map` function in order to create maps.
```c
lds_map *m = lds_create_map();
```

### Adding key-value pairs

You should use `lds_map_add` function to add values.
```c
int key1 = 1;
int value1 = 2;
int key2 = 3;
int value2 = 4;
int key3 = 5;
int value3 = 6;

lds_map_add(m, &key1, sizeof(int), &value1, sizeof(int));
lds_map_add(m, &key2, sizeof(int), &value2, sizeof(int));
lds_map_add(m, &key3, sizeof(int), &value3, sizeof(int));
```

### Accessing values from keys

In order to do that, you should use `lds_map_get` function.
```c
int val1 = lds_deref_int(lds_map_get(m, &key1, sizeof(int)));
int val2 = lds_deref_int(lds_map_get(m, &key2, sizeof(int)));
int val3 = lds_deref_int(lds_map_get(m, &key3, sizeof(int)));
```

### Looping through the map

You should use `lds_map_for_each` for looping through the map.
```c
void* key;
void* value;
int i = 0;

lds_map_for_each(m, key, value)
{
	printf("%d. key: %d\n", i, lds_deref_int(key));
	printf("%d. key: %d\n", i, lds_deref_int(value));
	i++;
}
```

### Freeing the map

You should use `lds_map_free` to free the map.
```c
lds_map_free(m);
```

## Stacks
Stacks are data structures like lists, but is LIFO (Last In First Out). This means you should pop all of the items to get the first pushed item.

### Creating a stack

To create a stack, you call `lds_create_stack`.
```c
lds_stack *s = lds_create_stack();
```

### Pushing values to stack

To push values, which is like adding values to stack, you should call `lds_stack_push` function.
```c
int val1 = 1;
int val2 = 2;
int val3 = 3;
int val4 = 4;

lds_stack_push(s, &val1, sizeof(int));
lds_stack_push(s, &val2, sizeof(int));
lds_stack_push(s, &val3, sizeof(int));
lds_stack_push(s, &val4, sizeof(int));
```

### Popping values from stack

To pop values from stack, you should call `lds_stack_pop` function.
```c
int popped_val1;
int popped_val2;
int popped_val3;
int popped_val4;

lds_stack_pop(s, &popped_val1);
lds_stack_pop(s, &popped_val2);
lds_stack_pop(s, &popped_val3);
lds_stack_pop(s, &popped_val4);
```

### Peeking values from stack

Peeking means checking the value in the top, without popping it. To do that, you should use `lds_stack_peek` function.
```c
int peeked_value = lds_deref_int(lds_stack_peek(s));
```

### Freeing stacks

You can free the stack with `lds_stack_free` function.
```c
lds_stack_free(s);
```

## Queues

Queues are like stacks, but instead queues are FIFO (First In First Out). Which means enqueue function will add the new item to back of the queue instead of the front.

### Creating queues
To create queues, you can call `lds_create_queue` function.
```c
lds_queue *q = lds_create_queue();
```

### Enqueuing items
To enqueue some items, you should call `lds_queue_enqueue` function.
```c
int val1 = 1;
int val2 = 2;
int val3 = 3;

lds_queue_enqueue(q, &val1, sizeof(int));
lds_queue_enqueue(q, &val2, sizeof(int));
lds_queue_enqueue(q, &val3, sizeof(int));
```

### Dequeuing items

You should call `lds_queue_dequeue` function to dequeue items.
```c
int dequeued_val;

lds_queue_dequeue(q, &dequeued_val);
```

### Getting the front item

There is a function called "front" in queues which returns the item that is going to be dequeued in the next call. To call that, you should use `lds_queue_front` function.
```c
int value_to_dequeue = lds_deref_int(lds_queue_front(q));
```

### Freeing queues

To free queues, you should use `lds_queue_free` function.
```c
lds_queue_free(q);
```

## Binary trees

Binary trees are data structures that holds pointers to two instances of binary tree nodes. Each binary tree nodes also holds pointers to another two instances of binary tree nodes, and so on. Actually they can be `NULL` pointer, which means it is the end. An important point is that this is not a binary search tree, which is completely different type of a tree.

### Creating a binary tree
To create a binary tree, you should call the `lds_create_bintree` function.
```c
lds_bintree *b = lds_create_bintree();
```

### Inserting items to left and right of nodes

There are two different functions for inserting items: `lds_bintree_insert_left` and `lds_bintree_insert_right`. Binary trees can have only 2 children, and each creates a specific child.
```c
int val1 = 1;
int val2 = 2;
int val3 = 3;
int val4 = 4;
int val5 = 5;
int val6 = 6;

lds_bintree* left_child = lds_bintree_insert_left(b, &val1, sizeof(int));
lds_bintree* right_child = lds_bintree_insert_left(b, &val2, sizeof(int));
lds_bintree_insert_left(left_child, &val3, sizeof(int));
lds_bintree_insert_right(left_child, &val4, sizeof(int));
lds_bintree_insert_left(right_child, &val5, sizeof(int));
lds_bintree_insert_right(right_child, &val6, sizeof(int));
```

These two functions returns a `lds_bintree *` pointer, so you can save it and don't have to use `lds_bintree_left` and `lds_bintree_right` functions every time.

### Getting the left and right child of a node
If you need to get the left and right children of a node, you can use `lds_bintree_left` and `lds_bintree_right` functions.
```c
lds_bintree *left_node = lds_bintree_left(b);
lds_bintree *right_node = lds_bintree_right(b);
```

### Updating values of nodes

To update values of nodes, you can use `lds_bintree_set` function.
```c
int new_val = 10;
lds_bintree_set(b, &new_val, sizeof(int));
```

This updates the node `b` itself, not a child.

### Getting the value of nodes

If you need the value itself but have the node, you can use the `lds_bintree_get` function.
```c
int data = lds_deref_int(lds_bintree_get(b));
```

### Checking the node has left or right children

You may want to check that node has left or right children. To do that, you can `lds_bintree_has_left` and `lds_bintree_has_right` functions.
```c
int has_node_left_child = lds_bintree_has_left(b);
int has_node_right_child = lds_bintree_has_right(b);
```

### Deleting children nodes

If you need to delete children nodes, you should use `lds_bintree_delete_left` and `lds_bintree_delete_right` functions.
```c
lds_bintree_delete_left(b);
lds_bintree_delete_right(b);
```

These two functions recursively delete the whole sub-tree.

### Traveling over binary tree

libdatastruct supports BFS traversal algorithm for this. Unlike other data structures, it is a function, so you pass a function pointer.
```c
void print_bintree_bfs(lds_bintree *b)
{
	printf("%d ", lds_deref_int(lds_bintree_get(b)));
}

lds_bintree_bfs(b, print_bintree_bfs);
printf("\n");
```

### Freeing binary trees

To free a binary tree, you should use `lds_bintree_free` function.
```c
lds_bintree_free(b);
```

## Tries
Tries (a.k.a prefix trees) are data structures that are specialized for holding strings. Every node holds one character and every sub-tree is a word. 

### Creating a trie

To create a trie, you should use the `lds_create_trie` function.
```c
lds_trie *t = lds_create_trie();
```

### Inserting some words

To insert some words to a trie, you should use the `lds_trie_insert` function.
```c
lds_trie_insert(t, "hi");
lds_trie_insert(t, "hello");
lds_trie_insert(t, "cat");
lds_trie_insert(t, "dog");
lds_trie_insert(t, "and");
lds_trie_insert(t, "ant");
lds_trie_insert(t, "camera");
```

This will result in a trie that has 4 sub trees: H, C, D and A. H has two sub trees, i and e. C has only one sub tree: a. a has two sub trees, t and m. And so on.

### Checking that trie has the value or not

To check that the trie contains the value or not, we should use the `lds_trie_search` function.
```c
int is_hi_in_trie = lds_trie_search(t, "hi");
int is_cat_in_trie = lds_trie_search(t, "cat");
```

### Removing words from a trie

If you need to remove a word from trie, you should call `lds_trie_remove` function.
```c
lds_trie_remove(t, "hi");
```

### Updating words in a trie

To update a word in a trie, you should call `lds_trie_update` function.
```c
lds_trie_remove(t, "camera", "computer");
```

### Freeing the trie

To free a trie, you should call `lds_trie_free` function.
```c
lds_trie_free(t);
```

## Trees

Trees are like binary trees, but trees can have any amount of children. Also trees are more generic.

### Creating trees

To create a tree, you should call `lds_create_tree` function.

```c
lds_tree *t = lds_create_tree();
```

### Inserting items

You can insert items with `lds_tree_add` function.
```c
int val1 = 1;
int val2 = 2;
int val3 = 3;
int val4 = 4;
int val5 = 5;
int val6 = 6;

lds_tree *n1 = lds_tree_add(t, &val1, sizeof(int));
lds_tree *n2 = lds_tree_add(t, &val2, sizeof(int));
lds_tree_add(n1, &val3, sizeof(int));
lds_tree_add(n1, &val4, sizeof(int));
lds_tree_add(n2, &val5, sizeof(int));
lds_tree_add(n2, &val6, sizeof(int));
```

`lds_tree_add` function returns a `lds_tree *` so you can directly pass it to `lds_tree` functions and avoid repeatedly accessing the nth child of a tree.

### Updating values of items

To update the value of items, you should use `lds_tree_set` function.
```c
int new_val = 10;
lds_tree_set(t, &new_val, sizeof(int));
```

### Getting values of nodes

To access the data of a node, you should use `lds_tree_get` function.
```c
int data = lds_tree_get(t);
```

### Getting the child count

To get the child count, you can use the `lds_tree_child_count` function.
```c
size_t child_count = lds_tree_child_count(t);
```

### Getting the nth child

To get the nth child, you should use the `lds_tree_child` function.
```c
lds_tree *n1 = lds_tree_child(t, 0);
```

### Getting the depth of nodes

To get the depth of nodes, you should use the `lds_tree_depth` function.
```c
size_t depth = lds_tree_depth(t);
```

### Getting the LCA of two nodes

To get the LCA (lowest common ancestor) of two nodes, you should use `lds_tree_lca` function.

```c
lds_tree* n = lds_tree_lca(n1, n2);
```

### Looping through the tree

To loop through the tree using BFS algorithm, you can use the `lds_tree_bfs` function.
```c
void print_tree_bfs(lds_tree *t)
{
	printf("%d ", lds_deref_int(lds_tree_get(t))));
}

lds_tree_bfs(t, print_tree_bfs);
```

### Freeing the tree

You should use the `lds_tree_free` function in order to free the tree.
```c
lds_tree_free(t);
```

## Graphs

Graphs are data structures similar to trees, but nodes can point to each other in graphs.

### Creating graphs

You should use `lds_create_graph` function in order to create a graph.

```c
lds_graph *g = lds_create_graph();
```

### Adding nodes
You can use `lds_graph_add` function to add nodes to other nodes.
```c
int val1 = 1;
int val2 = 2;

lds_graph *n1 = lds_graph_add(g, &val1, sizeof(int));
lds_graph *n2 = lds_graph_add(g, &val2, sizeof(int));
```

You can also use `lds_graph_add_weighted`, which creates the link between two nodes as weighted.
```c
int val3 = 3;
lds_graph_add_weighted(g, &val3, sizeof(int), 10);
```

### Changing the data and weight

To change the data and weight, you should use `lds_graph_set` and `lds_graph_set_weight` functions.
```c
int val4 = 4;
lds_graph_set(n1, &val4, sizeof(int));
lds_graph_set_weight(t, 0, 50);
```

The first argument for `lds_graph_set_weight` is the index of link and the second one is the new weight

### Getting the data from nodes

To get the data from a node, you should use `lds_graph_get` function.
```c
int value = lds_deref_int(lds_graph_get(n1));
```

### Getting the weight

To get the weight, you should use `lds_graph_get_weight` function.
```c
int weight = lds_graph_get_weight(g, 1);
```

### Getting the child count of nodes
To get the child count of nodes, you should use `lds_graph_child_count` function.
```c
size_t child_count = lds_graph_child_count(g);
```

### Getting the nth child
To get the nth child, you should use `lds_graph_child` function.
```c
lds_graph *n4 = lds_graph_child(n0, 1);
lds_graph *n5 = lds_graph_child(n1, 1);
```

### Linking two nodes
To link two nodes, you should use `lds_graph_link` function.
```c
lds_graph_link(g, n4);
```

You can also use `lds_graph_link_weighted` if you want to create the link as weighted.
```c
lds_graph_link(g, n5, 100);
```

### Looping the graph

You should use the `lds_graph_bfs` function in order to loop the graph using BFS algorithm.
```c
void print_graph_bfs(lds_graph *g)
{
	printf("%d ", lds_deref_int(lds_graph_get(g)));
}

lds_graph_bfs(g, print_graph_bfs);
```

### Freeing the graph

To free the graph, you should use the `lds_graph_free` function.
```c
lds_graph_free(g);
```

## Strings

Strings are one of the most used data structures in the world. Strings store bytes.

### Creating a string
To create a string, you can use one of `lds_create_string` or `lds_string_from` functions.
```c
lds_string *s1 = lds_create_string();
lds_string *s2 = lds_string_from("Hello, world!");
```

`lds_create_string` returns an empty string object and `lds_string_from` returns a string object with the content "Hello, world!".

### Appending data to strings
To append data to strings, you should use `lds_string_append` function.
```c
lds_string_append(s1, "42");
```

### Appending strings to front of strings
To push strings to front of other strings, we should use `lds_string_push_front` function.
```c
lds_string_push_front(s1, "The meaning of life: ");
```

So the value of string becomes "The meaning of life: 42"

### Getting the data
To get the data, you should use `lds_string_cstr` function.
```c
printf("%s\n", lds_string_cstr(s1));
```

### Getting the length

To get the length, you should use `lds_string_len` function.
```c
size_t length = lds_string_len(s1);
```

### Formatting strings

To format strings, you should use `lds_string_printf` function.
```c
lds_string_printf(s1, "%s are awesome!", "Strings");
```

### Copying strings

To copy down a string to a `lds_string`, you should use `lds_string_copy` function.
```c
lds_string_copy(s1, "A string");
```

### Comparing strings

To compare `lds_string` objects, you need to use `lds_string_compare` function.

```c
int are_strings_same = lds_string_compare(s1, s2);
```

### Finding the indexes of sub strings

To find where does the sub strings start, you should use `lds_string_find` function.
```c
size_t index = lds_string_find(s1, "str");
```

If you only need to check does the string contain a sub string or not, you can use `lds_string_contains` function.
```c
int is_it_containing = lds_string_contains(s1, "str");
```

### Making strings lowercase and uppercase

To make strings lowercase and uppercase, you should use `lds_string_lower` and `lds_string_upper` functions.
```c
lds_string_lower(s1);
lds_string_upper(s1);
```

### Splitting strings

To split strings, you should use `lds_string_split` function add use the vector returned by the function.
```c
lds_vector *splitted = lds_string_split(s1, " ");
lds_string **spart;
int i = 0;

lds_vector_for_each(splitted, spart)
{
	printf("%d. part: %s\n", i, lds_string_cstr(*spart));
	i++;
}
```

You should free `splitted` with `lds_string_split_free` function.

```c
lds_string_split_free(splitted);
```

### Reversing strings
To reverse strings, you should use `lds_string_reverse` function.
```c
lds_string_reverse(s1);
```

### Freeing strings

To free strings, you should use `lds_string_free` function.
```c
lds_string_free(s1);
```
