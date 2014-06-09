/* 
 * File:   main.cpp
 * Author: piter
 *
 * Created on June 9, 2014, 8:55 PM
 */

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

void print_combinations( const char *string)
{
    int i, j, k;
    int len = strlen(string);

    for (i = 0; i < len - 2; i++)
    {
        for (j = i + 1; j < len - 1; j++)
        {
            for (k = j + 1; k < len; k++)
                printf("%c%c%c\n", string[i], string[j], string[k]);
        }
    }
}
/*
 * 
 */
//int main(int argc, char** argv) {
//
//    const char* s = "12345";
//    print_combinations( s);
//    
//    return 0;
//}

#include<iostream>
#include<list>
#include <iterator>

void print( std::list<int> l){
    std::copy( l.begin(), l.end(), std::ostream_iterator<int>( std::cout, " "));
    std::cout << std::endl;
}

void subset( int arr[], int size, int left, int index, std::list<int> &l){
    if( left == 0){
        
        print(l);
        return;
    }
    
    for( int i = index; i < size; i++){
        l.push_back( arr[i]);
        subset( arr, size, left-1, i+1, l);
        l.pop_back();
    }

}     

int main() {
    
    int array[5] = { 1, 2, 3, 4, 5} ;
    std::list<int> lt;   
    subset( array, 5, 1, 0, lt);
    subset( array, 5, 2, 0, lt);
    subset( array, 5, 3, 0, lt);
    subset( array, 5, 4, 0, lt);
    subset( array, 5, 5, 0, lt);

    return 0;
}
