#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
	void *hc = huffman_new();

	huffman_compress(hc, "paulo roberto urio");
	
	huffman_free(hc);
	return EXIT_SUCCESS;
}
