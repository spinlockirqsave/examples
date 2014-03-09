/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 9, 2014, 12:53 AM
 */

#include <string>

std::string longestCommonSubstr( std::string& s, std::string& in) {
    size_t s_s = s.size();
    size_t in_s = in.size();
    if ( ( s_s == 0) || ( in_s == 0)) return std::string();
    size_t common_s = std::min( s_s, in_s);
    for ( size_t i = common_s; i > 0; i--) {
        size_t pos_beg = 0;
        size_t pos_end = i;
        while ( pos_end < s_s + 1) {
            std::string searched =  s.substr( pos_beg, pos_end);
            size_t found = in.find( searched);
            if ( found != std::string::npos) return searched;
            ++pos_beg;
            ++pos_end;
        }
    }
    return std::string();
}
/*
 * 
 */
int main(int argc, char** argv) {

    std::string me( "face");
    std::string ymey( "efftarcc");
    std::string res = longestCommonSubstr( me, ymey);
    return 0;
}

