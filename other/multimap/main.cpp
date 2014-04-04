/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on September 1, 2013, 8:04 PM
 */

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

std::pair<int,std::string> mytransform (const std::pair<std::string,int> p) {
                       return std::pair<int,std::string>(p.second, p.first);
                       }

std::multimap<int,std::string>::iterator 
          client(std::multimap<int,std::string,std::greater<int> >& dst) {

    std::vector<std::string> most;
    most.push_back("lion");
    most.push_back("tiger");
    most.push_back("kangaroo");
    most.push_back("donkey");
    most.push_back("lion");
    most.push_back("tiger");
    most.push_back("lion");
    most.push_back("donkey");
    most.push_back("tiger");
                                     
    std::map<std::string, int> src;
    for(std::vector<std::string>::iterator it = most.begin(); it!= most.end(); it++)
        ++src[*it];

    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
            mytransform
                     );

    std::multimap<int,std::string>::iterator it = dst.begin();

     for(it=dst.begin(); it !=dst.end();++it)
       std::cout<<it->second<<":"<<it->first<<std::endl;

     return dst.begin();  
    }

int main() {
    std::multimap<int, std::string, std::greater<int> > dst;
    std::multimap<int, std::string>::iterator rec;
    rec = client(dst);

    while (rec != dst.end()) {
        std::cout << rec->second << ":" << (rec)->first << std::endl;
        rec++;
    }

    rec = dst.begin();
    std::map<int, std::vector<std::string> > three_highest;

    while (three_highest.size() < 3 && rec != dst.end()) {
        three_highest[rec->first].push_back(rec->second);
        rec++;
    }

    std::cout << "\nthree_highest:\n";
    for (std::map<int, std::vector<std::string> >::iterator hit = three_highest.begin(); hit != three_highest.end(); ++hit) {
        //std::cout << hit->first << ":";

        for (std::vector<std::string>::iterator vit = (*hit).second.begin(); vit != (*hit).second.end(); vit++){
            std::cout << hit->first << ":";
            std::cout << *vit << "\n";
        }
    }

return 0;
}

