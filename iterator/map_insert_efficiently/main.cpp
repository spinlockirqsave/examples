/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on November 30, 2013, 1:07 AM
 */

#include <iostream>
#include <map>
using namespace std;

typedef map<int, int> MapType;
MapType myMap;

void insert_efficiently_with_hint(int k, int v) {
    MapType::iterator lb = myMap.lower_bound(k);

    if (lb != myMap.end() && !(myMap.key_comp()(k, lb->first))) {
        // key already exists
        // update lb->second if you care to
    } else {
        // the key does not exist in the map
        // add it to the map
        myMap.insert(lb, MapType::value_type(k, v)); // Use lb as a hint to insert,
        // so it can avoid another lookup
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    // Add elements to map
    for (int i = 0; i < 100; ++i) {
        myMap[i] = i;
    }
    int k = 4; // assume we're searching for keys equal to 4
    int v = 0; // assume we want the value 0 associated with the key of 4
    
    insert_efficiently_with_hint( k, v); // myMap.size() = 100
    insert_efficiently_with_hint( 1000, v); // myMap.size() = 101

    return 0;
}

