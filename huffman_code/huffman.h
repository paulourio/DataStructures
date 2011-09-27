#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

extern void *huffman_new(void);
extern void *huffman_free(void *pcode);
extern void huffman_map(void *pcode, const char *data);
extern void huffman_compress(void *pcode);
extern void huffman_print_final_tree(void *pcode);
extern void huffman_table(void *pcode);

#endif
