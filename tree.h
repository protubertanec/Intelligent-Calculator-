#ifndef TREE_H
#define TREE_H
/////////////////////////////////
template<class b_class, class c_class>
class tree_runner;

template<class a_class, class c_class>
class tree_node
{
private:
	a_class* field;
	tree_node* parent;
	tree_node* left_child;
	tree_node* right_child;
	bool is_left;
	tree_node();
	tree_node(a_class* x, bool left);
public:
	friend tree_runner<a_class, c_class> ;
	~tree_node();
	
};
//////////////////////////////////////////
enum label { parent_to_left, parent_to_right, it_was_left_child, it_was_right_child, it_was_abstract };


template<class b_class, class c_class>
class tree_runner
{
private:
	tree_node<b_class, c_class>* curent;
	tree_node<b_class, c_class>* previous;
	label previous_label;
	bool abstract_type;
public:
	c_class note;
public:
	tree_runner();
	~tree_runner();

	bool go_to_parent();
	bool go_to_left_child();
	bool go_to_right_child();

	bool is_left_child();// проверяет является ли обозреваемый узел левым дочерним 
	bool is_abstract();//проверяет является ли обозреваемый узел абстрактным
	bool swap_child_position();// меняет направление свободной валентной связи
	bool swap_childs();//меняет местами дочерние узлы


	bool create_node(); // создает первый узел, или связанный в точности с одним уже созданным
	bool delete_node(); // удаляет последний узел дерева или связанный в точности с одним существующим

	b_class* & access_field();

	bool unite_with_subtree(tree_runner<b_class, c_class> &);
	bool disunite_with_subtree(tree_runner<b_class, c_class> &);
	tree_runner<b_class, c_class> reduplicate_tree_runner();
};


#endif
