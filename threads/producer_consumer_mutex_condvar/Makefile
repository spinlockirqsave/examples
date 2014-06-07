# Environment 
MKDIR=mkdir
CC= gcc
CFLAGS+= -g
LIBS+= -lpthread


PROGS = producer_consumer_mutex_condvar

all:	${PROGS}
	
producer_consumer_mutex_condvar:	main.o
		${CC} ${CFLAGS} -o producer_consumer_mutex_condvar main.c ${LIBS}
	


clean:
		rm -f ${PROGS} ${CLEANFILES}