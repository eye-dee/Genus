#pragma once

#include<memory>

#include"myColor.h"
#include"RoadMaker.h"
#include"Power.h"

#include"const.h"

class Wheel
{
public:
	Wheel();
	Wheel(double setX,double setY);
	Wheel(double setX,double setY,double setR,double w);

	void draw() const;

	inline double getX() const
	{
		return x;
	}
	inline double getY() const
	{
		return y;
	}

	inline void setBack(RoadMakerPointer a)
	{
		back = a;
	}

	inline void accelerate()
	{
		double minY = getMin();
		if ( y < minY + 0.01)
		{
			isForce = true;
			force = newForce;
			newForce.set(WHEEL_FORCE,back->getAlphaOld(x));
		} else
		{
			isForce = false;
			force = newForce;
			newForce.set(0.0,0.0);
		}
	}

	inline void unAccelerate()
	{
		isForce = false;
		force = newForce;
		newForce.set(0.0,0.0);
	}
	inline void bendBack()
	{
	}

	inline void setFly()
	{
		double min = back->f(x);
		if ( y > min + 2.0)
			isFly = true;
		else
			isFly = false;
	}

	void calculate();
private:
	double x;
	double y;
	const double r;
	double acceleration, accelerationX, accelerationY;
	double speed, speedX, speedY;
	const double weight;
	
	bool isFly;
	
	MyColor mC;

	RoadMakerPointer back;
	
	Power N;
	Power friction;
	Power resistance;
	Power mg;
	Power force;
	Power newForce;
	bool isForce;

	Power sum;

	double stickAlpha;
	double stick[NUMBER_OF_STICK];

	inline double getMin() const
	{
		return back->f(x) + (r/cos(back->getAlphaOld(x))); 
	}

	inline double getAlpha() const
	{
		double x(speedX);
		if (abs(speedX) < MIN_SPEED)
			x = MIN_SPEED;
		double temp = atan(abs(speedY)/abs(x));

		if (speedX < 0.0)
		{
			if (speedY < 0.0)
				return temp;
			else
				return -temp;
		} else
		{
			if (speedY < 0.0)
				return PI - temp;
			else
				return PI + temp;
		}
	}
};