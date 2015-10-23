#include "RoadMaker.h"


RoadMaker :: RoadMaker(const double *x, const double *y, std :: size_t n,std :: size_t degree) : _x(x,x+n),
	_f(y,y+n),
	_k(n,Polynom(degree)),
	_N(n),
	spline(false)
{
}

RoadMaker :: RoadMaker(const double *x, const double *y, std :: size_t n,std :: size_t koefSize, std :: size_t degree) : _x(x,x+n),
	_f(y,y+n),
	_k(koefSize,Polynom(degree)),
	_N(n),
	spline(false)
{}


double RoadMaker :: f(double x)
{
	if(spline)
	{
		Polynom temp(_k[0].size());
	
		if (x < _x[0]) 
			temp = _k[0];
		else if (x > _x[_N-1])
			temp = _k[_N-1];
		else
		{
			std::size_t i = 0, j = _N - 1;
			while (i + 1 < j)
			{
				std::size_t k = i + (j - i)/2;
				if (x <= _x[k])
					j = k;
				else
					i = k;
			}
			temp = _k[j];
		}
		return temp.f(x);
	} else
	{
		throw UseWithoutSpline();
	}
}
