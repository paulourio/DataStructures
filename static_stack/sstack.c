#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "sstack.h"


void sstack_test(sstack *st)
{
	assert(*st != NULL);
	assert((*st)->data != NULL);
	assert((*st)->top <= (*st)->size);
}


void sstack_init(sstack *st, const int size)
{
	*st = malloc(sizeof(struct sstack));
	assert(st != NULL);
	(*st)->data = malloc(sizeof(int) * (size_t) size);
	assert((*st)->data != NULL);
	(*st)->top = -1;
	(*st)->size = size;
}


void sstack_free(sstack *st)
{
	if (*st == NULL)
		return;
	free((*st)->data);
	free(*st);
	*st = NULL;
}


void sstack_push(sstack *st, const int data)
{
	if (sstack_full(*st))
		return;
	(*st)->data[++(*st)->top] = data;
}


int sstack_pop(sstack *st)
{
	if (sstack_isempty(*st))
		return (0);
	return (*st)->data[(*st)->top--];
}
