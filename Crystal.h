#pragma once
#include "stdafx.h"
#include "MyColor.h"
#include <iostream>

class Crystal
{
public:
	Crystal() {};
	Crystal(int a, int b):type(rand()%3+1), x(a), y(b) {};
	~Crystal() {};
	void print();
	int getX();
	int getY();
private:
	int x,y,type;

};

