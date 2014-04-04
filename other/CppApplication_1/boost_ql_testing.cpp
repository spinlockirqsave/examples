// boost_ql_testing.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "myheaders.h"
#include <boost/current_function.hpp>
#include <boost/foreach.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/exception/all.hpp>
#include "TestClassA.h"
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#define MY_NUM 1300
int vint=4;
//int x;                           /* static stack storage */
//void main() {
//   int y;                        /* dynamic stack storage */
//   char str;                    /* dynamic stack storage */
//   str = malloc(50);        /* allocates 50 bytes of dynamic heap storage */
//   size = calcSize(10);       /* dynamic heap storage */
//void foo()
//{
//  int x; <<< x is on the stack
//  char *ptr = new char[255]; <<< 255 characters are allocated in the heap
//                                 but ptr object is on the stack
//int array[255]; <<< 255 ints are all on the stack
//}
/*When a program begins executing in the main() function, all variables declared within main() 
will be stored on the stack. If the main() function calls another function in the program, 
for example calcSize(), additional storage will be allocated for the variables in calcSize(). 
This storage will be allocated in the heap memory segment. Notice that the parameters passed by main()
to calcSize() are also stored on the stack. If the calcSize() function calls to any additional functions,
more space would be allocated at the heap again. When the calcSize() function returns the value, 
the space for its local variables at heap is then deallocated and heap clears to be available 
for other functions.
The memory allocated in the heap area is used and reused during program execution.
It should be noted that memory allocated in heap will contain garbage values left over from previous usage.

Memory space for objects is always allocated in heap. Objects are placed on the heap.

Built-in datatypes like int, double, float and parameters to methods are allocated on the stack.

Even though objects are held on heap, references to them are also variables and they are placed on stack.
The stack segment provides more stable storage of data for a program. The memory allocated in the stack 
remains in existence for the duration of a program. This is good for global and static variables. 
Therefore, global variables and static variables are allocated on the stack.*/

/* http://www.codeguru.com/forum/showthread.php?p=1186307#post1186307
Difference is in speed. To alllocate memory on the stack, all you have to do is move the stack pointer. 
To allocate memory on the heap takes a lot more effort. Also (bad practice but I've seen it in production 
code), if the constructor expects a class defined new operator to be executed first, it won't happen if 
it is stack based. Stack based stuff auto destruct when they go out of scope: very much like auto_ptrs.

Advantages of stack:
- Size required determined at compile-time, so no need at run time to determine amount of memory to allocate
at run time. This is obviously a performance advantage.
- Automatic "clean-up".

Advantages of heap (or why you need to use it)
- As size is determined at compile time, it is inflexible. Therefore heap is used when amount required is 
variable
- As stack cleans up automatically at exit of function, if you still need the memory on exit of function, 
use the heap. ("static" is also available but should only be used for singletons, which might include 
a critical section).
- Stack space is more limited than heap space.

auto_ptrs (mentioned above) combine the advantage of a stack object self-destructing when going out 
of scope, the flexibility of using a heap and the "automatic" destructor which gets called when an object 
it destroyed. As "auto_ptr" is destructed (on the stack) its destructor frees up the resources allocated 
on the heap at the same time.

You are the person wholly resposible for whatever you put on the heap. If you created an object on 
the heap, its your responsibility to clean/free it up. delete and delete[] are used for this.

*/

void testMacroa(){
	std::cout<<" You have called :" << BOOST_CURRENT_FUNCTION << std::endl;
}
void testMacrob(){
	BOOST_STATIC_ASSERT(MY_NUM==1300);
}
void testMacroc(){
	std::vector<double>myVec(10);
	BOOST_FOREACH(double & x, myVec) x=10.0;
	BOOST_FOREACH(double & x, myVec) std::cout<<x<<std::endl ;
}
void testMacrod(){
	//BOOST_ERROR(" Failure of this function ");
	double x =0.0;
	//BOOST_TEST(x!=0);
	int i=1;
	int j=2;
	double * ds=new double[2];
	ds[0]=1.0;
	ds[1]=2.34;
	std::cout<<std::endl<<std::setprecision(10)<<ds[1]<<std::endl;

}

void testSharedPtra(){
	// (a) Usual way to dynamically allocate memory space on the heap
	A* ptr_myA2 = new A(2.0);
	A* ptr_myA = new A(1.0);
	A* ptr_myA3 = ptr_myA;

	//delete ptr_myA ;
	//delete ptr_myA2;
	//delete ptr_myA;
	boost::shared_ptr<A> bptr_myA2(ptr_myA2);
	boost::shared_ptr<A> bptr_myA(ptr_myA);

}

void testSharedPtrb(){
	// (b) Behaviour of raw pointers for exceptions
	A* ptr_myA = new A(1.0);
	throw("Error ocurred for class A.");
	delete ptr_myA ;
}

void testSharedPtrc(){
// (c) Allocation via boost::shared_ptr
	A* ptr_myA2 = new A(3.0);
	A* ptr_myA = new A(4.0);
	int i=7;
	double d=9.998;
boost::shared_ptr<A> bptr_myA (new A(5.0));
}

void testSharedPtrd(){
// (d) Assign ownership of usual pointers to a shared_ptr
A* ptr_myA = new A(9.0);
boost::shared_ptr<A> bptr_myA(ptr_myA);
std::cout<<bptr_myA->getValue()<<std::endl;
}

void testSharedPtre(){
// (e) Behaviour of boost :: shared_ptr in exceptions
boost::shared_ptr<A> bptr_myA(new A(13.0));
throw " Error ocurred in testSharedPtr ";
}

void testSharedPtrg(){
// (g) Behaviour of smart pointers when reassigning
boost::shared_ptr<A> bptr_myA(new A(1.0));
bptr_myA .reset(new A(2.0));
boost::shared_ptr<A> bptr_myA2(new A(6.0));
boost::shared_ptr<A> bptr_myA3(new A(7.0));
bptr_myA2=bptr_myA3;
}

void testSharedPtrh(){
// (g) Behaviour of smart pointers when reassigning
std::vector<double>a(4);
std::cout<<"\n\n"<<"boost::shared_ptr<std::vector<double>> bptr_myV(new std::vector<double>[100])"<<std::endl;
boost::shared_ptr<std::vector<double> > bptr_myV(new std::vector<double>(100));
std::vector<double>::iterator it;
//it=bptr_myV->begin(); //wrong!
int i=0;
for(it=bptr_myV->begin()++;it!=bptr_myV->end();it++){
	*it=i++;
}
i=0;
for(it=bptr_myV->begin()++;it!=bptr_myV->end();it++){
	std::cout<<"\ni="<<i<<"bptr_myV["<<i<<"]="<<(*bptr_myV)[i];
	i++;
}
double vecSum=0;
BOOST_FOREACH(double v,*bptr_myV)vecSum+=v;
std::cout<<"\nvecSum="<<vecSum<<std::endl;
//bptr_myA .reset(new A(2.0));
}

void distributionFunctions(){
double leftBound=0.0, rightBound=2.0;
boost::math::uniform_distribution<> d1(leftBound, rightBound);
double numTrials=10, probTrial=0.2;
boost::math::binomial_distribution<> d2(numTrials, probTrial);
double degFreedom=20;
boost::math::students_t_distribution<> d3(degFreedom);
boost::math::chi_squared_distribution<> d4(degFreedom);
double mean=0.0, var=1.0;
boost::math::normal_distribution<> d5(mean,var);
boost::math::lognormal_distribution<> d6(mean, var);
boost::math::cauchy_distribution<> d7(mean, var);
double degFreedom1 =20, degFreedom2=35;
boost::math::fisher_f_distribution<> d8(degFreedom1, degFreedom2);
double nonCentPar=0.2;
boost::math::non_central_chi_squared_distribution<> d9(degFreedom1, nonCentPar);
double arrivRate=0.2;
boost::math::poisson_distribution<> d10(arrivRate);
boost::math::exponential_distribution<> d11(arrivRate);
}
void boostDistributionInfo(boost::math::lognormal_distribution<> * d){
	std::cout<<std::string(20,'-')<<std::endl;
	std::cout<<" CDF :"<<cdf(*d ,0.2)<<std::endl;
	std::cout<<" PDF :"<<pdf(*d ,0.0) <<std::endl;
	std::cout<<" Inverse :"<<quantile(*d,0.1)<<std::endl;
	std::cout<<" Mode :"<<mode(*d)<<std::endl;
	std::cout<<" Variance :"<<variance(*d)<<std::endl;
	std::cout<<" SD :"<<standard_deviation(*d)<<std::endl ;
	std::cout<<" Skew :"<<skewness(*d)<<std::endl ;
	std::cout<<" Kurtosis :"<<kurtosis(*d)<<std::endl;
	std::cout<<" Excess Kurt :"<<kurtosis_excess(*d)<<std::endl;
	std::cout<<std::string(20,'-')<<std::endl;
}

void WorkingMethod(int * &i)//reference to a pointer, "pointer byRef"
{
	i=&vint;
//i = new int();
//*i = 3;
}


void NotWorkingMethod(int* i)//"pointer byVal"
{
	i=&vint; //it doesn't change the address of original pointer, which still points to a NULL
//i=new int;
//*i=3;
}


int main(int argc, char* argv[])
{/*
	//testMacroa();
	//testMacrob();
	//testMacroc();
	//testMacrod();
	int * i1=NULL;
	int * i2=NULL;
	//int vint2=2;i2=&vint2; //it doesnt change anything,so the reason is passing byVal,not pointing to NULL
	WorkingMethod(i1);//it will change i1 address
	NotWorkingMethod(i2);//it still will be NULL
	std::cout<<"\ni1:"<<*i1;
	//std::cout<<"\ni2:"<<*i2; //error, expression cannot be evaluated (NULL pointer)

	
	myMaps myMap;myMap.clear();
	myMaps::iterator it;
	
	it=myMap.begin();
	v * v1=new v();
	(*v1).second=100.2;
	v * v2=new v();
	(*v2).second=100.3;
	//(it->second).second=2.0;
	myMap.insert(std::make_pair(1,*v1));
	myMap.insert(std::make_pair(2,*v2));
	//(it->second)=(v1); //to jest wpisanie do obiektu pair na ktory wskazuje iterator 100.123 w double
	//it++;
	//std::pair<int,double> v2;
	//v2.second=200.24;
	for(it=myMap.begin();it!=myMap.end();it++){
		std::cout<<((*it).first)<<std::cout<<"\t";
		v * v3=&(it->second);
		std::cout<<(v3->second)<<"\n";
	}
	//BOOST_FOREACH(v,myMap)std::cout<<v.first<<"\t"<<v.second<<std::endl;
	//std::cout<<(*v1).first<<"\t"<<(*v1).second<<std::endl;

	testSharedPtrh();

	std::cout<<std::string(20,'-')<<std::endl;
	double mi=0.0, var=1.0;
	boost::math::lognormal_distribution<> *lnd=new boost::math::lognormal_distribution<>(mi,var);
	boostDistributionInfo(lnd);

	boost::normal_distribution<> nd(mi,var);
	unsigned long seed=12345;
	boost::mt19937 rng(seed);
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> nd_rng(rng,nd);
	std::cout<<nd_rng()<<std::endl;
	std::cout<<nd_rng()<<std::endl;
	std::cout<<nd_rng()<<std::endl;

	boost::uniform_on_sphere<double,std::vector<double>> myUn(5);
	boost::variate_generator<boost::mt19937&,boost::uniform_on_sphere<double,std::vector<double>>>
	unSphere (rng,myUn);
	std::vector<double> res=unSphere();
	BOOST_FOREACH(double x, res) std::cout<<x<<std::endl;
	double sum=0.0;
	BOOST_FOREACH(double x,res) sum+=x*x;
	std::cout<<" ------------"<< std::endl;
	std::cout<<" Vector Length :"<<std::sqrt(sum)<<std::endl;
	std::cout<<std::string(20,'-')<<std::endl;

	double a=-1.0 , b =1.0;
	boost::function<double(double)> ind;
	ind=boost::bind(indicatorFunc,_1,a,b);
	std::cout<<ind(2.0)<<std::endl;
	std::cout<<ind(0.5)<<std::endl;

	boost::function<double(double, double, double)> myMultPtr;
	myMultPtr=boost::ref(indicatorFunc);
	std::cout<<myMultPtr(3.0,1.0,2.0)<<std::endl;
	std::cout<<myMultPtr(1.26,1.0,2.0)<<std::endl;

	*/
        std::cout<<std::endl<<std::string(20,'-')<<std::endl;
	double mi=0.0, var=1.0;
	boost::math::lognormal_distribution<> *lnd=new boost::math::lognormal_distribution<>(mi,var);
	boostDistributionInfo(lnd);
        std::cout<<std::endl<<std::string(20,'-')<<std::endl;
        
	testSharedPtra();
        std::cout<<"end main";
	//std::system("pause");
	return 0;
}

