#pragma once

#include "RoadMaker.h"

#define LAGRANZH_DEGREE 4u

class LagranzhRoadMaker : public RoadMaker
{
public:
	LagranzhRoadMaker(const double *x, const double *y, std :: size_t n);
		
	void makeSpline();
	void pushNewPoint(const double x,const double y);

	double f(double x) const;
private:
	std :: size_t partsAmount;
};

