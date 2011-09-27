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

static int list_compare(const list *l, const void *a, const void *b)
{
	if (l->compare != NULL)
		return l->compare(a, b);
	/* If compare function is not defined, value will be compared as int */
	const int *_a = a, *_b = b;

	if (_a < _b)
		return -1;
	else if (_a > _b)
		return 1;
	return 0;
}

static void *list_remove_node(list *l, struct lnode *node, 
		struct lnode *previous)
{
	void *result = NULL;

	if (previous != NULL)
		previous->next = node->next;
	else
		l->front = node->next;
	result = node->value;
	free(node);
	l->size--;
	return result;
}

/* Try to find a node in the list with the same value of
 * parameter v. This do not mean that v is the same
 * in the linked list.  If parameter compare is null,
 * it will try to use the global compare method. */
void *list_find(list *l, const void *v, f_list_cmp compare)
{
	struct lnode *node = l->front;

	while (node != NULL) {
		int ret;
		
		if (compare != NULL)
			ret = compare(node->value, v);
		else
			ret = list_compare(l, node->value, v);
		if (ret == 0)
			return node->value;
		node = node->next;
	}
	return NULL;
}

void *list_get(list *l, register int index)
{
	struct lnode *node = l->front;

	while (node != NULL && index--)
		node = node->next;
	return node != NULL?  node->value:  NULL;
}

void*list_remove(list *l, const void *value)
{
	struct lnode *prev = NULL, *node = l->front;
	void *result = NULL;

	while (node != NULL) {
		struct lnode *next = node->next;

		if (list_compare(l, node->value, value) == 0) {
			result = list_remove_node(l, node, prev);
			break;
		} else {
			prev = node;
		}
		node = next;
	}
	return result;
}

void *list_remove_front(list *l)
{
	if (l->front == NULL)
		return NULL;
	return list_remove_node(l, l->front, NULL);
}

static struct lnode *list_new_node(void *v)
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
	
static struct lnode *list_insert_after_node(struct lnode *node, void *v)
{
	struct lnode *n = list_new_node(v);

	if (node != NULL) {
		n->next = node->next;
		node->next = n;
	}
	return n;
}

void list_insert_front(list *l, void *v)
{
	struct lnode *n = list_new_node(v);

	n->next = l->front;
	l->front = n;
	l->size++;
}

void list_insert_sorted(list *l, void *v)
{
	struct lnode *n = l->front;

	if (n == NULL || list_compare(l, n->value, v) >= 0) {
		list_insert_front(l, v);
		return;
	}
	while (n->next != NULL) {
		if (list_compare(l, v, n->next->value) < 0)
			break;
		n = n->next;
	}
	list_insert_after_node(n, v);
	l->size++;
}


