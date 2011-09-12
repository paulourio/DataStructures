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
#include "avl.h"

static void print_node(const int v)
{
	printf(" %d", v);
}


int main(void)
{
	void    *arvore = NULL;
	//int valores[] = {7, 4, 3, 2, 6, 11, 9, 18, 14, 12, 17, 19, 22, 20, 0};
	//int valores[] = {8, 4, 10, 2, 6, 5, 0};
	//int valores[] = {10, 20, 30, 5, 15, 2, 0};
	//int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	//		-1, -2, -3, -4, -5, -6, -7, -8, 15, 14, 19, 
	//		21, 36, 32, 38, 50, -59, 35, 0};
	//int valores[] = {5, 1, 7, -3, 2, 6, -1, -2, 0};
	int valores[] = {9, 4, 11, 1, 7, 10, 3, 2, 0};
	//int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
	int i;

	for (i=0; valores[i] != 0; i++) {
		debug("Inserting %d \n", valores[i]);
		tree_insert(&arvore, valores[i]);

		tree_walk(arvore, print_node, WALK_PREORDER);
		printf(" . ");		
	}

	/*for (i-- ; i >= 0; i--) {
		debug("Remove %d \n", valores[i]);
		tree_delete(&arvore, valores[i]);
		
		tree_walk(arvore, print_node, WALK_PREORDER);
		printf(" . ");
	}*/
	
	printf("\n");
	tree_free(&arvore);
	return EXIT_SUCCESS;
}
