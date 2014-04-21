#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "ran_tg.h"

double ran_tg_devroye(gsl_rng *r,double a) {
// Assume that a>0
//
   double x, e, twoasq = 2*a*a;

   do  {
        x = -log(gsl_rng_uniform(r));
        e = -log(gsl_rng_uniform(r));
    }
    while(x*x>twoasq*e);
    return a+x/a;
}


