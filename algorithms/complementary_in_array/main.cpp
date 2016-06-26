/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on February 20, 2014, 1:32 PM
 */


#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cassert>

int brute_force(const int K, const std::vector<int>& v) {
    int res = 0;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size(); ++j) {
            if ( v[i] + v[j] == K) {
                    ++res;
            }
        }
    }
  return res;
}

int search(const int K, const std::vector<int>& v) {
    int result = 0;
    std::vector<int>::const_iterator lower = v.begin();
    std::vector<int>::const_iterator upper = v.end();
    
    while (lower < upper) {
        upper = std::upper_bound(lower, upper, K - *lower);
        int i = lower - v.begin();
        int u = upper - v.begin();
        
        while (i <= --u && v[i] + v[u] == K) {
            result++;
            if (u != i) { result++; }
            
        }
        ++lower;
    }
    return result; 
}

int solution(int K, const std::vector<int> &A) {
    // write your code in C++98
    std::vector<int> B ( A);
    std::sort( B.begin(), B.end());
    
    //return brute_force( K, B);
    return search( K, B);
    return K;
}

int main(int argc, char** argv) {
    std::vector<int> v(9);
    v[0] = 1;
    v[1] = 8;
    v[2] = -3;
    v[3] = 0;
    v[4] = 1;
    v[5] = 3;
    v[6] = -2;
    v[7] = 4;
    v[8] = 5;

    std::sort(v.begin(), v.end());

    assert( search(6, v) == 7);
    assert( brute_force(6, v) == 7);
    return 0;
}

