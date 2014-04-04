#ifndef TEST_CLASS_A
#define TEST_CLASS_A
#include <iostream>
class A
{
private :
	double myValue_;
public :
	A(const double & myValue):myValue_(myValue){
		std::cout<<" Constructor of A" <<std::endl;
	}
	~A (){
		std::cout<<" Destructor of A with value "<<myValue_<<std::endl;
	}
	double getValue() const {return myValue_;}
};
# endif