/*#include<iostream>
#include<fstream>

#include "Cipher.h"
#include "MagicSquare.h"

const std :: string output = "out.txt";

const int MAS_SIZE = 1024;
const double PI = 3.1415926535897932384626433832795; 

int f(int x)
{
	if ((x > 0) && (x < 100*PI/5))
		return (int)50*sin(5.0*x);
	else if (x < 120*PI)
		return (int)(0.01*(x - 20*PI)*(x - 120*PI) + 10);
	else if (x < 500)
		return (int)(2*x - 744);
	else 
		return (int)(-2*x + 1256);
}

int f1(int x)
{
	if ((x > 0) && (x < 200))
		return 200;
	else if (x < 600)
		return (int)(0.8*x + 40);
	else if (x < 800)
		return (int)(-1.8*x + 1600);
	else
		return 160;
}

int main()
{	
	Cipher c;

	int* mas = new int[MAS_SIZE];
	for (int i = 0; i < MAS_SIZE; ++i)
		mas[i] = abs(f1(i));

	c.readFromMain(mas,MAS_SIZE);

	c.loadToFile(output);

	c.readFromFile(output);

	std :: cout << c.check(mas);

	system("pause >> null");
	return 0;
}/**/

#include<iostream>
#include<fstream>
#include <windows.h>
#include <time.h>
#include <memory>
#include <glut.h>

#include "Cipher.h"
#include "MagicSquare.h"

#include "Wheel.h"

#include "LagranzhRoadMaker.h"
#include "CubicSplineRoadMaker.h"
#include "CanonicalRoadMaker.h"

#include "const.h"

double* X = new double[1024];
double* Y = new double[1024];
int N = 0;
int flag = -1;

bool KeyDown[256];

const std :: string output = "out.txt";
RoadMakerPointer cS;
std :: shared_ptr<Wheel> w;

const int MAS_SIZE = 1024;

void Init(void)
{
	glClearColor(1.0,0.5,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1024,0.0,900,-1.0,1.0);

	Cipher c;

	c.readFromFile(output);

	N = c.size();
	for (std :: size_t i = 0; i < N; ++i)
	{
		X[i] = i;
		Y[i] = c[i];
	}
};

void keyPress() 
{
	if (flag == 1)
	{
		if(KeyDown['d']) int i=1;
		if(KeyDown['a']) w->bendBack(); 
		if(KeyDown['w']) w->accelerate(); 
		if(KeyDown['e']) int i=1; 	
		if (flag == 1)
			w->calculate();
	}
}

void pole()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (flag == 1)
	{
		keyPress();
		if (!KeyDown['w'])
			w->unAccelerate();
		glClear(GL_COLOR_BUFFER_BIT);

			glColor3d(0.2,0.2,0.2);
			glBegin(GL_LINE_STRIP);
				for (double t = 0.0; t < 1024.0; t += 1.0)
					glVertex2d(t,cS->f(t));
			glEnd();
			glColor3d(0.5,0.5,0.5);
			//cS->fastDraw();
			w->draw();
	}

	glutSwapBuffers();
	//Sleep(500);
};

void make(int x,int y)
{
	y = 480 - y;
}

void control(int button, int state,
                                int x, int y)
{
	if (flag <= 0)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN)
				flag = 0;
			else
			{
				flag = 1;
				cS = CanonicalRoadMakerPointer(new CanonicalRoadMaker(X,Y,N));
				cS->makeSpline();
				w = std :: shared_ptr<Wheel>(new Wheel(20,300));
				w->setBack(cS);
				w->setFly();
			}
		}
	}
}

void key(unsigned char key, int x, int y)
{
	KeyDown[key] = 1;
	pole();
}

void keyUp(unsigned char key, int x, int y)
{
	if (flag == 1)
	{
		if ( key == 'w')
			w->unAccelerate();
		KeyDown[key] = 0;
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024,640);
	glutInitWindowPosition(30,30);
	glutCreateWindow("CanonicalRoadMaker");
	Init();
	glutDisplayFunc(pole);
	glutMotionFunc(make);
	glutMouseFunc(control);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(pole);
	glutMainLoop();
	return 0;
};/**/