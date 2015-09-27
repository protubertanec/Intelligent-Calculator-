#ifndef NOTE_H
#define NOTE_H
#include "fract.h"

class note
{
public:
	bool to_calculate;
	bool first_token;
	bool bracket_factor;
	fraction intermediate_result;
public:
	note();
	~note();
};


#endif