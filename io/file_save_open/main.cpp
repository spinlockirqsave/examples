/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 29, 2014, 11:53 PM
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {

    fstream f;
    f.open( "list.txt", std::ios::in);
    if (!f) return -1;
    vector<string> games;
    std::copy( istream_iterator<string > (f), // copy file content
            istream_iterator<string > (), std::back_inserter(games)); // to vector
    f.close();
    string response;
    while ( 1) {
        cin >> response;

        if (( response == "a")) {
            int number;
            string gameName;
            cout << "What is the name of the game you would like to add?\n";
            cout << "Name: ";
            cin >> gameName;
            games.push_back( gameName);
            cout << gameName << " was added to the system.\n\n";
        } else if ( response == "q") {
            f.open( "list.txt", std::ios::out);
            if ( !f) return -1;
            std::copy(games.begin(), games.end(), // copy from vector to a file
                    ostream_iterator<string > ( f, "\n"));
            f.close();
            return 0;
        }
    }
    return 0;
}

