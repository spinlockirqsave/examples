/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on February 18, 2014, 10:30 PM
 */

#include <vector>
using namespace std;

/*
 * 
 */
int solution(const vector<int> &A) {
    // write your code in C++98
    if( A.size() < 2) return -1;
    
    int increasing = 0;
    int decreasing = 0;
    int constant = 0;
    int N = A.size();
    int p = 0, q = 1;
    int monotonicity = p;
    int mode, curr_mode;
    int streak = 0;
    
    if ( A[0] < A[1]) curr_mode = 1, mode = 1;
    if ( A[0] > A[1]) curr_mode = -1, mode = -1;
    if ( A[0] == A[1]) curr_mode = 0, mode = 0;
    
    while ( q < N) {
        if ( A[monotonicity] < A[q]) 
            ++increasing, curr_mode = 1;
        if ( A[monotonicity] > A[q]) 
            ++decreasing, curr_mode = -1;
        if ( A[monotonicity] == A[q])  
            ++constant, curr_mode = 0;
        ++q; ++monotonicity;
        if ( curr_mode != mode) {
            if ( mode == 1) 
                increasing += (streak==1? 1 : (streak-1)*(streak)/2);
            if ( mode == -1) 
                decreasing += (streak==1? 1 : (streak-1)*(streak)/2);
            if ( mode == 0) 
                constant += (streak==1? 1 : (streak-1)*(streak)/2);
            
            mode = curr_mode;
            streak = 1;
            continue;
        }
        
        streak++;
    }
    
    return increasing + decreasing + constant + (streak-1)*(streak)/2;
}

int main(int argc, char** argv) {

    std::vector<int> v;
    v.push_back(1);v.push_back(2);v.push_back(3);v.push_back(4);v.push_back(3);v.push_back(2);//v.push_back(7);
    int i = solution(v);
    
    return 0;
}

