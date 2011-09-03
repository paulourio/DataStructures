/*
 * AUTHOR
 *      Paulo Roberto Urio
 * PURPOSE
 *      Testar a implementação de uma Pilha.
 */
#include <stdio.h>
#include <stdlib.h>
#include "sstack.h"

#define out(...)    printf(__VA_ARGS__)
#define topo        out("Topo: %d\n", sstack_top(&st))

int main(void) {
    sstack  st;
    int     i;

    sstack_init(&st, 5);
    topo;

    for (i = 1; i < 10; i++) {
        sstack_push(&st, i);
        topo;
    }

    while (!sstack_isempty(st))
        out("POP: %i\n", sstack_pop(&st));

    topo;
    sstack_free(&st);
    //st = NULL;
    return (EXIT_SUCCESS);
}

