#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"


void deque_test(const deque dq)
{
	assert(dq != NULL);
	if (dq != NULL) {
		assert(deque_maxsize(dq) >= 0);
		if (deque_maxsize(dq) != 0) { /* Check if limit is respected */
			assert(deque_size(dq) <= deque_maxsize(dq));
		}
		/* Check deque by its size */
		if (deque_size(dq) == 0) {	/* Empty dequeue. */
			//assert(dq->count == 0);
			assert(dq->front == NULL);
			assert(dq->back == NULL);
		} else
		if (deque_size(dq) == 1) {	/* One item in dequeue. */
			//assert(dq->count == 1);
			assert(dq->front != NULL);
			assert(dq->front == dq->back);
			assert(dq->front->next == NULL);
		} else {			/* Many items in dequeue. */
			assert(dq->count > 1);
			assert(dq->front != NULL);
			assert(dq->front != dq->back);
			if (deque_size(dq) == 2) {
				assert(dq->front->next == dq->back);
				assert(dq->back->next == NULL);
			}
		}
	}
}


deque deque_new(const int limit)
{
	deque   dq;

	dq = malloc(sizeof(struct deque));
	assert(dq != NULL);
	dq->front = NULL;
	dq->back = NULL;
	dq->limit = limit;
	dq->count = 0;
	return dq;
}


void deque_free(const deque dq)
{
	while (!deque_isempty(dq))
		(void) deque_pop_front(dq);
	free(dq);
}


#define create_node(dq, nd, dt) {		\
	assert(dq != NULL);			\
	if (dq == NULL)				\
		return (false);			\
	if (deque_isfull(dq))			\
		return (false);			\
	nd = malloc(sizeof(struct deque_node));	\
	assert(nd != NULL);			\
	if (nd == NULL)				\
		return (false);			\
	nd->data = dt; }

bool deque_push_front(const deque dq, const int data)
{
	deque_node  *node;

	create_node(dq, node, data);
	if (deque_isempty(dq)) {
		dq->front = node;
		dq->back = node;
	} else {
		node->next = dq->front;
		dq->front = (struct deque_node *) node;
	}
	dq->count++;
	return true;
}


bool deque_push_back(const deque dq, const int data)
{
	deque_node  *node;

	create_node(dq, node, data);
	if (deque_isempty(dq)) {
		dq->front = node;
		dq->back = node;
	} else {
		node->next = NULL;
		dq->back->next = (struct deque_node *) node;
		dq->back = node;
	}
	dq->count++;
	return true;
}
#undef create_node


int deque_pop_front(const deque dq) 
{
	deque_node	*node;
	int		toRet;

	if (deque_isempty(dq))	  /* underflow */
		return 0;
	node = dq->front;
	toRet = deque_front_value(dq);
	dq->front = node->next;
	dq->count--;
	if (dq->front == NULL)
		dq->back = NULL;
	free(node);
	return toRet;
}


int deque_pop_back(const deque dq)
{
	deque_node	*current, *prev = NULL;
	int		toRet;

	if (deque_isempty(dq))	  /* underflow */
		return 0;
	current = dq->front;
	while (current->next)	   /* Get last node */
		current = (prev = current)->next;
	toRet = current->data;
	if (prev != NULL)
		prev->next = NULL;
	dq->back = prev;
	dq->count--;
	if (deque_isempty(dq))
		dq->front = dq->back = NULL;
	free(current);
	return toRet;
}
