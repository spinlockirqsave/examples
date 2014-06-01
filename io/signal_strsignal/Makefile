# Environment 
MKDIR=mkdir
CC= gcc
CFLAGS+= -g


PROGS = signal_strsignal

all:	${PROGS}

signal_strsignal:	main.o
		${CC} ${CFLAGS} -o signal_strsignal main.c ${LIBS}



clean:
		rm -f ${PROGS} ${CLEANFILES}