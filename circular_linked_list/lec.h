#ifndef LEC_H_INCLUDED
#define LEC_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <features.h>

struct lec_node {
    int             value;
    struct lec_node *next;
};

typedef struct lec_node     lec_node;
typedef lec_node            *lec;


/*  Compare function for circular linked list
 *  Example:
 *      bool cmp(int a) { return (a % 2); }
 */
typedef bool (*f_lec_cmp_node)(const int);


extern void lec_test(const lec *lst) __nonnull ((1));
extern void lec_init(lec *lst) __nonnull ((1));

/* Print all items in the format [0, 1, 2, ...] */
extern void lec_print(const lec *lst) __nonnull ((1));

extern void lec_clear(lec *lst) __nonnull ((1));
extern bool lec_isempty(const lec *lst) __attribute_pure__
    __attribute_warn_unused_result__;
extern int *lec_get(register lec *lst, register int index) __nonnull ((1))
    __attribute_warn_unused_result__;

extern void lec_insert_front(register lec *lst, const int value) __nonnull ((1));
extern void lec_insert_back(register lec *lst, const int value) __nonnull ((1));
extern void lec_insert_pos(register lec *lst, int pos, const int value)
    __nonnull ((1));

/* Populate a list with items, starting at 1. */
extern void lec_fill(lec *lst, const int items) __nonnull ((1));

extern bool lec_sorted(lec *lst) __nonnull((1));

extern void lec_remove_node(lec *lst, lec node, lec previous);

extern void lec_remove_front(register lec *lst) __nonnull ((1));
extern void lec_remove_pos(register lec *lst, int pos) __nonnull ((1));
extern void lec_remove_back(register lec *lst) __nonnull ((1));
extern int lec_delete_if(lec *lst, const f_lec_cmp_node fcmp) __nonnull ((1));
extern int lec_remove(lec *lst, const int value) __nonnull ((1));

/* Count how many elements are in the list (It uses the compare function */
extern int lec_count_if(lec *lst, const f_lec_cmp_node fcmp) __nonnull ((1, 2))
    __attribute_warn_unused_result__;

#endif // LEC_H_INCLUDED
