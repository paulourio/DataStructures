/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (August 2011)
 */
#ifndef TREE_H_INCLUDE
#define TREE_H_INCLUDE

#define DEBUG

#ifdef DEBUG
#	include	<stdio.h>
#	define	err(...)	fprintf(stderr, __VA_ARGS__)
#	define	debug(...)	err("Debug: " __VA_ARGS__)
#else
#	define	debug
#endif

#define NOT_FOUND	(-1)


struct bstree {
	struct bstree *parent;
	struct bstree *lchild;
	struct bstree *rchild;
	int value;
	int position; /* Used to printing. */
};

enum TREE_WALKORDER {
	WALK_INORDER,
	WALK_PREORDER,
	WALK_POSORDER
};

typedef void (*fbst_walk)(struct bstree *);

static inline int tree_isleaf(const struct bstree *node)
{
	if (node == NULL)
		return 0;
	return (node->lchild == NULL && node->rchild == NULL);
}

extern void *tree_new(void);
extern void tree_free(void **ptr) __nonnull ((1));
extern void tree_insert(void **ptree, const int value) __nonnull ((1));
extern void tree_delete(void **ptree, const int value) __nonnull ((1));
extern void tree_set_childs(void *node, void *left, void *right);
extern void tree_walk(void *ptree, register const fbst_walk cblk,
		register const enum TREE_WALKORDER worder);
extern int tree_min_value(void *ptree);
extern int tree_max_value(void *ptree);
extern int tree_successor_value(void *ptree, const int value);
extern int tree_predecessor_value(void *ptree, const int value);
extern int tree_get_value(void *ptree);
extern int tree_root_value(void *ptree);
extern void tree_print_to_bosque(void *ptree);
extern void tree_create_table(void *ptree);

#endif
