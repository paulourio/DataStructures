/*
 * AUTOR
 *      Paulo Roberto Urio
 * PROPOSTA
 *      Testar implementação de lista encadeada circular.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ldec.h"

#define TAB         printf("\t");
#define INIT_TEST   int test_count = 0;
#define START_TEST  ldec_clear(&lst); \
                    printf("TEST %d\n", ++test_count);
#define END_TEST    ldec_test(&lst); \
                    TAB ldec_print(&lst);

#define out(...)    printf("\t" __VA_ARGS__)

#define Boolean(nome,valor) out("%s: %s\n", nome, valor? "sim": "não")

#define Section(name)   printf("\n*****************************\n"\
                               "%s\n"\
                               "*****************************\n", name)

__attribute_pure__
static bool numero_par(const int numero) {
    return (!(numero & 1));
}

int main(void) {
    ldec    lst;

    ldec_init(&lst);
    INIT_TEST

    START_TEST
    // null test
    END_TEST

    Section("Testando inserções");

    START_TEST
        ldec_insert_front(&lst, 1);
    END_TEST

    START_TEST
        ldec_insert_front(&lst, 2);
        ldec_test(&lst);
        ldec_insert_front(&lst, 1);
    END_TEST

    START_TEST
        ldec_insert_back(&lst, 0);
    END_TEST

    START_TEST
        ldec_fill(&lst, 15);
    END_TEST

    START_TEST
        ldec_insert_pos(&lst, 0, 0);
    END_TEST

    START_TEST
        ldec_insert_pos(&lst, 185, 1);
    END_TEST

    START_TEST
        ldec_insert_pos(&lst, 1, 2);
    END_TEST

    START_TEST
        ldec_fill(&lst, 15);
        ldec_insert_pos(&lst, 5, 0);
        ldec_insert_pos(&lst, 185, 0);
    END_TEST

    START_TEST
        ldec_fill(&lst, 1);
        ldec_insert_front(&lst, -1);
        ldec_insert_back(&lst, 4);
    END_TEST

    START_TEST
        ldec_insert_pos(&lst, 1, 3);
    END_TEST

    Section("Verificando se está ordenado");

    START_TEST
        ldec_insert_back(&lst, 16);
        TAB ldec_print(&lst);
        Boolean("Ordenado", ldec_sorted(&lst));
        ldec_insert_front(&lst, 800);
        TAB ldec_print(&lst);
        Boolean("Ordenado", ldec_sorted(&lst));
    END_TEST

    START_TEST
        ldec_fill(&lst, 15);
        ldec_insert_back(&lst, 16);
        TAB ldec_print(&lst);
        Boolean("Ordenado", ldec_sorted(&lst));
        ldec_insert_front(&lst, 800);
        TAB ldec_print(&lst);
        Boolean("Ordenado", ldec_sorted(&lst));
    END_TEST

    Section("Remoção de nós - Front");

    START_TEST
        ldec_remove_front(&lst);
    END_TEST

    START_TEST
        ldec_fill(&lst, 5);
        ldec_remove_front(&lst);
    END_TEST

    START_TEST
        ldec_fill(&lst, 2);
        ldec_remove_front(&lst);
        ldec_remove_front(&lst);
        ldec_remove_front(&lst);
    END_TEST

    Section("Remoção de nós - Back");

    START_TEST
        ldec_remove_back(&lst);
    END_TEST

    START_TEST
        ldec_fill(&lst, 5);
        ldec_remove_back(&lst);
    END_TEST

    START_TEST
        ldec_fill(&lst, 2);
        ldec_remove_back(&lst);
        ldec_remove_back(&lst);
        ldec_remove_back(&lst);
    END_TEST

    Section("Remoção de nós - Posição");

    START_TEST
        ldec_remove_pos(&lst, 0);
    END_TEST

    START_TEST
        ldec_remove_pos(&lst, 1);
    END_TEST

    START_TEST
        ldec_fill(&lst, 5);
        ldec_remove_pos(&lst, 0);
    END_TEST

    START_TEST
        ldec_fill(&lst, 5);
        ldec_remove_pos(&lst, 1);
    END_TEST

    START_TEST
        ldec_fill(&lst, 5);
        ldec_remove_pos(&lst, 2);
    END_TEST

    START_TEST
        ldec_fill(&lst, 2);
        ldec_remove_pos(&lst, 6);
        ldec_remove_pos(&lst, 89);
        ldec_remove_pos(&lst, 0);
    END_TEST

    Section("Remoção de nós");

    START_TEST
        ldec_fill(&lst, 5);
        TAB ldec_print(&lst);
        ldec_remove_pos(&lst, 2);
        ldec_remove_back(&lst);
        ldec_remove_front(&lst);
    END_TEST

    START_TEST
        ldec_delete_if(&lst, numero_par);
    END_TEST

    START_TEST
        ldec_fill(&lst, 20);
        ldec_delete_if(&lst, numero_par);
    END_TEST

    START_TEST
        ldec_fill(&lst, 10);
        ldec_insert_pos(&lst, 4, 5);
        ldec_insert_pos(&lst, 4, 5);
        ldec_insert_pos(&lst, 40, 5);
        ldec_insert_pos(&lst, 9, 5);
        TAB ldec_print(&lst);
        ldec_remove_value(&lst, 5);
    END_TEST

    Section("Funções somente-leitura");

    START_TEST
        out("Contagem: %d\n", ldec_count_if(&lst, numero_par));
    END_TEST

    START_TEST
        ldec_fill(&lst, 10);
        out("Contagem: %d\n", ldec_count_if(&lst, numero_par));
    END_TEST

    START_TEST
        ldec_fill(&lst, 3);
        int i;
        for (i=0; i<9; i++)
        	out("%d: %i\n", i, *ldec_get(&lst, i));
    END_TEST

    Section("Testando limite");

    START_TEST
        ldec_setmax(&lst, 3);
        ldec_fill(&lst, 10);
    END_TEST

    START_TEST
        ldec_setmax(&lst, 0);
        ldec_fill(&lst, 10);
    END_TEST

    ldec_free(&lst);
    return (EXIT_SUCCESS);
}
