#ifndef SSTACK_H_INCLUDED
#define SSTACK_H_INCLUDED

#include <features.h>

struct sstack {
	int	 *data;	  /* int array */
	int	 top;
	int	 size;
};

typedef struct sstack *	 sstack;


extern void sstack_init(sstack *st, const int size) __nonnull ((1));
extern void sstack_free(sstack *st) __nonnull ((1));

extern void sstack_test(sstack *st) __nonnull ((1));

#define sstack_size(s)	  ((s)->size)
#define sstack_isempty(s)   ((s)->top == -1)
#define sstack_top(s)	   (!sstack_isempty(*s)? (*s)->data[(*s)->top]: 0)
#define sstack_full(s)	  ((s)->top == sstack_size(s) - 1)

extern void sstack_push(sstack *st, const int data) __nonnull ((1));
extern int sstack_pop(sstack *st) __nonnull ((1));

#endif /* SSTACK_H_INCLUDED */
