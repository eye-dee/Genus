#include <windows.h>
#include <time.h>
#include <iostream>
#include <glut.h>
#include <memory>

#include "Hero.h"
#include "Background.h"

HeroPointer a(new Hero(200.0));
HeroPointer b(new Hero(300.0));
std :: auto_ptr<Background> back(new Background(a,b));

int KeyDown[256];

void Init(void)
{
	glClearColor(0.0,1.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,SCREEN_WIDTH,0.0,SCREEN_HEIGHT,-1.0,1.0);
};

void keyPress() 
{
	if (KeyDown['w'] == 1)
		a->accelerate();
	if (KeyDown['s'] == 1)
		a->brake();
	if (KeyDown['d'] == 1)
		a->bendForward();
	if (KeyDown['a'] == 1)
		a->bendBack();
}

void key(unsigned char key, int x, int y){
	KeyDown[key] = 1;
}
void keyUp(unsigned char key, int x, int y){
	KeyDown[key] = 0;
	if (key == 'w')
		a->unAccelerate();
	else if (key == 's') 
		a->unBrake();
}



void pole()
{
	glClear(GL_COLOR_BUFFER_BIT);
	keyPress();

	back->draw();

	glutSwapBuffers();

	//Sleep(500);
};


int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,200);
	glutCreateWindow("Hero");
	Init();
	glutDisplayFunc(pole);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(pole);
	glutMainLoop();
	return 0;
};