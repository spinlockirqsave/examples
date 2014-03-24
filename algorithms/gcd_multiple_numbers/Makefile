include Make.defines

PROGS =	cf16_gcd

all:	${PROGS}

cf16_gcd:	main.o
		${CC} ${CFLAGS} -o $@ main.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
