#include <stack.h>
#include <assert.h>

void *stack_new(const int size)
{
	struct stack *stack;

	stack = malloc(sizeof(struct stack));
	if (stack == NULL) {
		fprintf(stderr, "Can't allocate new stack.\n");
		exit(1);
	}
	assert(size > 0);
	stack->data = malloc(sizeof(char) * (size_t) size);
	if (stack->data == NULL) {
		fprintf(stderr, "No memory for stack of size %d.\n", size);
		free(stack);
		exit(1);
	}
	stack->top = EMPTY_STACK;
	stack->size = size;
	return stack;
}

void *stack_free(void *pstack)
{
	struct stack *stack = pstack;

	if (stack == NULL)
		return NULL;
	free(stack->data);
	free(stack);
	return NULL;
}

void stack_push(void *pstack, const int data)
{
	struct stack *stack = pstack;

	if (stack_isfull(stack))
		return;
	stack->data[++stack->top] = (char) data;
}

char stack_pop(void *pstack)
{
	struct stack *stack = pstack;

	if (stack_isempty(stack))
		return EMPTY_STACK;
	return stack->data[stack->top--];
}
