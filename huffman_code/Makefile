
PROGRAMA=huffman
OBJS=huffman.o tree.o list.o 

INCLUDES=-I. -Iinclude

BIBLIOTECAS=-lm

CC=cc
#CFLAGS=-g -Wall -Wextra
INSANE_FLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align \
        -Wundef -Wfloat-equal -Winline -Wmissing-declarations \
        -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wmain \
	-Wformat=2 -Wnonnull -Wuninitialized \
        -Wtraditional-conversion -Wunsafe-loop-optimizations \
        -Wpointer-arith -Wbad-function-cast -Wconversion -Wempty-body \
	-Wlogical-op -Waggregate-return -Wstrict-prototypes \
	-Wmissing-parameter-type -Wmissing-prototypes \
	-Wmissing-field-initializers -Wmissing-format-attribute \
        -Wpacked -Wdisabled-optimization -Wmissing-braces \
        -Werror-implicit-function-declaration

CFLAGS=-Wall -g -O2 -Wextra -x c -std=gnu99 -pipe -ffinite-math-only \
        -march=native \
	-DHAVE_INLINE $(INSANE_FLAGS)

$(PROGRAMA): $(OBJS) test.o
	$(CC) $(LDFLAGS) $(INCLUDES) $(OBJS) test.o -o$(PROGRAMA) $(BIBLIOTECAS)

huffman.o: include/list.h include/tree.h huffman.c
	$(CC) $(CFLAGS) $(INCLUDES) -c huffman.c

tree.o: include/tree.h lib/tree.c
	$(CC) $(CFLAGS) $(INCLUDES) -c lib/tree.c

list.o: include/list.h lib/list.c
	$(CC) $(CFLAGS) $(INCLUDES) -c lib/list.c

test.o: huffman.h
	$(CC) $(CFLAGS) $(INCLUDES) -c test.c

list_spec.o: include/list.h list.o spec/list_spec.c
	$(CC) $(CFLAGS) $(INCLUDES) -c spec/list_spec.c

test_list: list_spec.o list.o spec/list_spec.c
	$(CC) $(LDFLAGS) $(INCLUDES) list_spec.o list.o -o test_list

clean:
	$(RM) $(PROGRAMA) $(OBJS) test.o list_spec.o test_list
