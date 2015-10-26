#include "RoadMaker.h"

RoadMaker :: RoadMaker(const double xStart,const double yStart) : _x(1u,xStart),
	_f(1u,yStart),
	_k(1u,Polynom(yStart,0.0)),
	_N(1),
	spline(true)
	//так как этот конструктор создан для он-лайн рисования, то скорее всего для оптимизации будет правильнее сразу выделять некоторую память под вектора
{}

RoadMaker :: RoadMaker(const double x[2],const double y[2],std :: size_t degree) : _x(x,x+2),
	_f(y,y+2),
	_k(2u,Polynom(degree)),
	_N(2),
	spline(true)
{
	_k[0][0] = y[0];
	_k[0][1] = 0.0;
	_k[0][2] = 0.0;
	_k[0][3] = 0.0;
	_k[1][0] = y[0];
	_k[1][1] = 0.0;
	_k[1][2] = 0.0;
	_k[1][3] = 0.0;

}


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


double RoadMaker :: f(double x) const
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
