#include "Hero.h"


Hero :: Hero(void) : _x(100.0),
	_y(100.0),
	speed(0.0),
	a(0.0),
	F(0.0),
	mass(0.05),
	color(random(256),random(256),random(256))
{
}

Hero :: Hero(double x) : _x(x),
	_y(100.0),
	speed(0.0),
	a(0.0),
	F(0.0),
	mass(0.05),
	color(random(256),random(256),random(256))
{
}


Hero :: ~Hero(void)
{
}


void Hero :: accelerate()
{
	F = 1.0;
}
void Hero :: unAccelerate()
{
	F = 0.0;
}

void Hero :: brake()
{
	F = -1.0;
}
void Hero :: unBrake()
{
	F = 0.0;
}

void Hero :: bendForward()
{
}
void Hero :: bendBack()
{
}

void Hero :: draw()
{
	calculate();
	glColor(color);
	glBegin(GL_POINTS);
	for (double t = 0.0; t < 2*PI; t += 0.1)
		glVertex2d(_x + 10.0*cos(t),_y + 10.0*sin(t));
	glEnd();
}

void Hero :: calculate()
{
	double sumF = F - k*abs(speed)*speed;
/*	std :: cout << "sumF: " << sumF << std :: endl;
	std :: cout << a << std :: endl;
	std :: cout << speed << std :: endl;*/
	a = sumF/mass;
	speed += 0.1*a;
	_x += speed*0.1;
}

double Hero :: getX()
{
	return _x;
}
double Hero :: getY()
{
	return _y;
}

int random(int a)
{
	return rand()%a;
}