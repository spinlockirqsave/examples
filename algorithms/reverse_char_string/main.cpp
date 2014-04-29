/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 29, 2014, 3:00 PM
 */

#include <stdio.h>
#include <string.h>

void reverse1(char* str) {
        
    if( str) {
        char* first = &str[ 0 ];
        char* last = first;
        while( *last) ++last;
        
        while (first < --last) {
            char tmp = *first;
            *first = *last;
            *last = tmp;
            ++first;
        }
    }
}

// reverse the given null-terminated string in place
void inplace_reverse(char * str)
{
  if ( str)
  {
    char * end = str + strlen( str) - 1;

    // swap the values in the two given variables
    // XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

    // walk inwards from both ends of the string, 
    // swapping until we get to the middle
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

/* how XOR_SWAP(a,b) works:
 * 
 * This works because of three basic
 * properties of xor:
 * x ^ 0 = x, x ^ x = 0 and x ^ y = y ^ x
 * so:
 * (va ^ vb) ^ va = vb
 * (va ^ vb) ^ vb = va
 *  
  // initially:
  // a == va
  // b == vb
  a ^= b;
  // now: a == va ^ vb
  b ^= a;
  // now: b == vb ^ (va ^ vb)
  //        == va ^ (vb ^ vb)
  //        == va ^ 0
  //        == va
  a ^= b;
  // now: a == (va ^ vb) ^ va
  //        == (va ^ va) ^ vb
  //        == 0 ^ vb
  //        == vb
 */

/*
 * 
 */
int main(int argc, char** argv) {

    char c[] = "hello"; // note: NOT char* c = "hello"; -> UB
    printf( "%s\n", c);
    reverse1( c);
    printf( "%s\n", c);
    
    inplace_reverse( c);
    printf( "%s\n", c);
    return 0;
}

