/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on April 13, 2013, 10:17 PM
 */

#include <cstdlib>
#include <vector>

#include <iostream>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/microsec_time_clock.hpp>

class TestTimer
{
public:
    TestTimer(const std::string & name) : name(name),
        start(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time())
    {
    }

    ~TestTimer()
    {
        using namespace std;
        using namespace boost;

        posix_time::ptime now(date_time::microsec_clock<posix_time::ptime>::local_time());
        posix_time::time_duration d = now - start;

        cout << name << " completed in " << d.total_milliseconds() / 1000.0 <<
            " seconds" << endl;
    }

private:
    std::string name;
    boost::posix_time::ptime start;
};

struct Pixel
{
    Pixel()
    {
    }

    Pixel(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b)
    {
    }
    Pixel(const Pixel&) {}

    unsigned char r, g, b;
};

void UseVector()
{
    TestTimer t("UseVector");

    for(int i = 0; i < 1000; ++i)
    {
        int dimension = 999;

        std::vector<Pixel> pixels;
        pixels.resize(dimension * dimension);

        for(int i = 0; i < dimension * dimension; ++i)
        {
            pixels[i].r = 255;
            pixels[i].g = 0;
            pixels[i].b = 0;
        }
    }
}

void UseVectorPushBack()
{
    TestTimer t("UseVectorPushBack");

    for(int i = 0; i < 1000; ++i)
    {
        int dimension = 999;

        std::vector<Pixel> pixels;
            pixels.reserve(dimension * dimension);

        for(int i = 0; i < dimension * dimension; ++i)
            pixels.push_back(Pixel(255, 0, 0));
    }
}

void UseArray()
{
    TestTimer t("UseArray");

    for(int i = 0; i < 1000; ++i)
    {
        int dimension = 999;

        Pixel * pixels = (Pixel *)malloc(sizeof(Pixel) * dimension * dimension);

        for(int i = 0 ; i < dimension * dimension; ++i)
        {
            pixels[i].r = 255;
            pixels[i].g = 0;
            pixels[i].b = 0;
        }

        free(pixels);
    }
}
void UseVectorCtor()
{
    TestTimer t("UseConstructor");

    for(int i = 0; i < 1000; ++i)
    {
        int dimension = 999;

        std::vector<Pixel> pixels(dimension * dimension, Pixel(255, 0, 0));
    }
}

int main()
{
    TestTimer t1("The whole thing");

    UseArray();
    UseVector();
    UseVectorCtor();
    UseVectorPushBack();

    return 0;
}

