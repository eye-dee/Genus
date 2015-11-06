#pragma once
#include "myColor.h"
#include "defs.h"
#include <GL\GLAux.h>
#include <fstream>
//MyColor colorOfWheel(0.0,0.0,0.0);

struct wheel
{
	wheel():weight(5){};
	int x,y,r;
	double horizontalSpeed, horizontalAcceleration, verticalSpeed, verticalAcceleration, weight;
};

struct power
{
	double alpha, mean;
};

class hero
{
	public:
	int lengthOfBike;
	double stick[10];
	power gravity, reaction, resistance, friction, acceleration, rotate;
	wheel rightWheel, leftWheel, head;
	bool notAnyDike;
	double powerOfMotor, obstruct, speedLimit, backSpeedLimit, verticalReaction, gravityConst, agility,
		levelOfEarth, alphaOfEarth, densityOfEarth;

	
	hero(void):
		speedLimit(10), 
		backSpeedLimit(-5), 
		notAnyDike(true), 
		powerOfMotor(10), 
		obstruct(0.011),//проходимость, 
		verticalReaction(2),
		gravityConst(-1),
		levelOfEarth(300),
		alphaOfEarth(0),
		densityOfEarth(2),
		agility(10)
	{
		rightWheel.y=leftWheel.y=300;
		rightWheel.r=leftWheel.r=20;
		rightWheel.x=300;
		leftWheel.x=200;
		leftWheel.y=300;
		head.x=300;
		head.y=400;
		lengthOfBike=rightWheel.x-leftWheel.x;
		double tmp=2*P/10;
		for(int i=0; i<10; i++)
			stick[i]=tmp*i;
		gravity.mean=leftWheel.weight*G;
		gravity.alpha=1.5*P;
	
	}

	~hero(void);

	void print()
	{
		
		glColor3f(0,0,0);
		glBegin(GL_POINTS);
		/*for(double i=0; i<2*P; i+=0.01)
		{
			glVertex2d(leftWheel.x+leftWheel.r*cos(i), leftWheel.y+leftWheel.r*sin(i));
		}*/
		for(double i=0; i<2*P; i+=0.01)
		{
			glVertex2d(rightWheel.x+leftWheel.r*cos(i), rightWheel.y+leftWheel.r*sin(i));
		}
		glEnd();
/*
		glBegin(GL_LINES);
			glVertex2d(leftWheel.x, leftWheel.y);
			glVertex2d(rightWheel.x, rightWheel.y);
		glEnd();*/

		
		glBegin(GL_LINES);
		for(int i=0; i<10; i++)
		{
			/*glVertex2d(leftWheel.x, leftWheel.y);
			glVertex2d(leftWheel.x+leftWheel.r*cos(stick[i]), leftWheel.y+leftWheel.r*sin(stick[i]));*/
			glVertex2d(rightWheel.x, rightWheel.y);
			glVertex2d(rightWheel.x+rightWheel.r*cos(stick[i]), rightWheel.y+rightWheel.r*sin(stick[i]));
		}
		glEnd();
	}
	
	void recompute()
	{
		
	if((leftWheel.y-leftWheel.r)<=getCurrentY(leftWheel.x))
			reaction.mean=gravity.mean;
		else
			reaction.mean=0;
		if(leftWheel.horizontalSpeed>0)
		{
			friction.alpha=	acceleration.alpha+P;
			resistance.alpha=	acceleration.alpha+P;
		}
		else
		{
			friction.alpha=	getCurrentAlpha(rightWheel.x);
			resistance.alpha= getCurrentAlpha(rightWheel.x);
		}
		reaction.alpha=getCurrentAlpha(rightWheel.x)+0.5*P;
		resistance.mean=densityOfEarth*leftWheel.horizontalSpeed*leftWheel.horizontalSpeed/10;

		if(leftWheel.horizontalSpeed!=0)
			friction.mean=obstruct*reaction.mean;
		else friction.mean=0;
		leftWheel.horizontalAcceleration=	
			(acceleration.mean*cos(acceleration.alpha)
			+	friction.mean*cos(friction.alpha)
			+	resistance.mean*cos(resistance.alpha)
			+	gravity.mean*cos(getCurrentAlpha(rightWheel.x)+P*0.5))/leftWheel.weight;
		leftWheel.horizontalSpeed+=leftWheel.horizontalAcceleration;

		//обрабатываем изменение горизонтальной координаты
		if(fabs(leftWheel.horizontalSpeed)<0.1)
			leftWheel.horizontalSpeed=0;

		if(notAnyDike)
			rightWheel.horizontalSpeed=leftWheel.horizontalSpeed;
		leftWheel.x+=leftWheel.horizontalSpeed;
		rightWheel.x+=rightWheel.horizontalSpeed;

		/////вертикально
		if((rightWheel.y-rightWheel.r)<=getCurrentY(rightWheel.x))
			reaction.mean=gravity.mean;
		else
			reaction.mean=0;
		reaction.alpha=getCurrentAlpha(rightWheel.x)+0.5*P;

		rightWheel.verticalAcceleration=
			(gravity.mean*sin(gravity.alpha)
			+	reaction.mean*sin(reaction.alpha)
			+	rotate.mean*sin(rotate.alpha))/rightWheel.weight;
		rightWheel.verticalSpeed+=rightWheel.verticalAcceleration;
		///вертикальной координаты
		if((fabs(rightWheel.verticalSpeed)<0.1)||((rightWheel.y-rightWheel.r)<=getCurrentY(rightWheel.x)))
		{
			rightWheel.verticalSpeed=0;
		}
		
		
		if((rightWheel.y-rightWheel.r)<getCurrentY(rightWheel.x))
			rightWheel.y=getCurrentY(rightWheel.x)+rightWheel.r;
		rightWheel.y+=rightWheel.verticalSpeed;


		//спицы
		for(int i=0; i < 10; i++)
			stick[i]-=leftWheel.horizontalSpeed/leftWheel.r;
	}

	void accelerate()
	{
		acceleration.alpha=getCurrentAlpha(rightWheel.x);
		acceleration.mean=powerOfMotor;
	}
	void backWards()
	{
		acceleration.alpha=getCurrentAlpha(rightWheel.x)+P;
		acceleration.mean=1;//скорость шажочков назад, а не мотора
	}
	void restHorizontal()
	{
		acceleration.mean=0;
		acceleration.alpha=0;
		friction.alpha=acceleration.alpha+P/2;
	}
	void restVertical()
	{
		rotate.mean=0;
	}
	void bendBack()
	{
		rotate.mean=agility;
		rotate.alpha=P/2;
	}
	
	double getCurrentAlpha(int&x)
	{
		if(x<=300)
			return 0;
		if((x<=600)&(x>=300))
			return atan(0.2);
		if((x>600)&(x<=gameWidth))
			return atan(-0.2);
	}
	int getCurrentY(int& x)
	{
		if(x<300)
			return 300-leftWheel.r;
		if((x<=600)&(x>=300))
			return 300 +0.2*(x-300)-leftWheel.r;
		if((x>600)&(x<=gameWidth))
			return 360-0.2*(x-600)-leftWheel.r;
	}
};
