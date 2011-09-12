/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (March 2011)
 */
#ifndef LINKED_QUEUE_H_INCLUDE
#define LINKED_QUEUE_H_INCLUDE

#include <stdbool.h>
#include <features.h>

struct linked_queue_node {
	int				data;
	struct linked_queue_node	*next;
};

typedef	struct linked_queue_node	linked_queue_node;


struct linked_queue {
	linked_queue_node	*front;
	linked_queue_node	*back;
	int			limit;
	int			count;
};

typedef struct linked_queue *	linked_queue;


extern void linked_queue_test(const linked_queue queue);

extern linked_queue linked_queue_new(const int limit);
extern void linked_queue_free(const linked_queue queue) __nonnull ((1));

extern bool linked_queue_enqueue(const linked_queue queue, const int data);
extern int linked_queue_dequeue(const linked_queue queue) __nonnull ((1));

#define linked_queue_size(queue)	(queue->count)
#define linked_queue_empty(queue)   (linked_queue_size(queue) == 0)
#define linked_queue_limit(queue)   (queue->limit)
#define linked_queue_full(queue)	\
		(linked_queue_limit(queue) != 0 \
		&& linked_queue_size(queue) == linked_queue_limit(queue))

#define linked_queue_front(queue)	(queue->front)
#define linked_queue_back(queue)	(queue->back)

#define linked_queue_peek(queue)	\
			(linked_queue_empty(queue)? 0: queue->front->data)

#endif /* LINKED_QUEUE_H_INCLUDE */
