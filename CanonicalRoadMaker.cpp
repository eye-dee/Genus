#include "CanonicalRoadMaker.h"

#include <glut.h>

CanonicalRoadMaker :: CanonicalRoadMaker(const double xStart,const double yStart) : RoadMaker(xStart,yStart)
{}

CanonicalRoadMaker :: CanonicalRoadMaker(const double *x, const double *y, std :: size_t n) : 
	RoadMaker(x,y,n,DEGREE_CANONICAL)
{
}

void CanonicalRoadMaker :: makeSpline()
{
	if (!spline)
	{
		for (std :: size_t i = 0; i < _N - 1; ++i)
		{
			double temp = _x[i+1] - _x[i];
			_k[i+1][0] = (_x[i+1]*_f[i] - _x[i]*_f[i+1])/temp;
			_k[i+1][1] = (_f[i+1] - _f[i])/temp;
		}
		if (_N > 1)
			_k[0] = _k[1];
	

		spline = true;
	}/* else исключение написать
	{
	}*/
}

double CanonicalRoadMaker :: f(double x) const
{
	return RoadMaker :: f(x);
}

void CanonicalRoadMaker :: fastDraw()
{
	glBegin(GL_LINE_STRIP);
		for (std :: size_t i = 0; i < _N; ++i)
			glVertex2d(_x[i],_f[i]);
	glEnd();
}

void CanonicalRoadMaker :: pushNewPoint(const double x,const double y)
{
	if (_N >= _x.size())
	{
		_x.push_back(x);
		_f.push_back(y);
		++_N;
	} else
	{
		_x[_N] = x;
		_f[_N++] = y;
	}

	spline = true;

	double temp = _x[_N - 1u] - _x[_N - 2u];
	_k.push_back(Polynom(
		(_x[_N - 1u]*_f[_N - 2u] - _x[_N - 2u]*_f[_N - 1u])/temp,
		(_f[_N - 1u] - _f[_N - 2u])/temp)
				);
}

double CanonicalRoadMaker :: getAlpha(double x, double bottom, int st) const
{
	return RoadMaker :: getAlpha(x,bottom,st);
}