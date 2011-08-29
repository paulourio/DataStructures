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

enum TREE_WALKORDER {
	WALK_INORDER,
	WALK_PREORDER,
	WALK_POSORDER
};

typedef void (*fbst_print)(const int);

void *tree_new(void);
void tree_free(void **ptr) __nonnull ((1));
void tree_insert(void **ptree, const int value) __nonnull ((1));
void tree_delete(void **ptree, const int value) __nonnull ((1));
void tree_walk(void *ptree, register const fbst_print cblk,
		register const enum TREE_WALKORDER worder);

#endif
