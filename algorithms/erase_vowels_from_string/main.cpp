/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on March 14, 2014, 1:00 AM
 */

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
/*
 * 
 */

static inline bool isVowel( char ch)
{
        static const std::string vowels("aeiouEAIOU");
        return vowels.end() != std::find(vowels.begin(), vowels.end(), ch);
}

struct isVowel_{
    std::string& vowels;
    isVowel_( std::string& s) : vowels( s) {}
    bool operator()( std::string c) {
        bool b =vowels.end() != std::find(vowels.begin(), vowels.end(), *(c.c_str()));
        return b;
    }
};

int main() {
    std::vector<std::string> vowel;
    vowel.push_back("a");
    vowel.push_back("b");
    vowel.push_back("c");
    vowel.push_back("d");
    vowel.push_back("e");
    vowel.push_back("f");

    std::vector<std::string>::iterator k;

//for( k=vowel.begin(); k!=vowel.end();) {
//        if( isVowel( *((*k).c_str()))) // for every letter that is a vowel
//            k = vowel.erase(k);
//        else
//            ++k;
//}

    std::string vowels("aeiouEAIOU");
    k = std::remove_if( vowel.begin(), vowel.end(), isVowel_( vowels));
    vowel.erase( k, vowel.end());  // erases the unspecified values and reduces
                                   // the physical size of the container to match
                                   // its new logical size
    
    return 0;
}

