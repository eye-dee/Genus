#pragma once

#include <vector>
#include <string>

#include "MagicSquare.h"

const int BITS_IN_INT = 8*sizeof(int);

inline char* intToBit(int a)
{
	char* temp = new char[32];
	for (int i = 31; i >= 0; --i)
	{
		temp[i] = a%2;
		a = a >> 1;
	}
	return temp;
}

inline int bitToInt(char* a)
{
	int sum(0);
	int x = 1;
	for (int i = 31; i >= 0; --i)
	{
		sum += (int)a[i]*x;
		x = x << 1;
	}
	return sum;
}

class Cipher
{
public:
	Cipher();
	~Cipher();

	void readFromFile(std :: string inp);
	void readFromMain(int* mas,int s);
	void readFromMain(std :: vector<int> mas);
	void loadToFile(std :: string out);

	inline bool check(int mas[])
	{
		for (std :: size_t i = 0; i < inf.size(); ++i)
			if (mas[i] != inf[i])
				return false;
		return true;
	}

	inline void readKeyFromFile()
	{
		mS.readFromFile();
	}

	inline void loadKeyToFile() const
	{
		mS.loadToFile();
	}

	inline int operator [](int index) const
	{
		return inf[index];
	}

	inline std :: size_t size() const
	{
		return inf.size();
	}

private:
	std :: vector<int> inf;
	MagicSquare mS;
};

