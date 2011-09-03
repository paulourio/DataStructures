/*
 * AUTHOR
 *      Paulo Roberto Urio
 * PURPOSE
 *      Test linked list implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define MAX     (size_t) 19

__attribute_pure__
static bool multiplo_5(const int numero)
{
    return true;
}

int main(void)
{
    list    lst = NULL;
    size_t  pos = (size_t) (MAX / 2);
    int     rep = 0;

    list_clear(&lst);
    list_insert_pos(&lst, (size_t) 0, 1);
    list_print(&lst);

    list_clear(&lst);
    list_insert_back(&lst, 1);
    list_print(&lst);

    list_clear(&lst);
    list_insert_front(&lst, 1);
    list_print(&lst);

    list_fill(&lst, MAX);
    list_print(&lst);       /* Test print */
    list_test(&lst);
    list_clear(&lst);       /* Test clear */
    list_clear(&lst);       /* Test clear */

    list_fill(&lst, MAX);
    list_print(&lst);

    printf("Removing first element.\n");
    list_remove_pos(&lst, (size_t) 0);
    list_print(&lst);

    printf("Sorted? %s\n", list_sorted(&lst)? "Yes": "No");

    int     *a = list_get(&lst, 10);
    printf("The 10th element '%d'\n", a? *a: 0);

    printf("Removing %zd, adding value %d instead.\n", pos, rep);
    list_remove_pos(&lst, pos);
    list_insert_pos(&lst, pos, rep);
    list_print(&lst);

    printf("Inserting at start and end\n");
    list_insert_front(&lst, 42);
    list_insert_back(&lst, 42);
    list_print(&lst);

    printf("Sorted? %s\n", list_sorted(&lst)? "Yes": "No");

    list_remove_front(&lst);
    list_remove_back(&lst);
    list_print(&lst);

    list_clear(&lst);       /* Test if remove front and back workd when empty */
    list_remove_front(&lst);
    list_remove_back(&lst);

    list_insert_front(&lst, 42);
    list_insert_front(&lst, 42);
    list_insert_back(&lst, 42);
    list_insert_back(&lst, 42);
    list_print(&lst);

    list_clear(&lst);

    printf("Filling with 100 elements and counting multiples of 5\n");
    list_fill(&lst, (size_t) 100);
    printf("Were found %zd\n", list_count_if(&lst, multiplo_5));

    printf("Removing all multiples of 5\n");
    list_delete_if(&lst, multiplo_5);
    list_print(&lst);

    list_clear(&lst);
    return (EXIT_SUCCESS);
}
