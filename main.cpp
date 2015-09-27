#include "get_token.h"
#include "tree.hpp"
#include <iostream>
#include "conio.h"
#include "note.h"
#include "tree_field.h"
#include "parse.h"
#include "vocabulary.h"
#include "filter.h"
#include <iostream>

using namespace std;

int main()
{
	cout<< "Type any calculation contained following" << '\n'
		<< " operators: +, -, , / - and round brackets" << '\n'
		<< " (). Don’t worry about errors like missing " << '\n'
		<< "or extra brackets, wrong operator order and" << '\n'
		<< " ambiguity in expression! This program will" << '\n'
		<< " check and correct your input on the spot." << '\n'
		<< " For ex., (--5 turn into  -(-5, and " << '\n'
		<< "(5-7= into (5-7)= )." << '\n'
		<< "  In complex cases you should choose " << '\n'
		<< "the right way from offering: 4*(5/6)/7*  turn" << '\n'
		<< " into (4*5/6)/(7*... or ((4*5/6)/7)*..." << '\n'
		<< " according to your choice. Try your examples!" << '\n'
		<< "Do calculations as a right way and study math" << '\n'
		<< " like a game." <<'\n'<< endl;

	
	char oper;
	
	do
	{
		tree_runner<field, note> summ_tree;

		build_summ(summ_tree, oper);

		cout << '=';

		intermediate_result_under(summ_tree).show_fract();
		
		cout << "\n continue? y/n:";

			do
			{
				to_bell();
				oper = filter("yn");
			} while (oper==backspace);

			cout << oper<<'\n'<<endl;

	} while (oper=='y');
	
	return 0;
}