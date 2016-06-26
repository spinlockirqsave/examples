/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on November 16, 2013, 7:43 PM
 */
#include <iostream>

class Cell
    {
public:
        int totalCost;
    };

struct Comparator
        {
            bool operator()(Cell const *lfs, Cell const *rhs)
            {
                std::cout<<"called!\n";
                return lfs->totalCost < rhs->totalCost;
            }
        };
#include <qe>
#include <vector>
std::priority_qe<Cell*, std::vector<Cell*>, Comparator> path;

void function(Cell* cell)
{
    static int i = 0; 
     //cell->totalCost += ++i;
     path.push(cell);
}

int main(int, char**)
{
    Cell first;
    Cell second;
    Cell third;

    function(&first);
    function(&second);
    function(&third);

}

