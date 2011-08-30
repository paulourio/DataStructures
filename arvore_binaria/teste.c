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

    puts("Adicionando..");
    for (i=0; valores[i] != 0; i++)
        tree_insert(&arvore, valores[i]);

    puts("Imprimindo..");
    tree_walk(arvore, print_node, WALK_INORDER);
    puts("");
    printf("Maior: %d\n", tree_max_value(arvore));
    printf("Menor: %d\n", tree_min_value(arvore));
    printf("Sucessor de 5: %d\n", tree_successor_value(arvore, 5));
    printf("Sucessor de 15: %d\n", tree_predecessor_value(arvore, 15));

    puts("Removendo nó..");
    tree_delete(&arvore, 16);
    tree_walk(arvore, print_node, WALK_INORDER);
    puts("");


    puts("Liberando...");
    tree_free(&arvore);
    return EXIT_SUCCESS;
}
