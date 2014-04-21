    //****************************************
    // already #defined: N, I0, INVH, AMIN, AMAX
    #define ALPHA 1.83787706641  // = log(2*pi)
    double sim, simy, u;
    int k, ka, i;
    
    if (a<AMIN)  //if a is too small, use simple reject algorithm
        return ran_tg_reject(r,a);
    
    if (a>AMAX) // if a is too large, use Devroye's algorithm
        return ran_tg_devroye(r,a);

    i = I0+floor(a*INVH);
    ka = ncell[i];
    do {
      // sample integer between ka and N 
        k = ka+gsl_rng_uniform_int(r,N-ka+1); 
        if (k==N)  //right tail (last box on the right) 
                return ran_tg_devroye(r,x[N]); 
        if (k>ka+1)  {   // all the other boxes
            u = gsl_rng_uniform(r);
            simy = yu[k]*u;
            if (simy<yl[k]) { // that's what happens most of the time 
                sim = x[k]+u*delta[k];
                return sim;
            }
            // otherwise, check you're below the pdf curve
            sim = x[k]+d[k]*gsl_rng_uniform(r);
            if (sim*sim+2.*log(simy)+ALPHA<0.)
                return sim;
        }
	else {  // two leftmost regions 
            sim = x[k]+d[k]*gsl_rng_uniform(r);
            if (sim>=a) { //otherwise reject
                simy = yu[k]*gsl_rng_uniform(r);
                if (simy<yl[k])
                    return sim;
                if (sim*sim+2.*log(simy)+ALPHA<0.)
                    return sim;
                }
	}
    }
    while(1);

}


