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
	return ptree && ptree->lchild?  tree_min(ptree->lchild):  ptree;
}


/* Retorna o valor máximo na Árvore */
static struct bstree *tree_max(struct bstree *ptree)
{
	return ptree && ptree->rchild?  tree_max(ptree->rchild):  ptree;
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


/*
 * Se não tiver um dos filhos, o único filho será passado para o
 * pai, senão é buscado o nó sucessor. A função retorna qual nó
 * será removido.
 */
static struct bstree *tree_which_node(struct bstree *node)
{
	if (!node->lchild || !node->rchild)
		return node;
	else
		return tree_successor(node);
}


/*
 * Define qual nó "neto" vai virar filho.
 */
static struct bstree *tree_which_son_node(struct bstree *node)
{
	if (node->lchild != NULL)
		return node->lchild;
	else
		return node->rchild;
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
	struct bstree	*pai = TREE(node->parent);

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

	if (!ptree || !PTREE(ptree)) {
		debug("Árvore vazia.\n");
		return;
	}
	node = tree_search(PTREE(ptree), value);
	if (!node) {
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
