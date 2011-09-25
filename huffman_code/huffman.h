#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

extern void *huffman_new(void);
extern void *huffman_free(void *pcode);
extern void huffman_map(void *pcode, const unsigned char *data);
extern void huffman_compress(void *pcode);

#endif
