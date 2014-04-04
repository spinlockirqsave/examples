#ifndef MYHEADERS_H
#define MYHEADERS_H

typedef std::pair<const int,double> v;
typedef std::map<const int,std::pair<const int,double> > myMaps;

double indicatorFunc ( const double & x, const double & a, const double & b){
	if(x >=a && x <=b) return 1.0;
		else return 0.0;
	}

#endif