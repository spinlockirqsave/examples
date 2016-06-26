include Make.defines

PROGS =	_lcm

all:	${PROGS}

_lcm:	main.o
		${CC} ${CFLAGS} -o $@ main.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
