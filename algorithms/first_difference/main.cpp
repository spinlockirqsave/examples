/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on February 19, 2014, 4:07 PM
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

/*
 * first difference of elements: element present in first container
 * and not present in second
 */
template <class T>
T first_difference (T* first1, T* last1, T* first2, T* last2)
{
  while (first1 != last1 && first2 != last2)
  {
    if ( *first1 < *first2) { return *first1; }
    else if ( *first2 < *first1) ++first2;
    else { ++first1; ++first2; }
  }

  if ( first1 != last1 && first2 == last2) return *first1;
  return 0;
}
/*
 * 
 */
int main(int argc, char** argv) {

    int first[] = {500, 1000, 1500, 2000, 2500};
    int second[] = {5, 10, 15, 20, 25, 30};
    std::vector<int> v(10); // 0  0  0  0  0  0  0  0  0  0
    std::vector<int>::iterator it;

    std::sort(first, first + 5); //  5 10 15 20 25
    std::sort(second, second + 6); // 10 20 30 40 50

    it = std::set_difference(first, first + 5, second, second + 6, v.begin());
    //  5 15 25  0  0  0  0  0  0  0
    v.resize(it - v.begin()); //  5 15 25

    std::cout << "The difference has " << (v.size()) << " elements:\n";
    for (it = v.begin(); it != v.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    
    int i = first_difference( first, first + 5, second, second + 6);
    assert( i == 500);

    return 0;
}

