include Make.defines

PROGS =	main.out

all:	${PROGS}

main.out:	main.o
		${CC} ${CFLAGS} -o $@ main.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
