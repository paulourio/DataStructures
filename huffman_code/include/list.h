#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

struct value {
	unsigned char chr;
	int count;
};

struct lnode {
	struct value *value;
	struct lnode *next;
};

/* Function to compare two nodes. */
typedef int (*f_list_cmp)(const struct value*, const struct value *);

typedef void (*f_list_free_value)(const struct value *);


typedef struct {
	struct lnode *front;
	int size;
	f_list_cmp compare;
	f_list_free_value free_value;
} list;

extern void list_clear(list *l);
extern list *list_new(void);
extern list *list_free(list *l);
extern void list_set_compare_function(list *l, f_list_cmp compare);
extern void list_set_free_value_method(list *l, f_list_free_value method);
extern int list_size(const list *l);
extern int list_isempty(const list *l);
extern struct value *list_remove(list *l, const struct value *value);
extern struct value *list_remove_front(list *l);
extern void list_insert_front(list *l, struct value *v);
extern void list_insert_sorted(list *l, struct value *v);

#endif
