#ifndef LDEC_H_INCLUDED
#define LDEC_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <features.h>

struct ldec_node {
	int			value;
	struct ldec_node	*next;
	struct ldec_node	*prev;
};

typedef struct ldec_node	ldec_node;


struct ldec_t {
	ldec_node	*front;
	int		size;
	int		maxsize;
};

typedef struct ldec_t	ldec_t;
typedef ldec_t		*ldec;

/*  Compare function for circular linked list
 *  Example:
 *	  bool cmp(int a) { return (a % 2); }
 */
typedef bool (*f_lst_cmp_node)(const int);


#define ldec_front(lst)	 ((lst)->front)
#define ldec_back(lst)	  (ldec_front(lst)->prev)
#define ldec_size(lst)	  ((lst)->size)
#define ldec_maxsize(lst)   ((lst)->maxsize)
#define ldec_empty(lst)	 (ldec_size(lst) == 0)
#define ldec_full(lst)	  (ldec_maxsize(lst) > 0 \
			&& ldec_size(lst) >= ldec_maxsize(lst))

/* Note: ldec_setmax receives a (ldec *lst, int limit) */
#define ldec_setmax(lst,limit)	((*lst)->maxsize = limit)

extern void ldec_test(const ldec *p_stp) __nonnull ((1));
extern void ldec_init(ldec *lst) __nonnull ((1));
extern void ldec_free(ldec *lst) __nonnull ((1));
extern void ldec_clear(ldec *lst) __nonnull ((1));

extern void ldec_print(const ldec *lst) __nonnull ((1));

extern void ldec_insert_front(register ldec *lst, const int value) 
		__nonnull ((1));
extern void ldec_insert_back(register ldec *lst, const int value) 
		__nonnull ((1));
extern void ldec_insert_pos(ldec *lst, int pos, const int value) 
		__nonnull ((1));
extern void ldec_fill(ldec *lst, const int items) __nonnull ((1));

extern bool ldec_sorted(const ldec *lst) __wur __nonnull ((1));

extern void ldec_remove_front(ldec *lst) __nonnull ((1));
extern void ldec_remove_back(ldec *lst) __nonnull ((1));
extern void ldec_remove_pos(ldec *lst, int pos) __nonnull ((1));
extern int ldec_delete_if(ldec *lst, const f_lst_cmp_node fcmp) 
		__nonnull ((1));
extern int ldec_remove_value(ldec *lst, const int value) __nonnull ((1));
extern int ldec_pop_back(ldec *lst) __nonnull ((1));

extern int ldec_count_if(ldec *lst, const f_lst_cmp_node fcmp) 
		__nonnull ((1)) __wur;

extern int *ldec_get(register ldec *lst, register int index) __nonnull ((1));

extern int ldec_back_value(register ldec *lst) __nonnull ((1));
extern int ldec_front_value(register ldec *lst) __nonnull ((1));

#endif // LDEC_H_INCLUDED
