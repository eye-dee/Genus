#include "MagicSquare.h"

#include <fstream>

MagicSquare :: MagicSquare() : size(2*2*2),
	mas(size*size)
{
	std :: size_t s = size/2/2,d1,d2;
	for (std :: size_t i = 0; i < size*size; ++i)
		mas[i] = i + 1;
	for (std :: size_t i = 0; i < s; ++i)
	{
		for (std :: size_t j = 0; j < s/2; ++j)
			for (std :: size_t p = 0; p < 4; ++p)
			{
				d1 = (4*i+p)*size + 4*j + p;
				d2 = (4*i + 3 - p)*size + 4*j + p;
				std :: swap(mas[d1],mas[size*size - 1 - d1]);
				std :: swap(mas[d2],mas[size*size - 1 - d2]);
			}
		if (s%2 == 1)
		{
			for (std :: size_t j = s/2; j < s/2 + 1; ++j)
			for (std :: size_t p = 0; p < 2; ++p)
			{
				d1 = (4*i+p)*size + 4*j + p;
				d2 = (4*i + 3 - p)*size + 4*j + p;
				std :: swap(mas[d1],mas[size*size - 1 - d1]);
				std :: swap(mas[d2],mas[size*size - 1 - d2]);
			}
		}
	}
}


MagicSquare :: ~MagicSquare(void)
{
}

bool MagicSquare :: check() const
{
	int sum(0),sum1(0),sum2(0);
	for (std :: size_t i = 0; i < size; ++i)
		sum += mas[i];
	for (std :: size_t i = 0; i < size; ++i)
	{
		sum1 = 0;
		sum2 = 0; 
		for (std :: size_t j = 0; j < size; ++j)
		{
			sum1 += mas[i+j*size];
			sum2 += mas[i*size + j];
		}
		if ((sum != sum1) || (sum != sum2))
			return false;
	}

	sum1 = 0;
	sum2 = 0;
	for (std :: size_t i = 0; i < size; ++i)
	{
		sum1 += mas[i + i*size];
		sum2 += mas[i + (size-i-1)*size];
	}
	if ((sum != sum1) || (sum != sum2))
			return false;
	return true;
}

void MagicSquare :: makeNewSqaure()
{
	size = 2*2*random(20);
	std :: size_t s = size/2/2,d;
	for (std :: size_t i = 0; i < s; ++i)
		for (std :: size_t j = 0; j < s; ++j)
			for (std :: size_t p = 0; p < 4; ++p)
			{
				d = 4*i*size + 4*j + p;
				std :: swap(mas[d],mas[size*size - 1 - d]);
			}
}

void MagicSquare :: readFromFile()
{
	std :: ifstream in(MagicKey);

	in >> size;
	mas.assign(size*size,0);

	for (std :: size_t i = 0; i < size*size; ++i)
		in >> mas[i];

	in.close();
}
void MagicSquare :: loadToFile() const
{
	std :: ofstream ou(MagicKey);

	ou << size << ' ';

	for (std :: size_t i = 0; i < size*size; ++i)
		ou << mas[i] << ' ';

	ou.close();
}