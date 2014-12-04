#include <iostream>
#include <vector>

/*
 * Returns max difference, but the condition is
 * that difference can be calculated only from
 * elements right-left
 */
int max_difference( std::vector<int> const &v) {
    
    if( v.size() < 2) return -1;
    int max = v[1]-v[0];
    size_t sz = v.size();
    size_t curr1=0, curr2=1, curr;
    size_t minElement = curr1;

    for( curr=1; curr<sz; ++curr) {
        if( v[curr]>v[curr2]) {
            curr2=curr;
            curr1 = minElement;
            max = v[ curr2] - v[ curr1];
        }
        if( v[curr]<v[curr1]) {
            minElement = curr;
            continue;
        }
        if( v[curr]-v[minElement] > max) {
            curr1 = minElement;
            curr2 = curr;
            max = v[ curr2] - v[ curr1];
        }
    }

    return max;
}

int main()
{
    std::vector<int> v = { 10, 11, 15, -1, 15, -2, -3, -10, 10, 7};
    int max_diff = max_difference( v);
    std::vector<int> v2 = { 10, 9, 8, 7};
    max_diff = max_difference( v2);
    return 0;
}
