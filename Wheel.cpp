#include "Wheel.h"

#include "const.h"

Wheel :: Wheel() : x(0.0),
	y(0.0),
	r(10.0),
	acceleration(0.0),
	speed(0.0),
	weight(10.0),
	mC(10.0,50.0,200.0)
{
	double tmp = 2.0*PI/NUMBER_OF_STICK;
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = tmp*i;
}
Wheel::Wheel(double setX,double setY) : x(setX),
	y(setY),
	r(10.0),
	acceleration(0.0),
	speed(0.0),
	weight(10.0),
	mC(10.0,50.0,200.0)
{
	double tmp = 2.0*PI/NUMBER_OF_STICK;
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = tmp*i;
}
Wheel::Wheel(double setX,double setY,double setR,double w) : x(setX),
	y(setY),
	r(setR),
	acceleration(0.0),
	speed(0.0),
	weight(w),
	mC(10.0,50.0,200.0)
{
	double tmp = 2.0*PI/NUMBER_OF_STICK;
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = tmp*i;
}

void Wheel :: draw() const
{
		glColor(mC);
		glBegin(GL_POINTS);
			for(double t = 0; t < 2*PI; t += 0.01)
				glVertex2d(x + r*cos(t), y + r*sin(t));
		glEnd();
	
		glBegin(GL_LINES);
			for(int i=0; i<10; ++i)
			{
				glVertex2d(x, y);
				glVertex2d(x + r*cos(stick[i]), y + r*sin(stick[i]));
			}
		glEnd();
}

void Wheel :: calculate()
{
	alpha = back->getAlpha(x,y-r);
	double dir = (alpha > PI/2.0) ?  -1.0 : 1.0;
	
	double sopr = K_FRICTOIN*(weight*cos(alpha)) + AIR_RESISTANCE*speed*abs(speed);

	sum.set(-dir*weight*G*sin(alpha)-sopr+force.get(),alpha);

	acceleration = sum.get()/weight;

	speed += acceleration;

	x += speed*cos(alpha);
	y += speed*sin(alpha);

	double border = r/cos(alpha) + back->f(x);
	if (y < border)
	{
		y = back->f(x) + r;
	}

	for(int i=0; i < NUMBER_OF_STICK; ++i)
		stick[i] -= speed*cos(alpha)/r;
}