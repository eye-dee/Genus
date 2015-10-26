#pragma once

#include<vector>
#include<algorithm>

#include "RoadMaker.h"


#define DEGREE_CUBIC 4u
const double xStart[2] = {90.0,100.0};
const double yStart[2] = {100.0,100.0};
	
class CubicSplineRoadMaker : public RoadMaker
{
public:
	CubicSplineRoadMaker(const double x[2], const double y[2]);
	CubicSplineRoadMaker(const double *x, const double *y, std :: size_t n);

	void pushNewPoint(const double x,const double y);
	void makeSpline();

	double f(double x) const;
};