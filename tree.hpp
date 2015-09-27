#ifndef TREE_HPP
#define TREE_HPP

#include "tree.h"
#include "process.h"
#include <iostream>
#include "conio.h"

///////////////////////////////

template<class a_class, class c_class>
tree_node <a_class, c_class>::tree_node() : field(nullptr), parent(nullptr), left_child(nullptr), right_child(nullptr), is_left(true)
{};


template<class a_class, class c_class>
tree_node <a_class, c_class>::tree_node(a_class* x, bool left): field(x), parent(nullptr), left_child(nullptr),right_child(nullptr),
is_left(left)
{};


template<class a_class, class c_class>
tree_node <a_class, c_class>::~tree_node()
{};


////////////////////////////////////////////
template<class b_class, class c_class>
tree_runner<b_class, c_class>::tree_runner() : curent(nullptr),previous(nullptr), abstract_type(true), previous_label(it_was_abstract)
{};


template<class b_class, class c_class>
tree_runner<b_class, c_class>::~tree_runner()
{};


template<class b_class, class c_class>
b_class* & tree_runner<b_class, c_class>::access_field()
{
	if (!(abstract_type))
		return curent->field;
	else
	{
		cout << "\ntry have access to nonexistent field"<<endl<<"press any key";
		_getch();
		exit(1);
	}
};



template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::go_to_parent()
{
	if (abstract_type)
	{
		if ((previous_label == parent_to_left) + (previous_label == parent_to_right))
		{
			curent = previous;
			previous = nullptr;
			abstract_type = false;
			previous_label = it_was_abstract;
			return true;
		}
		else
			return false;
	}
	else
	{
		if (curent->is_left)
			previous_label = it_was_left_child;
		else
			previous_label = it_was_right_child;
		previous = curent;
		if (curent->parent == nullptr)
			abstract_type = true;
		else
			abstract_type = false;
		curent = curent->parent;
		return true;
	}
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::go_to_left_child()
{
	if (abstract_type)
	{
		if (previous_label == it_was_left_child)
		{
			curent = previous;
			previous = nullptr;
			abstract_type = false;
			previous_label = it_was_abstract;
			return true;
		}
		else
			return false;
	}
	else
	{
		previous_label = parent_to_left;
		previous = curent;
		if (curent->left_child == nullptr)
			abstract_type = true;
		else
			abstract_type = false;
		curent = curent->left_child;
		return true;
	}
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::go_to_right_child()
{
	if (abstract_type)
	{
		if (previous_label == it_was_right_child)
		{
			curent = previous;
			previous = nullptr;
			abstract_type = false;
			previous_label = it_was_abstract;
			return true;
		}
		else
			return false;
	}
	else
	{
		previous_label = parent_to_right;
		previous = curent;
		if (curent->right_child == nullptr)
			abstract_type = true;
		else
			abstract_type = false;
		curent = curent->right_child;
		return true;
	}
};



template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::is_left_child()
{
	if (abstract_type)
	{
		if (previous_label == parent_to_right)
			return false;
		else
			return true;
	}
	else
		return curent->is_left;
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::is_abstract()
{
	return abstract_type;
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::swap_child_position()
{
	if (is_abstract())
	{
		if (previous_label == it_was_abstract)
			return true;
		else
			return false;
	}
	else if (curent->parent == nullptr)
	{
		curent->is_left = !(curent->is_left);
		return true;
	}
	else
		return false;
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::swap_childs()
{
	if (!(abstract_type))
	{
		if (curent->left_child != nullptr)
			curent->left_child->is_left = false;
		if (curent->right_child != nullptr)
			curent->right_child->is_left = true;
		return true;
	}
	else
		return false;
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::create_node()
{
	if (abstract_type)
	{
		curent = new tree_node<b_class, c_class>();
		curent->field = new b_class();
		abstract_type = false;
		switch (previous_label)
		{
		case it_was_abstract:
			break;
		case parent_to_left:
			curent->parent = previous;
			previous->left_child = curent;
			break;
		case parent_to_right:
			curent->parent = previous;
			previous->right_child = curent;
			curent->is_left = false;
			break;
		case it_was_right_child:
			curent->right_child = previous;
			previous->parent = curent;
			break;
		case it_was_left_child:
			curent->left_child = previous;
			previous->parent = curent;
			break;
		default:
			break;
		}
		return true;
	}
	else
		return false;
};



template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::delete_node()
{
	if (!abstract_type)
	{
		delete (curent->field);

		if ((curent->left_child == nullptr) && (curent->right_child == nullptr) && (curent->parent != nullptr))
		{
			abstract_type = true;
			previous = curent->parent;
			if (curent->is_left)
			{
				previous_label = parent_to_left;
				previous->left_child = nullptr;
			}
			else
			{
				previous_label = parent_to_right;
				previous->right_child = nullptr;
			}
			delete curent;

		}

		else if ((curent->left_child != nullptr)*(curent->right_child == nullptr)*(curent->parent == nullptr))
		{
			abstract_type = true;
			previous = curent->left_child;
			previous_label = it_was_left_child;
			previous->parent = nullptr;
			delete curent;
		}
		else if ((curent->left_child == nullptr)*(curent->right_child != nullptr)*(curent->parent == nullptr))
		{
			abstract_type = true;
			previous = curent->right_child;
			previous_label = it_was_right_child;
			previous->parent = nullptr;
			delete curent;
		}
		else if ((curent->left_child == nullptr)*(curent->right_child == nullptr)*(curent->parent == nullptr))
		{
			abstract_type = true;
			previous = nullptr;
			previous_label = it_was_abstract;
			delete curent;
		}
		else
		{
			cout << "error of node delete" << endl << "press any key";
			_getch();
			exit(2);
		}

		curent = nullptr;

		return true;
	}
	else
		return false;
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::unite_with_subtree(tree_runner<b_class, c_class> & runner)
{
	if ((!abstract_type) && (!runner.abstract_type) && (runner.curent->parent == nullptr))
	{
		if ((curent->left_child == nullptr) && (runner.is_left_child()))
		{
			curent->left_child = runner.curent;
			runner.curent->parent = curent;
			return true;
		}

		else if ((curent->right_child == nullptr) && (!(runner.is_left_child())))
		{
			curent->right_child = runner.curent;
			runner.curent->parent = curent;
			return true;
		}
		else
			return false;
	}
	else
		return false;
};


template<class b_class, class c_class>
bool tree_runner<b_class, c_class>::disunite_with_subtree(tree_runner<b_class, c_class> & runner)
{
	if ((!abstract_type) && (!runner.abstract_type) && (runner.curent->parent == curent))
	{
		runner.curent->parent = nullptr;
		if (runner.curent->is_left)
			curent->left_child = nullptr;
		else
			curent->right_child = nullptr;
		return true;
	}
	else if ((!abstract_type) && (runner.abstract_type) && (runner.previous == curent) && ((runner.previous_label == parent_to_left) || (runner.previous_label == parent_to_right)))
	{

		runner.previous_label = it_was_abstract;
		runner.previous = nullptr;
		return true;
	}
	else
		return false;
}


template<class b_class, class c_class>
tree_runner<b_class, c_class> tree_runner<b_class, c_class>::reduplicate_tree_runner()
{
	return (*this);
}


////////////////////////////////////

#endif