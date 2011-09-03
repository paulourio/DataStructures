/*
 *  Author: Paulo Roberto Urio
 *  Date: May 2, 2011
 *  Description: Linked list header.
 */
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <features.h>

struct lst_node {
    int             value;
    struct lst_node *next;
};

typedef struct lst_node     lst_node;
typedef lst_node            *list;


/*  Compare function for linked list
 *  Example:
 *      bool cmp(int a) { return (a % 2); }
 */
typedef bool (*f_lst_cmp_node)(const int);

/* Test if the list is valid (assert will fail when list is empty) */
extern void list_test(const list *lst) __nonnull ((1));
void list_clear(register list *lst) __nonnull ((1));
extern bool list_isempty(const list *lst) __attribute_pure__
    __attribute_warn_unused_result__;

/* Print all items in the format [0, 1, 2, ...] */
void list_print(const list *lst) __nonnull ((1));

int *list_get(register list *lst, register int index) __nonnull ((1))
    __attribute_warn_unused_result__;
    
list list_get_back_node(const list *lst) __nonnull ((1))
    __attribute_warn_unused_result__;

/* Remove methods */
size_t list_remove(const list *lst, const int value) __nonnull ((1));
size_t list_delete_if(list *lst, const f_lst_cmp_node fcmp) __nonnull ((1, 2));
void list_remove_front(register list *lst) __nonnull ((1));
void list_remove_back(register list *lst) __nonnull ((1));
void list_remove_pos(register list *lst, size_t pos) __nonnull ((1));

/* Insert methods */
void list_insert_pos(list *lst, size_t pos, const int value) __nonnull ((1));
void list_insert_front(list *lst, const int value) __nonnull ((1));
void list_insert_back(list *lst, const int value) __nonnull ((1));

/* Populate a list with items, starting at 1. */
void list_fill(list *lst, const size_t items) __nonnull ((1));

/* Count how many elements are in the list (It uses the compare function */
size_t list_count_if(list *lst, const f_lst_cmp_node fcmp) __nonnull ((1,2))
    __attribute_warn_unused_result__;

bool list_sorted(list *lst) __nonnull((1));

#endif
