#ifndef FRACT_H
#define FRACT_H


class fraction
{
private:
	int u;
	int d;
public:
	fraction();
	fraction(int a, int b);
	fraction(int x);
	static fraction uni( fraction a);
	friend fraction operator + (fraction f, fraction g);
	friend fraction operator - (fraction f, fraction g);
	friend fraction operator * (fraction f, fraction g);
	friend fraction operator / (fraction f, fraction g);
	fraction operator += (fraction g);
	fraction operator -= (fraction g);
	fraction operator *= (fraction g);
	fraction operator /= (fraction g);
	bool operator == (fraction g);
	void show_fract();
};

int unif(int a, int b);

#endif