#ifndef TREE_FIELD_H
#define TREE_FIELD_H
#include "fract.h"

class field
{
public:
	char oper;
	bool uno;
	int length;
	int  number;
	fraction intermediate_result;
	bool first_token;
public:
	field();
	~field();
};

#endif
