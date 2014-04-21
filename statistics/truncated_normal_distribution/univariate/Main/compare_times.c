#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <time.h>
#include <stdio.h>
#include "ran_tg.h"
#define NSIMS 10*1000*1000

double ran_tg_robert(gsl_rng *r,double a)
{
    double t,logu,z;

    if (a<0.)
        return ran_tg_reject(r,a);

    t = 0.5*(a+sqrt(a*a+4.));
    do
    {
        z = a - log(gsl_rng_uniform(r))/t;
        logu = log(gsl_rng_uniform(r));
    }
    while (logu>-0.5*gsl_pow_2(z-t));
    return z;
}

double ran_tg_devroye_reject(gsl_rng *r,double a)
{
    if (a<0.65)
        return ran_tg_reject(r,a);
    else
        return ran_tg_devroye(r,a);
}

double ran_tg_inverse(gsl_rng *r,double a)
{
    double u,z;

    if (a<5.) {
      u = gsl_rng_uniform(r);
      z = gsl_cdf_ugaussian_P(-a);
      return -gsl_cdf_ugaussian_Pinv(z*u);
    }
    else
      return ran_tg_devroye(r,a);
}



int main()
{
    long int i, j;
    double x, a;
    clock_t tic, tac;

    /* RNG initialisation */
    gsl_rng_type * T;
    gsl_rng * r;
    gsl_rng_env_setup();
    //T = gsl_rng_ranlxd1;  // generator with good math properties
    //T = gsl_rng_taus; //default generator
    T = gsl_rng_mrg;
    r = gsl_rng_alloc(T);

    a = -4.1;
    for (j = 0; j< 80; j++) {
        
        a = a + 0.1;
        printf("%f  ",a);
        tic = clock();
        for (i = 0; i < NSIMS; i++) 
            x = ran_tg_zig1000(r,a);
        tac = clock();
        printf("%f  ",((double)(tac-tic))/CLOCKS_PER_SEC);

        tic = clock();
        for (i = 0; i < NSIMS; i++) 
            x = ran_tg_zig2000(r,a);
        tac = clock();
        printf("%f  ",((double)(tac-tic))/CLOCKS_PER_SEC);    

        tic = clock();
        for (i = 0; i < NSIMS; i++) 
            x = ran_tg_zig4000(r,a);
        tac = clock();
        printf("%f  ",((double)(tac-tic))/CLOCKS_PER_SEC);

        tic = clock();
        for (i  = 0; i < NSIMS; i++)
            x = ran_tg_robert(r,a);
        tac = clock();
        printf("%f  ",((double)(tac-tic))/CLOCKS_PER_SEC);
    
        tic = clock();
            for (i = 0; i < NSIMS; i++)
                x = ran_tg_devroye_reject(r,a);
            tac = clock();
            printf("%f ",((double)(tac-tic))/CLOCKS_PER_SEC);
    
        tic = clock();
            for (i = 0; i < NSIMS; i++)
                x = ran_tg_inverse(r,a);
            tac = clock();
            printf("%f\n",((double)(tac-tic))/CLOCKS_PER_SEC);
    }
    
}

