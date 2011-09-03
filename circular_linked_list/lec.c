/*
 *  Author: Paulo Roberto Urio
 *  Date: 7 de Maio de 2011
 *  Description: Circular linked list source-code.
 *
 *  Implementation note:
 *      The lec stores the last node pointer, to have a lower
 *      time of execution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <features.h>
#include "lec.h"

#define	MALLOC(type,size)	(type *) malloc(size * sizeof(type))
#define TALLOC(type)		MALLOC(type,1)

#define create_node(node,next_node) \
    {                               \
        node = TALLOC(lec_node);    \
        assert(node != NULL);       \
        node->value = value;        \
        node->next = next_node;     \
    }


__always_inline
inline void lec_init(lec *lst) {
    *lst = NULL;
}


__always_inline
inline void lec_test(const lec *lst) {
    if (*lst != NULL)
        assert((*lst)->next != NULL);
}


void lec_print(const lec *lst) {
    lec     node, first;

    if (*lst == NULL) {
        puts("(empty)");
        return;
    }
    node = first = (*lst)->next;
    printf("[");
    do {
        if (node != first)
            printf(", ");
        printf("%i", node->value);
        node = node->next;
    } while (node != first);
    puts("]");
}


void lec_clear(lec *lst) {
    register lec    current;
    lec             last, next;

    last = current = *lst;
    while (current) {
        next = current->next;
        free(current);
        current = next;
        if (current == last)
            break;
    }
    *lst = NULL;
}


__always_inline
inline bool lec_isempty(const lec *lst) {
    return (*lst == NULL);
}


int *lec_get(register lec *lst, register int index) {
    lec     node = *lst;

    if (node == NULL)
        return (NULL);
    while ((node = node->next) && index--)
        ; /* VOID */
    return (&node->value);
}


__always_inline __nonnull ((1))
static inline void *lec_insert_after_node(register lec node, const int value) {
    lec     new_node;

    create_node(new_node, (node? node->next: new_node));
    if (node)
        node->next = new_node;
    return (new_node);
}


void lec_insert_pos(register lec *lst, int pos, const int value) {
    lec     node, new_node;

    if (*lst == NULL) {
        lec_insert_front(lst, value);
        return;
    }
    node = (*lst)->next;                 /* Store the first node */
    while (pos != 0 && --pos)
        node = node->next;
    new_node = lec_insert_after_node(node, value);
    if (node == *lst)                   /* Update back pointer when necessary */
        *lst = new_node;
}


void lec_insert_front(register lec *lst, const int value) {
    lec     new_node;

    new_node = lec_insert_after_node(*lst, value);
    if (*lst == NULL)
        *lst = new_node;
}


void lec_insert_back(register lec *lst, const int value) {
    lec     new_node;

    new_node = lec_insert_after_node(*lst, value);
    *lst = new_node;
}


void lec_fill(lec *lst, const int items) {
    int     i;

    for (i = 0; i < items; i++)
        lec_insert_front(lst, (items - i));
}


bool lec_sorted(lec *lst) {
    lec     first, node;
    int     prev;

    if (*lst == NULL)
        return (true);
    first = node = (*lst)->next;
    while ((prev = node->value) && (node = node->next) != first)
        if (prev >= node->value)
            return (false);
    return (true);
}


// Warning: We do not check for invalid arguments.
// Remember that lst is the last node pointer.
__always_inline __nonnull ((1))
void lec_remove_node(lec *lst, lec node, lec previous) {
    previous->next = node->next;
    if (*lst == node)      {             // When removing the back node
        *lst = previous != node? previous: NULL;
    }
    free(node);
}


void lec_remove_front(register lec *lst) {
    if (*lst == NULL)
        return;
    lec_remove_node(lst, (*lst)->next, *lst);
}


void lec_remove_pos(register lec *lst, int pos) {
    lec    prev = NULL, node = *lst;

    if (node == NULL)
        return;
    if (pos == 0) {
        lec_remove_front(lst);
        return;
    }
    node = node->next;              // Start from the first node
    if (*lst != node) {             /* Skip the 'while' when there is just  */
        while (pos--)               /* one element in the list.             */
            node = (prev = node)->next;
    } else
        prev = node;
    lec_remove_node(lst, node, prev);
}


void lec_remove_back(register lec *lst) {
    lec     prev, node = *lst;

    if (node == NULL)
        return;
    node = (prev = node)->next;
    while (node != *lst)
        node = (prev = node)->next;
    lec_remove_node(lst, node, prev);
}


int lec_delete_if(lec *lst, const f_lec_cmp_node fcmp) {
    lec     node = *lst, next, prev = NULL;
    int     result = 0;
    bool    stop;

    if (node == NULL)
        return (0);
    node = (prev = node)->next;
    for (;;) {
        stop = (node == *lst);
        next = node->next;
        if (fcmp(node->value)) {
            lec_remove_node(lst, node, prev);
            result++;
        } else
            prev = node;
        if (stop)
            break;
        node = next;
    }
    return (result);
}


int lec_remove(lec *lst, const int value) {

    bool equals(const int number) {
        return (number == value);
    }

    return (lec_delete_if(lst, equals));
}


int lec_count_if(lec *lst, const f_lec_cmp_node fcmp) {
    lec node = *lst;
    int result = 0;

    if (node == NULL)
        return (0);
    while ((node = node->next)) {
        if (fcmp(node->value))
            result++;
        if (node == *lst)
            break;
    }
    return (result);
}

