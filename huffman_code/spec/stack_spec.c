#include <stdio.h>
#include <stdlib.h>
#include <stack.h>
#include <assert.h>

int main(void)
{
	void *stack = stack_new(3);
	
	assert(stack_isempty(stack) == 1);
	assert(stack_isfull(stack) == 0);
	assert(stack_pop(stack) == EMPTY_STACK);
	stack_push(stack, 'a');
	stack_push(stack, 'b');
	stack_push(stack, 'c');
	assert(stack_isfull(stack) == 1);
	stack_push(stack, 'd'); /* Must do not push this. */
	assert(stack_isempty(stack) == 0);
	assert(stack_pop(stack) == 'c');
	assert(stack_pop(stack) == 'b');
	assert(stack_pop(stack) == 'a');
	assert(stack_pop(stack) == EMPTY_STACK);
	assert(stack_isempty(stack) == 1);
	
	stack = stack_free(stack);
	return EXIT_SUCCESS;
}
