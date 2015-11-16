 #ifndef CONST_H
 #define CONST_H

	#include<iostream>

	const double STANDART_WHEEL_RAD = 30.0;

	const double PI = 3.1415926535897932384626433832795;
	
	const double EPSILON = 0.0001;
	const double WHEEL_FORCE = 100.0;

	const double GAME_WIDTH = 640.0;
	const double GAME_HEIGHT = 480.0;

	const double G = 9.8;
	const double AIR_RESISTANCE = 0.4;
	const double K_FRICTOIN = 0.011;

	const int NUMBER_OF_STICK = 10;

	const double MIN_SPEED = 0.00001;

	class RoadMaker;
	class CubicSplineRoadMaker;
	class LagranzhRoadMaker;
	class CanonicalRoadMaker;

	typedef std :: shared_ptr<RoadMaker> RoadMakerPointer;
	typedef std :: shared_ptr<CubicSplineRoadMaker> CubicSplineRoadMakerPointer;
	typedef std :: shared_ptr<LagranzhRoadMaker> LagranzhRoadMakerPointer;
	typedef std :: shared_ptr<CanonicalRoadMaker> CanonicalRoadMakerPointer;

#endif