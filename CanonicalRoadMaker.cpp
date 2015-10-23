#include "CanonicalRoadMaker.h"

#include <glut.h>

CanonicalRoadMaker :: CanonicalRoadMaker(const double *x, const double *y, std :: size_t n) : 
	RoadMaker(x,y,n,DEGREE_CANONICAL)
{
}

void CanonicalRoadMaker :: makeSpline()
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
}

double CanonicalRoadMaker :: f(double x)
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