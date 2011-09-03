
PROGRAMA=ldec
FONTES=ldec.c test.c
INCLUDES=.

BIBLIOTECAS=m

CC=cc
#CFLAGS=-g -Wall -Wextra
CFLAGS=-Wall -g -O2 -Wshadow -Winit-self -Wredundant-decls -Wcast-align \
        -Wundef -Wfloat-equal -Winline -Wmissing-declarations \
        -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wmain -Wextra \
        -Wall -x c -std=gnu99 -pipe -Wformat=2 -Wnonnull -Wuninitialized \
        -Wtraditional-conversion -Wunsafe-loop-optimizations \
        -Wpointer-arith -Wbad-function-cast -Wconversion -Wempty-body -Wlogical-op \
        -Waggregate-return -Wstrict-prototypes -Wmissing-parameter-type \
        -Wmissing-prototypes -Wmissing-field-initializers -Wmissing-format-attribute \
        -Wpacked -Wdisabled-optimization -Wmissing-braces \
        -Werror-implicit-function-declaration -ffinite-math-only -march=native \
        -DHAVE_INLINE 

default: $(PROGRAMA)

$(PROGRAMA): $(FONTES:.c=.o)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(FONTES) -o$(PROGRAMA) -l$(BIBLIOTECAS)

clean:
	$(RM) -f $(PROGRAMA) $(FONTES:.c=.o)
