#include "parse.h"
#include <iostream>
#include "get_token.h"
#include "filter.h"
#include  "vocabulary.h"
using namespace std;



void mutate_fract(tree_runner<field, note> &,char , int & );
void to_make_intermediate_result(tree_runner<field, note> &);



void build_summ(tree_runner<field, note> & summ_tree, char & oper)
{
	//cout << "build_summ" << endl;
	int temp_number;
	char temp_oper;
	
	if (summ_tree.is_abstract())
	{
		summ_tree.create_node();			//ñîçäàåì óçåë äëÿ çíàêà +- 
		ooperator_under(summ_tree) = '+'; //  îí óíàðíûé
	}

	while (true)
	{
			redetermin_intermediate_result_under(summ_tree);
			tree_runner<field, note> fract;
			fract = summ_tree.reduplicate_tree_runner();
			if((ooperator_is_unary_under(summ_tree)) && (ooperator_under(summ_tree) == '+'))
				fract.note.first_token = true;
			fract.go_to_right_child();
			summ_tree.disunite_with_subtree(fract);

			build_fract(fract, temp_oper);
			summ_tree.note.to_calculate = fract.note.to_calculate;
			if (fract.is_left_child())
				fract.swap_child_position(); // ìåíÿåì íàïðàâëåíèå âàëåíòíîñòè íà ïðàâóþ

			//cout << "retern_to_summ" << endl;


			if ((temp_oper == '-') && (fract.note.first_token == true))
			{
				cout << '-';
				summ_tree.unite_with_subtree(fract);
				ooperator_under(summ_tree) = '-';
				length_of_operator_under(summ_tree) = 1;
			}


			else if ((temp_oper == '-') + (temp_oper == '+'))
			{
				summ_tree.unite_with_subtree(fract); // ïðèêðåïëÿåì ïðàâîãî ñûíà
				to_make_intermediate_result(summ_tree);
				
				cout << temp_oper;
				summ_tree.go_to_parent();
				summ_tree.create_node();			//ñîçäàåì óçåë äëÿ çíàêà +-
				ooperator_under(summ_tree) = temp_oper;
				ooperator_is_unary_under( summ_tree) = false;
				length_of_operator_under(summ_tree) = 1;
			}


			else if ((temp_oper == '=') || (temp_oper == ')'))
			{
				summ_tree.unite_with_subtree(fract);// ïðèêðåïëÿåì ïðàâîãî ñûíà
				to_make_intermediate_result(summ_tree);
				oper = temp_oper;
				return;
			}


			else if (temp_oper == backspace)
			{
				if ((ooperator_is_unary_under(summ_tree)) && (ooperator_under(summ_tree) =='+'))
				{
					summ_tree.delete_node();
					oper = temp_oper;
					return;
				}

				else if ((ooperator_is_unary_under(summ_tree)) && (ooperator_under(summ_tree) == '-'))
				{
					erase(1);
					ooperator_under(summ_tree) = '+';
					length_of_operator_under(summ_tree) = 0;
				}

				else
				{
					erase(1);
					summ_tree.delete_node();
					summ_tree.go_to_left_child();
				}
			}

			else
			{
				cout << "wrong summ construction";
				return;
			}
	}
};


//////////////////////////////////////////////////////////////////


void build_fract(tree_runner<field, note> & fract_tree, char & oper)
{
	//cout << "build_fract" << endl;
	char temp_oper;
	int instr;

	if (fract_tree.is_abstract())
	{
		fract_tree.create_node();			//ñoçäàåì óçåë äëÿ çíàêà ïîêà îí óíàðíûé
		ooperator_under(fract_tree) = '/';
		instr = 0;
	}
	else 
	{
		if (ooperator_is_unary_under(fract_tree))
			instr = 0;
		else
			instr = 1;
	}

	

	while (true)
	{
		switch (instr)
		{
		case 0:
		{
			//cout << "build_fract0" << endl;
			intermediate_result_under(fract_tree) = 1;
			tree_runner<field, note> mult;
			mult = fract_tree.reduplicate_tree_runner();
			mult.go_to_left_child();
			fract_tree.disunite_with_subtree(mult);

			build_mult(mult, temp_oper);
			fract_tree.note.to_calculate = mult.note.to_calculate;

			//cout << "retern_to_fract0" << endl;
	
			if (temp_oper == '/')
			{
				cout << '/';
				ooperator_is_unary_under(fract_tree) = false;
				length_of_operator_under(fract_tree) = 1;
				fract_tree.unite_with_subtree(mult); //ïðèêëåèâàåì ê óçëó '/' äåðåâî ïðîèçâåäåíèÿ â êà÷å÷òâå ëåâîãî îïåðàíäà
				instr = 1;
			}

			else if ((temp_oper == '-') && (mult.note.first_token))
			{
				oper = '-';
				return;
			}

			else if ((temp_oper == '+') || (temp_oper == '-') || (temp_oper == '=') || (temp_oper == ')'))
			{
				fract_tree.unite_with_subtree(mult);
				redetermin_intermediate_result_under(fract_tree);
				fract_tree.note.first_token = false;
				oper = temp_oper;
				return;
			}

			else if (temp_oper == backspace)
			{
				fract_tree.delete_node();
				oper = temp_oper;
				return;
			}

			else
			{
				cout << "error divided's building";
				return;
			}
			break;
		}
		case 1:
		{
			//cout << "build_fract1" << endl;
			redetermin_intermediate_result_under(fract_tree);
			tree_runner<field, note> num;
			num = fract_tree.reduplicate_tree_runner();
			num.note.first_token = false;
			num.go_to_right_child();
			fract_tree.disunite_with_subtree(num);

			build_num(num, temp_oper, write_not_null);// âîçüìåì èëè äîïðåäåëèì ÷èñëî íå íîëü
			fract_tree.note.to_calculate = num.note.to_calculate;
			if(num.is_left_child())
				num.swap_child_position();


			//cout << "retern_to_fract1" << endl;  


			if ((temp_oper == '+') || (temp_oper == '-') || (temp_oper == '=') || (temp_oper == ')'))
			{
				fract_tree.unite_with_subtree(num);
				to_make_intermediate_result(fract_tree);
				fract_tree.note.first_token = false;
				oper = temp_oper;
				return;
			}

			else if ((temp_oper == '/') || (temp_oper == '*'))
			{
				fract_tree.unite_with_subtree(num);
				mutate_fract(fract_tree, temp_oper, instr);
			}

			else if (temp_oper == backspace)
			{
				erase(1);
				ooperator_is_unary_under(fract_tree) = true;
				length_of_operator_under(fract_tree) = 0;
				instr = 0;
			}
			else
			{
				cout << "somethig wrong with divisor";
			}

			break;
		}
		default:
			cout << "out of fract instr";
			break;
		}
	}	
};

///////////////////////////////////////////////////////////////////



void build_mult(tree_runner<field, note> & mult_tree, char & oper)
{
	//cout << "build_mult" << endl;
	char temp_oper;

	if (mult_tree.is_abstract())
	{
		mult_tree.create_node();			//ñùçäàåì óçåë äëÿ çíàêà * ïîêà îí óíàðíûé
		ooperator_under(mult_tree) = '*';
	}


	while (true)
	{
			//cout << "build_mult iteration" << endl;
			redetermin_intermediate_result_under(mult_tree);
			tree_runner<field, note> num;
			num = mult_tree.reduplicate_tree_runner();
			if (!ooperator_is_unary_under(mult_tree))
				num.note.first_token = false;
			num.note.bracket_factor = true;
			num.go_to_right_child();
			mult_tree.disunite_with_subtree(num);

			build_num(num, temp_oper, write);// âîçüìåì èëè äîïðåäåëèì ÷èñëî 
			mult_tree.note.to_calculate = num.note.to_calculate;
			if (num.is_left_child())
				num.swap_child_position();

			//cout << "return_mult" << endl;

			if (temp_oper == '*')
			{
				mult_tree.unite_with_subtree(num); // ïðèêðåïëÿåì ïðàâîãî ñûíà
				to_make_intermediate_result(mult_tree);

				cout << temp_oper;
				mult_tree.go_to_parent();
				mult_tree.create_node();			//ñîçäàåì óçåë äëÿ çíàêà *
				ooperator_under(mult_tree) = '*';
				ooperator_is_unary_under(mult_tree) = false;
				length_of_operator_under(mult_tree) = 1;
				redetermin_intermediate_result_under(mult_tree);
			}

			else if ((temp_oper == '-') && (num.note.first_token))
			{
				oper = '-';
				return;
			}

			else if ((temp_oper == '=') || (temp_oper == '+') || (temp_oper == '-') || (temp_oper == '/') || (temp_oper == ')'))
			{
				mult_tree.unite_with_subtree(num);
				to_make_intermediate_result(mult_tree);
				mult_tree.note.first_token = false;
				oper = temp_oper;
				return;
			}

			else if (temp_oper == backspace)
			{

				if (ooperator_is_unary_under(mult_tree))
				{
					mult_tree.delete_node();
					oper = temp_oper;
					return;
				}

				else
				{
					erase(1);
					mult_tree.delete_node();
					mult_tree.go_to_left_child();
				}
			}

			else if (temp_oper=='b')
			{
				mult_tree.unite_with_subtree(num);
				to_make_intermediate_result(mult_tree);
			}
		}
};


//////////////////////////////////////////////////////////////////////////



void build_num(tree_runner<field, note> & num_tree, char & oper, config conf)
{
	//cout << "build_num" << endl;

	int num_length(int);
	char temp_oper;
	int temp_num;
	int instr = 0;


	while (true)
	{
		switch (instr)
		{
		case 0:
		{
			if (num_tree.is_abstract())
			{
				num_tree.create_node();
				temp_oper = 0;
				temp_num = 0;
				if (conf == write) 
					instr = 1;
				else
					instr = 2;
			}

			else if (ooperator_under(num_tree) == 0)// äîîïðåäèëèòü ïîñëåäîâàòåëüíîñòü öèôð
			{
				temp_oper = 1;
				temp_num = num_tree.access_field()->number;
				if (conf == write)
					instr = 1;
				else
					instr = 2;
			}

			else if (ooperator_under(num_tree) == '(')
			{
				num_tree.go_to_right_child();
				if (length_of_operator_under(num_tree))
				{
					num_tree.go_to_parent();
					get_oper(temp_oper);
					if (temp_oper == backspace)
					{
						erase(1);
						num_tree.go_to_right_child();
						instr = 4;
					}

					else
					{
						num_tree.note.first_token = false;
						oper = temp_oper;
						return;
					}
				}

				else
					instr = 4;
			}

			else
			{
				cout << "error in num seporation" << endl;
			}
			break;
		}

		case 1:// âçÿòü ÷èñëî èëè òîêåí
		{
			get_token(temp_num, temp_oper);

			while (temp_oper == '0')
			{
				cout << '0';
				temp_oper = 1;
				temp_num = 0;
				get_token(temp_num, temp_oper);
			}
			instr = 3;
			break;
		}

		case 2:// âçÿòü íåíóëåâîå ÷èñëî èëè òîêåí
		{
			do
			{
				if (temp_oper == '0')
					temp_oper = 0;
				temp_num = 0;
				get_token(temp_num, temp_oper);
				if (temp_oper == '0')// ðàñïå÷àòêà çâóêîâîãî ïðåäóïðåæäåíèÿ
					to_bell();
			} while (temp_oper == '0');

			instr = 3;
			break;
		}

		case 3:
		{

			if (temp_num >= 0)
			{
				(num_tree.access_field()->number) = temp_num;
				length_of_operator_under(num_tree) = num_length(temp_num);
				intermediate_result_under(num_tree) = temp_num;
				num_tree.note.first_token = false;
				oper = temp_oper;
				return;
			}

			else if (temp_oper == '(')
			{
				cout << '(';
				ooperator_under(num_tree) = '(';
				length_of_operator_under(num_tree) = 1;

				num_tree.go_to_right_child();
				num_tree.create_node();
				ooperator_under(num_tree) = ')';
				length_of_operator_under(num_tree) = 0;
				instr = 4;
			}

			else if (temp_oper == '-')
				instr = 5;
			else if (temp_oper == backspace)
			{
				num_tree.delete_node();
				oper = temp_oper;
				return;
			}
			else
				cout << "exept in num case 3";
			break;

		}

		case 4:
		{
			tree_runner<field, note> summ;
			summ = num_tree.reduplicate_tree_runner();
			summ.note.first_token = false;
			summ.go_to_left_child();
			num_tree.disunite_with_subtree(summ);

			build_summ(summ, temp_oper);
			num_tree.note.to_calculate = summ.note.to_calculate;

			//cout << "return_to_num" << endl;

			if ((temp_oper == ')') || (temp_oper == '='))
			{
				num_tree.unite_with_subtree(summ);
				redetermin_intermediate_result_under(num_tree);

				// îãðàíè÷åíèÿ íà íóëåâûå çíà÷åíèÿ
				if ((conf == write_not_null) && (intermediate_result_under(summ) == 0))
				{
					to_bell();
					cout << " divisor=0,pr. a key";
					_getch();
					erase(20);
					instr = 4;
				}

				else if (temp_oper == ')')
				{
					cout << ')';
					length_of_operator_under(num_tree) = 1;
					num_tree.go_to_parent();
					to_make_intermediate_result(num_tree);

					if ((num_tree.note.bracket_factor) && ((ooperator_under(summ) == '+') && (ooperator_is_unary_under(summ))))
					{
						/*
						cout << " rem.br?y/n:";
						do
						{
							to_bell();
							temp_oper = filter("yn");
						} while (temp_oper == backspace);
						erase(12);*/

						temp_oper = 'y';

						if (temp_oper == 'y')
						{
							oper = 'b';//
							return;
						}

						else
							instr = 0;
					}
					else
						instr = 0;
				}


				else if (temp_oper == '=')
				{
					if (!summ.note.to_calculate)
					{
						cout << " confirm'='? y/n:";
						do
						{
							to_bell();
							temp_oper = filter("yn");
						} while (temp_oper == backspace);
						erase(17);

						if (temp_oper == 'n')
							instr = 4;
						else
							instr = 6;
					}

					else
						instr = 6;
				}
			}

			else if (temp_oper == backspace)
			{
				num_tree.delete_node();
				num_tree.go_to_parent();
				erase(1);
				num_tree.delete_node();  
				instr = 0;
			}

			break;
		}
		case 5:
		{
			if (num_tree.note.first_token)
			{
				oper = '-';
				return;
			}

			else// îòêðîåì ñêîáêè è ñêàæåì áóäóùåé ñóììå â íèõ, ÷òî îíà íà÷íåòñÿ ñ "-"
			{
				to_bell();
				cout << "(-";
				ooperator_under(num_tree) = '(';
				length_of_operator_under(num_tree) = 1;


				num_tree.go_to_right_child();
				num_tree.create_node();
				ooperator_under(num_tree) = ')';
				length_of_operator_under(num_tree) = 0;

				num_tree.go_to_left_child();
				num_tree.create_node();
				ooperator_under(num_tree) = '-';
				length_of_operator_under(num_tree) = 1;
				num_tree.go_to_parent();
				instr = 4;
			}
			break;
		}

		case 6:// ëàâèíîîáðàçíîå âû÷èñëåíèå ðåçóëüòàòà
		{
			cout << ')';
			num_tree.note.to_calculate = true;//
			length_of_operator_under(num_tree) = 1;
			redetermin_intermediate_result_under(num_tree);
			num_tree.go_to_parent();
			to_make_intermediate_result(num_tree); //â òîì ÷èñëå óáèðàåò âëîæåííûå ñêîáêè
			oper = '=';
			return;
			break;
		}




		default:
			cout << "num cases default";
			break;
		}
	}




};




/////////////////////////////////////////////////////////////////////////


void transforme_second_summ_to_first(tree_runner<field, note> & summ1, tree_runner<field, note> & summ2)
{
	// ñ÷èòàåòñÿ, ÷òî ïåðâûé áåãóíîê íàä îïåðàòîðîì +, à âòîðîé íàä ñêîáêîé, ïîä êîòîðîé èäåò âòîðàÿ ñóììà

	bool abstr;

	erase_up_to(summ1);

	tree_runner<field, note> left_limit;

	summ2.go_to_right_child();// )

	tree_runner<field, note> servant;
	servant = summ1.reduplicate_tree_runner();
	servant.go_to_left_child();
	if (!servant.is_abstract())
	{
		summ1.disunite_with_subtree(servant);
		while (summ2.go_to_left_child())// ïåðåéòè ñî ñêîáêè ) íà îïåðàòîð
			;
		summ2.go_to_parent();// òåïåðü ýòîò áåãóíîê â íà÷àëå âòîðîé ñóììû
		left_limit = summ2.reduplicate_tree_runner();
		summ2.unite_with_subtree(servant);



		while (ooperator_under(summ2)!= ')')
			summ2.go_to_parent();// à òåïåðü ñíîâà íà ñêîáêå

		servant.note.intermediate_result = intermediate_result_under(servant);// äàëüøå êîððåêòèðóåì ïðîìåæóòî÷íûå çíà÷åíèÿ
		while (ooperator_under(servant) != ')')
		{
			servant.go_to_parent();
			intermediate_result_under(servant) += servant.note.intermediate_result;
			ooperator_is_unary_under(servant) = false;
			length_of_operator_under(servant) = 1;
		}

	}

	else
	{
		servant = summ2.reduplicate_tree_runner();
		left_limit= summ2.reduplicate_tree_runner();
		while (left_limit.go_to_left_child())
			;
		left_limit.go_to_parent();
	}

	servant.go_to_left_child();
	summ2.disunite_with_subtree(servant);
	summ1.go_to_parent();

	if (summ1.is_abstract())
	{
		abstr = true;
		summ1.create_node();
	}

	while (summ2.access_field() != summ1.access_field())
	{
		summ2.delete_node();
		summ2.go_to_parent();
	}
	summ1.unite_with_subtree(servant);
	summ2.go_to_left_child();

	if (abstr)
		summ1.delete_node();

	summ1.go_to_left_child();
		

	print_tree_from(left_limit);
	
	return;
};



void transform_second_mult_to_first(tree_runner<field, note> & mult1, tree_runner<field, note> & mult2)
{
	// c÷èòàåòñÿ, ÷òî ùáà áåãóíêà íàä îïåðàòîðàìè *: ïåðâûé íàä òåì ê êîòîðîìó ïðèñîåäèíÿþò, à âòîðé - íàäãëàâíûì

	bool abstr;

	erase_up_to(mult1);

	tree_runner<field, note> left_limit;

	tree_runner<field, note> servant;
	servant = mult1.reduplicate_tree_runner();
	servant.go_to_left_child();
	if (!servant.is_abstract())
	{
		mult1.disunite_with_subtree(servant);

		while (mult2.go_to_left_child())
			;
		mult2.go_to_parent();// òåïåðü ýòîò áåãóíîê â íà÷àëå âòîðîãî ïðîèçâåäåíèÿ
		left_limit = mult2.reduplicate_tree_runner();
		mult2.unite_with_subtree(servant);



		while (ooperator_under(mult2) != '/')
			mult2.go_to_parent();// à òåïåðü ñíîâà íà '/'

		servant.note.intermediate_result = intermediate_result_under(servant);// äàëüøå êîððåêòèðóåì ïðîìåæóòî÷íûå çíà÷åíèÿ
		while (ooperator_under(servant) != '/')
		{
			servant.go_to_parent();
			intermediate_result_under(servant) *= servant.note.intermediate_result;
			length_of_operator_under(servant) = 1;
			ooperator_is_unary_under(servant) = false;
		}

	}

	else
	{
		mult2.go_to_parent();
		servant = mult2.reduplicate_tree_runner();
		left_limit = mult2.reduplicate_tree_runner();
		while (left_limit.go_to_left_child())
			;
		left_limit.go_to_parent();
	}

	servant.go_to_left_child();
	mult2.disunite_with_subtree(servant);
	mult1.go_to_parent();

	if (mult1.is_abstract())
	{
		abstr = true;
		mult1.create_node();
	}

	while (mult2.access_field() != mult1.access_field())
	{
		mult2.delete_node();
		mult2.go_to_parent();
	}

	mult1.unite_with_subtree(servant);
	mult2.go_to_left_child();

	if (abstr)
		mult1.delete_node();

		mult1.go_to_left_child();

	print_tree_from(left_limit);
};



void transform_fract_and_mult_to_fract(tree_runner<field, note> & mult, tree_runner<field, note> & fract)
{
	//ñ÷èòàåòñÿ, ÷òî îáà áåãóíêà íàõîäÿòñÿ íàä ñâîèìè îïåðàòîðàìè 
	// ïî ðåçóëüòàòó ñëèòàÿ äðîáü áóäåò â ñêîáêàõ, à áåãóíêè íàä * ïåðåä íèìè

	bool abstr;

	tree_runner<field, note> restart_point;

	tree_runner<field, note> left_limit;
	left_limit = mult.reduplicate_tree_runner();

	while (left_limit.go_to_left_child())
		;
	left_limit.go_to_parent();

	erase_up_to(left_limit);


	//////////

	tree_runner<field, note> servant_of_divisor;
	servant_of_divisor = fract.reduplicate_tree_runner();

	servant_of_divisor.go_to_right_child();
	fract.disunite_with_subtree(servant_of_divisor);

	ooperator_is_unary_under(fract) = true;
	length_of_operator_under(fract) = 0;

	fract.go_to_left_child();// *

	print_tree_from(left_limit);

	transform_second_mult_to_first(mult, fract);// îáà íàä ãëàâíûì *

	erase_up_to(left_limit);

	mult.go_to_parent();					// òåïåðü íàä"/" 

	if (mult.is_abstract())
	{
		abstr = true;
		mult.create_node();
	}

	mult.disunite_with_subtree(fract);

	mult.go_to_left_child();
	mult.create_node();

	if (abstr)
	{
		mult.go_to_parent();
		mult.delete_node();
		mult.go_to_left_child();
	}

	ooperator_under(mult) = '*';
	restart_point = mult.reduplicate_tree_runner();

	mult.go_to_right_child();
	mult.create_node();
	ooperator_under(mult) = '(';
	length_of_operator_under(mult) = 1;

	mult.go_to_right_child();
	mult.create_node();
	ooperator_under(mult) = ')';
	length_of_operator_under(mult) = 1;

	mult.go_to_left_child();
	mult.create_node();
	ooperator_under(mult) = '+';

	//////////

	fract.go_to_parent();
	fract.create_node();
	ooperator_under(fract) = '/';
	length_of_operator_under(fract) = 1;
	ooperator_is_unary_under(fract) = false;
	redetermin_intermediate_result_under(fract);

	fract.unite_with_subtree(servant_of_divisor);
	to_make_intermediate_result(fract);
	fract.swap_child_position();
	mult.unite_with_subtree(fract);

	mult = restart_point.reduplicate_tree_runner();

	fract.note.intermediate_result = intermediate_result_under(fract);
	do
	{
		fract.go_to_parent();
		intermediate_result_under(fract) = fract.note.intermediate_result;
	} while (fract.access_field()!=mult.access_field());

	print_tree_from(mult);

	return;
};



 void mutate_fract(tree_runner<field, note> & fract, char oper, int & instr)
 {
	 char choise;

	 bool abstr;

	 tree_runner<field, note> servant;

	 tree_runner<field, note> restart_point;

	 cout << "fr" << oper << " ?y/n:";

	 do
	 {
		 to_bell();
		 choise = filter("yn");
	 } while (choise == backspace);

	 erase(9);

	 if (choise == 'y')
	 {
		 to_make_intermediate_result(fract);
												    // ñåé÷àñ ìû îòäåëèì äðîáü è, îáëî÷èâ åå â ñêîáêè, ïðèêðåïèì îáðàòíî 
													// ê ñëåãêà äîñòðîåííîìó äåðåâó
		 if (fract.is_left_child())
			 fract.swap_child_position();

		 servant = fract.reduplicate_tree_runner();
		 fract.go_to_parent();

		 if (fract.is_abstract())
		 {
			 abstr = true;
			 fract.create_node();
			 ooperator_under(fract) = '+';
		 }

		 erase_up_to(fract);
		 restart_point = fract.reduplicate_tree_runner();
		 fract.disunite_with_subtree(servant);
		 servant.note.intermediate_result = intermediate_result_under(servant);

		 servant.go_to_parent();
		 servant.create_node();
		 ooperator_under(servant) = '+';
		 intermediate_result_under(servant) = servant.note.intermediate_result;

		 servant.go_to_parent();
		 servant.create_node();
		 ooperator_under(servant) = ')';
		 intermediate_result_under(servant) = servant.note.intermediate_result;
		 length_of_operator_under(servant) = 1;
		 servant.swap_child_position();

		 servant.go_to_parent();
		 servant.create_node();
		 ooperator_under(servant) = '(';
		 intermediate_result_under(servant) = servant.note.intermediate_result;
		 length_of_operator_under(servant) = 1;
		 servant.swap_child_position();

		 fract.go_to_right_child();
		 fract.create_node();
		 ooperator_under(fract) = '/';
		 intermediate_result_under(fract) = 1;

		 fract.go_to_left_child();
		 fract.create_node();
		 ooperator_under(fract) = '*';
		 




		 switch (oper)
		 {
		 case '/':
		 {
			 intermediate_result_under(fract) = servant.note.intermediate_result;
			 fract.unite_with_subtree(servant);
			 fract.go_to_parent();

			 ooperator_is_unary_under(fract) = false;
			 length_of_operator_under(fract) = 1;
			 intermediate_result_under(fract) = servant.note.intermediate_result;
			
			 print_tree_from(restart_point);

			 if (abstr)
				 restart_point.delete_node();
			 
			 instr = 1;

			 return;
			 break;
		 }

		 case '*':
		 {
			 servant.go_to_parent();
			 servant.create_node();
			 ooperator_under(servant) = '*';
			 intermediate_result_under(servant) = servant.note.intermediate_result;
			
			 intermediate_result_under(fract) = servant.note.intermediate_result;
			 ooperator_is_unary_under(fract) = false;
			 length_of_operator_under(fract) = 1;
			 fract.unite_with_subtree(servant);
			 fract.go_to_parent();

			 print_tree_from(restart_point);

			 if (abstr)
				 restart_point.delete_node();

			 instr = 0;

			 return;
			 break;
		 }
		 default:
			 break;
		 }
	 }

	 else
	 {
		 servant = fract.reduplicate_tree_runner();

		 servant.go_to_right_child();

		 tree_runner<field, note> left_limit;
		 left_limit = fract.reduplicate_tree_runner();

		 erase_up_to(fract);
		 fract.disunite_with_subtree(servant);

		 servant.note.intermediate_result = intermediate_result_under(servant);
		 servant.go_to_parent();

		 servant.create_node();
		 ooperator_under(servant) = '*';
		 intermediate_result_under(servant) = servant.note.intermediate_result;

		 ////////////////////

		 redetermin_intermediate_result_under(fract);
		 fract.go_to_right_child();

		 fract.create_node();
		 ooperator_under(fract) = '(';
		 length_of_operator_under(fract) = 1;
		 fract.go_to_right_child();

		 fract.create_node();
		 ooperator_under(fract) = ')';
		 length_of_operator_under(fract) = 0;
		 fract.go_to_left_child();

		 fract.create_node();
		 ooperator_under(fract) = '+';
		 fract.go_to_right_child();

		 fract.create_node();
		 ooperator_under(fract) = '/';
		 intermediate_result_under(fract) = 1;
		 
		 switch (oper)
		 {
		 case '/':
		 {
			 ooperator_is_unary_under(fract) = false;
			 length_of_operator_under(fract) = 1;
			 fract.unite_with_subtree(servant);

			 fract = left_limit.reduplicate_tree_runner();

			 while (servant.access_field() != fract.access_field())
			 {
				 servant.go_to_parent();
				 intermediate_result_under(servant) = servant.note.intermediate_result;
			 }

			 print_tree_from(left_limit);
			 instr = 1;

			 return;
			 break;
		 }

		 case '*':
		 {
			 fract.go_to_left_child();
			 fract.create_node();
			 ooperator_under(fract) = '*';
			 ooperator_is_unary_under(fract) = false;
			 length_of_operator_under(fract) = 1;
			 fract.unite_with_subtree(servant);

			 fract = left_limit.reduplicate_tree_runner();

			 while (servant.access_field() != fract.access_field())
			 {
				 servant.go_to_parent();
				 intermediate_result_under(servant) = servant.note.intermediate_result;
			 }

			 print_tree_from(left_limit);
			 instr = 1;

			 return;
			 break;
		 }
			 return;

		 default:
			 break;
		 }

	 }

 };


////////////////////////////////////////////////////////////////





void to_make_intermediate_result(tree_runner<field, note> & runner)
{
	//cout << "to_make_intermediate_result" << endl;

	calculate_intermediate_result_under(runner);

	switch (ooperator_under(runner))
	{
	case '+':
	{
		//cout << "case '+'" << endl;

		tree_runner<field, note> servant;
		servant = runner.reduplicate_tree_runner();

		servant.go_to_right_child();

		move_down_to_the_first_valid_operator(servant);
		if (ooperator_under(servant) == '(')
		{

			transforme_second_summ_to_first(runner, servant);
			return;
		}

		return;

		break;
	}

	case '-':
	{

		//cout << "case '-'" << endl;

		tree_runner<field, note> servant;
		servant = runner.reduplicate_tree_runner();

		servant.go_to_right_child();

		move_down_to_the_first_valid_operator(servant);
		if (ooperator_under(servant) == '(')
		{
			servant.go_to_right_child();
			servant.go_to_left_child();
			if ((ooperator_under(servant) == '-') && (ooperator_is_unary_under(servant)))
			{
				erase_up_to(runner);

				ooperator_under(runner) = '+';
				if(ooperator_is_unary_under(runner))
					length_of_operator_under(runner) = 0;

				ooperator_under(servant) = '+';
				length_of_operator_under(servant) = 0;
				intermediate_result_under(servant) = 0 - intermediate_result_under(servant);

				print_tree_from(runner);// äàëüøå áóäåò âñå êàê â àíåêäîòå ïðî ÷àéíèê ñ âîäîé è ìàòåìàòèêà

				servant.go_to_parent();
				servant.go_to_parent();

				transforme_second_summ_to_first(runner, servant);
				return;
			}
		}
		return;
		break;
	}

	case '/':
	{
		//cout << "case '/'" << endl;

		return;
		break;
	}

	case '*':
	{
		tree_runner<field, note> servant;
		servant = runner.reduplicate_tree_runner();

		servant.go_to_right_child();

		move_down_to_the_first_valid_operator(servant);

		if (ooperator_under(servant) == '(')
		{
			servant.go_to_right_child();
			servant.go_to_left_child();

			move_down_to_the_first_valid_operator(servant);
			switch (ooperator_under(servant))
			{
				case '*':
				{
					transform_second_mult_to_first(runner, servant);
					return;
					break;
				}
				case '/':
				{
					if(!ooperator_is_unary_under(runner))
						transform_fract_and_mult_to_fract(runner, servant);
					return;
					break;
				}


			default:
				break;
			}
		}
		return;
		break;
	}

	case '(':
	{
		//cout << "case '('" << endl;

		tree_runner<field, note> servant;
		servant = runner.reduplicate_tree_runner();

		servant.go_to_right_child();
		servant.go_to_left_child();

		move_down_to_the_first_valid_operator(servant);

		if ((ooperator_under(servant) == '(') || (ooperator_under(servant) == 0))
		{
			bool abstr;
			if (runner.is_left_child())
				runner.swap_child_position();
			runner.go_to_parent();

			if (runner.is_abstract())
			{
				abstr = true;
				runner.create_node();
				ooperator_under(runner) = '+';
			}

			erase_up_to(runner);

			tree_runner<field, note> servant2;

			servant2 = servant.reduplicate_tree_runner();
			servant2.go_to_parent();

			servant2.disunite_with_subtree(servant);

			while (servant2.access_field()!=runner.access_field())
			{
				servant2.delete_node();
				servant2.go_to_parent();
			}

			runner.unite_with_subtree(servant);			
			print_tree_from(runner);

			if (abstr)
				runner.delete_node();

			runner.go_to_right_child();
		}
	
		return;
		break;
	}


	default:
		cout << "to_make_intermediate_result's default";
		break;
	}
};




















