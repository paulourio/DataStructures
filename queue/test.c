/*
 * AUTHOR
 *	  Paulo Roberto Urio
 * PURPOSE
 *	  Testar a implementação de uma queue
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define testar  linked_queue_test(lst);

int main(void)
{
	linked_queue	lst;
	int		i;
	
	lst = linked_queue_new(5);
	testar;
	for (i=1; i<=10; i++)
		(void) linked_queue_enqueue(lst, i);
	while (!linked_queue_empty(lst)) {
		printf("%d\n", linked_queue_dequeue(lst));
		testar;
	}
	testar;
	linked_queue_free(lst);
	lst = NULL;
	return (EXIT_SUCCESS);
}

	
