/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (March 2011)
 */
#ifndef STACK_H_INCLUDE
#define STACK_H_INCLUDE

#include <stdbool.h>
#include <features.h>

struct st_node {
    int             data;
    struct st_node  *next;
};

typedef struct st_node  st_node;


struct stack {
    st_node *top;
};

typedef struct stack *  stack;


extern stack stack_new(void);
extern void stack_free(const stack s) __nonnull ((1));

#define stack_isempty(s)    (s->top == NULL)
#define stack_top(s)        (!stack_isempty(s)? s->top->data: 0)

extern void stack_push(const stack s, const int data) __nonnull ((1));
extern int stack_pop(const stack s) __nonnull ((1));

#endif /* STACK_H_INCLUDE */
