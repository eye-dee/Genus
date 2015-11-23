#pragma once

#include<math.h>

class Power
{
public:
	Power();
	Power(double p, double al);

	inline double getX() const
	{
		return projectionX;
	}
	inline double getY() const
	{
		return projectionY;
	}
	inline double get() const
	{
		return value;
	}
	inline void set(double v,double alpha)
	{
		projectionX = v*cos(alpha);
		projectionY = v*sin(alpha);
		value = v;
	}
	inline Power& operator =(double p)
	{
		value = p;
		projectionX = p;
		return *this;
	}
private:
	double projectionX;
	double projectionY;
	double value;
};

