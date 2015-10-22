#include "Background.h"
#include "LagranzhMaker.h"
#include "Polynom.h"


Background::Background(HeroPointer hP1) : players(1)
{
	players[0] = hP1;
}

Background::Background(HeroPointer hP1,HeroPointer hP2) : players(2)
{
	players[0] = hP1;
	players[1] = hP2;
}

Background::~Background(void)
{
}

void Background :: draw()
{
	std :: sort(players.begin(),players.end(),Comparator());

	unsigned int size = players.size();
	double dist = players[size-1]->getX() - players[0]->getX() + 2*BASE_SCREEN_DIST;



	glPushMatrix();	
		glScaled(SCREEN_WIDTH/dist,SCREEN_WIDTH/dist,1.0);
		//glScaled(dist/SCREEN_WIDTH,dist/SCREEN_WIDTH,1.0);
		glTranslated(-players[0]->getX() + BASE_SCREEN_DIST,0.0,0.0);
		//glTranslated(players[0]->getX() - BASE_SCREEN_DIST,0.0,0.0);

		glBegin(GL_POLYGON);
			glColor3f(0.0,0.0,0.0);
			glVertex2d(0.0,0.0);
			glVertex2d(0.0,SCREEN_HEIGHT);
			glColor3d(1.0,1.0,1.0);
			glVertex2d(SCREEN_WIDTH,SCREEN_HEIGHT);
			glVertex2d(SCREEN_WIDTH,0.0);
		glEnd();

		for (unsigned int i = 0; i < size; ++i)
			players[i]->draw();

	glPopMatrix();
}

void Background :: newPoint(int x,int y)
{
	xPoints.push_back(x);
	yPoints.push_back(y);
}