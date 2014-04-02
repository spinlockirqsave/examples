/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 2, 2014, 11:31 AM
 * program asks user for a number designating a "rejestr"
 * and returns a value associated with this key
 */

#include <iostream>
#include <fstream>

#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>

/* overloads hash function in case we want a different hash logic*/
template<typename T>
struct Hash : public std::unary_function<T, std::size_t> {
    std::size_t operator()(T const& val) const {
        boost::hash<std::string> hasher;
        return hasher( val);
    }
};

typedef boost::unordered_map<std::string, std::string, Hash<std::string> > HashMap;
/*
 * 
 */
int main(int argc, char** argv) {

    if ( argc < 2) {
        std::cerr << "Program has to be run with 1 argument: file path.\n";
        return -1;
    }
    
    const char* file_path = ( argv[1]);

    std::ifstream f;
    f.open( file_path, std::ios::in);
    if ( !f) {
        std::cerr << "Cannot open file \"" << file_path 
                  << "\". Please verify that file exists.\n";
        return -2;
    }
    std::cout << "File \"" << file_path << "\" has been opened.\n";
    
    std::string line;
    std::string key;
    std::string value;
    HashMap hashMap;
    
    /* Read stream line by line and insert into hash map */
    while ( std::getline( f, line, '\n')) {
        std::size_t leftBracketPos = line.find( '(');
        if ( leftBracketPos == std::string::npos) {
            std::cerr << "No '(' has been found in line \"" << line << "\".\n";
            return -3;            
        }
        key.assign( line, 0, leftBracketPos);
        
        std::size_t rightBracketPos = line.substr( leftBracketPos).find_last_of( ')');
        if ( rightBracketPos == std::string::npos) {
            std::cerr << "No ')' has been found in line \"" << line << "\".\n";
            return -3;            
        }
        value = line.substr( leftBracketPos + 1).substr( 0, rightBracketPos - 1);
                
        /* We check if an insertion actually took place but currently
         * we consider that repeated key is not an error giving only 
         * the warning to a cerr  */
        if ( !hashMap.insert( std::make_pair( key, value)).second) {
            std::cerr << "The key \"" << key << "\" in line \"" << line << "\" duplicated."
                    << " Not overwriting the entry for this key. The old value is \"" 
                    << (*( hashMap.find( key))).second << "\".\n";
        }
    }
    f.close();
    
    if ( hashMap.size() == 1) {
        std::cout << "There is 1 entry in the table.\n"
                << "Please enter the key or \"q\" to quit.\n";
    } else {
        std::cout << "There are " << hashMap.size() << " entries in the table.\n"
                << "Please enter the key or \"q\" to quit.\n";
    }
    
    HashMap::const_iterator it;
    /* intentionally there is no space left after colon */
    std::cout << "Key:";
    while ( std::cin >> key && key != "q") {
        if ( ( it = hashMap.find( key)) != hashMap.end()) {
            std::cout << "Value:" << (*it).second << std::endl;
        } else {
            std::cout << "The key doesn't exist.\n";
        }
        std::cout << "Key:";
    }

    return 0;
}

