#include <tree.h>
#include <list.h>

struct node {
	void *tree;
	int count;
};

struct hm_data {
	char *data;
	int data_pos;
	list trees;
};
