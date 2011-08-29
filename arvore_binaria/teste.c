#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define	TAM	6

static void print_node(const int v) {
	printf(" %d", v);
}


int main(void) {
	void	*arvore = NULL;
	int	valores[TAM] = {5, 3, 2, 5, 4, 6};
	int	i;

	puts("Adicionando..");
	for (i=0; i<TAM; i++)
		tree_insert(&arvore, valores[i]);

	puts("Imprimindo..");
	tree_walk(arvore, print_node, WALK_INORDER);
	puts("");

	puts("Removendo nó..");
	tree_delete(&arvore, 3);
	tree_walk(arvore, print_node, WALK_INORDER);
	puts("");

	puts("Liberando...");
	tree_free(&arvore);
	return EXIT_SUCCESS;
}
