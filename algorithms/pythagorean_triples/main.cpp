/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on June 19, 2014, 12:05 PM
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include <fstream>

struct pt {
    int a;
    int b;
    int c;
};

bool pythagorean_triples( int sum, std::vector<pt>& v)
{
    int a = 0, b = 0, c = 0;
    bool found = false;
    
    for ( a = 0; a < sum; a++) {
        for ( b = a; b < sum - a; b++) {
            if( (( c = sum - a - b) < a) || c < b) break;

            if ( a * a + b * b == c * c) {
                found = true;
                v.push_back( pt{ a, b, c});
            }
        }
        std::cout << "break\n";
    }
    
    return found;
}


int 
gcd ( int a, int b )
{
  int c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

/*
 * 
 */
int main(int argc, char** argv) {

    std::vector<pt> v;
    bool found = pythagorean_triples( 4070, v);
    
    if (found)
    {
        for( int i = 0; i < v.size(); ++i)
        {
            std::cout << v[i].a << "," << v[i].b << "," << v[i].c;
            if( gcd( v[i].a, 256) == 1) std::cout << " Yes[a] mod(256)=" << v[i].a % 256; // 1045,1332,1693 Yes[a] mod(256)=21
            if( gcd( v[i].b, 256) == 1) std::cout << " Yes[b] mod(256)=" << v[i].b % 256;
            std::cout << std::endl;
        }
    }
    
    int a = 1045;
    int b = 1332;
    int c = 1693;
    int A = a % 256;
    int B = b % 256;
    int C = c % 256;
    std::cout << A << "," << B << "," << C << std::endl;
    
    FILE* fp = fopen( "application/encrypted.txt", "r");
    if (fp == NULL) {
        perror( "Failed to open file encrypted.txt");
        return EXIT_FAILURE;
    }
    fseek( fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek( fp, 0L, SEEK_SET);
    std::cout << "encrypted.txt size=" << sz << "\n";
    
    char enc[496];
    char dec[496];
    
    for ( int i = 0; i < sz; i++) {
        int rc = getc(fp);
        if ( rc == EOF) {
            fputs("An error occurred while reading the file.\n", stderr);
            return EXIT_FAILURE;
        }
        enc[i] = rc;
        if( rc - C >= 0) {
            dec[i] = ( rc - C)/A;
        } else {
            dec[i] = ( rc - C)/A;
        }
    }
 
    fclose(fp);
    
    for ( int i = 0; i < sz; i++) std::cout << (int)dec[i] << "\n";
    return 0;
}

