#ifndef VOCABULARY_H
#define VOCABULARY_H
#include "tree.hpp"
#include "tree_field.h"
#include "note.h"

const char backspace = 8;

void erase(int k);

void to_bell();

int num_length(int k);



char & ooperator_under(tree_runner<field, note> & runner);


bool & ooperator_is_unary_under(tree_runner<field, note> & runner);


int & length_of_operator_under(tree_runner<field, note> & runner);


fraction & intermediate_result_under(tree_runner<field, note> & runner);


void redetermin_intermediate_result_under(tree_runner<field, note> & runner);


void calculate_intermediate_result_under(tree_runner<field, note> & runner);


void rightmost_node_is_next_position_of(tree_runner<field, note> & right_limit);


void move_down_to_the_first_valid_operator(tree_runner<field, note> & runner);


void print_node(tree_runner<field, note> & runner);


void erase_up_to(tree_runner<field, note> & left_limit);


void print_tree_from(tree_runner<field, note> & left_limit);




#endif
