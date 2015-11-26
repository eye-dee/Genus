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
	weight(STANDART_WHEEL_MASS),
	mC(10.0,50.0,200.0),
	N(G*weight,0.0),
	friction(),
	resistance(),
	mg(G*weight,-PI/2.0),
	force(),
	newForce(),
	isForce(false),
	sum(),
	stickAlpha(2.0*PI/NUMBER_OF_STICK)
{
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = stickAlpha*i;
}
Wheel :: Wheel(double setX,double setY) : x(setX),
	y(setY),
	r(STANDART_WHEEL_RAD),
	acceleration(0.0),
	accelerationX(0.0),
	accelerationY(0.0),
	speed(0.0),
	speedX(0.0),
	speedY(0.0),
	weight(STANDART_WHEEL_MASS),
	mC(10.0,50.0,200.0),
	N(G*weight,PI/2.0),
	friction(),
	resistance(),
	mg(G*weight,-PI/2.0),
	force(),
	newForce(),
	isForce(false),
	sum(),
	stickAlpha(2.0*PI/NUMBER_OF_STICK)
{
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = stickAlpha*i;
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
	sum(),
	stickAlpha(2.0*PI/NUMBER_OF_STICK)
{
	for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] = stickAlpha*i;
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

	std :: cout << x << ' '<< alpha << '\n';

	double temp =  atan(-1.0/tan(alpha));
	Power newN, newMg, newFriction, newResistance;
	if (temp < 0.0)	
		newN = Power(-G*weight*cos(alpha), temp);
	else
		newN = Power(-G*weight*cos(alpha), PI + temp);

	double minY = getMin();
	if ( y > minY + 0.01)
	{
		newN.null();
		newMg = Power(G*weight,-PI/2.0);
	} else
	{
		newMg.null();
	}
		
	speed = sqrt(speedX*speedX + speedY*speedY);

	temp = getAlpha();

	if(speed < MIN_SPEED) //min_speed - приглядеться
		newFriction.null();
	else
		newFriction = Power(abs(N.get()) * K_FRICTION, temp);

	newResistance = Power(speed*speed*AIR_RESISTANCE, temp);//force - ok, n - ok, friction - ok, res - ok

	accelerationX += ((newForce.getX() - force.getX()) + 
		(newN.getX() - N.getX()) +
		(newFriction.getX() - friction.getX()) +
		(newResistance.getX() - resistance.getX())) / weight;

	accelerationY += ((newForce.getY() - force.getY()) + 
		(newN.getY() - N.getY()) +
		(newFriction.getY() - friction.getY()) +
		(newResistance.getY() - resistance.getY()) +
		(newMg.getY() - mg.getY())) / weight;

	speedX += accelerationX;
	speedY += accelerationY;

	if(abs(speedX) > 6)
	{
		x += 0.1*speedX;
		for (int i = 0; i < NUMBER_OF_STICK; ++i)
			stick[i] -= 0.1*speedX/r;
	}
	if(abs(speedY) > 6)
		y += 0.1*speedY;

	N = newN;
	mg = newMg;
	resistance = newResistance;
	friction = newFriction;

	minY = getMin();
	if (y < minY)
	{
		y = minY;
	}
}