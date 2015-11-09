#include <GL\GLAux.h>
#include <fstream>

#include "wheel.h"
#include "const.h"
#include"CanonicalRoadMaker.h"

bool KeyDown[256];
RoadMakerPointer road = RoadMakerPointer(new CanonicalRoadMaker(50.0,50.0));
std :: shared_ptr<Wheel> w;

double* X = new double[640];
double* Y = new double[640];
int N = 0;
int flag = -1;

void Init(void)
{
	glClearColor(0.0,1.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,640,0.0,480,-1.0,1.0);
};



void make(int x,int y)
{
	y = 480 - y;
	if (flag == 0)
	{
		if (N == 0) 
		{
			X[N] = x;
			Y[N++] = y;
		} else if ((abs(X[N-1] - x) >= 1))
		{
			X[N] = x;
			Y[N++] = y;
		}
	}
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
				road = CanonicalRoadMakerPointer(new CanonicalRoadMaker(X,Y,N));
				road->makeSpline();
				w = std :: shared_ptr<Wheel>(new Wheel(X[0],Y[0] + 10.0)); 
				w->setBack(road);
			}
		}
	}
}
void keyPress() 
{
	if(KeyDown['d']) int i=1;
	if(KeyDown['a']) w->bendBack(); 
	if(KeyDown['w']) w->accelerate(); 
	if(KeyDown['e']) int i=1; 
	/*if(KeyDown['s']==1) w->backWards(); 
	if(!((KeyDown['a']==1)||(KeyDown['d']==1)))
		w->restVertical();*/	
	if (flag == 1)
		w->calculate();
}

void pole()
{
	keyPress();
	glClear(GL_COLOR_BUFFER_BIT);

	if (flag == 1)
	{
		glColor3d(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			for (double t = 0.0; t < 640.0; t += 0.1)
				glVertex2d(t,road->f(t));
		glEnd();
		glColor3d(0.5,0.5,0.5);
		
		w->draw();
	}

	glColor3d(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i < N; ++i)
			glVertex2d(X[i],Y[i]);
	glEnd();

	
	glutSwapBuffers();
};


void key(unsigned char key, int x, int y)
{
	KeyDown[key] = 1;
	pole();
}

void keyUp(unsigned char key, int x, int y)
{
	if ( key == 'w')
		w->unAccelerate();
	KeyDown[key] = 0;
}


int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,200);
	glutCreateWindow("Genus");
	Init();
	glutDisplayFunc(pole);
	glutMotionFunc(make);
	glutMouseFunc(control);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	keyPress();
	glutIdleFunc(pole);
	glutMainLoop();								
	return 0;
}