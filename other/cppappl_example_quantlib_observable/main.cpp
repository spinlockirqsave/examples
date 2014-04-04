/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 26, 2013, 3:12 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <ql/patterns/../patterns/observable.hpp>
#include <iostream> 
/*
 * 
 */

class DataRepository : public QuantLib::Observable{
    public:
        void run();
        int getData();
    private:
        int data;
            
};

void DataRepository::run(){
    for(int i=0;i<10;++i){
        data=i;
        notifyObservers();
    }
}
int DataRepository::getData(){
    return data;
}

typedef boost::shared_ptr<DataRepository> pMyObservable;

class myObserver : public QuantLib::Observer{
public:
    myObserver(pMyObservable obs, std::string n)
        : observable(obs), name(n){
      this->registerWith(observable);
    }
    myObserver(const myObserver &observer)
      : Observer(observer),
        observable(observer.observable),
        name("Copy of "+observer.name){
    }
    
    void update(){
        data=observable->getData();
        std::cout<<"new data: "<<data<<std::endl;
    }
private:
    int data;
    pMyObservable observable;
    std::string name;
};

int main(int argc, char** argv) {

    pMyObservable d(new DataRepository);
    myObserver obs(d,"count_to_10_data");
    d->run();

    return 0;
}

