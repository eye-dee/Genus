#include "myColor.h"

myColor::~myColor()
{}

myColor :: myColor (double& setR,double& setG,double& setB) :
		r(setR),
		g(setG),
		b(setB)
	{}

myColor :: myColor(double&& setR,double&& setG,double&& setB) :
		r(setR),
		g(setG),
		b(setB)
	{}

myColor myColor :: getPart(double l,myColor& c)
{
	return myColor((r + l*c.r)/(1+l),(g + l*c.g)/(1+l),(b + l*c.b)/(1+l));
}

myColor myColor :: getPart(double l,myColor&& c)
{
	return myColor((r + l*c.r)/(1+l),(g + l*c.g)/(1+l),(b + l*c.b)/(1+l));
}

void glColor(myColor& c)
{
	glColor3d(c.r/255.0,c.g/255.0,c.b/255.0);
}

void glColor(myColor&& c)
{
	glColor3d(c.r/255.0,c.g/255.0,c.b/255.0);
}
