include Make.defines

PROGS =	cf16_lcm

all:	${PROGS}

cf16_lcm:	main.o
		${CC} ${CFLAGS} -o $@ main.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
