#include "CubicSplineRoadMaker.h"

CubicSplineRoadMaker ::	CubicSplineRoadMaker(const double x[2], const double y[2]) : RoadMaker(x,y,DEGREE_CUBIC)
{}

CubicSplineRoadMaker :: CubicSplineRoadMaker(const double *x, const double *y, std :: size_t n) : 
	RoadMaker(x,y,n,DEGREE_CUBIC)
{
	for (unsigned int i = 0; i < _N; ++i)
		_k[i][0] = _f[i];
}

void CubicSplineRoadMaker :: makeSpline()
{
	double *alpha = new double[_N - 1];
	double *beta = new double[_N - 1];
	double A, B, C, F, h_i, h_i1, z;
	alpha[0] = beta[0] = 0.0;
	for (std :: size_t i = 1; i < _N - 1; ++i)
	{
		h_i = _x[i] - _x[i - 1], 
			h_i1 = _x[i + 1] - _x[i];
		A = h_i;
		C = 2.0*(h_i + h_i1);
		B = h_i1;
		F = 6.0*((_f[i + 1] - _f[i]) / h_i1 - (_f[i] - _f[i - 1]) / h_i);
		z = (A*alpha[i - 1] + C);
		alpha[i] = -B/z;
		beta[i] = (F - A * beta[i - 1])/z;
	}

	_k[_N - 1][2] = (F - A*beta[_N - 2])/(C + A*alpha[_N - 2]);

	// Нахождение решения - обратный ход метода прогонки
	for (std::size_t i = _N - 2; i > 0; --i)
		_k[i][2] = alpha[i]*_k[i + 1][2] + beta[i];

	// Освобождение памяти, занимаемой прогоночными коэффициентами
	delete[] beta;
	delete[] alpha;

	for (std::size_t i = _N - 1; i > 0; --i)
	{
		double h_i = _x[i] - _x[i - 1];
		_k[i][3] = (_k[i][2] - _k[i - 1][2])/h_i;
		_k[i][1] = h_i * (2.0*_k[i][2] + _k[i - 1][2])/6.0 + (_f[i] - _f[i - 1])/h_i;
	}

	spline = true;
}
double CubicSplineRoadMaker :: f(double x) const
{
	Polynom temp(DEGREE_CUBIC);
	std::size_t i = 0, j = _N - 1;
	if (x < _x[0]) 
		temp = _k[0];
	else if (x > _x[_N-1])
		temp = _k[_N-1];
	else
	{
		while (i + 1 < j)
		{
			std::size_t k = i + (j - i)/2;
			if (x <= _x[k])
				j = k;
			else
				i = k;
		}
		temp = _k[j];
	}

	double dx = (x - _x[j]);
	return temp[0] + (temp[1] + (temp[2]/2.0 + temp[3]*dx/6.0)*dx)*dx;
}

void CubicSplineRoadMaker :: pushNewPoint(const double x,const double y)
{
	_x.push_back(x);
	_f.push_back(y);

	double * mas1 = new double[4];

	mas1[0] = _f[_N];
	mas1[1] = 0.0;
	mas1[2] = 0.0;
	mas1[3] = 0.0;

	_k.push_back(Polynom(mas1,4));

	++_N;
}