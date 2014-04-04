/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 8, 2013, 3:56 AM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;

class Vehicle {
public:
  virtual ~Vehicle() { }
  virtual void startEngine() = 0;
};

class Car : public Vehicle {
public:
  virtual void startEngine(){printf("Car engine brummm\n");}
  virtual void openGasCap(){printf("Car: open gas cap\n");}
    virtual void openGasCap2(){printf("Car: open gas cap2\n");}
      virtual void openGasCap3(){printf("Car: open gas cap3\n");}
            virtual void openGasCap4(){printf("Car: open gas cap3\n");}
                  virtual void openGasCap5(){printf("Car: open gas cap3\n");}
};

class NuclearSubmarine : public Vehicle {
public:
    int i;
    double t;
  virtual void startEngine(){printf("Nuclear submarine engine brummm\n");}
    virtual void fireNuclearMissle4(){printf("Nuclear submarine: fire the missle4!\n");}
    virtual void fireNuclearMissle(){printf("Nuclear submarine: fire the missle!\n");}
  virtual void fireNuclearMissle2(){printf("Nuclear submarine: fire the missle2!\n");}
    virtual void fireNuclearMissle3(){printf("Nuclear submarine: fire the missle3!\n");}
};

int main()
{
  Car   car;
  Car*  carPtr = &car;
  Car** carPtrPtr = &carPtr;
  //Vehicle** vehiclePtrPtr = carPtrPtr;  // This is an error in C++, But:
  Vehicle** vehiclePtrPtr = reinterpret_cast<Vehicle**>(carPtrPtr);
  NuclearSubmarine  sub;
  NuclearSubmarine* subPtr = &sub;
  *vehiclePtrPtr = subPtr;
  // This last line would have caused carPtr to point to sub !
  carPtr->openGasCap();  // Nuclear submarine: fire the missle4!
  carPtr->openGasCap2();  // Nuclear submarine: fire the missle!
  carPtr->openGasCap3();  // Nuclear submarine: fire the missle2!
  carPtr->openGasCap4();  // Nuclear submarine: fire the missle3!
  //carPtr->openGasCap5();  // SEG FAULT!

  
}


