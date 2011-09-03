/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (March 2011)
 */
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "queue.h"


void linked_queue_test(const linked_queue queue)
{
	assert(queue != NULL);
	if (queue != NULL) {
		assert(queue->limit >= 0);
		if (queue->limit != 0) { /* Check if limit is respected.  */
			assert(queue->count <= queue->limit);
		}
		/* Check queue by its size */
		if (queue->count == 0) {	/* Empty queue. */
			//assert(queue->count == 0);
			assert(queue->front == NULL);
			assert(queue->back == NULL);
		} else
		if (queue->count == 1) {	/* One item in queue. */
			//assert(queue->count == 1);
			assert(queue->front != NULL);
			assert(queue->front == queue->back);
			assert(queue->front->next == NULL);
		} else {			/* Many items in queue. */
			assert(queue->count > 1);
			assert(queue->front != NULL);
			assert(queue->front != queue->back);
			if (queue->count == 2) {
				assert(queue->front->next == queue->back);
				assert(queue->back->next == NULL);
			}
		}
	}
}


linked_queue linked_queue_new(const int limit)
{
	linked_queue	queue;

	queue = malloc(sizeof(struct linked_queue));
	assert(queue != NULL);
	queue->front = NULL;
	queue->back  = NULL;
	queue->limit = limit;
	queue->count = 0;
	return queue;
}


void linked_queue_free(const linked_queue queue)
{
	while (!linked_queue_empty(queue))
		(void) linked_queue_dequeue(queue);
	free(queue);
}


bool linked_queue_enqueue(const linked_queue queue, const int data)
{
	linked_queue_node	*node;

	if (queue == NULL || linked_queue_full(queue))
		return false;
	node = malloc(sizeof(linked_queue_node));
	assert(node != NULL);
	node->data = data;
	node->next = NULL;
	if (linked_queue_empty(queue)) {
		queue->front = queue->back = node;
	} else {
		queue->back->next = node;
		queue->back = node;
	}
	queue->count++;
	return true;
}


int linked_queue_dequeue(const linked_queue queue)
{
	linked_queue_node	*node;
	int			toReturn;

	if (linked_queue_empty(queue))
		return 0;
	node = queue->front;
	queue->front = node->next;
	queue->count--;
	toReturn = node->data;
	free(node);
	if (queue->count == 0)
		queue->front = queue->back = NULL;
	return toReturn;
}
