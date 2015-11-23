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
		isForce = true;
		force = newForce;
		newForce.set(WHEEL_FORCE,back->getAlphaOld(x));
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

	/*inline double getAlpha() const
	{
		return alpha;
	}*/

	/*inline void setAlpha(double al)
	{
		alpha = al;
	}*/

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
	const Power mg;
	Power force;
	Power newForce;
	bool isForce;

	Power sum;

	double stick[NUMBER_OF_STICK];

	inline double getAlpha() const
	{
		if (speedX < MIN_SPEED)
			if (speedY > 0)
				return PI/2.0;
			else
				return -PI/2.0;
		return atan(speedY/speedX);
	}
};