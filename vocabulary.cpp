#include "vocabulary.h"

using namespace std;

void erase(int k)
{
	for (int i = 0; i < k; i++)
		cout << '\b' << " " << '\b';
	return;
};

void to_bell()
{
	char temp = 7;
	cout << temp;
	return;
};

int num_length(int k)
{
	int length = 0;

	if (k == 0)
		return 1;
	else
	{
		while (k>0)
		{
			length++;
			k = static_cast<int>(k / 10);
		}
		return length;
	}
};


char & ooperator_under(tree_runner<field, note> & runner)
{
	return (runner.access_field()->oper);
};


bool & ooperator_is_unary_under(tree_runner<field, note> & runner)
{
	return (runner.access_field()->uno);
};


int & length_of_operator_under(tree_runner<field, note> & runner)
{
	return (runner.access_field()->length);
};


fraction & intermediate_result_under(tree_runner<field, note> & runner)
{
	return (runner.access_field()->intermediate_result);
};


void redetermin_intermediate_result_under(tree_runner<field, note> & runner)
{
	int first_case;
	if ((ooperator_under(runner) == '+') || (ooperator_under(runner) == '-')
		|| (ooperator_under(runner) == '(') || (ooperator_under(runner) == ')'))

		first_case = 0;
	else
		first_case = 1;

	runner.go_to_left_child();
	if (!runner.is_abstract())
		runner.note.intermediate_result = intermediate_result_under(runner);
	else
		runner.note.intermediate_result = first_case;

	runner.go_to_parent();
	intermediate_result_under(runner) = runner.note.intermediate_result;

	return;

};


void calculate_intermediate_result_under(tree_runner<field, note> & runner)
{
	runner.go_to_right_child();
	runner.note.intermediate_result = intermediate_result_under(runner);
	runner.go_to_parent();
	if(ooperator_under(runner)=='+')
		intermediate_result_under(runner) += runner.note.intermediate_result;
	else if(ooperator_under(runner) == '-')
		intermediate_result_under(runner) -= runner.note.intermediate_result;
	else if (ooperator_under(runner) == '*')
		intermediate_result_under(runner) *= runner.note.intermediate_result;
	else if (ooperator_under(runner) == '/')
		intermediate_result_under(runner) /= runner.note.intermediate_result;
	else if (ooperator_under(runner) == '(')
		intermediate_result_under(runner) = runner.note.intermediate_result;
	else
		cout << "error: calculate_intermediate_result_under";
};


void rightmost_node_is_next_position_of(tree_runner<field, note> & right_limit)
{

	while (right_limit.go_to_parent());

	right_limit.go_to_left_child();

	while (right_limit.go_to_right_child())
		;
	right_limit.go_to_parent();

	return;
};


void move_down_to_the_first_valid_operator(tree_runner<field, note> & runner)
{
	char temp;
	do
	{
		if (length_of_operator_under(runner) == 0)
		{
			temp = runner.access_field()->oper;
			switch (temp)
			{
			case '(':
				return;
			case '+':
				runner.go_to_right_child();
				break;
			case '/':
				runner.go_to_left_child();
				break;
			case '*':
				runner.go_to_right_child();
				break;
			default:
				cout << "error: move_down_to_the_first_valid_operator";
				break;
			}
		}
		else
			return;
	} while (true);

	return;
};


void print_node(tree_runner<field, note> & runner)
{
	if (ooperator_under(runner) == 0)
		cout << runner.access_field()->number;
	else if (length_of_operator_under(runner)!= 0)
			cout << ooperator_under(runner);
	return;
};



void erase_from_right_limit_up_to_left_limit(tree_runner<field, note> & left_limit, tree_runner<field, note> & right_limit)
{
	erase(length_of_operator_under(right_limit));

	if (right_limit.access_field() == left_limit.access_field())
		return;
	// а теперь найдем узел, отвечающий соседнему слева токену

	right_limit.go_to_left_child();
	if (!right_limit.is_abstract())
	{
		while (right_limit.go_to_right_child())
			;
		right_limit.go_to_parent();

		erase_from_right_limit_up_to_left_limit(left_limit, right_limit);
		return;
	}

	else
	{
		while (right_limit.is_left_child())
			right_limit.go_to_parent();

		right_limit.go_to_parent();

		erase_from_right_limit_up_to_left_limit(left_limit, right_limit);
		return;
	}
};


void erase_up_to(tree_runner<field, note> & left_limit)
{
	tree_runner<field, note> right_limit;
	right_limit = left_limit.reduplicate_tree_runner();
	rightmost_node_is_next_position_of(right_limit);
	erase_from_right_limit_up_to_left_limit(left_limit, right_limit);
};


void print_tree_from(tree_runner<field, note> & left_limit)
{
	tree_runner<field, note> printer;
	printer = left_limit.reduplicate_tree_runner();

	print_node(printer);

	printer.go_to_right_child();
	if (printer.is_abstract())
	{
		do
		{
			printer.go_to_parent();
			if (printer.is_abstract())
				return;
		} while (!printer.is_left_child());

		printer.go_to_parent();

		if (!printer.is_abstract())		
			print_tree_from(printer);
		
		return;
	}

	else
	{
		while (printer.go_to_left_child())
			;
		printer.go_to_parent();

		print_tree_from(printer);
		return;
	}
};
