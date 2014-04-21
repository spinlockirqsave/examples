#-*- coding: utf-8 -*-
from scipy import *
import scipy.optimize as optimize
import scipy.stats as stats

# This Python 2.5 script generates all the necessary constants
# for the univariate algorithm, and send them to std output. 
# use the run.sh script to update the corresponding C routine


def declar(x, name_x):
    """ generate C declaration of array x, send it to stdout.
    Assume implicitly that x is an array of either double or int elements.
    """
    n = len(x)
    decl = name_x+"["+str(n)+"]={"
    if x.dtype.name == "float64":
        print "static const double", decl
        nline = 4
    else:
        print "static const unsigned short int", decl
        nline = 20
    s = ""
    for i in range(n):
        if i<n-1:
            s += str(x[i])+", "
        else:
            s += str(x[n-1])+"};"
        if (i+1)%nline == 0: # Flush line
            print s
            s = ""
    print s

def f(area,N,dist = stats.norm, return_x = False):
    """ calibrate the x-grid so that the "tail cell"
    is of same area as the n-1 rectangle cells
    """
    area = area/N
    x = zeros(N,dtype="d")
    x[0] = 0.
    for i in range(N-1):
        delta = area/dist.pdf(x[i])
        x[i+1] = x[i]+delta
    if return_x:
        return x
    else:
        return area-dist.cdf(-x[-1])
    
def gentab(N,amin):
    " Generate the arrays x,y,d,delta, assuming a partition in n boxes for [0,+infty) " 
    
    area_low = 0.5
    area_up = 0.7
    area_zig = optimize.bisect(f,area_low,area_up,args=(N))
    xpos = f(area_zig,N,stats.norm,return_x=True)
    # don't store x_i such that x_i<a_min
    j = 0
    while(j<N) and (xpos[j]<-amin):
        j += 1
    x = concatenate((-xpos[j:0:-1],xpos)) 
    nd = x.size-1 # number of intervals [xi,x(i+1)]
    d = empty(nd,dtype="double")
    delta = empty(nd,dtype="double")
    yl = empty(nd,dtype="double")
    yu = empty(nd,dtype="double")
    for i in range(nd):
        if x[i]<0.:
            yl[i] = stats.norm.pdf(x[i])
            yu[i] = stats.norm.pdf(x[i+1])
        else:
            yl[i] = stats.norm.pdf(x[i+1])
            yu[i] = stats.norm.pdf(x[i])
        d[i] = x[i+1] - x[i]
        delta[i] = d[i]*yu[i]/yl[i]
    return (x,yl,yu,d,delta)
    
def ar(a,n):
    " Compute the acceptance rate corresponding to truncation points a (sorted array)"
    
    (x,yl,yu,d,delta) = gentab(n)
    z = stats.norm.cdf(-x[-1])
    la = a.size; j = la-1
    ar = ones(la,dtype="d")
    while(a[j]>x[-1]):
        j = j-1
        if j==0: return ar
    for i in range(n-3,-1,-1):
        h = max(y[i],y[i+1])
        while a[j]>x[i]:
            ar[j] = stats.norm.cdf(-a[j])/(z + h*(x[i+1]-a[j]))
            j = j-1
            if j==0: return ar
        z = z + d[i]*h
    ar[:(j+1)] = stats.norm.cdf(-a[:(j+1)])
    return ar

def main(n, amin=-2.): 
    """ Main routine: send to standard ouptut a bit of C code that generates
    the arrays of constant used in the vertical zig simulation.
    n: number of rectangles on positive range [0,+infty) (must be <= 65536) 
    (rule of thumb: actual nb of rectangles is approx 1.5*n)
    
    Output:
        
        ncell: ncell[i] =  largest k such that x[k]<=h*(i-i0)
    """

    (x,yl,yu,d,delta) = gentab(n,amin)
    nboxes = x.size-1
    h = min( x[1:]-x[:-1] ) # minimum interval range
    amax = x[-20] # when less that 20 boxes, use Devroye's algo instead
    p = int(ceil( (amax-x[0])/h ))
    i0 = -floor(x[0]/h)
    
    ncell = zeros(p,dtype="int")
    k = 0
    for i in xrange(p): #ncell[0]=0 by construction
        if (k>nboxes): # if reach x[max]
            ncell[i] = nboxes
        else:
            while x[k]<=h*(i-i0):
                    k += 1
                    if (k>nboxes): break
            ncell[i] = max((k-1,0)) # by construction a>=x[0]

    # generate C variable declaration
    print "#define N", nboxes, "//total number of vertical boxes"
    print "#define I0", int(i0)
    print "#define INVH", 1/h
    print "#define AMIN", x[0] 
    print "#define AMAX", amax
    print
    for v in ['x','yl','yu','d','delta','ncell']:
        declar(eval(v),v)
        print

def ar_devroye(a):
    """ Computes acceptance rate of Devroye's algorithm  
    a: truncation point 
    """
    return sqrt(2*pi)*a*stats.norm.cdf(-a)*exp(0.5*a**2)

def ar_robert(a):
    """ Computes acceptance rate of Robert's algorithm  
    a: truncation point 
    """
    l = 0.5*(a+sqrt(a**2+4))
    return sqrt(2*pi)*l*stats.norm.cdf(-a)*exp(l*a-0.5*l**2)

def plot_proposal(n=20):
    " plot a N(0,1) density, and the n boxes"
    
    (x,yl,yu,d,delta) = gentab(n,-2.)
    bar(x[:-1],yu,width=d,color='w')
    xx = linspace(-3,3)
    plot(xx,stats.norm.pdf(xx),'k')
    axis([-3,3,0,0.5])
            

# change the argument here if you want more/less regions
#main(513)  # N=513 ==> N_s = 1001
#main(1025)    # N=1025 ==> N_s = 2001 
main(2048)    # N=2048 ==> N_s = 4001


# this was used to produce Fig 1 in the paper
#plot_proposal()
