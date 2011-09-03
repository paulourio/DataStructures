/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (August 2011)
 */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

static void print_node(const int v)
{
	printf(" %d", v);
}


int main(void)
{
	void    *arvore = NULL;
	int valores[] = {15, 5, 3, 12, 10, 13, 6, 7, 16, 20, 18, 23, 0};
	int i;

	puts("Inserting");
	for (i=0; valores[i] != 0; i++)
	tree_insert(&arvore, valores[i]);

	puts("Printing");
	tree_walk(arvore, print_node, WALK_INORDER);
	puts("");
	printf("Maximum%d\n", tree_max_value(arvore));
	printf("Minimum: %d\n", tree_min_value(arvore));
	printf("Successor of 5: %d\n", tree_successor_value(arvore, 5));
	printf("Successor of 15: %d\n", tree_predecessor_value(arvore, 15));

	puts("Deleting node 16");
	tree_delete(&arvore, 16);
	tree_walk(arvore, print_node, WALK_INORDER);
	puts("");


	puts("Free'ing");
	tree_free(&arvore);
	return EXIT_SUCCESS;
}
