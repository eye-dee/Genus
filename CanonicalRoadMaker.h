#pragma once

#include<vector>
#include<algorithm>

#include "RoadMaker.h"

#define DEGREE_CANONICAL 2u

class CanonicalRoadMaker : public RoadMaker
{
public:

	CanonicalRoadMaker(const double *x, const double *y, std :: size_t n);

	void makeSpline();

	double f(double x);

	void fastDraw();
};

