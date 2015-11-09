#include "MyColor.h"

MyColor::~MyColor()
{}

MyColor :: MyColor (double& setR,double& setG,double& setB) :
		r(setR),
		g(setG),
		b(setB)
	{}

MyColor :: MyColor(double&& setR,double&& setG,double&& setB) :
		r(setR),
		g(setG),
		b(setB)
	{}

MyColor MyColor :: getPart(double l,MyColor& c)
{
	return MyColor((r + l*c.r)/(1+l),(g + l*c.g)/(1+l),(b + l*c.b)/(1+l));
}

MyColor MyColor :: getPart(double l,MyColor&& c)
{
	return MyColor((r + l*c.r)/(1+l),(g + l*c.g)/(1+l),(b + l*c.b)/(1+l));
}

void glColor(const MyColor& c)
{
	glColor3d(c.r/255.0,c.g/255.0,c.b/255.0);
}

void glColor(const MyColor&& c)
{
	glColor3d(c.r/255.0,c.g/255.0,c.b/255.0);
}
