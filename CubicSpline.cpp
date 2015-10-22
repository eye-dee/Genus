#include "CubicSpline.h"

CubicSpline :: CubicSpline(const double *x, const double *y, std :: size_t n) : _x(x,x+n),
	_f(y,y+n),
	_k(n),
	_N(n),
	spline(false)
{
	for (unsigned int i = 0; i < _N; ++i)
		_k[i].a = _f[i];
}

void CubicSpline :: makeSpline()
{
	double *alpha = new double[_N - 1];
	double *beta = new double[_N - 1];
	double A, B, C, F, h_i, h_i1, z;
	alpha[0] = beta[0] = 0.0;
	for (std::size_t i = 1; i < _N - 1; ++i)
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

	_k[_N - 1].c = (F - A*beta[_N - 2])/(C + A*alpha[_N - 2]);

	// Нахождение решения - обратный ход метода прогонки
	for (std::size_t i = _N - 2; i > 0; --i)
		_k[i].c = alpha[i]*_k[i + 1].c + beta[i];

	// Освобождение памяти, занимаемой прогоночными коэффициентами
	delete[] beta;
	delete[] alpha;

	for (std::size_t i = _N - 1; i > 0; --i)
	{
		double h_i = _x[i] - _x[i - 1];
		_k[i].d = (_k[i].c - _k[i - 1].c)/h_i;
		_k[i].b = h_i * (2.0*_k[i].c + _k[i - 1].c)/6.0 + (_f[i] - _f[i - 1])/h_i;
	}
}
double CubicSpline :: f(double x)
{
	polynomK temp;
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
	return temp.a + (temp.b + (temp.c/2.0 + temp.d*dx/6.0)*dx)*dx;
}