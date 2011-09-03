/*
 * AUTOR
 *      Paulo Roberto Urio
 * PROPOSTA
 *      Testar implementação de lista encadeada circular.
 */
#include <stdio.h>
#include <stdlib.h>
#include "lec.h"

#define TAB         printf("\t");
#define INIT_TEST   int test_count = 0;
#define START_TEST  lec_clear(&lst); \
                    printf("TEST %d\n", ++test_count);
#define END_TEST    lec_test(&lst); \
                    TAB lec_print(&lst);

#define out(...)    printf("\t" __VA_ARGS__)

#define Boolean(nome,valor) out("%s: %s\n", nome, valor? "sim": "não")

#define Section(name)   printf("\n*****************************\n"\
                               "%s\n"\
                               "*****************************\n", name)

//__attribute_pure__
//static bool multiplo_5(const int numero) {
//    return (numero % 5 == 0);
//}

__attribute_pure__
static bool numero_par(const int numero) {
    return (!(numero & 1));
}

int main(void) {
    lec     lst;

    INIT_TEST
    lec_init(&lst);


    START_TEST
    // Null test
    END_TEST

    Section("Testando inserções");

    START_TEST
        lec_insert_front(&lst, 3);
        lec_insert_front(&lst, 2);
        lec_insert_front(&lst, 1);
        lec_insert_back(&lst, 5);
        lec_insert_back(&lst, 6);
    END_TEST

    START_TEST
        lec_insert_back(&lst, 1);
        lec_insert_back(&lst, 3);
    END_TEST

    START_TEST
        lec_clear(&lst);
        lec_insert_front(&lst, 1);
        lec_insert_back(&lst, 3);
        lec_insert_pos(&lst, 1, 2);
    END_TEST

    START_TEST
        lec_insert_pos(&lst, 0, 4);
    END_TEST

    START_TEST
        lec_insert_pos(&lst, 100, 4);
        lec_insert_back(&lst, 10);
        lec_insert_front(&lst, 6);
    END_TEST

    Section("Testando verificação de ordenação");

    START_TEST
        lec_fill(&lst, 10);
        Boolean("Ordenado", lec_sorted(&lst));
        lec_insert_front(&lst, 2);
        Boolean("Ordenado", lec_sorted(&lst));
    END_TEST

    Section("Testando métodos de remoção");

    START_TEST
        lec_fill(&lst, 3);
        lec_remove_front(&lst);
        TAB lec_print(&lst);
        lec_remove_front(&lst);
        lec_remove_front(&lst);
        lec_remove_front(&lst);
        lec_insert_front(&lst, 0);
    END_TEST

    START_TEST
        lec_fill(&lst, 2);
        lec_remove_pos(&lst, 0);
    END_TEST

    START_TEST
        lec_fill(&lst, 5);
        while (!lec_isempty(&lst)) {
            lec_remove_pos(&lst, 2);
            if (lec_isempty(&lst))
                break;
            TAB lec_print(&lst);
        }
    END_TEST

    START_TEST
        lec_fill(&lst, 5);
        lec_remove_back(&lst);
    END_TEST

    START_TEST
        lec_fill(&lst, 5);
        lec_remove_back(&lst);
    END_TEST

    START_TEST
        lec_fill(&lst, 1);
        lec_remove_back(&lst);
        lec_remove_back(&lst);
    END_TEST

    START_TEST
        lec_fill(&lst, 3);
        lec_remove_front(&lst);
        lec_remove_back(&lst);
    END_TEST

    START_TEST
        lec_fill(&lst, 30);
        lec_delete_if(&lst, numero_par);
    END_TEST

    START_TEST
        lec_fill(&lst, 10);
        lec_insert_pos(&lst, 3, 4);
        lec_insert_pos(&lst, 7, 4);
        lec_insert_pos(&lst, 9, 4);
        TAB lec_print(&lst);
        lec_remove(&lst, 4);
    END_TEST

    Section("Testando função de contagem");

    START_TEST
        lec_fill(&lst, 30);
        out("Contagem: %i\n", lec_count_if(&lst, numero_par));
    END_TEST

    Section("Testando métodos de leitura");

    START_TEST
        lec_fill(&lst, 4);
        int i;
        for (i=0;i<7;i++)
            out("%d: %d\n", i, *lec_get(&lst, i));
    END_TEST

    lec_clear(&lst);
    return (EXIT_SUCCESS);
}
