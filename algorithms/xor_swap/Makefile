# Environment 
MKDIR=mkdir
CC= gcc
CFLAGS+= -g


PROGS = xor_swap

all:	${PROGS}

xor_swap:	main.o
		${CC} ${CFLAGS} -o xor_swap main.c ${LIBS}



clean:
		rm -f ${PROGS} ${CLEANFILES}