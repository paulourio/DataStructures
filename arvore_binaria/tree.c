/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (August 2011)
 */
#include <stdlib.h>
#include "tree.h"

struct bstree {
	void    *parent;
	void    *lchild;
	void    *rchild;
	int 	value;
};


/* Aloca um novo nó */
static struct bstree *tree_new_node(const int value)
{
	struct bstree   *bst;

	bst = malloc(sizeof(struct bstree));
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


/* Procura um valor na árvore e retorna o nó */
static struct bstree *tree_search(struct bstree *ptree, const int valor)
{
	while (ptree != NULL && valor != ptree->value)
		if (valor < ptree->value)
			ptree = ptree->lchild;
		else
			ptree = ptree->rchild;
	return ptree;
}


/* Retorna o nó com o valor mínimo na árvore */
static struct bstree *tree_min(struct bstree *ptree)
{
	if (ptree != NULL && ptree->lchild)
		return tree_min(ptree->lchild);
	else
		return ptree;
}


/* Retorna o nó com o valor máximo na árvore */
static struct bstree *tree_max(struct bstree *ptree)
{
	if (ptree != NULL && ptree->rchild)
		return tree_max(ptree->rchild);
	else
		return ptree;
}


/* Encontra o sucessor */
static struct bstree *tree_successor(struct bstree *bst)
{
	struct bstree   *pai = bst->parent;

	if (bst->rchild != NULL)
		return tree_min(bst->rchild);
	while (pai != NULL && bst == pai->rchild)
		pai = (bst = pai)->parent;
	return pai;
}


/* Encontra o predecessor */
static struct bstree *tree_predecessor(struct bstree *bst)
{
	struct bstree   *pai = bst->parent;

	if (bst->lchild != NULL)
		return tree_max(bst->lchild);
	while (pai != NULL && bst == pai->lchild)
		pai = (bst = pai)->parent;
	return pai;
}


/* Inicializa uma árvore binária de busca vazia */
void *tree_new(void)
{
	return NULL;
}


/* Liberar todos os nós da árvore */
void tree_free(void **ptr)
{
	struct bstree	*tree;

	if (*ptr == NULL)
		return;
	tree = *ptr;
	tree_free(&tree->lchild);
	tree_free(&tree->rchild);
	free(*ptr);
	*ptr = NULL;
}


/* Inserir um valor na árvore */
void tree_insert(void **ptree, const int value)
{
	struct bstree   *prev = NULL, *bst = *ptree,
			*node = tree_new_node(value);

	while (bst != NULL) {
		prev = bst;
		bst = (value < bst->value)?  bst->lchild:  bst->rchild;
	}
	node->parent = prev;
	if (prev == NULL)
		*ptree = node;		/* Árvore está vazia. */
	else if (value < prev->value)
		prev->lchild = node;
	else
		prev->rchild = node;
}


/*
 * Se não tiver um dos filhos, o único filho será passado para o
 * pai, senão é buscado o nó sucessor. A função retorna qual nó
 * será removido.
 */
static struct bstree *tree_which_node(struct bstree *node)
{
	if (node->lchild == NULL || node->rchild == NULL)
		return node;
	else
		return tree_successor(node);
}


/* Define qual nó "neto" vai virar filho. */
static struct bstree *tree_which_son_node(struct bstree *node)
{
	return node->lchild != NULL?  node->lchild:  node->rchild;
}


/*
 * Atualiza a ligação do pai com o novo filho.
 * Se o nó a ser removido for na raiz, atualiza a raiz da árvore.
 * Senão atualiza o filho do pai, dependendo se o nó a ser removido
 * estiver na esquerda ou direita do pai.
 */
static void tree_update_father_node(void **ptree, struct bstree *node,
					struct bstree *new_son)
{
	struct bstree	*pai = node->parent;

	if (node->parent == NULL)
		*ptree = new_son;
	else if (node == pai->lchild)
		pai->lchild = new_son;
	else
		pai->rchild = new_son;
}


/*
 * Deletar um valor da árvore
 * Encontra o nó y que será removido e o filho x de que passará a ser
 * filho do pai.  Existe um caso em que nó y não tem o valor a ser removido,
 * neste caso y é uma folha e o valor é copiado para o nó com o valor a ser
 * removido.
 */
void tree_delete(void **ptree, const int value)
{
	struct bstree   *node, *y, *x;

	if (*ptree == NULL) {
		debug("Árvore vazia.\n");
		return;
	}
	node = tree_search(*ptree, value);
	if (node == NULL) {
		debug("Nó '%d' não encontrado.\n", value);
		return;
	}
	y = tree_which_node(node);
	x = tree_which_son_node(y);
	tree_update_father_node(ptree, y, x);
	if (y != node)
		node->value = y->value;
	free(y);
}


/* Percorre a Árvore */
void tree_walk(void *ptree, register const fbst_print cblk,
		register const enum TREE_WALKORDER worder)
{
	if (ptree != NULL) {
		struct bstree	*node = ptree;

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


int tree_min_value(void *ptree)
{
	return ptree != NULL?  tree_min(ptree)->value:  NOT_FOUND;
}


int tree_max_value(void *ptree)
{
	return ptree != NULL?  tree_max(ptree)->value:  NOT_FOUND;
}


int tree_successor_value(void *ptree, const int value)
{
	struct bstree   *no, *succ;

	if (ptree == NULL)
		return NOT_FOUND;
	no = tree_search(ptree, value);
	succ = tree_successor(no);
	return succ?  succ->value:  NOT_FOUND;
}


int tree_predecessor_value(void *ptree, const int value)
{
	struct bstree   *no, *pred;

	if (ptree == NULL)
		return NOT_FOUND;
	no = tree_search(ptree, value);
	pred = tree_predecessor(no);
	return pred != NULL?  pred->value:  NOT_FOUND;
}
