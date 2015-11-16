#include "Power.h"


Power :: Power() : projectionX(0.0),
	projectionY(0.0),
	value(0.0)
{
}

Power :: Power(double p, double al) : projectionX(p*cos(al)),
	projectionY(p*sin(al)),
	value(p)
{
}
