
PROGRAMA=huffman
OBJS=huffman.o tree.o list.o 

INCLUDES=-I. -Iinclude

BIBLIOTECAS=-lm

CC=cc
#CFLAGS=-g -Wall -Wextra
CFLAGS=-Wall -g -O2 -Wshadow -Winit-self -Wredundant-decls -Wcast-align \
        -Wundef -Wfloat-equal -Winline -Wmissing-declarations \
        -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wmain -Wextra \
        -Wall -x c -std=gnu99 -pipe -Wformat=2 -Wnonnull -Wuninitialized \
        -Wtraditional-conversion -Wunsafe-loop-optimizations \
        -Wpointer-arith -Wbad-function-cast -Wconversion -Wempty-body \
	-Wlogical-op -Waggregate-return -Wstrict-prototypes \
	-Wmissing-parameter-type -Wmissing-prototypes \
	-Wmissing-field-initializers -Wmissing-format-attribute \
        -Wpacked -Wdisabled-optimization -Wmissing-braces \
        -Werror-implicit-function-declaration -ffinite-math-only -march=native \
        -DHAVE_INLINE 

$(PROGRAMA): $(OBJS) test.o
	$(CC) $(LDFLAGS) $(INCLUDES) $(OBJS) test.o -o$(PROGRAMA) $(BIBLIOTECAS)

huffman.o: include/list.h include/tree.h huffman.c
	$(CC) $(CFLAGS) $(INCLUDES) -c huffman.c

tree.o: include/tree.h lib/tree.c
	$(CC) $(CFLAGS) $(INCLUDES) -c lib/tree.c

list.o: include/list.h lib/list.c
	$(CC) $(CFLAGS) $(INCLUDES) -c lib/list.c

test.o: huffman.h
	$(CC) $(CFLAGS) $(CINLUDES) -c test.c


#test: $(PROGRAMA)
#	echo "TODO"

clean:
	$(RM) $(PROGRAMA) $(OBJS) test.o
