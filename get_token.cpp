#include "get_token.h"
#include "filter.h"
#include <iostream>
using namespace std;

void get_token(int& number, char& oper)
{
	int state_number;
	char temp;
	const char backspase = 8;

	switch (oper)
	{
	case 0:// принять число
		state_number = 0;
		number = 0;
		break;
	case 1:// доопределить число
		if(number>0)
		state_number = 1;
		else
		{
			temp = filter("+-*/=)");
			if(temp== backspase)
			{
				cout << backspase <<" "<< backspase;
				state_number = 0;
			}
			else
			{
				number = 0;
				oper = temp;
				return;
			}
		}
		break;

	default:
		cout << "wrog oper in get_token:"<<oper<<endl;
		break;
	}

	while (true)// реализация конечного автомата с двумя состояниями
	{
		switch (state_number)
		{
		case 0:
			temp = filter("-0123456789(");
			if (('0' < temp)&&(temp <= '9'))
			{
				cout << temp;
				number = temp - '0';
				state_number = 1;
			}
			else
			{
				oper = temp;
				number = -1;
				return;
			}
			break;
		case 1:
			temp = filter("0123456789+-*/=)");
			if(('0'<=temp)&&(temp<='9'))
			{
				cout << temp;
				number = 10 * number + (temp - '0');
				state_number = 1;
			}
			else if (temp == backspase)// пользователь стер последний символ
			{
				number = static_cast<int>(number / 10);
				cout << backspase<< " "<< backspase;
				if (number == 0)
					state_number = 0;
				else
					state_number = 1;
			}
			else// пользователь ввел оператор, ) или =
			{
				oper = temp;
				return;
			}


		default:
			break;
		}
	
	}


}


void get_oper(char& oper)
{
	oper = filter("+-*/=)");
}







