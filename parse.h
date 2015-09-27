#ifndef PARSE_H
#define PARSE_H
#include "tree.hpp"
#include "tree_field.h"
#include "note.h"
//вводимая строка может быть всегда представленна как сумма и разность дробей,
//каждая дробь - как числитель-произведение и знаменатель выражение числа,
// каждое произведение - как произведение выражений чисел,
// а каждое выражение либо есть число, либо сумма или дробь или произведение в скобках
// приведенные ниже функции строят синтаксический разбор соответствующей их названию сущности

enum config { write, write_not_null};


void build_summ(tree_runner<field, note> & summ_tree, char & oper);
void build_fract(tree_runner<field, note> & fract_tree, char & oper);
void build_mult(tree_runner<field, note> & mult_tree, char & oper);
void build_num(tree_runner<field, note> & mult_tree, char & oper, config);

#endif

