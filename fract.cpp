#include "fract.h"
#include <iostream>
#include "conio.h"
using namespace std;


fraction::fraction()
{};


fraction::fraction(int x): u(x), d(1)
{};


fraction::fraction(int a, int b) : u(a), d(b)
{};

 fraction fraction::uni(fraction a)
{
	if (a.u != 0)
	{
		int v = unif(a.u, a.d);
		a.u = a.u / v;
		a.d = a.d / v;
		return a;
	}
	else
		return fraction(0, 1);
 };

 fraction operator + (fraction f, fraction g)
 {
	 fraction temp;
	 temp.u = f.u*g.d + f.d*g.u;
	 temp.d = f.d*g.d;
	 return fraction::uni(temp);
 };


 fraction operator - (fraction f,fraction g)
 {
	 fraction temp;
	 temp.u = f.u*g.d - f.d*g.u;
	 temp.d = f.d*g.d;
	 return fraction::uni(temp);
 };


 fraction operator * (fraction f,fraction g)
 {
	 fraction temp;
	 temp.u = f.u*g.u;
	 temp.d = f.d*g.d;
	 return fraction::uni(temp);
 };

 fraction operator / (fraction f, fraction g)
 {
	 if (g.u != 0)
	 {
		 fraction temp;
		 temp.u = f.u*g.d;
		 temp.d = f.d*g.u;

		 if (temp.d < 0)
		 {
			 temp.u *= -1;
			 temp.d *= -1;
		 }

		 return fraction::uni(temp);
	 }
	 else
	 {
		 cout << "divisor is null"<<endl
			 <<"press any key";
		 _getch();
	 }
 };

 fraction fraction::operator += (fraction g)
 {
	 *(this) = *(this) + g;
	 return *(this);
 };

 fraction fraction::operator -= (fraction g)
 {
	 *(this) = *(this) - g;
	 return *(this);
 };

 fraction fraction::operator *= (fraction g)
 {
	 *(this) = *(this) * g;
	 return *(this);
 };
 fraction fraction::operator /= (fraction g)
 {
	 *(this) = *(this) / g;
	 return *(this);
 };


 bool fraction::operator == (fraction g)
 {
	 if ((u == g.u) && (d == g.d))
		 return true;
	 else
		 return false;
 }

 void fraction::show_fract()
 {
	 cout << u << '/' << d << endl;
 };



 int unif(int a, int b)
 {
	 a = abs(a);
	 b = abs(b);
	 int temp;
	 if (a < b)
	 {
		 temp = a;
		 a = b;
		 b = temp;
	 }
	 temp = a%b;
	 if (temp == 0)
		 return b;
	 else
	 return unif(b, temp);
 };