#-*- coding: utf-8 -*-

# Simulation of bivariate truncated distributions,
# where truncations intervals are semi-finites 

# Nicolas Chopin, Sept. 2009
# nicolas dot chopin at ensae dot fr 
# see paper "Fast simulation of Truncated Gaussian distributions"

import scipy.stats as stats

LAMBDA = 0.68
SQRT_HALF_PI = sqrt(0.5*pi)
INV_SQRT_TWO_PI = 1./sqrt(2.*pi)


def hist_with_density(x,n,f):
    """ plot an histogram of x, with n bins,
    and overlays the density f"""
    h = hist(x,n,normed=True)
    plot(h[1],f(h[1])/sum(f(h[1]))*sum(h[0]),'r')

def simtruncugauss(a,b = None): 
    """ Simulate N(0,1) truncated to [a,b]
     with b= None means b = +infty
    """
    if a>1.: #accept-reject
        cont = True
        while(cont):
            u0 = 0. if (b==None) else exp(-a*(b-a))
            x = -log(u0+rand(1)*(1-u0))/a
            # Exp(a) variate truncated to [0,(b-a)]
            cont = (2.*log(rand(1))>-x**2)
        return double(a+x)
    if (b!=None) and (b<-1.):
        return -simtruncugauss(-b,-a)
    # inversion method
    ua = stats.norm.cdf(a)
    ub = 1. if (b==None) else stats.norm.cdf(b)
    return double(stats.norm.ppf(ua+(ub-ua)*rand(1)))

    
def simtruncgauss(mu,sigma,a,b=None): 
    """ Simulate N(mu,sigma^2) truncated to [a,b]
    """
    if (b==None):
        return mu+sigma*simtruncugauss((a-mu)/sigma)
    else:
        return mu+sigma*simtruncugauss((a-mu)/sigma,(b-mu)/sigma)
    

def c(m):
    """ 1/c(m) = min(sqrt(pi/2),-1/m) 
    c(m) is s.t. Phi(x)<phi(x)/c(m) for all x<=m<0
    """
    return max(0.797884560803,-m)

def r(x):
    " r(x) = Phi(x)/phi(x)"
    if x<-30:
        minvx = -1./x
        minvxsq = minvx**2
        r = minvx*(1-minvxsq+3.*minvxsq**2-15*minvxsq**3+105*minvxsq**4)
    else:
        r =  stats.norm.cdf(x)/stats.norm.pdf(x) 
    return r
    
    
def psi(x):
    " psi(x) = Phi(x)/phi(x)*exp(-LAMBDA*x) "
    return r(x)*exp(-LAMBDA*x)


def SP(mx,my,rho):
    " S+ algorithm"
    nsim = 1
    while(True):
        x = simtruncugauss(mx)
        y = stats.norm.rvs(rho*x,sqrt(1-rho**2))
        if y>my:
            break
        nsim += 1
    return (x,y,1./nsim)


def SM(mx,my,rho):
    "Algorithm S-"
    nsim = 1; spa = 0.
    nu = sqrt(1-rho**2); invnu = 1./nu
    while(True):
        x = simtruncgauss(rho*my,nu,mx)
        praccept = r(invnu*(rho*x-my))*c(invnu*(rho*mx-my))
        spa += praccept
        if rand(1) <= praccept: 
            break
        nsim += 1 
    y = simtruncgauss(rho*x,nu,my)
    return (x,y,spa/nsim)


def MP(mx,my,rho):
    " Algorithm M+"
    nsim = 1; spa = 0.
    nu = sqrt(1-rho**2); invnu = 1./nu
    b = -my*invnu
    shifted_mean = rho*(my+LAMBDA*nu)
    weight_p = stats.norm.cdf(-my/rho)
    psi_max = max(SQRT_HALF_PI,psi(invnu*(rho*mx-my)))
    weight_m = INV_SQRT_TWO_PI*nu*( stats.norm.cdf( invnu*(my/rho-shifted_mean)) 
        - stats.norm.cdf( invnu*(mx-shifted_mean)) )*exp( b*(LAMBDA-0.5*b)
        +0.5*invnu**2*shifted_mean**2 )*psi_max 
    sw = weight_p + weight_m
    while(True):
        if rand(1)*sw<weight_p:
            x = simtruncugauss(my/rho)
            y = stats.norm.rvs(rho*x,nu)
            # NOTE: LINE BELOW IS HERE ONLY BECAUSE WE WANT TO EVALUATE 
            # THE ACCEPTANCE RATE, OTHERWISE IT SHOULD BE REMOVED TO MAKE
            # COMPUTATIONS FASTER
            praccept = stats.norm.cdf(invnu*(rho*x-my))
            spa += praccept
            if y>=my:
                break
        else:
            x = simtruncgauss(shifted_mean,nu,mx,my/rho)
            praccept = psi(invnu*(rho*x-my))/psi_max
            spa += praccept
            if rand(1)<praccept:
                y = simtruncgauss(rho*x,nu,my)
                break
        nsim += 1
    return (x,y,spa/nsim)


def MM(mx,my,rho):
    " Algorithm M-"
    nsim = 1; spa = 0.
    nu = sqrt(1-rho**2); invnu = 1./nu
    weight_p = stats.norm.cdf(my/rho)-stats.norm.cdf(mx)
    weight_m = 0.5*nu*exp(-0.5*my**2)*stats.norm.cdf(-my*nu/rho)
    sw = weight_p + weight_m
    while(True):
        if sw*rand(1)<weight_p:
            x = simtruncugauss(mx,my/rho)
            y = stats.norm.rvs(rho*x,nu)
            # NOTE: LINE BELOW IS HERE ONLY BECAUSE WE WANT TO EVALUATE 
            # THE ACCEPTANCE RATE, OTHERWISE IT SHOULD BE REMOVED TO MAKE
            # COMPUTATIONS FASTER
            praccept = stats.norm.cdf( invnu*(rho*x-my))
            spa += praccept
            if y>=my:
                break
        else:
            x = simtruncgauss(rho*my,nu,my/rho)
            praccept = sqrt(2/pi)*r( invnu*(rho*x-my) )
            spa += praccept
            if rand(1)<praccept:
                y = simtruncgauss(rho*x,nu,my)
                break
        nsim += 1
    return (x,y,spa/nsim)


def bitg(mx,my,rho):
    """ Simulate bivariate Gaussian (x,y) ~ N( (0,0) , (1, rho; rho 1) ) 
    truncated to x>mx and y>my
    Note: reqires that mx>my
    """
    
    if rho>0.:
        if my<rho*mx: # Algorithm S+
            return SP(mx,my,rho)
        else: # Algorithm M+
            return MP(mx,my,rho)
    else: # if rho<=0
        if mx < -0.43072729929545756: # = Phi^{-1} (1/3)
            return SP(mx,my,rho)
        if my>rho*mx:
            return SM(mx,my,rho)
        else:  # Algorithm M-
            return MM(mx,my,rho)
                
            
def test(mx,my,rho,N=1000):
    """ for a given set (mx,my,rho) of parameters,
    return the average acceptance rate over N simulations
    """
    p = empty(N,double)
    for i in xrange(N):
        (x,y,p[i]) = bitg(mx,my,rho)
    res = mean(p)
    return double(res)


def testmc(N):
    """ Monte Carlo test:
    simulate N parameters (mx,my,rho) and compute
    the average acceptance rate for each parameter 
    """
    mymx = sort(randn(N,2),axis=1) # sort so that mx>my
    rho = rand(N)
    ar = empty(N,double)
    for i in xrange(N):
        ar[i] = test(mymx[i,1],mymx[i,0],rho[i])
        if ar[i]<0.5:
            ar[i] = test(mymx[i,1],mymx[i,0],rho[i],10000)
            print ar[i], mymx[i,1],mymx[i,0],rho[i]
    return ar


def testmc2d(N):
    " same as above, but with mx=my " 
    m = randn(N)
    rho = rand(N)
    ar = empty(N,double)
    for i in xrange(N):
        ar[i] = test(m[i],m[i],rho[i])
        if ar[i]<0.5:
            print m[i], rho[i], ar[i]
    return ar


def histx(mx,my,rho,N=5000):
    """ Histogram of simulated values, with
    marginal density of x overlaid
    """
    
    def marg_x(x):
        return stats.norm.pdf(x)*stats.norm.cdf((rho*x-my)/sqrt(1-rho**2))
    
    if mx<my:
        return "error: mx<my"
    x = empty(N,double)
    for i in xrange(N):
        (x[i],y,p)=bitg(mx,my,rho)
    hist_with_density(x,100,marg_x)


# examples
ar = testmc(100)
hist(ar)
figure()
a1,b1,rho = 1.2,1.,0.3 # we need that a1>b1
histx(a1,b1,rho,500)
title(r'$(a_1,b_1,\rho)=($'+str(a1)+','+str(b1)+','+str(rho)+')')
