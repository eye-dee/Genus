#pragma once
#include <iostream>
#include<windows.h>
#include<vector>

const std :: string MagicKey = "MagicSquareKey.txt";

inline int random(int a)
{
	return rand()%a;
}

class MagicSquare
{
public:
	MagicSquare();
	~MagicSquare();

	bool check() const;

	void makeNewSqaure();

	void readFromFile();
	void loadToFile() const;

	inline std :: size_t getSize() const
	{
		return size;
	}

	inline const int operator [] (int i)
	{
		return mas[i];
	}
private:
	std :: size_t size;
	std :: vector<int> mas;
};

