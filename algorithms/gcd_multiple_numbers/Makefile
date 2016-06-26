include Make.defines

PROGS =	_gcd

all:	${PROGS}

_gcd:	main.o
		${CC} ${CFLAGS} -o $@ main.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
