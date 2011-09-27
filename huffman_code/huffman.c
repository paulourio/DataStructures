#include <tree.h>
#include <list.h>
#include <string.h>
#include "huffman.h"

#define EXTENDED_TREE (47)

struct value {
	void *tree;
	int count;
};

struct huffdata {
	list *trees;
	void *final; /* Final compressed tree. */
	dict *table;
};

static void print_data(const struct huffdata *code)
{
	struct lnode *n = code->trees->front;

	while (n != NULL) {
		struct value *nv = n->value;
		fprintf(stderr, "%c:%d ", 
				tree_root_value(nv->tree), nv->count);
		n = n->next;
	}
	fprintf(stderr, "\n");
}

static int compare_count(const void *a, const void *b)
{
	const struct value *_a = a, *_b = b;
	int va = _a->count;
	int vb = _b->count;

	if (va > vb)
		return 1;
	else if (vb > va)
		return -1;
	return 0;
}

static int compare_char(const void *a, const void *b)
{
	const struct value *_a = a, *_b = b;
	int va = tree_root_value(_a->tree);
	int vb = tree_root_value(_b->tree);

	if (va > vb)
		return 1;
	else if (vb > va)
		return -1;
	return 0;
}

static void free_list_node_value(void *v)
{
	struct value *value = v;
	if (value->tree != NULL)
		tree_free(&value->tree);
	else
		fprintf(stderr, "Trying to free a null tree.\n");
	free(v);
}

void *huffman_new(void)
{
	struct huffdata *code;

	code = malloc(sizeof(struct huffdata));
	if (code == NULL) {
		fprintf(stderr, "Can't create new huffman's code.\n");
		exit(1);
	}
	code->trees = list_new();
	code->final = NULL;
	code->table = NULL;
	list_set_free_value_method(code->trees, free_list_node_value);
	list_set_compare_function(code->trees, compare_count);
	return code;
}

void *huffman_free(void *pcode)
{
	struct huffdata *code = pcode;

	if (code != NULL) {
		code->trees = list_free(code->trees);
		if (code->table != NULL)
			dict_free(code->table);
		free(code);
	}
	return NULL;
}

static void process_char(struct huffdata *code, const char *chr)
{
	const char current = *chr;
	struct value *new, *v;

	new = malloc(sizeof(struct value));
	if (new == NULL) {
		fprintf(stderr, "Can't allocate node for '%c'.\n", current);
		exit(1);
	}
	new->tree = tree_new();
	tree_insert(&new->tree, (int) current);

	v = list_find(code->trees, new, compare_char);
	if (v == NULL) {
		int count = 0;

		while (*chr) {
			if (*chr++ == current)
				count++;
		}
		new->count = count;
		list_insert_sorted(code->trees, new);
	} else {
		tree_free(&new->tree);
		free(new);
	}
}

/*
 * Process the input and update the tree list. The map process must be
 * executed before compress execution.
 */
static void huffman_map(void *pcode, const char *data)
{
	while (*data)
		process_char(pcode, data++);
	print_data(pcode);
}

static void huffman_merge(list *trees, struct value *a, 
		struct value *b)
{
	void *m = tree_new();

	tree_insert(&m, EXTENDED_TREE);
	/* Instead the usual insertion, we will force the childs. */
	tree_set_childs(m, a->tree, b->tree);
	/* Both struct values are not useful anymore. We reutilize one
	 * and other is free'd */
	a->tree = m;
	a->count += b->count;
	free(b);
	/* Add the new merged tree to the list. */
	list_insert_sorted(trees, a);
}

static void huffman_compress_tree(void *pcode)
{
	struct huffdata *code = pcode;
		
	while (list_size(code->trees) > 1) {
		struct value *a = list_remove_front(code->trees);
		struct value *b = list_remove_front(code->trees);

		//fprintf(stderr, "Merging %c with %c\n", 
		//		tree_get_value(a->tree),
		//		tree_get_value(b->tree));
		huffman_merge(code->trees, a, b);
		//print_data(code);
	}
	code->final = list_get(code->trees, 0); 
}

static int node_count;
static void huffman_print_node(const int v)
{
	char c = (char) v;
	
	if (c == ' ')
		c = '~';
	printf("%d %c ", node_count++, c);
}

static void huffman_print_final_tree(void *pcode)
{
	struct huffdata *code = pcode;
	struct value *v = code->final;
	
	if (v == NULL) {
		fprintf(stderr, "Empty list.\n");
	}
	tree_print_to_bosque(v->tree);
}

static void huffman_table(void *pcode)
{
	struct huffdata *code = pcode;
	struct value *v = code->final;

	/* check empty list */
	code->table = tree_create_table(v->tree);
}

static int huffman_export_bits(struct huffdata *code, char *data)
{
	int bits = 0;

	fprintf(stderr, "Result: \n");
	while (*data) {
		char key[2] = { *data++, 0 };
		char *value = dict_value(code->table, (char *) &key);

		fprintf(stderr, "%s", value);
		bits += (int) strlen(value);
	}
	fprintf(stderr, "\n");
	return bits;
}

void huffman_compress(void *pcode, const char *data)
{
	/*fprintf(stderr, "Compressing \"%s\"\n", data); */
	huffman_map(pcode, data);
	huffman_compress_tree(pcode);
	huffman_table(pcode);
	/*huffman_print_final_tree(pcode); /* Bosque */
	int new_size = huffman_export_bits(pcode, (char *) data);
	int old_size = (int) strlen(data);
	fprintf(stderr, "Compressed %.2f%%\n", 
			(1 - ((new_size/8.0) / old_size)) * 100);
}
