#pragma once

#include<memory>

#include"myColor.h"
#include"RoadMaker.h"
#include"Power.h"

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
		force.set(WHEEL_FORCE,back->getAlpha(x,y-r));
	}

	inline void unAccelerate()
	{
		force.set(0.0,0.0);
	}
	inline void bendBack()
	{
	}

	inline double getAlpha() const
	{
		return alpha;
	}
	inline void setAlpha(double al)
	{
		alpha = al;
	}

	void calculate();
private:
	double x;
	double y;
	const double r;
	double acceleration;
	double speed;
	const double weight;
	
	double alpha;
	
	MyColor mC;

	RoadMakerPointer back;

	Power force;
	Power sum;

	double stick[NUMBER_OF_STICK];
};