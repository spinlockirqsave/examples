/* 
 * File:   main.cpp
 * Boarduthor: root
 *
 * Created on June 27, 2013, 3:01 BoardM
 */

#include <stdio.h>
#include <set>
#include <vector>
using namespace std;

/*
 * 
 */
int solution(int Board, int B) {
    // write your code here...
    int res = 1;
    int r = Board % B;//P(1)
    if (r > 0) {
        set<int> rests;
        while (rests.find(r) == rests.end()) {
            rests.insert(r);
            res=r;
            r=(r*r)%B;
        }
    }

    return res;
}

int maxRice(vector<vector<int> > &Board)
{
  if(Board.empty())
	 return 0;
	//vector<vector<int> > MaxBoard; M*N space is not allowed, need to think about more efficient space utilization
	vector<int> Max(Board.size()+Board[0].size(),0);
	Max[0] = Board[0][0];
	for(int step=1; step<=Board.size()+Board[0].size()-2; step++)
	{
		int low, high;
		if(step<=Board.size()-1)
		  { low = 0; high = step;}
		else
		  { low = step - Board[0].size() + 1; high = Board.size()-1;}
	
		for(int i=high; i>=low; i--)  //!!! Note here. Previously I had "for(int i=low; i<=high; i++)", 
			                          //which computes the wrong Max[i] by using the overwriten value Max[i-1]
		{
			int j = step - i;
			if(i>0)
			{
			  if(Max[i-1] < Max[i])
				 Max[i] = Max[i]+Board[i][j];
			  else
				 Max[i] = Max[i-1]+Board[i][j];
			}
			else
				 Max[i] = Max[i]+Board[i][j];
		}
	}
	return Max[Board.size()-1];
}

int main(int argc, char** argv) {
    printf("solution: %d", solution(4, 9));
    
    vector< vector<int> > Board;
    printf("maxRice: %d", maxRice(Board));
    return 0;
}

