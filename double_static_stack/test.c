#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {
	dstack	s;
	
	dstack_init(&s, (size_t) 10);
	/* ... */
	dstack_free(&s);
	return EXIT_SUCCESS;
}
