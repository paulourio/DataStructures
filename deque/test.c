/*
 * AUTHOR
 *	  Paulo Roberto Urio
 * PURPOSE
 *	  Testar a implementação de uma deque
 */
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

#define testar  deque_test(lst);

int main(void) {
	deque 	lst;
	int	i;

	lst = deque_new(5);
	testar;
	for (i=1; i<=10; i++)
		(void) deque_push_back(lst, i);
	while (!deque_isempty(lst)) {
		printf("%d\n", deque_pop_front(lst));
		testar;
	}
	testar;
	for (i=1; i<=10; i++)
		(void) deque_push_front(lst, i);
	while (!deque_isempty(lst)) {
		printf("%d\n", deque_pop_back(lst));
		testar;
	}
	deque_free(lst);
	lst = NULL;
	return (EXIT_SUCCESS);
}


