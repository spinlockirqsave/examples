/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 29, 2013, 5:24 PM
 */

#include <cstdlib>
#include <stdio.h>

class Window {
protected:
    virtual void draw(){
        printf("Base_draw\n");
    }
public:
};

class WindowA : public virtual Window {
protected:
    void own_draw(){
        printf("WindowA_own_draw\n");
    }
    void draw(){
        printf("WindowA_draw\n");
        own_draw();
        Window::draw();
    }
public:
};

class WindowB : public virtual Window {
protected:
    void own_draw(){
        printf("WindowB_own_draw\n");
    }
    void draw(){
        printf("WindowB_draw\n");
        own_draw();
        Window::draw();
    }
public:
};

class WindowDer : public WindowA, public WindowB {
    void own_draw(){
        printf("WindowDer_own_draw\n");
    }
public:
    void draw(){
        printf("WindowDer_draw\n");
        Window::draw();
        WindowA::draw();
        WindowB::draw();
        own_draw();
    }
};

/*
 * 
 */
int main(int argc, char** argv) {

    WindowDer w;
    w.draw();
    return 0;
}

