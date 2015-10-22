#pragma once

#include<vector>
#include<algorithm>

class CubicSpline
{
public:
	struct polynomK
	{
		double a;
		double b;
		double c;
		double d;
		polynomK() : a(0.0),
			b(0.0),
			c(0.0),
			d(0.0)
		{};
	};

	CubicSpline(const double *x, const double *y, std :: size_t n);

	void makeSpline();
	double f(double x);

private:
	std :: vector<double> _x; //xi from 0 to N
	std :: vector<double> _f; //fi from 0 to N

	std :: vector<polynomK> _k;

	std :: size_t _N;
	bool spline;
};