/* 
 * File:   classes.h
 * Author: peterg
 *
 * Created on October 27, 2014, 12:16 AM
 */

#ifndef CLASSES_H
#define	CLASSES_H


class A;
class B;
class C;

class Object {
public:
    virtual void f() = 0;
};

class A : public Object {
public:
    virtual void f(){}
};

class B  : public Object {
public:
    virtual void f(){}
};

class C  : public Object {
public:
    virtual void f(){}
};

#endif	/* CLASSES_H */

