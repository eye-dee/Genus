#include "Cipher.h"

#include <fstream>


Cipher :: Cipher()
{
}


Cipher :: ~Cipher()
{
}

void Cipher :: readFromFile(std :: string inp)
{
	std :: ifstream in(inp);

	std :: size_t countOfbits = 0;
	std :: size_t s = mS.getSize();
	in >> countOfbits;

	char* source = new char[countOfbits];
	char* res = new char[countOfbits];
	char* t = res;
	inf.assign(countOfbits/BITS_IN_INT,0);

	int i = 0;

	in.get(source[0]);

	while( in.get(source[i++]));

	/*for(;in.get(source[i++]);)
		if (i % 32 == 0)
			in.get(source[i++]);*/

	/*for (int i = 0; i < countOfbits; ++i)
		std :: cout << (int)source[i] << ' ';*/

	for (int p = 0; p < countOfbits/(s*s); ++p)
	{
		for (int i = 0; i < s*s; ++i)
		{
				res[p*s*s + mS[i] - 1] = source[p*s*s + i];
		}
	}

	int temp;
	for (i = 0; i < countOfbits/BITS_IN_INT; ++i)
	{
		temp = bitToInt(res);
		inf[i] = temp;
		res += 32;
	}

	in.close();

	delete[] source;
	delete[] t;
}
void Cipher :: readFromMain(int* mas,int s)
{
	inf.assign(s,0);
	for (std :: size_t i = 0; i < s; ++i)
		inf[i] = mas[i];
}
void Cipher :: readFromMain(std :: vector<int> mas)
{
	inf.assign(mas.size(),0);
	inf = mas;
	for (std :: size_t i = 0; i < inf.size(); ++i)
		inf[i] = mas[i];
}
void Cipher :: loadToFile(std :: string out)
{
	std :: size_t s = mS.getSize();
	std :: size_t countOfbits = BITS_IN_INT*inf.size();
	char* source = new char[countOfbits];
	char* temp = new char[BITS_IN_INT];

	for (int p = 0; p < countOfbits/(s*s); ++p)
	{
		for (int i = 0; i < s*s/BITS_IN_INT; ++i)
		{
			temp = intToBit(inf[p*s*s/BITS_IN_INT + i]);
			for (int j = 0; j < BITS_IN_INT; ++j)
				source[p*s*s + i*BITS_IN_INT + j] = temp[j];
		}
	}

	/*for (int i = 0; i < countOfbits; ++i)
		std :: cout << (int)source[i] << ' ';
		*/
	std :: ofstream ou(out);


		ou << countOfbits << '\n';

		for (int p = 0; p < countOfbits/(s*s); ++p)
		{
			for (int i = 0; i < s*s; ++i)
				ou << source[p*s*s + mS[i] - 1];
		}
		/*for (int i = 0; i < countOfbits; ++i)
			ou << source[i];
			*/
	ou.close();

	delete source;

	loadKeyToFile();
}