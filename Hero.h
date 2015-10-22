#pragma once

#include <math.h>
#include <glut.h>
#include <iostream>
#include <memory>

#include "defs.h"
#include "myColor.h"

#define k 0.1

int random(int);

class Hero
{
public:
	Hero(void);
	Hero(double x);
	~Hero(void);

	void accelerate();
	void unAccelerate();
	void brake();
	void unBrake();
	void bendForward();
	void bendBack();

	void draw();

	double getX();
	double getY();

private:
	double _x,_y;
	double speed;
	double a;
	double F;
	double mass;

	myColor color;

	void calculate();
};

typedef std :: shared_ptr<Hero> HeroPointer;

class Comparator
{
public:
	int operator () (HeroPointer lhs, HeroPointer rhs)
	{
		return lhs->getX() < rhs->getX();
	}
};