#pragma once
#include<glut.h>



class MyColor
{
public:
	double r;
	double g;
	double b;
	MyColor(double& setR,double& setG,double& setB);
	MyColor(double&& setR,double&& setG,double&& setB);
	MyColor();
	~MyColor();
	MyColor getPart(double l,MyColor& c);
	MyColor getPart(double l,MyColor&& c);
};

void glColor(const MyColor&);

void glColor(const MyColor&&);