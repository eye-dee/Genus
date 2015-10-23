#pragma once

#include<vector>
#include<algorithm>

#include "RoadMaker.h"

#define DEGREE_CUBIC 4u

class CubicSplineRoadMaker : public RoadMaker
{
public:
	CubicSplineRoadMaker(const double *x, const double *y, std :: size_t n);

	void makeSpline();
	double f(double x);
};