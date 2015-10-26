#pragma once

#include<vector>
#include<string>
#include<algorithm>
#include <glut.h>

#include "Polynom.h"

class RoadMaker
{
public:
	class UseWithoutSpline
	{};

	virtual void makeSpline() = 0;
	virtual void pushNewPoint(const double x,const double y) = 0;

	virtual double f(double x) const;

	RoadMaker(const double xStart,const double yStart);
	RoadMaker(const double x[2],const double y[2],std :: size_t degree);
	RoadMaker(const double *x, const double *y, std :: size_t n,std :: size_t degree);
	RoadMaker(const double *x, const double *y, std :: size_t n,std :: size_t koefSize, std :: size_t degree);
protected:
	std :: vector<double> _x;
	std :: vector<double> _f;

	std :: vector<Polynom> _k;

	std :: size_t _N;

	bool spline;
};

