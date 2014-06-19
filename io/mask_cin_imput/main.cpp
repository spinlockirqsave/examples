/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on June 19, 2014, 8:48 PM
 */

#include <iostream>
#include <string>
#include <termios.h>


#include <stdio.h>

int getch() {
    struct termios oldtc, newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}


int main(int argc, char **argv) {
    int ch;
    printf("Press ENTER to exit.\n\n");
    for (;;) {
        ch = getch();

        if(ch == '\n')
              break;
        printf("*");
    }
    return 0;
}