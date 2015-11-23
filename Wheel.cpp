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
	N(G*weight,0.0),
	friction(),
	resistance(),
	mg(G*weight,-PI/2.0),
	force(),
	newForce(),
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
	N(G*weight,PI/2.0),
	friction(),
	resistance(),
	mg(G*weight,-PI/2.0),
	force(),
	newForce(),
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
	N(G*weight,0.0),
	friction(),
	resistance(),
	mg(G*weight,-PI/2.0),
	force(),
	newForce(),
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
	double alpha = back->getAlphaOld(x);//mg-const, N -ok, force - ok, friction - ok, resistance - ok
	Power newN, newFriction, newResistance;
	if(alpha > 0)	//нашли альфу для на горку и с горки
		newN = Power(mg.get()*cos(alpha), PI/2 + alpha);
	else
		newN = Power(mg.get()*cos(alpha), PI/2 - alpha);
	
	speed = sqrt(speedX*speedX + speedY*speedY);
	if(speed < MIN_SPEED) //min_speed - приглядеться
	{
		/*accelerationX = 0.0;
		speedX = 0.0;*/
		newFriction = 0.0;
	}
	else
		newFriction = Power(newN.get() * K_FRICTION, PI + getAlpha());

	std :: cout << x << ' ' << y << ' ' << speedX << ' ' << accelerationY << '\n'
			 << getAlpha() << '\n';
	newResistance = Power(speed*speed*AIR_RESISTANCE, PI + getAlpha());//force - ok, n - ok, friction - ok, res - ok
	accelerationX += ((newForce.getX() - force.getX()) + 
		(newN.getX() - N.getX()) +
		(newFriction.getX() - friction.getX()) +
		(newResistance.getX() - resistance.getX())) / weight;

	accelerationY += ((newForce.getY() - force.getY()) + 
		(newN.getY() - N.getY()) +
		(newFriction.getY() - friction.getY()) +
		(newResistance.getY() - resistance.getY())) / weight;

	speedX += accelerationX;
	speedY += accelerationY;

	x += speedX;
	y += speedY;

	double minY = back->f(x);
	if (y < minY)
	{
		/*x -= speedX;
		y -= speedY;*/
		y = minY;
	}

	N = newN;
	friction = newFriction;
	resistance = newResistance;
}