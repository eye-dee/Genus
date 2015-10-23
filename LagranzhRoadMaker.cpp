#include "LagranzhRoadMaker.h"


LagranzhRoadMaker :: LagranzhRoadMaker(const double *x, const double *y, std :: size_t n) :
	RoadMaker(x,y,n,n/(LAGRANZH_DEGREE - 1u) + 1u,LAGRANZH_DEGREE),
//	RoadMaker(x,y,n,1u,LAGRANZH_DEGREE),
	partsAmount(n/(LAGRANZH_DEGREE - 1u) + 1u)
//	partsAmount(1u)
{
}

void LagranzhRoadMaker :: makeSpline()
{
	Polynom temp(1u);
	for (std :: size_t i = 0; i < _k.size(); ++i)
	{
		for (std :: size_t j = 8u*i; (j < 8u*i + 11u) && (j < _N); ++j)
		//for (std :: size_t j = 0u; j < _N; ++j)
		{
			temp = Polynom(_f[j]);
			for (std :: size_t p = 8u*i; (p < 8u*i + 11u) && (p < _N); ++p)
		//	for (std :: size_t p = 0u; p < _N; ++p)
			{
				if (j == p)
					continue;
				temp = temp*Polynom(-_x[p],1.0);
				temp = temp*Polynom(1.0/(_x[j] - _x[p]));
			}
			_k[i] = _k[i] + temp;
			temp.nulling();
		}
	}

	spline = true;
}
double LagranzhRoadMaker :: f(double x)
{
	//x -= 0.5;
	if (spline)
	{
		Polynom temp(_k[0]);

		if (x < _x[0]) 
			temp = _k[0];
		else if (x > _x[_N-1])
			temp = _k[partsAmount-1];
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
			temp = _k[j/(LAGRANZH_DEGREE-1u)];
		}
		//x += 0.5;
		return temp.f(x);
	} else
	{
		throw UseWithoutSpline();
	}
}