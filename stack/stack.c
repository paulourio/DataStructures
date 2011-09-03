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
#include "stack.h"


stack stack_new(void)
{
	stack	st;

	st = malloc(sizeof(struct stack));
	assert(st != NULL);
	st->top = NULL;
	return st;
}


void stack_free(stack s)
{
	while (!stack_isempty(s))
		(void) stack_pop(s);
	free(s);
}


void stack_push(const stack s, const int data)
{
	struct st_node	*node;

	node = malloc(sizeof(struct st_node));
	assert(node != NULL);
	node->data = data;
	node->next = s->top;
	s->top = node;
}


int stack_pop(const stack s)
{
	int	toRet;
	st_node	*Top;

	if (stack_isempty(s))	/* underflow */
		return 0;
	Top = s->top;
	toRet = Top->data;
	s->top = Top->next;
	free(Top);
	return toRet;
}
