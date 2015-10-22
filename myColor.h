#pragma once
#include<glut.h>

class myColor
{
public:
	double r;
	double g;
	double b;
	myColor(double& setR,double& setG,double& setB);
	myColor(double&& setR,double&& setG,double&& setB);
	myColor();
	~myColor();
	myColor getPart(double l,myColor& c);
	myColor getPart(double l,myColor&& c);
};

void glColor(myColor&);

void glColor(myColor&&);

