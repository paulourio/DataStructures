/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (August 2011)
 */
#include <stdlib.h>
#include <math.h>
#include "rbtree.h"

#define TESTING

#ifdef TESTING
#	include <assert.h>
#endif

#define color(node)	(node != NULL?  node->color:  RB_BLACK)

#define	max(a,b)	(a > b?	a: b)

/* Allocate memory for a new node */
static struct rbtree *rbtree_new_node(const int value)
{
	struct rbtree *bst;

	bst = malloc(sizeof(struct rbtree));
	if (bst == NULL) {
		err("Error: Can't allocate memory to node of value '%d'\n", 
			value);
		return NULL;
	}
	bst->parent = NULL;
	bst->lchild = NULL;
	bst->rchild = NULL;
	bst->value = value;
	bst->color = RB_RED;
	return bst;
}


/* Search a value in the rbtree and returns its node */
static struct rbtree *rbtree_search(struct rbtree *ptree, const int valor)
{
	while (ptree != NULL && valor != ptree->value)
		if (valor < ptree->value)
			ptree = ptree->lchild;
		else
			ptree = ptree->rchild;
	return ptree;
}


/* Returns the minimum value node in the rbtree */
static struct rbtree *rbtree_min(struct rbtree *ptree)
{
	if (ptree != NULL && ptree->lchild)
		return rbtree_min(ptree->lchild);
	else
		return ptree;
}


/* Returns the maximum value node in the rbtree */
static struct rbtree *rbtree_max(struct rbtree *ptree)
{
	if (ptree != NULL && ptree->rchild)
		return rbtree_max(ptree->rchild);
	else
		return ptree;
}


#ifdef TESTING
/* Will not admit duplicate values in rbtree */
static void rbtree_test(struct rbtree *ptree)
{
	if (ptree == NULL)
		return;
	if (ptree->parent != NULL) {
		struct rbtree *parent = ptree->parent;
		int left_child = parent->lchild == ptree;
		int right_child = parent->rchild == ptree;
		
		assert(left_child || right_child);
		assert(left_child != right_child);
	}
	if (ptree->lchild != NULL) {
		rbtree_test(ptree->lchild);
		assert(rbtree_max(ptree->lchild)->value < ptree->value);
	}
	if (ptree->rchild != NULL) {
		rbtree_test(ptree->rchild);
		assert(rbtree_max(ptree->rchild)->value > ptree->value);
	}
}
#else
#	define rbtree_test(p)
#endif


/* Finds the successor node */
static struct rbtree *rbtree_successor(struct rbtree *bst)
{
	struct rbtree *pai = bst->parent;

	if (bst->rchild != NULL)
		return rbtree_min(bst->rchild);
	while (pai != NULL && bst == pai->rchild)
		pai = (bst = pai)->parent;
	return pai;
}


/* Finds the predecessor node */
static struct rbtree *rbtree_predecessor(struct rbtree *bst)
{
	struct rbtree *pai = bst->parent;

	if (bst->lchild != NULL)
		return rbtree_max(bst->lchild);
	while (pai != NULL && bst == pai->lchild)
		pai = (bst = pai)->parent;
	return pai;
}


/* Initialize an empty binary search rbtree */
void *rbtree_new(void)
{
	return NULL;
}


/* Free all rbtree nodes */
void rbtree_free(void **ptr)
{
	struct rbtree *tree;

	if (*ptr == NULL)
		return;
	tree = *ptr;
	rbtree_free((void **) &tree->lchild);
	rbtree_free((void **) &tree->rchild);
	free(*ptr);
	*ptr = NULL;
}


static void rbtree_left_rotate(struct rbtree **ptree, struct rbtree *node)
{
	struct rbtree *y = node->rchild, *parent;
	
	node->rchild = y->lchild;
	if (y->lchild != NULL)
		y->lchild->parent = node;
	y->parent = node->parent;
	parent = node->parent;
	if (parent == NULL)
		*ptree = y;
	else if (node == parent->lchild)
		parent->lchild = y;
	else
		parent->rchild = y;
	y->lchild = node;
	node->parent = y;
}


static void rbtree_right_rotate(struct rbtree **ptree, struct rbtree *node)
{
	struct rbtree *y = node->lchild, *parent;
	
	node->lchild = y->rchild;
	if (y->rchild != NULL)
		y->rchild->parent = node;
	y->parent = node->parent;
	parent = node->parent;
	if (parent == NULL)
		*ptree = y;
	else if (node == parent->rchild)
		parent->rchild = y;
	else
		parent->lchild = y;
	y->rchild = node;
	node->parent = y;
}


/* Fix the tree after insertion of node 'node'. */
static void rbtree_insert_fixup(struct rbtree **tree, struct rbtree *node)
{
	struct rbtree *parent = node->parent;
	struct rbtree *y, *grandparent;

	while (color(parent) == RB_RED) {
		grandparent = parent->parent;
		if (parent == grandparent->lchild) {
			y = grandparent->rchild;
			if (color(y) == RB_RED) {
				parent->color = RB_BLACK;
				y->color = RB_BLACK;
				grandparent->color = RB_RED;
				node = grandparent;
			} else {
				if (node == parent->rchild) {
					node = parent;
					rbtree_left_rotate(tree, node);
					parent = node->parent;
					grandparent = parent->parent;
				}
				parent->color = RB_BLACK;
				grandparent->color = RB_RED;
				rbtree_right_rotate(tree, grandparent);
			}
		} else { /* parent == grandparent->rchild */
			y = grandparent->lchild;
			if (color(y) == RB_RED) {
				parent->color = RB_BLACK;
				y->color = RB_BLACK;
				grandparent->color = RB_RED;
				node = grandparent;
			} else {
				if (node == parent->lchild) {
					node = parent;
					rbtree_left_rotate(tree, node);
					parent = node->parent;
					grandparent = parent->parent;
				}
				parent->color = RB_BLACK;
				grandparent->color = RB_RED;
				rbtree_right_rotate(tree, grandparent);
			}	
		}
		parent = node->parent;
	}
	(*tree)->color = RB_BLACK;
}

/* Insert a value in the rbtree */
void rbtree_insert(void **ptree, const int value)
{
	struct rbtree	*prev = NULL, *bst = *ptree,
			*node = rbtree_new_node(value),
			**tree = (struct rbtree **) ptree;

	while (bst != NULL) {
		prev = bst;
		bst = (value < bst->value)?  bst->lchild:  bst->rchild;
	}
	node->parent = prev;
	if (prev == NULL) {
		*ptree = node;		/* The rbtree is empty. */
	} else if (value < prev->value)
		prev->lchild = node;
	else
		prev->rchild = node;
	rbtree_insert_fixup(tree, node);
	rbtree_test(*tree);
}


/*
 * If the node has only one child, this child will be child of the
 * parent node, else will be found the successor node of node. 
 * Returns which node will be removed.
 */
static struct rbtree *rbtree_which_node(struct rbtree *node)
{
	if (node->lchild == NULL || node->rchild == NULL)
		return node;
	else
		return rbtree_successor(node);
}


/* Select which node switch with node. */
static struct rbtree *rbtree_which_son_node(struct rbtree *node)
{
	return node->lchild != NULL?  node->lchild:  node->rchild;
}


/*
 * Updates the connection of parent with new child.
 * If the node to be removed is the root, update the rbtree's root.
 * Else will be updated the son, depending whether the node to be removed
 * is on left or right of parent node.
 */
static void rbtree_update_father_node(void **ptree, struct rbtree *node,
				    struct rbtree *new_son)
{
	struct rbtree *pai = node->parent;

	if (node->parent == NULL)
		*ptree = new_son;
	else if (node == pai->lchild)
		pai->lchild = new_son;
	else
		pai->rchild = new_son;
}


/*
 * Delete a rbtree's node
 * Finds the y node to be removed and its x child that will be the new
 * child of y's parent.  There's a case that y node isn't the node within
 * value to be removed.  In this case, y node is a leaf and its value
 * should be switched with the real node to be removed.
 */
void rbtree_delete(void **ptree, const int value)
{
	struct rbtree *node, *y, *x;

	if (*ptree == NULL) {
		err("Empty rbtree.\n");
		return;
	}
	node = rbtree_search(*ptree, value);
	if (node == NULL) {
		err("Node '%d' was not found.\n", value);
		return;
	}
	y = rbtree_which_node(node);
	x = rbtree_which_son_node(y);
	if (x != NULL)
		x->parent = y->parent;
	rbtree_update_father_node(ptree, y, x);
	if (y != node)
		node->value = y->value;
	free(y);
	rbtree_test(*ptree);
}


/* Walk the rbtree in three orders */
void rbtree_walk(void *ptree, register const fbst_print cblk,
		register const enum RBTREE_WALKORDER worder)
{
	if (ptree != NULL) {
		struct rbtree *node = ptree;

		if (worder == WALK_PREORDER)
			cblk(node->value);
			
		rbtree_walk(node->lchild, cblk, worder);
		
		if (worder == WALK_INORDER)
			cblk(node->value);
			
		rbtree_walk(node->rchild, cblk, worder);
		
		if (worder == WALK_POSORDER)
			cblk(node->value);
	}
}

/* Walk the rbtree in three orders, passing to the callback,
 * the node color. */
void rbtree_walk_ex(void *ptree, register const fbst_print_ex cblk,
		register const enum RBTREE_WALKORDER worder)
{
	if (ptree != NULL) {
		struct rbtree *node = ptree;

		if (worder == WALK_PREORDER)
			cblk(node->value, node->color);
			
		rbtree_walk_ex(node->lchild, cblk, worder);
		
		if (worder == WALK_INORDER)
			cblk(node->value, node->color);
			
		rbtree_walk_ex(node->rchild, cblk, worder);
		
		if (worder == WALK_POSORDER)
			cblk(node->value, node->color);
	}
}

/* Returns the minimum value in the rbtree */
int rbtree_min_value(void *ptree)
{
	return ptree != NULL?  rbtree_min(ptree)->value:  NOT_FOUND;
}


/* Returns the maximum value in the rbtree */
int rbtree_max_value(void *ptree)
{
	return ptree != NULL?  rbtree_max(ptree)->value:  NOT_FOUND;
}


/* Returns the successor value in the rbtree */
int rbtree_successor_value(void *ptree, const int value)
{
	struct rbtree *no, *succ;

	if (ptree == NULL)
		return NOT_FOUND;
	no = rbtree_search(ptree, value);
	succ = rbtree_successor(no);
	return succ != NULL?  succ->value:  NOT_FOUND;
}


/* Returns the predecessor value in the rbtree */
int rbtree_predecessor_value(void *ptree, const int value)
{
	struct rbtree *no, *pred;

	if (ptree == NULL)
		return NOT_FOUND;
	no = rbtree_search(ptree, value);
	pred = rbtree_predecessor(no);
	return pred != NULL?  pred->value:  NOT_FOUND;
}
