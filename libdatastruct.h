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

linkedlist *create_linkedlist(void);
void linkedlist_add(linkedlist *, void *, size_t);
int linkedlist_length(linkedlist *);
void *linkedlist_get(linkedlist *, int);
void linkedlist_delete(linkedlist *, int);
void linkedlist_update(linkedlist *, int, void *, size_t);
void linkedlist_insert(linkedlist *, void *, size_t, int);
void linkedlist_free(linkedlist *);
