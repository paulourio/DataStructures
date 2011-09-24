/*
 * Author: Paulo Roberto Urio
 * Date: September, 2011
 * Description: Linked list
 */
#include <list.h>

static void list_free_node(const list *l, struct lnode *n)
{
	if (l->free_value != NULL)
		l->free_value(n->value);
	free(n);
}

void list_clear(list *l)
{
	struct lnode *current = l->front, *next;

	while (current != NULL) {
		next = current->next;
		list_free_node(l, current);
		free(current);
		current = next;
	}
	l->front = NULL;
	l->size = 0;
}

list *list_new(void)
{
	list *l = malloc(sizeof(list));
	l->front = NULL;
	l->size = 0;
	l->compare = NULL;
	l->free_value = NULL;
	return l;
}

/* Returns NULL everytime. */
list *list_free(list *l)
{
	list_clear(l);
	free(l);
	return NULL;
}

void list_set_compare_function(list *l, f_list_cmp compare)
{
	l->compare = compare;
}

void list_set_free_value_method(list *l, f_list_free_value method)
{
	l->free_value = method;
}

int list_size(const list *l)
{
	return l->size;
}

int list_isempty(const list *l)
{
	return (list_size(l) == 0);
}

static int list_compare(const list *l, const struct value *a, 
		const struct value *b)
{
	if (l->compare != NULL)
		return l->compare(a, b);
	/* If compare function is not defined, value will be compared as int */
	int *_a = (void *) a, *_b = (void *) b;

	if (_a < _b)
		return -1;
	else if (_a > _b)
		return 1;
	return 0;
}

static struct value *list_remove_node(list *l, struct lnode *node, 
		struct lnode *previous)
{
	struct value *result = NULL;

	if (previous != NULL)
		previous->next = node->next;
	else
		l->front = node->next;
	result = node->value;
	free(node);
	l->size--;
	return result;
}

struct value *list_remove(list *l, const struct value *value)
{
	struct lnode *prev = NULL, *node = l->front;
	struct value *result = NULL;

	while (node != NULL) {
		struct lnode *next = node->next;

		if (list_compare(l, node->value, value) == 0)
			result = list_remove_node(l, node, prev);
		else
			prev = node;
		node = next;
	}
	return result;
}

struct value *list_remove_front(list *l)
{
	if (l->front == NULL)
		return NULL;
	return list_remove_node(l, l->front, NULL);
}

static struct lnode *list_new_node(struct value *v)
{
	struct lnode *new_node;

	new_node = malloc(sizeof(struct lnode));
	if (new_node == NULL) {
		fprintf(stderr, "Can't allocate memory to linked list node.\n");
		exit(1);
	}
	new_node->value = v;
	new_node->next = NULL;  
	return new_node;
}
	
static struct lnode *list_insert_after_node(struct lnode *node, 
		struct value *v)
{
	struct lnode *n = list_new_node(v);

	if (node != NULL)
		node->next = n;
	return n;
}

void list_insert_front(list *l, struct value *v)
{
	struct lnode *n = list_new_node(v);

	n->next = l->front;
	l->front = n;
	l->size++;
}

void list_insert_sorted(list *l, struct value *v)
{
	struct lnode *n = l->front;

	if (n == NULL || list_compare(l, n->value, v) >= 0) {
		list_insert_front(l, v);
		return;
	}
	while (n->next != NULL) {
		if (list_compare(l, n->value, v) >= 0)
			break;
		n = n->next;
	}
	list_insert_after_node(n, v);
	l->size++;
}


