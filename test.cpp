#include "hero.h"
#include "defs.h"
#include <GL\GLAux.h>
#include <fstream>

bool KeyDown[256];
hero myFirstHero; 

void Initialize()
{
	int step=20;
	glClearColor(1.0,1.0,0.5,5.0);		
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();					
	gluOrtho2D(0.0,gameWidth,0.0,gameHeight);
}

void printBackGround()
{
	glColor3f(0,0,0);
		glBegin(GL_POINTS);
		for(int i=0; i<300; i++)
			glVertex2d(i, 300-myFirstHero.leftWheel.r);
		for(int i=300; i<600; i++)
			glVertex2d(i, 300 +0.2*(i-300)-myFirstHero.leftWheel.r);
		for(int i=600; i<gameWidth; i++)
			glVertex2d(i, 360-0.2*(i-600)-myFirstHero.leftWheel.r);
		glEnd();
}

void keyPress() 
{
	if(KeyDown['d']==1) int i=1;
	if(KeyDown['a']==1) myFirstHero.bendBack(); 
	if(KeyDown['w']==1) myFirstHero.accelerate(); 
	if(KeyDown['e']==1) int i=1; 
	if(KeyDown['s']==1) myFirstHero.backWards(); 
	if(!((KeyDown['w']==1)||(KeyDown['s']==1)))
		myFirstHero.restHorizontal();
	if(!((KeyDown['a']==1)||(KeyDown['d']==1)))
		myFirstHero.restVertical();
	myFirstHero.recompute();
	if(KeyDown['r']==1) myFirstHero.reboot(); 
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	keyPress();
	myFirstHero.print();
	printBackGround();
	glutSwapBuffers();
	Sleep(20);
}


void key(unsigned char key, int x, int y)
{
	KeyDown[key] = 1;
	draw();
}



void keyUp(unsigned char key, int x, int y)
{
	KeyDown[key] = 0;
}


int main(int argc, char **argv)
{
	glutInit(&argc,argv);						
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);  
	glutInitWindowSize(gameWidth,gameHeight);				
	glutInitWindowPosition(100,0);			
	glutCreateWindow("Genus");				
	Initialize();	
	glutDisplayFunc(draw);			
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	keyPress();
	glutIdleFunc(draw);
	glutMainLoop();								
	return 0;
}

