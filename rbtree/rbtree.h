/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (August 2011)
 */
#ifndef RBTREE_H_INCLUDE
#define RBTREE_H_INCLUDE

#define DEBUG

#ifdef DEBUG
#	include	<stdio.h>
#	define	err(...)	fprintf(stderr, __VA_ARGS__)
#	define	debug(...)	err(__VA_ARGS__)
#else
#	define	debug
#endif

#define NOT_FOUND	(-1)

struct rbtree {
	struct rbtree *parent;
	struct rbtree *lchild;
	struct rbtree *rchild;
	int value;
	int height;
};

enum RBTREE_WALKORDER {
	WALK_INORDER,
	WALK_PREORDER,
	WALK_POSORDER
};

typedef void (*fbst_print)(const int);

extern void *rbtree_new(void);
extern void rbtree_free(void **ptr) __nonnull ((1));
extern void rbtree_insert(void **ptree, const int value) __nonnull ((1));
extern void rbtree_delete(void **ptree, const int value) __nonnull ((1));
extern void rbtree_walk(void *ptree, register const fbst_print cblk,
		      register const enum RBTREE_WALKORDER worder);
extern int rbtree_min_value(void *ptree);
extern int rbtree_max_value(void *ptree);
extern int rbtree_successor_value(void *ptree, const int value);
extern int rbtree_predecessor_value(void *ptree, const int value);

#endif
