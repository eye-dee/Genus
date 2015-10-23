#pragma once

#include "RoadMaker.h"

#define LAGRANZH_DEGREE 9u

class LagranzhRoadMaker : public RoadMaker
{
public:
	LagranzhRoadMaker(const double *x, const double *y, std :: size_t n);
		
	void makeSpline();
	double f(double x);
private:
	std :: size_t partsAmount;
};

