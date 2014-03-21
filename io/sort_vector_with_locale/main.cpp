#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::string> v;
    v.push_back( "a");
    v.push_back( "b");
    
    try {
        std::locale en( "en_US.utf8");
        const std::collate<char>& col = std::use_facet< std::collate<char> >( en); // string comparison
        const std::ctype<char>& ctyp = std::use_facet< std::ctype<char> >( en); // character classification
        const std::locale loc; // current global locale
        std::locale l1( loc, &col); // use global with US string comp
        std::locale l2( l1, &ctyp); // use global with US string comp and US character classification
        
        std::sort( v.begin(), v.end(), l2); 
    } catch ( std::exception& e) {
        std::cout << e.what();
    }
    return 0;
}
