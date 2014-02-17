/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 * 2010-2012 by Tim Day
 * http://timday.bitbucket.org/lru.html
 *
 * Created on February 17, 2014, 3:44 PM
 */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>

#include "lru_cache_using_std.h"

/*
 * 
 */
size_t count_evaluations = 0;
// Dummy function we want to cache 

std::string fn(const std::string& s) {
    ++count_evaluations;
    std::string r;
    std::copy(s.rbegin(), s.rend(), std::back_inserter(r));
    return r;
}

int main(int argc, char** argv) {

    lru_cache_using_std< std::string, std::string> lru(fn, 5);

    // Some initial accesses to prime state 
    assert(lru("first") == "tsrif");
    assert(lru("second") == "dnoces");
    assert(lru("third") == "driht");
    assert(lru("fourth") == "htruof");
    assert(lru("fifth") == "htfif");
    assert(count_evaluations == 5);
    assert(lru("sixth") == "htxis");
    assert(count_evaluations == 6);

    // This should be retrieved from cache 
    assert(lru("second") == "dnoces");
    assert(count_evaluations == 6);

    // This will have been evicted 
    assert(lru("first") == "tsrif");
    assert(count_evaluations == 7);

    // Cache contents by access time 
    // (most recent to least recent) 
    // should now be: 
    // first,second,sixth,fifth,fourth 
    {
        std::vector<std::string> expected;
        expected.push_back("first");
        expected.push_back("second");
        expected.push_back("sixth");
        expected.push_back("fifth");
        expected.push_back("fourth");
        std::vector<std::string> actual;
        lru.get_keys(std::back_inserter(actual));
        assert(actual == expected);
    }

    return 0;
}

