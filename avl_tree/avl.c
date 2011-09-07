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
#include "avl.h"

#define	max(a,b)	(a > b?	a: b)

/* Allocate memory for a new node */
static struct avltree *tree_new_node(const int value)
{
	struct avltree   *bst;

	bst = malloc(sizeof(struct avltree));
	if (bst == NULL) {
		debug("Can't allocate memory to node of value '%d'\n", value);
		return NULL;
	}
	bst->parent = NULL;
	bst->lchild = NULL;
	bst->rchild = NULL;
	bst->value = value;
	bst->height = 0;
	return bst;
}


/* Search a value in the tree and returns its node */
static struct avltree *tree_search(struct avltree *ptree, const int valor)
{
	while (ptree != NULL && valor != ptree->value)
		if (valor < ptree->value)
			ptree = ptree->lchild;
		else
			ptree = ptree->rchild;
	return ptree;
}


/* Returns the minimum value node in the tree */
static struct avltree *tree_min(struct avltree *ptree)
{
	if (ptree != NULL && ptree->lchild)
		return tree_min(ptree->lchild);
	else
		return ptree;
}


/* Returns the maximum value node in the tree */
static struct avltree *tree_max(struct avltree *ptree)
{
	if (ptree != NULL && ptree->rchild)
		return tree_max(ptree->rchild);
	else
		return ptree;
}


/* Finds the successor node */
static struct avltree *tree_successor(struct avltree *bst)
{
	struct avltree   *pai = bst->parent;

	if (bst->rchild != NULL)
		return tree_min(bst->rchild);
	while (pai != NULL && bst == pai->rchild)
		pai = (bst = pai)->parent;
	return pai;
}


/* Finds the predecessor node */
static struct avltree *tree_predecessor(struct avltree *bst)
{
	struct avltree   *pai = bst->parent;

	if (bst->lchild != NULL)
		return tree_max(bst->lchild);
	while (pai != NULL && bst == pai->lchild)
		pai = (bst = pai)->parent;
	return pai;
}


/* Initialize an empty binary search tree */
void *tree_new(void)
{
	return NULL;
}


/* Free all tree nodes */
void tree_free(void **ptr)
{
	struct avltree	*tree;

	if (*ptr == NULL)
		return;
	tree = *ptr;
	tree_free((void **) &tree->lchild);
	tree_free((void **) &tree->rchild);
	free(*ptr);
	*ptr = NULL;
}


static int tree_update_height(struct avltree *node)
{
	if (node == NULL)
		return 0;
	if (node->lchild == NULL && node->rchild == NULL) {
		node->height = 0;
		debug("Node '%d' height %d (leaf)\n", node->value, node->height);
		return 0;
	}
	int left = tree_update_height(node->lchild);
	int right = tree_update_height(node->rchild);
	node->height = max(left, right) + 1;
	debug("Node '%d' height %d\n", node->value, node->height);
	return node->height;
}


static void tree_left_rotate(void **ptree, struct avltree *node)
{
	struct avltree	*y = node->rchild, *parent;
	
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
	tree_update_height(node->parent);
}


static void tree_right_rotate(void **ptree, struct avltree *node)
{
	struct avltree	*y = node->lchild, *parent;
	
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
	tree_update_height(node->parent);
}


/*
 * Rotate a node. If double_ is true, it will be done a double 
 * node rotation, otherwise a single node rotation. Left tell
 * which direction the rotation will be done. On double rotation,
 * which means their balance factor have opposite signs, the 
 * left will mean actually right rotation.
 */
static void tree_rotate(void **ptree, struct avltree *node, 
	struct avltree *previous, int is_double, int to_left)
{
	if (is_double) {
		if (!to_left) {
			tree_left_rotate(ptree, previous);
			tree_right_rotate(ptree, node);
		} else {
			tree_right_rotate(ptree, previous);
			tree_left_rotate(ptree, node);
		}
	} else {
		if (to_left) {
			tree_left_rotate(ptree, node);
		} else {
			tree_right_rotate(ptree, node);
		}
	}
}


#define	height(t)	(t != NULL?  t->height:  -1)
static void tree_balance(void **ptree, struct avltree *node)
{
	struct avltree *old;
	int bal, oldbal;
	
	while (node != NULL) {
		int rh = height(node->rchild);
		int lh = height(node->lchild);
		
		bal = rh - lh;
		node->height = max(rh, lh) + 1;
		if (abs(bal) == 2) {
			int is_double = (bal < 0 && oldbal > 0);
			int to_left = (bal == 2);
			
			tree_rotate(ptree, node, old, is_double, to_left);
			debug(" -- recursion --\n");
			tree_balance(ptree, node);
			break;
		}	
		oldbal = bal;
		old = node;
		node = node->parent;
	}
}


/* Insert a value in the tree */
void tree_insert(void **ptree, const int value)
{
	struct avltree   *prev = NULL, *bst = *ptree,
			*node = tree_new_node(value);

	while (bst != NULL) {
		prev = bst;
		bst = (value < bst->value)?  bst->lchild:  bst->rchild;
	}
	node->parent = prev;
	if (prev == NULL)
		*ptree = node;		/* The tree is empty. */
	else {
		node->height = prev->height + 1;
		if (value < prev->value)
			prev->lchild = node;
		else
			prev->rchild = node;
	}
	tree_balance(ptree, node);
}


/*
 * If the node has only one child, this child will be child of the
 * parent node, else will be found the successor node of node. 
 * Returns which node will be removed.
 */
static struct avltree *tree_which_node(struct avltree *node)
{
	if (node->lchild == NULL || node->rchild == NULL)
		return node;
	else
		return tree_successor(node);
}


/* Select which node switch with node. */
static struct avltree *tree_which_son_node(struct avltree *node)
{
	return node->lchild != NULL?  node->lchild:  node->rchild;
}


/*
 * Updates the connection of parent with new child.
 * If the node to be removed is the root, update the tree's root.
 * Else will be updated the son, depending whether the node to be removed
 * is on left or right of parent node.
 */
static void tree_update_father_node(void **ptree, struct avltree *node,
					struct avltree *new_son)
{
	struct avltree	*pai = node->parent;

	if (node->parent == NULL)
		*ptree = new_son;
	else if (node == pai->lchild)
		pai->lchild = new_son;
	else
		pai->rchild = new_son;
}


/*
 * Delete a tree's node
 * Finds the y node to be removed and its x child that will be the new
 * child of y's parent.  There's a case that y node isn't the node within
 * value to be removed.  In this case, y node is a leaf and its value
 * should be switched with the real node to be removed.
 */
void tree_delete(void **ptree, const int value)
{
	struct avltree   *node, *y, *x;

	if (*ptree == NULL) {
		debug("Empty tree.\n");
		return;
	}
	node = tree_search(*ptree, value);
	if (node == NULL) {
		debug("Node '%d' was not found.\n", value);
		return;
	}
	y = tree_which_node(node);
	x = tree_which_son_node(y);
	tree_update_father_node(ptree, y, x);
	if (y != node)
		node->value = y->value;
	free(y);
}


/* Walk the tree in three orders */
void tree_walk(void *ptree, register const fbst_print cblk,
		register const enum TREE_WALKORDER worder)
{
	if (ptree != NULL) {
		struct avltree	*node = ptree;

		if (worder == WALK_PREORDER)
			cblk(node->value);
			
		tree_walk(node->lchild, cblk, worder);
		
		if (worder == WALK_INORDER)
			cblk(node->value);
			
		tree_walk(node->rchild, cblk, worder);
		
		if (worder == WALK_POSORDER)
			cblk(node->value);
	}
}


/* Returns the minimum value in the tree */
int tree_min_value(void *ptree)
{
	return ptree != NULL?  tree_min(ptree)->value:  NOT_FOUND;
}


/* Returns the maximum value in the tree */
int tree_max_value(void *ptree)
{
	return ptree != NULL?  tree_max(ptree)->value:  NOT_FOUND;
}


/* Returns the successor value in the tree */
int tree_successor_value(void *ptree, const int value)
{
	struct avltree   *no, *succ;

	if (ptree == NULL)
		return NOT_FOUND;
	no = tree_search(ptree, value);
	succ = tree_successor(no);
	return succ != NULL?  succ->value:  NOT_FOUND;
}


/* Returns the predecessor value in the tree */
int tree_predecessor_value(void *ptree, const int value)
{
	struct avltree   *no, *pred;

	if (ptree == NULL)
		return NOT_FOUND;
	no = tree_search(ptree, value);
	pred = tree_predecessor(no);
	return pred != NULL?  pred->value:  NOT_FOUND;
}
