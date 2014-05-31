# Environment 
MKDIR=mkdir
CC= gcc
CFLAGS+= -g


PROGS = xor_swap_as

all:	${PROGS}

xor_swap_as:	main.o
		${CC} ${CFLAGS} -o xor_swap_as main.c ${LIBS}



clean:
		rm -f ${PROGS} ${CLEANFILES}