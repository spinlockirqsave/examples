/*
 * File:   main.cpp
 * Author: piter cf16.eu
 * Created on March 24, 2014, 1:06 AM
 */

#include <iostream>
#include <numeric>

int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };

    int result = std::accumulate(arr, arr + 21, 1, lcm);

    std::cout << result << '\n';
}