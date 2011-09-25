#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
	void *hc = huffman_new();

	huffman_map(hc, "paulo roberto urio");
	huffman_compress(hc);

	huffman_free(hc);
	return EXIT_SUCCESS;
}
