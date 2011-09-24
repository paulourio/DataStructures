#include <stdio.h>
#include <stdlib.h>
#include <list.h>

static struct value *new_value(int v)
{
	struct value *new = malloc(sizeof(struct value));

	new->count = v;
	return new;
}

static int comp_data(const struct value *a, const struct value *b)
{
	int _b = b->count, _a = a->count;

	if (_a > _b)
		return 1;
	else if (_b > _a)
		return -1;
	return 0;
}

int main(void)
{
	list *test = list_new(NULL);
	list_set_compare_function(test, comp_data);

	char cmd;
	int read;
	while ((scanf("%c ", &cmd) == 1)) {
		switch (cmd) {
		case 'f': /* Insert at front */
			if (scanf("%d ", &read) == 1)
				list_insert_front(test, new_value(read));
			break;
		case 's': /* Insert sorted */
			if (scanf("%d ", &read) == 1) 
				list_insert_sorted(test, new_value(read));
			break;
		case 'd': /* Remove item */
			if (scanf("%d ", &read) == 1) {
				struct value v = { .count = read } ;
				struct value *r = list_remove(test, &v);
				if (r != NULL)
					free(r);
			}
			break;
		case 'x': /* Remove front item */ {
			struct value *r = list_remove_front(test);
			if (r != NULL)
				free(r);
			break;
		}
		case 'p': /* Print values */
			while (!list_isempty(test)) {
				struct value *n = list_remove_front(test);

				printf("%d", n->count);
				free(n);
				if (!list_isempty(test))
					printf(" ");
			}
			printf("\n");
			break;
		case 'e': /* End of test */
			(void) list_free(test);
			test = list_new(NULL);
			list_set_compare_function(test, comp_data);
			break;
		default:
			printf("I do not understand '%c'\n", cmd);
		}
	}
	test = list_free(test);
	return EXIT_SUCCESS;
}
