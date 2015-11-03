#include<iostream>
#include<fstream>

#include "Cipher.h"
#include "MagicSquare.h"

const std :: string output = "out.txt";

const int MAS_SIZE = 8;

int main()
{	
	Cipher c;
	int* mas = new int[MAS_SIZE];
	for (int i = 0; i < MAS_SIZE; ++i)
		mas[i] = random(486465);

	/*std :: ofstream ou(output);

	char* temp = intToBit(3001);
	for (int i = 0; i < 32; ++i)
		ou << temp[i];

	char* temp = intToBit(31);
	for (int i = 0; i < 32; ++i)
		ou << temp[i]; 

	ou.close();*/

	c.readFromMain(mas,MAS_SIZE);

	c.loadToFile(output);

	c.readFromFile(output);

	std :: cout << c.check(mas);

	system("pause >> null");
	return 0;
}

int main1()
{
	char* temp = intToBit(3001);
	
	std :: ofstream ou(output);
		for (int i = 0; i < 32; ++i)
			ou << temp[i];
	ou.close();

	std :: ifstream in(output);

	int i = 0;
	temp = new char[32];

	while( in.get(temp[i++]));

	std :: cout << bitToInt(temp);

	system("pause >> null");
	return 0;
}