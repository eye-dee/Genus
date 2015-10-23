#pragma once

#include <vector>
#include <iostream>
#include <ostream>
#include <iterator>

class Polynom
{
public:
	Polynom(std :: size_t size);
	Polynom(double* mas,int size);
	Polynom(double value);
	Polynom(double value1,double value2);

	Polynom& operator *(const Polynom& lhs) const;
	Polynom& operator +(const Polynom& lhs) const;
	
	inline void print() const
	{
		std :: copy(_k.begin(),_k.end(),std :: ostream_iterator<double>(std :: cout, " "));
	}
	inline void print(std :: ostream& os) const
	{
		std :: copy(_k.begin(),_k.end(),std :: ostream_iterator<double>(os, " "));
		os << "\n";
	}

	inline double& operator [](int i)
	{
		return _k[i];
	}
	inline std :: size_t size() const
	{
		return degree;
	}

	inline double f(double x)
	{
		double sum = _k[0],temp = x;
		for (std :: size_t i = 1; i < _k.size(); ++i)
		{
			sum += temp*_k[i];
			temp *= x;
		}
		return sum;
	}

	inline void nulling()
	{
		for (std :: size_t i = 0; i < degree; ++i)
			_k[i] = 0.0;
	}
private:
	std :: size_t degree;
	std :: vector<double> _k;
};

