#include "filter.h"
#include <iostream>
#include "conio.h"
using namespace std;

char filter(char* s)
{
	int k=0;
	bool trig = false;
	char temp;
	const char backspase = 8;
	while (true)
	{
		temp = _getch();
		while (*(s + k) != 0)
		{
			if (*(s + k) == temp)
				trig = true;
			k++;
		}
		k = 0;
		if (temp == backspase)
			trig = true;
		if (trig)
			return temp;
		else
		{
			temp = 7;
				cout << temp;
		}
			
	}
};
