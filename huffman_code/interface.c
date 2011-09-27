#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

#define MAX 10000000

int main(void)
{
	void *hc = huffman_new();
	char *buffer = malloc(sizeof(char) * MAX);
	int offset = 0;
	int bytes_left = MAX;
	int read;

	while (!feof(stdin) && bytes_left > 0) {
		if (fgets(buffer + offset, bytes_left, stdin) == NULL)
			break;
		read = (int) strlen(buffer + offset);
		bytes_left -= read;
		offset += read - 1;
	}
	fprintf(stderr, "I read \"%s\"\n", buffer);

	huffman_compress(hc, buffer); 
	
	free(buffer);
	huffman_free(hc);
	return EXIT_SUCCESS;
}
