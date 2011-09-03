#ifndef INCLUDE_DSTACK_H
#define INCLUDE_DSTACK_H

#include <stddef.h>
#include <features.h>

struct dstack {
	int	*array;	 	/* Array for the two stacks. */
	int	left_top;	/* Left stack */
	int	right_top;	/* Right stack */
	size_t	size;		/* Array length */
};

typedef struct dstack *	 dstack;

void dstack_init(dstack *ds, const size_t size) __nonnull ((1));
void dstack_free(dstack *ds) __nonnull ((1));

void dstack_test(const dstack ds);

void dstack_left_push(const dstack ds, const int value) __nonnull ((1));
void dstack_right_push(const dstack ds, const int value) __nonnull ((1));

int dstack_left_pop(const dstack ds) __nonnull ((1));
int dstack_right_pop(const dstack ds) __nonnull ((1));

#define dstack_left_isempty(s)  ((s)->left_top == -1)
#define dstack_left_top(s)	  (!dstack_left_isempty(s)\
				? (s)->array[(s)->left_top]: 0)

#define dstack_isfull(s)		((s)->left_top == (s)->right_top - 1)
#define dstack_left_isfull(s)   dstack_isfull(s)
#define dstack_right_isfull(s)  dstack_isfull(s)

#define dstack_right_isempty(s) ((s)->right_top == (int) (s)->size)
#define dstack_right_top(s)	 (!dstack_right_isempty(s)\
				? (s)->array[(s)->right_top]: 0)

#endif  /* INCLUDE_DSTACK_H */
