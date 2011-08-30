#include <stdlib.h>
#include "tree.h"

struct bstree {
	void    *parent;
	void    *lchild;
	void    *rchild;
	int value;
};


/* Acessar Árvore quando for ponteiro */
#define TREE(bst)   ((struct bstree *) bst)
/* Acessar Árvore quando for ponteiro para ponteiro */
#define PTREE(bst)  (* (struct bstree **) bst)
/* Verificar se é uma folha */
#define LEAF(bst)   (!(bst)->lchild && !(bst)->rchild)

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
	while (ptree && valor != ptree->value)
		if (valor < ptree->value)
			ptree = ptree->lchild;
		else
			ptree = ptree->rchild;
	return ptree;
}


/* Retorna o valor mínimo na Árvore */
static struct bstree *tree_min(struct bstree *ptree)
{
	return ptree && ptree->lchild? tree_min(ptree->lchild): ptree;
}


/* Retorna o valor máximo na Árvore */
static struct bstree *tree_max(struct bstree *ptree)
{
	return ptree && ptree->rchild? tree_max(ptree->rchild): ptree;
}


/* Encontrar o sucessor */
static struct bstree *tree_successor(struct bstree *bst)
{
	struct bstree   *pai = bst->parent;

	if (bst->rchild != NULL)
		return tree_min(bst->rchild);
	while (pai && bst == pai->rchild) {
		bst = pai;
		pai = pai->parent;
	}
	return pai;
}


/* Encontrar o predecessor */
static struct bstree *tree_predecessor(struct bstree *bst)
{
	struct bstree   *pai = bst->parent;

	if (bst->lchild != NULL)
		return tree_max(bst->lchild);
	while (pai && bst == pai->lchild) {
		bst = pai;
		pai = pai->parent;
	}
	return pai;
}


/* Inicializa uma Árvore binária de busca vazia */
void *tree_new(void)
{
	return NULL;
}


/* Liberar todos os nós da árvore */
void tree_free(void **ptr)
{
	if (!ptr || !PTREE(ptr))
		return;
	tree_free(&PTREE(ptr)->lchild);
	tree_free(&PTREE(ptr)->rchild);
	free(PTREE(ptr));
	PTREE(ptr) = NULL;
}


/* Inserir um valor na árvore */
void tree_insert(void **ptree, const int value)
{
	struct bstree   *prev = NULL, *bst = PTREE(ptree),
			*node = tree_new_node(value);

	while (bst) {
		prev = bst;
		bst = (value < bst->value)?  bst->lchild:  bst->rchild;
	}
	node->parent = prev;
	if (prev == NULL)
		PTREE(ptree) = node;    /* Árvore está vazia. */
	else if (value < prev->value)
		prev->lchild = node;
	else
		prev->rchild = node;
}


/* Deletar um valor da árvore */
void tree_delete(void **ptree, const int value)
{
	struct bstree   *node, *y, *x;

	if (!ptree || !PTREE(ptree)) {
		debug("Árvore vazia.\n");
		return;
	}
	node = tree_search(PTREE(ptree), value);
	if (!node) {
		debug("Nó '%d' não encontrado.\n", value);
		return;
	}
	if (!node->lchild || !node->rchild) {
		/* Se não tiver os dois filhos o único filho vira
		filha do pai. */
		y = node;
	} else {
		/* Possui os dois filhos, procura o nó sucessor. */
		y = tree_successor(node);
	}
	/* Qual "neto" vai virar filho ? */
	if (y->lchild) {
		x = y->lchild;
	} else {
		x = y->rchild;
	}
	if (x) {
		/* Atualiza a ligação do filho com o novo pai. */
		x->parent = y->parent;
	}
	if (y->parent == NULL) {
		/* Se estiver removendo a raiz, atualiza a nova raiz */
		PTREE(ptree) = x;
	} else if (y == TREE(TREE(y->parent)->lchild)) {
		/* Se estiver removendo o filho esquerdo */
		TREE(y->parent)->lchild = x;
		} else {
			/* Se estiver removendo o filho direito */
		TREE(y->parent)->rchild = x;
		}
	if (y != node) {
		/* Se estiver na verdade removendo um nó que era
		   sucessor, copia os dados do sucessor para o lugar do
		   nó que era pra ser removido. */
		node->value = y->value;
	}
	free(y);
}


/* Percorrer a Árvore */
void tree_walk(void *ptree, register const fbst_print cblk,
		register const enum TREE_WALKORDER worder)
{
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


int tree_min_value(void *ptree)
{
	return ptree? tree_min(ptree)->value: 0;
}


int tree_max_value(void *ptree)
{
	return ptree? tree_max(ptree)->value: 0;
}


int tree_successor_value(void *ptree, const int value)
{
	struct bstree   *no, *succ;

	if (!ptree)
		return NOT_FOUND;
	no = tree_search(ptree, value);
	succ = tree_successor(no);
	return succ?  succ->value:  NOT_FOUND;
}


int tree_predecessor_value(void *ptree, const int value)
{
	struct bstree   *no, *pred;

	if (!ptree)
		return NOT_FOUND;
	no = tree_search(ptree, value);
	pred = tree_predecessor(no);
	return pred?  pred->value:  NOT_FOUND;
}
