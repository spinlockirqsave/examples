/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on December 18, 2013, 2:03 PM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
#include <vector>  
#include <fstream>  
#include <boost/serialization/vector.hpp>  
#include <boost/archive/text_oarchive.hpp>  
#include <boost/archive/text_iarchive.hpp>  
  
class Info  
{  
private:  
    // Allow serialization to access non-public data members.  
    friend class boost::serialization::access;  
  
    // Serialize the std::vector member of Info  
    template<class Archive>  
    void serialize(Archive & ar, const unsigned int version)  
    {  
      ar & filenames;      
    }  
     
    std::vector<std::string> filenames;  
  
public:  
    void AddFilename( const std::string& filename );      
    void Print() const;  
};  
  
void Info::Print() const  
{  
    std::copy(filenames.begin(),       
              filenames.end(),       
              std::ostream_iterator<std::string>(std::cout, "\n"));       
}  
  
void Info::AddFilename( const std::string& filename )  
{  
    filenames.push_back( filename );      
}  
  
int main(int argc, char** argv)   
{  
    Info info;  
    info.AddFilename( "ThisFile.txt" );  
    info.AddFilename( "ThatFile.txt" );  
    info.AddFilename( "OtherFile.txt" );  
      
    // Save filename data contained in Info object  
    {  
      // Create an output archive  
      std::ofstream ofs( "store.dat" );  
      boost::archive::text_oarchive ar(ofs);  
  
      // Save the data  
      ar & info;  
    }  
      
    // Restore from saved data and print to verify contents  
    Info restored_info;  
    {  
        // Create and input archive  
        std::ifstream ifs( "store.dat" );  
        boost::archive::text_iarchive ar(ifs);  
  
        // Load the data  
        ar & restored_info;  
   }  
      
    restored_info.Print();  
  
    return 0;  
}

