#include <stdlib.h>
#include "tree.h"

struct bstree {
	void	*parent;
	void	*lchild;
	void	*rchild;
	int	value;
};


#define	leaf(node)	((node)->lchild == NULL && (node)->rchild == NULL)
#define	TREE(bst)	((struct bstree *) bst)
#define	PTREE(bst)	(* (struct bstree **) bst)


static struct bstree *tree_new_node(const int value) {
	struct bstree	*bst;

	bst = (struct bstree *) malloc(sizeof(struct bstree));
	if (bst == NULL) {
		debug("Erro ao alocar nó com valor '%d'.\n", value);
		return NULL;
	}
	bst->parent = NULL;
	bst->lchild = NULL;
	bst->rchild = NULL;
	bst->value = value;
	return bst;
}


void *tree_new(void) {
	return NULL;
}


void tree_free(void **ptr) {
	if (!ptr || !PTREE(ptr))
		return;
	tree_free(&PTREE(ptr)->lchild);
	tree_free(&PTREE(ptr)->rchild);
	free(PTREE(ptr));
	PTREE(ptr) = NULL;
}


void tree_insert(void **ptree, const int value) {
	struct bstree	*prev = NULL, *bst = PTREE(ptree),
			*node = tree_new_node(value);

	while (bst) {
		prev = bst;
		if (value < bst->value)
			bst = bst->lchild;
		else
			bst = bst->rchild;
	}
	node->parent = prev;
	if (prev == NULL) 
		PTREE(ptree) = node;	/* Árvore está vazia. */
	else if (value < prev->value)
		prev->lchild = node;
	else
		prev->rchild = node;
}


void tree_walk(void *ptree, const register fbst_print cblk, 
		const register enum TREE_WALKORDER worder) {
	if (ptree != NULL) {
		if (worder == WALK_INORDER)
			cblk(TREE(ptree)->value);
		tree_walk(TREE(ptree)->lchild, cblk, worder);
		if (worder == WALK_PREORDER)
			cblk(TREE(ptree)->value);
		tree_walk(TREE(ptree)->rchild, cblk, worder);
		if (worder == WALK_POSORDER)
			cblk(TREE(ptree)->value);
	}
}
