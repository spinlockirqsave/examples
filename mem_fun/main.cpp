/* 
 * File:   main.cpp
 * Author: Piotr Gregor  postmaster@cf16.eu
 *
 * Created on October 21, 2013, 11:54 PM
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <functional>
using namespace std;

/*
 * 
 */
class Shape {
public:
    void draw() { std::cout<<"draw"; }
};

void draw_all_shapes(std::list<Shape*>& lsp) {
    for_each(lsp.begin(), lsp.end(), std::mem_fun(&Shape::draw));
    //std::mem_fun(&Shape::draw) is a function that returns object
    //of type mem_fun_t<R,T>. This object is a functor
}

int main(int argc, char** argv) {
    Shape a,b;
    std::list<Shape*> lsp;
    lsp.push_back(&a);
    lsp.push_back(&b);
    draw_all_shapes(lsp);
    
    return 0;
}

