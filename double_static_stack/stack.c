#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "stack.h"


void dstack_init(dstack *ds, const size_t size)
{
    (*ds) = malloc(sizeof(struct dstack));
    assert(*ds != NULL);
    (*ds)->array = malloc(sizeof(int) * size);
    (*ds)->left_top = -1;
    (*ds)->right_top = (int) size;
    (*ds)->size = size;
}


void dstack_free(dstack *ds)
{
    if (*ds == NULL)
        return;
    free((*ds)->array);
    free(*ds);
    *ds = NULL;
}


void dstack_test(const dstack ds)
{
    assert(ds->array != NULL);
    assert(ds->left_top >= -1);
    assert(ds->left_top < (int) ds->size);
    assert(ds->right_top >= (int) ds->size);
    assert(ds->right_top >= 0);
    assert(ds->left_top < ds->right_top);
}


void dstack_left_push(const dstack ds, const int value)
{
    if (dstack_isfull(ds))
        return;                 /* Overflow */
    ds->array[++ds->left_top] = value;
}


void dstack_right_push(const dstack ds, const int value)
{
    if (dstack_isfull(ds))
        return;                 /* Overflow */
    ds->array[--ds->right_top] = value;
}


int dstack_left_pop(const dstack ds)
{
    int toRet = dstack_left_top(ds);

    if (!dstack_left_isempty(ds))
        ds->left_top--;         /* Avoid underflow */
    return toRet;
}


int dstack_right_pop(const dstack ds)
{
    int toRet = dstack_right_top(ds);

    if (!dstack_right_isempty(ds))
        ds->right_top++;         /* Avoid underflow */
    return toRet;
}
