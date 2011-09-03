/*
 * AUTHOR
 *	  Paulo Roberto Urio
 * PURPOSE
 *	  Testar a implementação de uma sdeque
 */
#include <stdio.h>
#include <stdlib.h>
#include "sdeque.h"

#define testar  sdeque_test(lst);

int main(void) {
	sdeque   lst;
	int	 i;

	sdeque_init(&lst, 5);
	testar;
	for (i=1; i<=10; i++)
		(void) sdeque_push_back(lst, i);
	while (!sdeque_empty(lst)) {
		printf("%d\n", sdeque_pop_front(lst));
		testar;
	}
	testar;
	for (i=1; i<=10; i++)
		(void) sdeque_push_front(lst, i);
	while (!sdeque_empty(lst)) {
		printf("%d\n", sdeque_pop_back(lst));
		testar;
	}
	sdeque_free(&lst);
	return (EXIT_SUCCESS);
}


