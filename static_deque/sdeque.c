#include <stdlib.h>
#include <assert.h>
#include "sdeque.h"


void sdeque_test(const sdeque sq)
{
	assert(sq != NULL);
	if (sq != NULL) {
		assert(sq->data != NULL);
		assert(sdeque_maxsize(sq) >= 0);
		if (sdeque_maxsize(sq) > 0) 
			assert(sdeque_size(sq) <= sdeque_maxsize(sq));
		if (sdeque_size(sq) == 0) {
			// assert(sq->size == 0);
			assert(sq->front == -1);
			assert(sq->front == sq->back);
		} else
		if (sdeque_size(sq) == 1) {
			// assert(sq->size == 1);
			assert(sq->front > -1);
			assert(sq->front = sq->back);
		} else {
			assert(sq->size > 1);
			assert(sq->front >= 0);
			assert(sq->front < sdeque_maxsize(sq));
			assert(sq->back >= 0);
			assert(sq->back < sdeque_maxsize(sq));
		}
	}
}


void sdeque_init(sdeque *sq, const int size)
{
	*sq = malloc(sizeof(struct sdeque));
	assert(*sq != NULL);
	(*sq)->data = malloc(sizeof(int) * (size_t) size);
	(*sq)->maxsize = size;
	(*sq)->size = 0;
	(*sq)->back = (*sq)->front = -1;
}


void sdeque_free(sdeque *sq)
{
	assert(*sq != NULL);
	if (*sq != NULL) {
		free((*sq)->data);
		free(*sq);
		*sq = NULL;
	}
}


void sdeque_push_front(sdeque sq, const int value)
{
	if (sdeque_full(sq))
		return;				/* Overflow */
	if (sdeque_empty(sq)) {
		sq->front = sq->back = 0;
	} else {
		if (sq->front == 0)		/* First array position */
			sq->front = sdeque_maxsize(sq);
		sq->front--;
	}
	sq->data[sq->front] = value;
	sq->size++;
}


void sdeque_push_back(sdeque sq, const int value)
{
	if (sdeque_full(sq))
		return;				/* Overflow */
	if (sdeque_empty(sq)) {
		sq->front = sq->back = 0;
	} else {
		if (sq->back == sdeque_maxsize(sq) - 1) {
			sq->back = -1;
		}
		sq->back++;
	}
	sq->data[sq->back] = value;
	sq->size++;
}


int sdeque_pop_front(sdeque sq)
{
	int	toRet;

	if (sdeque_empty(sq))
		return (0);			/* Underflow */
	toRet = sq->data[sq->front];
	sq->front++;
	if (sq->front == sdeque_maxsize(sq))
		sq->front = 0;
	sq->size--;
	if (sdeque_empty(sq))
		sq->front = sq->back = -1;
	return toRet;
}


int sdeque_pop_back(sdeque sq)
{
	int	toRet;

	if (sdeque_empty(sq))
		return 0;			/* Underflow */
	toRet = sq->data[sq->back];
	sq->back--;
	if (sq->back == -1)
		sq->back = sdeque_maxsize(sq) - 1;
	sq->size--;
	if (sdeque_empty(sq))
		sq->front = sq->back = -1;
	return toRet;
}
