#include <stdio.h>
#include <stdlib.h>
#include <dict.h>
#include <assert.h>
#include <string.h>

int main(void)
{
	dict *d = dict_new();
	
	assert( dict_value(d, "a") == NULL );
	assert( dict_remove(d, "a") == 0 );

	assert( dict_set(d, "a", "01") == 1 );
	assert( strcmp(dict_value(d, "a"), "01") == 0 );

	assert( dict_set(d, "a", "10") == 0 );
	assert( strcmp(dict_value(d, "a"), "10") == 0 );

	assert( dict_remove(d, "b") == 0 );
	assert( dict_remove(d, "a") == 1 );

	assert( dict_value(d, "a") == NULL);

	d = dict_free(d);
	return EXIT_SUCCESS;
}
