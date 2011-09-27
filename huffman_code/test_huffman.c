#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
	void *hc = huffman_new();

	//huffman_map(hc, "paulo roberto urio");
	huffman_map(hc, "victor alexandre padilha");
	huffman_compress(hc);
	
	huffman_print_final_tree(hc);

	huffman_table(hc);

	huffman_free(hc);
	return EXIT_SUCCESS;
}
