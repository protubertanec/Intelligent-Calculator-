#include "tree_field.h"
#include "fract.h"

field::field():oper(0), uno(true), length(0), number(0), intermediate_result(0), first_token(false)
{};

field::~field()
{};