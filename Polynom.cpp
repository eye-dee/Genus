#include "Polynom.h"

Polynom :: Polynom(std :: size_t size) : degree(size),
	_k(size,0.0)
{}
Polynom :: Polynom(double* mas,int size) : degree(size),
	_k(mas,mas + size)
{}
Polynom :: Polynom(double value1,double value2) : degree(2)
{
	_k.push_back(value1);
	_k.push_back(value2);
}
Polynom :: Polynom(double value) : degree(1)
{
	_k.push_back(value);
}

Polynom& Polynom :: operator *(const Polynom& lhs) const
{
	std :: size_t i = degree + lhs.degree - 1, size = degree;
	//std :: size_t i = _k.size() + lhs._k.size() - 1, size = _k.size();
	Polynom* temp = new Polynom(i);

	for (i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < lhs._k.size(); ++j)
		{
			temp->_k[i+j] += _k[i]*lhs._k[j];
		}
	}
	return *temp;
}
Polynom& Polynom :: operator +(const Polynom& lhs) const
{
	if (_k.size() < lhs._k.size())
		return lhs + *this;
	Polynom* temp = new Polynom(*this);
	for (std :: size_t j = 0; j < lhs._k.size(); ++j)
	{
		temp->_k[j] += lhs._k[j];
	}
	return *temp;
}
