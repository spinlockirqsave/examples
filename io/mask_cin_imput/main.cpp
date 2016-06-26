/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on June 19, 2014, 8:48 PM
 * 
 * Here we are masking input with asterisk.
 * We use tcgetattr/tcsetattr to get and set
 * terminal attributes so echo is disabled
 * on stdin and we print "*" instead on
 * each character user input.
 */

#include <iostream>
#include <string>
#include <termios.h>
#include <stdio.h>

/* get/set attributes of termional*/
int getch() {
    
    struct termios oldtc, newtc;
    int ch;
    tcgetattr( STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldtc);
    
    return ch;
}


int main( int argc, char **argv) {
    int ch;
    printf( "Press ENTER to exit.\n\n");
    for (;;) {
        ch = getch();

        if(ch == '\n')
              break;
        printf("*");
    }
    return 0;
}