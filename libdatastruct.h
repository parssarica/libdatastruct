/*
Pars SARICA <pars@parssarica.com>
*/

typedef struct _linkedlist
{
    void *data;
    int stored_in_heap;
    struct _linkedlist *prev;
    struct _linkedlist *next;
} linkedlist;

linkedlist *create_linkedlist(void);
void linkedlist_add(linkedlist *, void *);
void linkedlist_add_int(linkedlist *, int);
void linkedlist_add_string(linkedlist *, char *);
void linkedlist_add_double(linkedlist *, double);
int linkedlist_length(linkedlist *);
void *linkedlist_get(linkedlist *, int);
void linkedlist_delete(linkedlist *, int);
