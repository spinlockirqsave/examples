#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "ran_tg.h"


double ran_tg_reject(gsl_rng *r,double a)
{
    double x;

    do 
        x = ziggurat(r);
    while(x<a);
    return x;
}
