#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>

#include "Hero.h"
#include "defs.h"

class LagranzhMaker;
class Polynom;


class Background
{
public:
	Background(HeroPointer hP1);
	Background(HeroPointer hP1,HeroPointer hP2);
	~Background();

	virtual void draw();

	void newPoint(int x,int y);

private:
	std :: vector<std::shared_ptr<Hero>> players;
	std :: vector<int> xPoints;
	std :: vector<int> yPoints;
};

