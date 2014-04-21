#-*- coding: utf-8 -*-

# Simulation of a bivariate truncated Gaussian distribution
# subject to each component being in a finite interval.

# Nicolas Chopin
# nicolas dot chopin at ensae dot fr
# see paper "Fast simulation of Truncated Gaussian distributions"

from scipy import *
import scipy.stats as stats 

LAMBDA = 0.68
DELTAMAX = 2.
NSIM_MAX = 20
SQRT_HALF_PI = sqrt(0.5*pi)
INV_SQRT_TWO_PI = 1./sqrt(2.*pi)
LOG_INV_SQRT_TWO_PI = log(INV_SQRT_TWO_PI)
G = stats.norm


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
            x = -log(u0+rand(1)*(1-u0))/a # Exp(a) truncated to [0,(b-a)]
            cont = (2.*log(rand(1))>-x**2)
        return double(a+x)
    if (b!=None) and (b<-1.):
        return -simtruncugauss(-b,-a)
    # inversion method
    ua = G.cdf(a)
    ub = 1. if (b==None) else G.cdf(b)
    return double(G.ppf(ua+(ub-ua)*rand(1)))

    
def simtruncgauss(mu,sigma,a,b=None): 
    """ Simulate N(mu,sigma^2) truncated to [a,b]
    """
    if (b==None):
        return mu+sigma*simtruncugauss((a-mu)/sigma)
    else:
        return mu+sigma*simtruncugauss((a-mu)/sigma,(b-mu)/sigma)
    
def simtruncexp(l,a,b): 
    """ Simulates X~ Exp(-l) subject to X in [a,b]
    note: l may be negative
    """
    z = exp(l*(b-a))-1.
    u = rand()
    x =  a+log(1.+u*z)/l
    return real(x)

def c(m):
    """ 1/c(m) = min(sqrt(pi/2),-1/m) for m<=0
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
        r =  G.cdf(x)/G.pdf(x) 
    return r
    
def chi(x):
    " chi(x) = Phi(x)/phi(x)*exp(-LAMBDA*x) "
    return r(x)*exp(-LAMBDA*x)


def btg(rho,ax,bx,ay,by):
    """ simulates a bivariate Gaussian vector (x,y)~ N(0,(rho 1,1 rho)) 
    subject to x in [ax,bx], y in [ay,by]
    """
    
    def logdG(y,x):
        """returns log(Phi(y)-Phi(x)), for y>x
        note: use asymptotic expansions to avoid overflow errors
        """
        if y>0:
            x,y = -y, -x
        if y>-30:
            d  = log(G.cdf(y)-G.cdf(x))
        else:
            y2 = y*y
            d = ( log(r(y)-r(x)*exp(0.5*(y2-x*x)))-0.5*y2 
                + LOG_INV_SQRT_TWO_PI )
        return d
    
    def logf(x,alpha,beta0,beta1):
       "log marginal density"
       return -0.5*x**2+logdG(alpha*x+beta1,alpha*x+beta0)
    
    def dlogf(x,alpha,beta0,beta1):
        "derivative of above function"
        a1 = alpha*x+beta1; a0 = alpha*x+beta0
        d = ( -x+alpha*exp(-logdG(a1,a0)+
                log(1.-exp(0.5*(a1**2-a0**2)))
                + LOG_INV_SQRT_TWO_PI-0.5*a1**2) )
        return d
    
    nsim = 0
    spa = 0.
    sgn = 1.
    nu = sqrt(1.-rho**2)
    invnu = 1./nu
    alpha, beta0,beta1 = invnu*rho,-invnu*by,-invnu*ay
    # marginal of X is : phi(x)*[Phi(alpha*x+beta1)-Phi(alpha*x+beta0)]
    if (beta1-beta0<DELTAMAX):
        # Algorithm T
        approx_mean = -0.5*alpha/(1+alpha**2)*(beta0+beta1)
        approx_std = nu
        if (ax>approx_mean) or (bx<approx_mean):
            if ax>approx_mean:
                x0 = max(min(approx_mean+approx_std,bx),ax)
            else:
                x0 = min(max(approx_mean-approx_std,ax),bx)
            y0 = logf(x0,alpha,beta0,beta1)
            l = dlogf(x0,alpha,beta0,beta1)
            while(True):
                nsim += 1
                x = simtruncexp(l,ax,bx)
                praccept = exp(logf(x,alpha,beta0,beta1)-y0-l*(x-x0))
                spa += praccept
                if (rand()<praccept) or (nsim>NSIM_MAX):
                    break
        else:
            x0 = max(approx_mean-approx_std,ax)
            x1 = min(approx_mean+approx_std,bx)
            y0 = logf(x0,alpha,beta0,beta1)
            y1 = logf(x1,alpha,beta0,beta1)
            l0 = dlogf(x0,alpha,beta0,beta1)
            l1 = dlogf(x1,alpha,beta0,beta1)
            xc = (y0-l0*x0-y1+l1*x1)/(l1-l0)
            left_mass = exp(-l0*xc)-exp(-l0*ax)
            right_mass = exp(-l1*bx)-exp(-l1*xc)
            mass = left_mass + right_mass
            while(True):
                nsim += 1 
                if left_mass*rand()<mass:
                    x = simtruncexp(l0,ax,xc)
                    praccept = exp(logf(x,alpha,beta0,beta1)-y0-l0*(x-x0))
                else:
                    x = simtruncexp(l1,xc,bx)
                    praccept = exp(logf(x,alpha,beta0,beta1)-y1-l1*(x-x1))
                spa += praccept
                if (rand()<praccept)  or (nsim>NSIM_MAX):
                    break
    else: #beta1-beta0>DELTAMAX
        # Algorithm M3
            xl = -beta1/alpha; xr = -beta0/alpha
            # Left component
            if ax>xl: #if left component is empty
                weight_left = 0. 
            else:
                if min(bx,xl)>0.:
                    mean_left =  rho*(ay+LAMBDA*nu)
                    pmax = max(SQRT_HALF_PI,chi(alpha*ax+beta1))
                    if bx<xl:
                        weight_left = 1. 
                    else:
                        weight_left = INV_SQRT_TWO_PI*nu*pmax*exp(
                            0.5*invnu**2*(mean_left**2-ay**2-2.*LAMBDA*nu*ay)+
                            logdG(invnu*(xl-mean_left),invnu*(ax-mean_left)) )
                else:
                    mean_left = rho*ay
                    if bx<xl:
                        weight_left = 1. 
                        pmax = 1./c(alpha*bx+beta1)
                    else:
                        weight_left = 0.5*nu*exp( -0.5*ay**2+ 
                            logdG(invnu*(xl-mean_left),invnu*(ax-mean_left)) )
                        pmax = SQRT_HALF_PI
            # Right component
            if bx<xr:
                weight_right = 0.
            else:
                mean_right = rho*by
                if ax<xr:
                    weight_right = 0.5*nu*exp( -0.5*by**2 +
                        logdG(invnu*(bx-mean_right),invnu*(xr-mean_right)) )
                    maxpa = SQRT_HALF_PI
                else:
                    weight_right = 1.
                    maxpa = 1./c(-alpha*ax-beta0) # CHECK
            # Center component
            if (ax>xr) or (bx<xl):
                weight_center = 0.
            else:
                x1 = min(bx,xr)
                x0 = max(ax,xl)
                dPhi_max = 2.*G.cdf(0.5*(beta1-beta0))-1.
                if (ax>xl) and (bx<xr): # if [ax,bx] inside center interval
                    weight_center = 1. 
                else:
                    weight_center = dPhi_max*(G.cdf(x1)-G.cdf(x0))
            sw = weight_left+weight_right+weight_center
            # Sample mixture index
            while(True):
                u = sw*rand(1)
                if u<weight_left: # left
                    x = simtruncgauss(mean_left,nu,ax,min(bx,xl))
                    if min(bx,xl)<0.:
                        praccept = ( r(alpha*x+beta1)-G.cdf(alpha*x+beta0)/
                                    G.pdf(alpha*x+beta1))/pmax
                    
                    else:
                        praccept = ( chi(alpha*x+beta1)-G.cdf(alpha*x+beta0)/
                            G.pdf(alpha*x+beta1)*exp(LAMBDA*(alpha*x+beta1))
                                    )/pmax

                elif u<weight_left+weight_center: # center 
                    x = simtruncugauss(x0,x1)
                    praccept = (
                     G.cdf(alpha*x+beta1)-G.cdf(alpha*x+beta0) )/dPhi_max
                else: # right mass
                    x = simtruncgauss(mean_right,nu,max(ax,xr),bx)
                    # a bit involved, but necessary to avoid overflow
                    praccept = ( r(-alpha*x-beta0)-r(-alpha*x-beta1)
                            *exp((beta0-beta1)*(alpha*x+0.5*(beta0+beta1))) 
                                )/maxpa

                spa += praccept
                nsim += 1
                if (rand(1)<praccept) or (nsim>NSIM_MAX):
                    break

    if spa<0.:
        print (rho,ax,bx,ay,by)
    y = simtruncgauss(rho*x,nu,ay,by)
    return (x,y,spa/nsim)

def bitg_ab(rho,ax,bx,ay,by):
    """ simulates a bivariate Gaussian vector (x,y)~ N(0,(rho 1,1 rho)) 
    subject to x in [ax,bx], y in [ay,by]
    """
    sgnx,sgny,swap= 1.,1.,False
    if rho<0.: # Force rho>0
        rho = -rho
        sgnx, ax,bx = -sgnx,-bx,-ax  
    if by<0.: # Force by>0
        sgnx, ax,bx = -sgnx,-bx,-ax  
        sgny,ay,by = -sgny, -by,-ay
    if (ax<ay) and (bx>0): # ensure that either ax>ay or bx<0
        swap = True
    if swap:
        (y,x,pa) = btg(rho,ay,by,ax,bx)
    else:
        (x,y,pa) = btg(rho,ax,bx,ay,by)
    return (sgnx*x,sgny*y,pa)


def ar(rho,ax,bx,ay,by,N=200,plot=False):
    """ computes average acceptance rate for a given parameter
    vector, over N simulations
    If plot=True, plots an histogram and the corresponding marginal
    density for x """
    spa = 0.
    x = empty(N); y = empty(N)
    for i in xrange(N):
        (x[i],y[i],pa) = bitg_ab(rho,ax,bx,ay,by)
        spa += pa
    if plot:
        invnu = 1./sqrt(1-rho**2)
        margin_x = lambda x:G.pdf(x)*(
                G.cdf(invnu*(rho*x-ay))-G.cdf(invnu*(rho*x-by)))
        hist_with_density(x,min(N/30,100),margin_x)
    return spa/N

def mc(N=1000):
    " computes accept. rate for N random values of parameters"
    rho = 2.*rand(N)-1.
    ax = 2*randn(N); ay = 2*randn(N)
    bx = ax-2.*log(rand(N))
    by = ay-2.*log(rand(N))
    a = zeros(N)
    for i in xrange(N):
        a[i] = ar(rho[i],ax[i],bx[i],ay[i],by[i])
        if a[i]<0.5:
            a[i] = ar(rho[i],ax[i],bx[i],ay[i],by[i],200)
            if a[i]<0.5:
                print rho[i],ax[i],bx[i],ay[i],by[i], "ar:", a[i]
    return (rho,ax,bx,ay,by,a) 

def arhist(N=1000):
    " Histogram of acceptance rates"
    toto = mc(N)
    hist(toto[-1],min(100,N/10))
    
def arsav(N=10000):
    " save figure " 
    toto = mc(N)
    save('sav_ar_bitgab.gz',toto[-1])

# example 
arhist()
figure()
ar(0.2,1.,2.,0.3,0.9,plot=True)
