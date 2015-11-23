#include "Crystal.h"


void Crystal::print()
	{
		int n=10;
		switch(type)
		{
		case 1:
			{
				MyColor a(255,0,0);
				glColor(a);
				glBegin(GL_QUADS);
				glVertex2i(x-n,y-n);
				glVertex2i(x+n,y-n);
				glVertex2i(x+n,y+n);
				glVertex2i(x-n,y+n);
				glEnd();
				break;
			}
		case 2:
			{
				MyColor a(0,255,0);
				glColor(a);
				glBegin(GL_QUADS);
				glVertex2i(x-n,y-n);
				glVertex2i(x+n,y-n);
				glVertex2i(x+n,y+n);
				glVertex2i(x-n,y+n);
				glEnd();
				break;
			}
		case 3:
			{
				MyColor a(0,0,255);
				glColor(a);
				glBegin(GL_QUADS);
				glVertex2i(x-n,y-n);
				glVertex2i(x+n,y-n);
				glVertex2i(x+n,y+n);
				glVertex2i(x-n,y+n);
				glEnd();
				break;
			}
		}
	}
int Crystal::getX()
	{
		return x;
	}
int Crystal::getY()
	{
		return y;
	}