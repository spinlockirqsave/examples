/* 
 * File:   main.cpp
 * Author: Piotr Gregor  peter@
 *
 * Created on June 27, 2013, 1:49 AM
 */

/*
 *      Przykładowy program dla kursu "POSIX Threads" z wikibooks.pl
 *
 *      Temat: priorytety wątków
 *
 *      Autor: Wojciech Muła
 *      Ostatnia zmiana: 2010-03-xx
 */
#define _XOPEN_SOURCE   500
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
 
#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)
 
typedef struct {
        int     licznik;
        char    przerwij;
        int     priorytet;
} Arg;
 
/* funkcja wykonywana w wątku - zwiększa licznik */
void* watek(void* _arg) {
        Arg *arg = (Arg*)_arg;
 
        arg->licznik = 0;
        while (!arg->przerwij) {
                arg->licznik += 1;
                usleep(10);
        }
 
        return NULL;
}
//------------------------------------------------------------------------
 
#define N 4     /* liczba wątków */
 
int main(int argc, char* argv[]) {
        pthread_t id[N];
        pthread_attr_t attr;
        Arg arg[N];
        int pmin, pmax;
        int i, sched_policy;
        struct sched_param sp;
 
        sched_policy = SCHED_OTHER;
        if (argc > 1)
                switch (atoi(argv[1])) {
                        case 0:
                                sched_policy = SCHED_OTHER;
                                break;
                        case 1:
                                sched_policy = SCHED_RR;
                                break;
                        case 2:
                                sched_policy = SCHED_FIFO;
                                break;
                }
        else {
                puts("program [0|1|2]");
                return EXIT_FAILURE;
        }
 
        pmin = sched_get_priority_min(sched_policy);
        pmax = sched_get_priority_max(sched_policy);
        switch (sched_policy) {
                case SCHED_OTHER:
                        printf("SCHED_OTHER: priorytety w zakresie %d ... %d\n", pmin, pmax);
                        break;
                case SCHED_RR:
                        printf("SCHED_RR: priorytety w zakresie %d ... %d\n", pmin, pmax);
                        break;
                case SCHED_FIFO:
                        printf("SCHED_FIFO: priorytety w zakresie %d ... %d\n", pmin, pmax);
                        break;
        }
 
        errno = pthread_attr_init(&attr);
        test_errno("pthread_attr_init");
 
        /* parametry szeregowania odczytywane z atrybutów  */
        errno = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        test_errno("pthread_attr_setinheritsched");
 
        /* wybór podanego algorytmu szeregowania */
        errno = pthread_attr_setschedpolicy(&attr, sched_policy);
        test_errno("pthread_attr_setschedpolicy");
 
        /* utworzenie kilku wątków wątku z różnymi priorytetami */
        for (i=0; i < N; i++) {
                /* kolejne wątki mają coraz wyższe priorytety */
                sp.sched_priority = pmin + (pmax-pmin) * i/(float)(N-1);
                arg[i].przerwij   = 0;
                arg[i].licznik    = 0;
                arg[i].priorytet  = sp.sched_priority;
 
                /* ustawienie priorytetu */
                errno = pthread_attr_setschedparam(&attr, &sp);
                test_errno("pthread_attr_setschedparam");
 
                /* uruchomienie wątku */
                errno = pthread_create(&id[i], &attr, watek, &arg[i]);
                test_errno("pthread_create");
 
                printf("utworzono wątek #%d o priorytecie %d\n", i, arg[i].priorytet);
        }
 
        errno = pthread_attr_destroy(&attr);
        test_errno("pthread_attr_destroy");
 
        /* oczekiwanie */
        sleep(2);
 
        /* ustawienie flagi zakończenia pracy, którą testują funkcje wątków 
           oraz odczyt ich bieżących liczników */
        for (i=0; i < N; i++) {
                arg[i].przerwij = 1;
                printf("wątek #%d (priorytet %3d): licznik = %d\n",
                        i,
                        arg[i].priorytet,
                        arg[i].licznik
                );
        }
 
        /* teraz oczekiwanie na ich zakończenie */
        for (i=0; i < N; i++) {
                errno = pthread_join(id[i], NULL);
                test_errno("pthread_join");
        }
 
        return EXIT_SUCCESS;
}
//------------------------------------------------------------------------

