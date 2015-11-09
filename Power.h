#pragma once

#include<math.h>

class Power
{
public:
	Power();

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
private:
	double projectionX;
	double projectionY;
	double value;
};

