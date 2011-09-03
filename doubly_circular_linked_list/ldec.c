#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include "ldec.h"


void ldec_test(const ldec *p_lst)
{
	ldec		lst = *p_lst;
	ldec_node	*front, *back;

	assert(lst != NULL);
	if (lst != NULL) {
		if (ldec_size(lst) == 0 || ldec_front(lst) == NULL) {
			assert(ldec_size(lst) == 0);
			assert(ldec_front(lst) == NULL);
		} else {
			assert(ldec_size(lst) > 0);
			front = ldec_front(lst);
			back = ldec_back(lst);
			assert(front != NULL);
			assert(front == front->next->prev);
			assert(front == back->next);
		}
	}
}


void ldec_init(ldec *lst)
{
	*lst = malloc(sizeof(ldec_t));
	assert(*lst != NULL);
	(*lst)->front = NULL;
	(*lst)->size = 0;
}


void ldec_free(ldec *lst)
{
	ldec_clear(lst);
	free(*lst);
	*lst = NULL;
}


void ldec_clear(ldec *lst)
{
	ldec_node   *node;

	if (ldec_empty(*lst))
		return;
	node = ldec_front(*lst);
	while (ldec_size(*lst))
		ldec_remove_front(lst);
	ldec_front(*lst) = NULL;
	ldec_size(*lst) = 0;
}


void ldec_print(const ldec *lst)
{
	ldec_node	*node;
	int		 len;

	if (ldec_empty(*lst)) {
		puts("(empty)");
		return;
	}
	node = ldec_front(*lst);
	len = ldec_size(*lst);
	printf("[");
	while (len--) {
		if (node != ldec_front(*lst))
			printf(", ");
		printf("%i", node->value);
		node = node->next;
	};
	puts("]");
}


__always_inline
static inline void *ldec_insert_after_node(ldec_node *node, const int value)
{
	ldec_node   *new_node;

	new_node = malloc(sizeof(ldec_node));
	assert(new_node != NULL);
	new_node->value = value;
	if (node != NULL) {
		/* Update next node */
		new_node->next = node->next;
		node->next->prev = new_node;
		/* Update previous node */
		node->next = new_node;
		new_node->prev = node;
	} else {
		new_node->next = new_node->prev = new_node;
	}
	return (new_node);
}


void ldec_insert_front(register ldec *lst, const int value)
{
	ldec_node	*new_node, *front = ldec_front(*lst);

	if (ldec_full(*lst))
		return;
	new_node = ldec_insert_after_node(front? front->prev: NULL, value);
	ldec_size(*lst)++;
	ldec_front(*lst) = new_node;
}


void ldec_insert_back(register ldec *lst, const int value)
{
	if (ldec_full(*lst))
		return;
	if (ldec_front(*lst) == NULL) {
		ldec_insert_front(lst, value);
		return;
	}
	(void) ldec_insert_after_node(ldec_back(*lst), value);
	ldec_size(*lst)++;
}


void ldec_insert_pos(ldec *lst, int pos, const int value)
{
	ldec_node	*node;

	if (ldec_full(*lst))
		return;
	if (ldec_front(*lst) == NULL || pos == 0) {
		ldec_insert_front(lst, value);
		return;
	}
	node = ldec_front(*lst);
	while (--pos)
		node = node->next;
	ldec_insert_after_node(node, value);
	ldec_size(*lst)++;
}


void ldec_fill(ldec *lst, const int items)
{
	int	i;

	for (i = 0; i < items; i++)
		ldec_insert_front(lst, (items - i));
}


bool ldec_sorted(const ldec *lst)
{
	ldec_node	*node;
	int		size;

	if (ldec_empty(*lst))
		return true;
	size = ldec_size(*lst);
	node = ldec_front(*lst);
	while (--size && (node = node->next))
		if (node->prev->value > node->value)
			return false;
	return true;
}


static void ldec_remove_node(ldec *lst, ldec_node *node)
{
	ldec_node	*prev = node->prev;

	if (prev == node) {			/* There is just one item */
		ldec_front(*lst) = NULL;
	} else {
		prev->next = node->next;
		node->next->prev = prev;
		if (node == ldec_front(*lst))  /* Update front pointer */
			ldec_front(*lst) = node->next;
	}
	free(node);
	ldec_size(*lst)--;
}


void ldec_remove_front(ldec *lst)
{
	if (ldec_empty(*lst))
		return;
	ldec_remove_node(lst, ldec_front(*lst));
}


void ldec_remove_back(ldec *lst)
{
	if (ldec_empty(*lst))
		return;
	ldec_remove_node(lst, ldec_back(*lst));
}


int ldec_pop_back(ldec *lst)
{
	int	 toReturn;

	if (ldec_empty(*lst))
		return 0;
	toReturn = ldec_back(*lst)->value;
	ldec_remove_back(lst);
	return toReturn;
}


void ldec_remove_pos(ldec *lst, int pos)
{
	ldec_node	*node = ldec_front(*lst);

	if (ldec_empty(*lst))
		return;
	while (pos--)
		node = node->next;
	ldec_remove_node(lst, node);
}


int ldec_delete_if(ldec *lst, const f_lst_cmp_node fcmp)
{
	ldec_node	*next, *node = ldec_front(*lst);
	int		count = 0, size = ldec_size(*lst);

	if (ldec_empty(*lst))
		return 0;
	while (size--) {
		next = node->next;
		if (fcmp(node->value)) {
			ldec_remove_node(lst, node);
			count++;
		}
		node = next;
	}
	return count;
}


int ldec_remove_value(ldec *lst, const int value)
{

	bool equals(const int number) {
		return (number == value);
	}

	return ldec_delete_if(lst, equals);
}


int ldec_count_if(ldec *lst, const f_lst_cmp_node fcmp)
{
	ldec_node	*node = ldec_front(*lst);
	int		result = 0, size = ldec_size(*lst);

	if (ldec_empty(*lst))
		return 0;
	while (size--) {
		if (fcmp(node->value))
			result++;
		node = node->next;
	}
	return result;
}


int *ldec_get(register ldec *lst, register int index)
{
	ldec_node	*node = ldec_front(*lst);

	if (ldec_empty(*lst))
		return NULL;
	while (index--)
		node = node->next;
	return &node->value;
}


int ldec_back_value(register ldec *lst) {
	if (ldec_empty(*lst))
		return 0;
	return ldec_back(*lst)->value;
}


int ldec_front_value(register ldec *lst) {
	if (ldec_empty(*lst))
		return 0;
	return ldec_front(*lst)->value;
}
