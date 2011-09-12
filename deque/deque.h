#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <stdbool.h>
#include <features.h>

struct deque_node {
	int			data;
	struct deque_node	*next;
};

typedef struct deque_node   deque_node;


struct deque {
	deque_node	*front;
	deque_node	*back;
	int		limit;
	int		count;
};

typedef struct deque *  deque;

#define deque_size(dq)		  (dq->count)
#define deque_maxsize(dq)	  (dq->limit)
#define deque_isempty(dq)	  (deque_size(dq) == 0)
#define deque_isfull(dq)		\
				((deque_maxsize(dq) > 0) && \
				(deque_size(dq) >= deque_maxsize(dq)))
#define deque_back_value(dq)	(deque_isempty(dq)? 0: dq->back->data)
#define deque_front_value(dq)   (deque_isempty(dq)? 0: dq->front->data)

extern deque deque_new(const int limit);   // 0 = No limit
extern void deque_free(const deque dq);
extern void deque_test(const deque dq);

extern bool deque_push_front(const deque dq, const int data) __nonnull ((1));
extern bool deque_push_back(const deque dq, const int data) __nonnull ((1));
extern int deque_pop_front(const deque dq) __wur __nonnull ((1));
extern int deque_pop_back(const deque dq) __wur __nonnull ((1));

#endif /* DEQUE_H_INCLUDED */
