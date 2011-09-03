/*
 * AUTHOR
 *	  Paulo Roberto Urio
 * PURPOSE
 *	  Testar a implementação de uma Pilha.
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define out(...)	printf(__VA_ARGS__)
#define topo		out("Topo: %d\n", stack_top(st))

int main(void) {
	stack   st;
	int	 i;
	
	st = stack_new();
	topo;
	
	for (i = 1; i < 10; i++) {
		stack_push(st, i);		
		topo;
	}
	
	while (!stack_isempty(st))
		out("POP: %i\n", stack_pop(st));

	topo;
	stack_free(st);
	//st = NULL;
	return (EXIT_SUCCESS);
}

