#include "Wheel.h"

#include "const.h"

Wheel :: Wheel() : x(0.0),
	y(0.0),
	r(STANDART_WHEEL_RAD),
	acceleration(0.0),
	accelerationX(0.0),
	accelerationY(0.0),
	speed(0.0),
	speedX(0.0),
	speedY(0.0),
	weight(10.0),
	mC(10.0,50.0,200.0),
	force(),
	isForce(false),
	sum()
{
	double tmp = 2.0*PI/NUMBER_OF_STICK;
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = tmp*i;
}
Wheel::Wheel(double setX,double setY) : x(setX),
	y(setY),
	r(STANDART_WHEEL_RAD),
	acceleration(0.0),
	accelerationX(0.0),
	accelerationY(0.0),
	speed(0.0),
	speedX(0.0),
	speedY(0.0),
	weight(10.0),
	mC(10.0,50.0,200.0),
	force(),
	isForce(false),
	sum()
{
	double tmp = 2.0*PI/NUMBER_OF_STICK;
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = tmp*i;
}
Wheel::Wheel(double setX,double setY,double setR,double w) : x(setX),
	y(setY),
	r(setR),
	acceleration(0.0),
	accelerationX(0.0),
	accelerationY(0.0),
	speed(0.0),
	speedX(0.0),
	speedY(0.0),
	weight(w),
	mC(10.0,50.0,200.0),
	force(),
	isForce(false),
	sum()
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
	/*double alpha = (back->getAlpha(x,y));
	double alphaDir = getAlpha();

	Power N(weight*G*cos(alpha),alpha + PI/2.0);

	speed = sqrt(speedX*speedX + speedY*speedY)*(sin(alphaDir)/abs(sin(alphaDir)));

	Power newSum;
	newSum = (force.get() - K_FRICTOIN*N.get() - AIR_RESISTANCE*speed*abs(speed) - weight*G*sin(alpha));

	acceleration -= (newSum.get()/abs(newSum.get()))*((newSum.get() - sum.get()))/weight;
	sum = newSum;

	accelerationX = acceleration*cos(alphaDir);
	accelerationY = acceleration*abs(sin(alphaDir));

	speedX += accelerationX;
	speedY += accelerationY;

	x += speedX;
	y += speedY;

	std :: cout << x << ' ' << y << ' ' << alpha << '\n';

	double minY(back->f(x));
	if (y < minY)
	{
		y = minY;
		speedY = 0.0;
		acceleration = sqrt(accelerationX*accelerationX + 0.2*accelerationY*accelerationY);
	}*/ /*пытаемся сдалать изменение силы*/

	setFly();
	double alpha = (back->getAlphaOld(x));
	double alphaDir = getAlpha();

	Power N(weight*G*cos(alpha),alpha + PI/2.0);

	speed = sqrt(speedX*speedX + speedY*speedY)*(sin(alphaDir)/abs(sin(alphaDir)));

	Power newSum;
	if(isFly)
		newSum = (- K_FRICTOIN*N.get() - AIR_RESISTANCE*speed*abs(speed) - weight*G*sin(alphaDir));
	else
		newSum = (force.get() - K_FRICTOIN*N.get() - AIR_RESISTANCE*speed*abs(speed) - weight*G*sin(alphaDir));

	acceleration += newSum.get()/weight;
	sum = newSum;

	if(isForce)
		accelerationX = acceleration*cos(alpha);
	else
		accelerationX = acceleration*cos(alphaDir);
	accelerationY = acceleration*abs(sin(alphaDir));

	speedX += accelerationX;
	speedY += accelerationY;

	x += speedX;
	y += speedY;

	std :: cout << x << ' ' << y << ' ' << alpha << '\n';

	double minY(back->f(x));
	if (y < minY)
	{
		y = minY;
		speedY = 0.0;
		acceleration /= -2.0;
	}
}