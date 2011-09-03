#ifndef SDEQUE_H_INCLUDE
#define SDEQUE_H_INCLUDE

struct sdeque {
	int	 *data;  /* int array */
	int	 front;
	int	 back;
	int	 maxsize;
	int	 size;
};

typedef struct sdeque *	 sdeque;

void sdeque_init(sdeque *sq, const int size) __nonnull ((1));
void sdeque_free(sdeque *sq) __nonnull ((1));

void sdeque_test(const sdeque sq);

void sdeque_push_front(sdeque sq, const int value) __nonnull ((1));
void sdeque_push_back(sdeque sq, const int value) __nonnull ((1));

int sdeque_pop_front(sdeque sq) __nonnull ((1));
int sdeque_pop_back(sdeque sq) __nonnull ((1));

#define sdeque_size(s)	  ((s)->size)
#define sdeque_maxsize(s)   ((s)->maxsize)
#define sdeque_empty(s)	 (sdeque_size(s) == 0)
#define sdeque_full(s)	  (sdeque_size(s) >= sdeque_maxsize(s))

#endif /* SDEQUE_H_INCLUDE */
