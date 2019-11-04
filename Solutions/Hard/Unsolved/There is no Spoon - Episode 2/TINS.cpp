/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: There is no spoon - Episode 2
Difficulty: Hard
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * The machines are gaining ground. Time to show them what we're really made of...
 **/
 
class Node;
class Field_tree;
class Field;




template <typename T>
class Queue
{
public:

	std::vector<T> list = {};

	void Enqueue(T i);
	T Dequeue();
	void clear();

	Queue();
	~Queue();
};

template <typename T>
Queue<T>::Queue()
{
}

template <typename T>
Queue<T>::~Queue()
{
}

template <typename T>
void Queue<T>::Enqueue(T i)
{
	list.push_back(i);
}

template <typename T>
T Queue<T>::Dequeue()
{
	T val = list[0];
	list = std::vector<T>(list.begin() + 1, list.end());
	return val;

}

template <typename T>
void Queue<T>::clear()
{
	list.clear();
}



class Node
{
public:
	int x = -1; //x coordinate
	int y = -1; //y coordinate
	bool is_node_val;
	bool link_in_use = false;
	int no_links = 0; //total number of current links
	int no_req_links; //number of links required

	//initialize pointers to neighbours
	Node* neighbour_up = nullptr;
	bool bool_neighbour_up = false;
	Node* neighbour_down = nullptr;
	bool bool_neighbour_down = false;
	Node* neighbour_left = nullptr;
	bool bool_neighbour_left = false;
	Node* neighbour_right = nullptr;
	bool bool_neighbour_right = false;
	int number_of_neighbours = 0;
	
	//initialize pointers to linked nodes
	Node* link_up = nullptr;
	int link_up_no = 0;
	Node* link_down = nullptr;
	int link_down_no = 0;
	Node* link_left = nullptr;
	int link_left_no = 0;
	Node* link_right = nullptr;
	int link_right_no = 0;
	int unique_links_val = 0;

	Node(int xx, int yy, int zz);
	bool check_saturated();
	bool is_node();
	void linking(Node* linking_node, Field &my_field);
	bool link_possible(Node* linking_node, Field my_field);
	void print();
	bool link_nodes(int x2, int y2, Field &field);
	void print2();
	void link_to_all_neighbours(Field &my_field);
 	void link_to_only_neighbour(Field &my_field);   
 	int unique_links();
 	void try_linking(Field &my_field);
};


class Field
{
public:
	vector<vector<Node>> my_node = {};
	bool is_solution_val = true;
	Queue<Node> nodes_to_check = {};

	Field(vector<string> field_string);
	Field();
	void generate_field(vector<string> field_string);
	void is_solution();
	void find_all_neighbours();
	

private:
	void find_neighbours(int x, int y);
};

class Field_tree
{
public:
	Field value;
	bool possible_sol = true;
	bool definite_sol = false;
	Field_tree* parent = nullptr;
	Field_tree* left = nullptr;
	bool left_check = false;
	Field_tree* right = nullptr;
	bool right_check = false;
	Field_tree* up = nullptr;
	bool up_check = false;
	Field_tree* down = nullptr;
	bool down_check = false;
	Node node_to_check{ 0, 0, 0 };
	bool already_checked = false;


	Field_tree();
	void Find_first_node();
	bool Find_next_node(bool found_node);
	bool check_solution();
	void find_initial_solutions();
};

Field::Field(vector<string> field_string)
{
	generate_field(field_string);
	find_all_neighbours();
}

Field::Field()
{

}




void Field_tree::find_initial_solutions()
{
	Field temp_field = value;
	for (vector<Node> node_v : temp_field.my_node)
	{
		for (Node this_node : node_v)
		{
			if (this_node.number_of_neighbours == 1)
			{
				value.my_node[this_node.y][this_node.x].link_to_only_neighbour(value);
			}
			//else if (this_node.number_of_neighbours*2 == this_node.no_req_links)
			else if (this_node.no_req_links > 0 && (this_node.number_of_neighbours*2 == this_node.no_req_links))
			{
				value.my_node[this_node.y][this_node.x].link_to_all_neighbours(value);
			}
			//if ((value.my_node[this_node.y][this_node.x].number_of_neighbours -
			//value.my_node[this_node.y][this_node.x].unique_links()) == 1)
			//{
            //    value.my_node[this_node.y][this_node.x].try_linking(value);
			//}
			
		}
	}

}



void Node::try_linking (Field &my_field)
{
	//cerr << &my_field << endl;
	if (bool_neighbour_down)
	{
		if (link_possible(neighbour_down, my_field))
		{
			linking(neighbour_down, my_field);
			if (no_links < no_req_links)
			{
				link_to_only_neighbour(my_field);
			}
		}
	}
	if (bool_neighbour_up)
	{
		if (link_possible(neighbour_up, my_field))
		{
			linking(neighbour_up, my_field);
			if (no_links < no_req_links)
			{
				link_to_only_neighbour(my_field);
			}
		}
		return;
	}
	if (bool_neighbour_right)
	{
		if (link_possible(neighbour_right, my_field))
		{
			linking(neighbour_right, my_field);
			if (no_links < no_req_links)
			{
				link_to_only_neighbour(my_field);
			}
		}
		return;
	}
	if (bool_neighbour_left)
	{
		if (link_possible(neighbour_left, my_field))
		{
			linking(neighbour_left, my_field);
			if (no_links < no_req_links)
			{
				link_to_only_neighbour(my_field);
			}
		}
	}
}


void Node:: link_to_only_neighbour(Field &my_field)
{
	if (bool_neighbour_down)
	{
		if (link_possible(neighbour_down, my_field))
		{
			linking(neighbour_down, my_field);
				if (no_links < no_req_links)
				{
					link_to_only_neighbour(my_field);
				}
		}
		return;
	}
	else if (bool_neighbour_up)
	{
		if (link_possible(neighbour_up, my_field))
		{
			linking(neighbour_up, my_field);
			if (no_links < no_req_links)
			{
				link_to_only_neighbour(my_field);
			}
		}
		return;
	}
	else if (bool_neighbour_right)
	{
		if (link_possible(neighbour_right, my_field))
		{
			linking(neighbour_right, my_field);
			if (no_links < no_req_links)
			{
				link_to_only_neighbour(my_field);
			}
		}
		return;
	}
	else if (bool_neighbour_left)
	{
		if (link_possible(neighbour_left, my_field))
		{
			linking(neighbour_left, my_field);
			if (no_links < no_req_links)
			{
				link_to_only_neighbour(my_field);
			}
		}
		return;
	}
}

int Node::unique_links()
{
	int val = (link_down_no > 1) ? 1 : 0;
	int val1 = (link_up_no > 1) ? 1 : 0;
	int val2 = (link_left_no > 1) ? 1 : 0;
	int val3 = (link_right_no > 1) ? 1 : 0;

	return (val + val1 + val2 + val3);
}

void Field::generate_field(vector<string> field_string)
{
	//generates the field given the input strings

	int y = 0;
	int x = 0;
	int req_links = 0;



	for (string x_string : field_string)
	{
		x = 0;
		vector<Node> x_vector = {};
		for (char c : x_string)
		{

			switch (c)
			{
			case '.':
				req_links = 0;
				break;
			case '1':
				req_links = 1;
				break;
			case '2':
				req_links = 2;
				break;
			case '3':
				req_links = 3;
				break;
			case '4':
				req_links = 4;
				break;
			case '5':
				req_links = 5;
				break;
			case '6':
				req_links = 6;
				break;
			case '7':
				req_links = 7;
				break;
			case '8':
				req_links = 8;
				break;
			default:
				req_links = 9;
				break;
			}
			Node temp_node(x, y, req_links);
			if (req_links > 0)
			{
			    this->nodes_to_check.Enqueue(temp_node);
			}
			x_vector.push_back(temp_node);
			++x;
		}
		my_node.push_back(x_vector);
		++y;
	}
}

void Field::is_solution()
{
	//check if solution to the problem has been found
	for (vector<Node> x_vector : my_node)
	{
		for (Node my_node : x_vector)
		{
			if (not(my_node.check_saturated()))
			{

				is_solution_val = false;
				return;
			}
		}
	}
}

void Field::find_all_neighbours()
{
	for (int y = 0; y < my_node.size(); ++y)
		for (int x = 0; x < my_node[0].size(); ++x)
		{
			if (my_node[y][x].is_node())
			{
				find_neighbours(x, y);
			}
		}
}

void Field::find_neighbours(int x, int y)
{
	int max_y = my_node.size() - 1;
	int max_x = my_node[0].size() - 1;
	
	if (my_node[y][x].number_of_neighbours > 0)
	{
		my_node[y][x].number_of_neighbours = 0;
	}

	for (int y_check = y + 1; y_check <= max_y; ++y_check)
	{
		Node node_test = my_node[y_check][x];
		if (node_test.is_node())
		{
			my_node[y][x].neighbour_down = &my_node[y_check][x];
			my_node[y][x].bool_neighbour_down = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}
	for (int y_check = y - 1; y_check >= 0; --y_check)
	{
		Node node_test = my_node[y_check][x];
		if (node_test.is_node())
		{
			my_node[y][x].neighbour_up = &my_node[y_check][x];
			my_node[y][x].bool_neighbour_up = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}
	for (int x_check = x + 1; x_check <= max_x; ++x_check)
	{
		Node node_test = my_node[y][x_check];
		if (node_test.is_node())
		{
			my_node[y][x].neighbour_right = &my_node[y][x_check];
			my_node[y][x].bool_neighbour_right = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}
	for (int x_check = x - 1; x_check >= 0; --x_check)
	{
		Node node_test = my_node[y][x_check];
		if (node_test.is_node())
		{
			my_node[y][x].neighbour_left = &my_node[y][x_check];
			my_node[y][x].bool_neighbour_left = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}
	
}

Field_tree::Field_tree()
{

}

void Node::link_to_all_neighbours(Field &my_field)

{
	if (bool_neighbour_down)
	{
		if (link_possible(neighbour_down, my_field))
		{
			linking(neighbour_down, my_field);
			linking(neighbour_down, my_field);
		}
	}
	if (bool_neighbour_up)
	{
		if (link_possible(neighbour_up, my_field))
		{
			linking(neighbour_up, my_field);
			linking(neighbour_up, my_field);
		}
	}
	if (bool_neighbour_right)
	{
		if (link_possible(neighbour_right, my_field))
		{
			linking(neighbour_right, my_field);
			linking(neighbour_right, my_field);
		}
	}
	if (bool_neighbour_left)
	{
		if (link_possible(neighbour_left, my_field))
		{
			linking(neighbour_left, my_field);
			linking(neighbour_left, my_field);
		}
	}
}


void Field_tree::Find_first_node()
{
	for (int y = 0; y < value.my_node.size(); ++y)
	{
		for (int x = 0; x < value.my_node[y].size(); ++x)
		{
			if (value.my_node[y][x].is_node())
			{
				node_to_check.x = x;
				node_to_check.y = y;
				return;
			}
		}
	}
}

bool Field_tree::Find_next_node(bool found_node)
{
	int x = node_to_check.x;
	int y = node_to_check.y;

	if (node_to_check.x < value.my_node[node_to_check.y].size() - 1 && (value.my_node[y][x].check_saturated() || (value.my_node[y][x].no_links == 0)) && not(found_node))
	{
		node_to_check.x += 1;
		x += 1;
		
		if (not(value.my_node[y][x].check_saturated()) && (value.my_node[y][x].no_links > 0) && (value.my_node[y][x].no_links < value.my_node[y][x].no_req_links))
		{
			return true;
		}
		else
		{
			return Find_next_node(false);
		}
	}
	else if (node_to_check.y < value.my_node.size() - 1 && not(found_node) && (value.my_node[y][x].check_saturated() || (value.my_node[y][x].no_links == 0)))
	{
		node_to_check.x = 0;
		x = 0;
		node_to_check.y += 1;
		y += 1;

		if (not(value.my_node[y][x].check_saturated()) && (value.my_node[y][x].no_links > 0) && (value.my_node[y][x].no_links < value.my_node[y][x].no_req_links))
		{
			return true;
		}
		else
		{
			return Find_next_node(false);
		}
	}
	else if (not(found_node) && (value.my_node[y][x].check_saturated()) && not(already_checked))
	{
		node_to_check.x = 0;
		x = 0;
		node_to_check.y = 0;
		y = 0;
		already_checked = true;
		return Find_next_node(false);
	}
	else
	{
		if (found_node)
		{
			return true;
		}
		already_checked = false;
		possible_sol = false;
		return true;
	}

	return false;
}

bool Field_tree::check_solution()
{
	Field temp_field = value;
	for (vector<Node> node_v : temp_field.my_node)
	{
		for (Node this_node : node_v)
		{
			if (not(this_node.no_links == this_node.no_req_links))
			{
				return false;
			}
			else if(this_node.unique_links_val == 1)
			{
    			if (not(this_node.number_of_neighbours == this_node.unique_links_val))
    		    {
    			    if (this_node.link_up_no > 0)
    			    {
    			        if (this_node.neighbour_up->unique_links_val == 1)
    			        {
    			            return false;
    			        }
    			    }
    			    else if (this_node.link_down_no > 0)
    			    {
    			        if (this_node.neighbour_down->unique_links_val == 1)
    			        {
    			            return false;
    			        }
    			    }			    
    			    else if (this_node.link_left_no > 0)
    			    {
    			        if (this_node.neighbour_left->unique_links_val == 1)
    			        {
    			            return false;
    			        }
    			    }
    		        else if (this_node.link_right_no > 0)
    			    {
    			        if (this_node.neighbour_right->unique_links_val == 1)
    			        {
    			            return false;
    			        }
    			    }
    			}
    		}
		}
	}
	definite_sol = true;
	return true;
}

Node::Node(int xx, int yy, int links_req)
	:x{ xx }, y{ yy }, no_req_links{ links_req }
{
	is_node_val = is_node();
}

bool Node::is_node()
{
	if (no_req_links == 0)
	{
		return false;
	}
	return true;
}

bool Node::check_saturated()
{
	if (no_links == no_req_links)
	{
		return true;
	}
	else if (no_links > no_req_links)
	{
		cerr << "Node " << x << " " << y << " exceeds maximum links" << endl;
	}
	return false;
}

void Node::linking(Node* linking_node, Field &my_field)
{
	++no_links;
	linking_node->no_links += 1;

	if (linking_node == neighbour_up)
	{
	    if (link_up_no == 0)
	    {
	        unique_links_val += 1;
	    }
	    if (linking_node->link_down_no == 0)
	    {
	        linking_node->unique_links_val += 1;
	    }
		link_up = linking_node;
		++link_up_no;
		linking_node->link_down_no += 1;
		linking_node->link_down = this;

		int current_x = x;
		int current_y = y - 1;

		while (current_y > linking_node->y)
		{
			my_field.my_node[current_y][current_x].link_in_use = true;
			--current_y;
		}
	}
	if (linking_node == neighbour_down)
	{
		link_down = linking_node;
		if (link_down_no == 0)
	    {
	        unique_links_val += 1;
	    }
	    if (linking_node->link_up_no == 0)
	    {
	        linking_node->unique_links_val += 1;
	    }
		++link_down_no;
		linking_node->link_up_no += 1;
		linking_node->link_up = this;

		int current_x = x;
		int current_y = y + 1;

		while (current_y < linking_node->y)
		{
			
			my_field.my_node[current_y][current_x].link_in_use = true;
			++current_y;
		}
	}
	if (linking_node == neighbour_right)
	{
		link_right = linking_node;
	    if (link_right_no == 0)
	    {
	        unique_links_val += 1;
	    }
	    if (linking_node->link_left_no == 0)
	    {
	        linking_node->unique_links_val += 1;
	    }
		++link_right_no;
		linking_node->link_left_no += 1;
		linking_node->link_left = this;

		int current_x = x + 1;
		int current_y = y;

		while (current_x < linking_node->x)
		{
			my_field.my_node[current_y][current_x].link_in_use = true;
			++current_x;
		}
	}
	if (linking_node == neighbour_left)
	{
		link_left = linking_node;
		if (link_left_no == 0)
	    {
	        unique_links_val += 1;
	    }
	    if (linking_node->link_right_no == 0)
	    {
	        linking_node->unique_links_val += 1;
	    }
		++link_left_no;
		linking_node->link_right_no += 1;
		linking_node->link_right = this;

		int current_x = x - 1;
		int current_y = y;

		while (current_x > linking_node->x)
		{
			my_field.my_node[current_y][current_x].link_in_use = true;
			--current_x;
		}
	}

}
bool Node::link_possible(Node* linking_node, Field my_field)
{

	if (not(linking_node == neighbour_up) && not(linking_node == neighbour_down)
		&& not(linking_node == neighbour_left) && not(linking_node == neighbour_right))
	{
		return false;
	}

	if (check_saturated() || linking_node->check_saturated()
		|| not(is_node()) || not(linking_node->is_node()))
	{
		return false;
	}
	if (linking_node == neighbour_up)
	{
		if (link_up_no >= 2)
		{
			return false;
		}

		int current_x = x;
		int current_y = y - 1;
		if (link_up_no == 0)
		{
			while (current_y > linking_node->y)
			{
				if (my_field.my_node[current_y][current_x].link_in_use)
				{
					return false;
				}
				--current_y;
			}
		}
	} 
	if (linking_node == neighbour_down)
	{
		if (link_down_no >= 2)
		{
			return false;
		}

		int current_x = x;
		int current_y = y + 1;
		if (link_down_no == 0)
		{
			while (current_y < linking_node->y)
			{
				if (my_field.my_node[current_y][current_x].link_in_use)
				{
					return false;
				}
				++current_y;
			}
		}
	}
	if (linking_node == neighbour_right)
	{
		if (link_right_no >= 2)
		{
			return false;
		}

		int current_x = x + 1;
		int current_y = y;

		if (link_right_no == 0)
		{
			while (current_x < linking_node->x)
			{
				if (my_field.my_node[current_y][current_x].link_in_use)
				{
					return false;
				}
				++current_x;
			}
		}
	}
	if (linking_node == neighbour_left)
	{
		if (link_left_no >= 2)
		{
			return false;
		}

		int current_x = x - 1;
		int current_y = y;

		if (link_left_no == 0)
		{
			while (current_x > linking_node->x)
			{
				if (my_field.my_node[current_y][current_x].link_in_use)
				{
					return false;
				}
				--current_x;
			}
		}
	}
	return true;
}

void Node::print()
{
	cout << "Start: " << endl;
	cout << "I am node " << x << " " << y << endl;

	if (not(is_node()))
	{
	cout << "I AM NOT A NODE" << endl;
	cout << "Am I in use? " << link_in_use << endl << endl;
	return;
	}
	cout << "I require: " << no_req_links << " links, and currently have: " << no_links << endl;
	cout << "My neighbours are: " << endl;

	if (neighbour_up)
	{
		cout << "My top neighbour is: " << neighbour_up->x << " " << neighbour_up->y << endl;
		cout << "I am connected to my top neighbour: " << neighbour_up->x << " " << neighbour_up->y << " with " << link_up_no << " links" << endl;
	}
	if (neighbour_down)
	{
		cout << "My bottom neighbour is: " << neighbour_down->x << " " << neighbour_down->y << endl;
		cout << "I am connected to my down neighbour: " << neighbour_down->x << " " << neighbour_down->y << " with " << link_down_no << " links" << endl;
	}
	if (neighbour_left)
	{
		cout << "My left neighbour is: " << neighbour_left->x << " " << neighbour_left->y << endl;
		cout << "I am connected to my left neighbour: " << neighbour_left->x << " " << neighbour_left->y << " with " << link_left_no << " links" << endl;
	}
	if (neighbour_right)
	{
		cout << "My right neighbour is: " << neighbour_right->x << " " << neighbour_right->y << endl;
		cout << "I am connected to my link_right neighbour: " << neighbour_right->x << " " << neighbour_right->y << " with " << link_right_no << " links" << endl;
	}

	cout << "Finish " << endl;
	cout << endl;
}

bool Node::link_nodes(int x2, int y2, Field &field)
{
	if (not(link_possible(&field.my_node[y2][x2], field)))
	{
		return false;
	}
	linking(&field.my_node[y2][x2], field);

	return true;
}

void Node::print2()
{
	if (link_right_no > 0)
	{
		cout << x << " " << y << " "
			<< neighbour_right->x << " " << neighbour_right->y
			<< " " << link_right_no << endl;
	}
	if (link_down_no > 0)
	{
		cout << x << " " << y << " "
			<< neighbour_down->x << " " << neighbour_down->y
			<< " " << link_down_no << endl;
	}
}


Field_tree* backtracking(Field_tree* tree)
{
	if (tree->definite_sol)
	{
		return tree;
	}

	//insert function which tests if current tree is a possible solution
	//if it is not flag it as not a possible solution
	if (tree->check_solution())
	{
		return tree;
	}

	if (not(tree->possible_sol))
	{
		Field_tree* pointer = tree->parent;
		delete tree;
		return backtracking(pointer);
	}
    
    //Added this
    //tree->node_to_check = tree->value.nodes_to_check.Dequeue();
	
	int x = tree->node_to_check.x;
	int y = tree->node_to_check.y;

	Field field = tree->value;

    //commented out this
    
	if (tree->value.my_node[y][x].check_saturated())
	{	
		tree->Find_next_node(false);
	}
	
	//and added this
	//if (tree->value.my_node[y][x].check_saturated())
	//{	
	//	tree->node_to_check = tree->value.nodes_to_check.Dequeue();
	//}
	

    //cerr << "x is: " << x << " y is: " << y << endl;

	x = tree->node_to_check.x;
	y = tree->node_to_check.y;

	if (tree->left_check == false)
	{
		Node temp_node = tree->value.my_node[tree->node_to_check.y][tree->node_to_check.x];

		if (temp_node.bool_neighbour_left)
		{
			if (temp_node.link_possible(temp_node.neighbour_left, field))
			{
				Field_tree* new_tree = new Field_tree;
				new_tree->value = tree->value;
				new_tree->parent = tree;
				tree->left = new_tree;
				new_tree->node_to_check = tree->node_to_check;
				new_tree->value.find_all_neighbours();
				new_tree->value.my_node[y][x].linking(new_tree->value.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_left, new_tree->value);
				tree->left_check = true;
				return backtracking(new_tree);
			}
		}
		tree->left_check = true;
	}
	else if (tree->right_check == false)
	{
		Node temp_node = tree->value.my_node[tree->node_to_check.y][tree->node_to_check.x];

		if (temp_node.bool_neighbour_right)
		{
			if (temp_node.link_possible(temp_node.neighbour_right, field))
			{
				Field_tree* new_tree = new Field_tree;
				new_tree->value = tree->value;
				new_tree->parent = tree;
				tree->right = new_tree;
				new_tree->node_to_check = tree->node_to_check;
				new_tree->value.find_all_neighbours();
				new_tree->value.my_node[y][x].linking(new_tree->value.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_right, new_tree->value);
				tree->right_check = true;
				return backtracking(new_tree);
			}
		}
		tree->right_check = true;
	}
	else if (tree->up_check == false)
	{
		Node temp_node = tree->value.my_node[tree->node_to_check.y][tree->node_to_check.x];

		if (temp_node.bool_neighbour_up)
		{
			if (temp_node.link_possible(temp_node.neighbour_up, field))
			{
				Field_tree* new_tree = new Field_tree;
				new_tree->value = tree->value;
				new_tree->parent = tree;
				tree->up = new_tree;
				new_tree->node_to_check = tree->node_to_check;
				new_tree->value.find_all_neighbours();
				new_tree->value.my_node[y][x].linking(new_tree->value.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_up, new_tree->value);
				tree->up_check = true;
				return backtracking(new_tree);
			}
		}
		tree->up_check = true;
	}
	else if (tree->down_check == false)
	{
		Node temp_node = tree->value.my_node[tree->node_to_check.y][tree->node_to_check.x];

		if (temp_node.bool_neighbour_down)
		{
			if (temp_node.link_possible(temp_node.neighbour_down, field))
			{
				Field_tree* new_tree = new Field_tree;
				new_tree->value = tree->value;
				new_tree->parent = tree;
				tree->down = new_tree;
				new_tree->node_to_check = tree->node_to_check;
				new_tree->value.find_all_neighbours();
				new_tree->value.my_node[y][x].linking(new_tree->value.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_down, new_tree->value);
				tree->down_check = true;
				return backtracking(new_tree);
			}
		}
		tree->down_check = true;
	}
	else
	{
		tree->possible_sol = false;
		//delete tree->left;
		//delete tree->right;
		//delete tree->up;
		//delete tree->down;

	}

	return backtracking(tree);
}

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    vector<string> field_v{};
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line); // width characters, each either a number or a '.'
        field_v.push_back(line);
    }

    Field first_field(field_v);

	Field_tree* tree = new Field_tree;
	tree->value = first_field;
	tree->value.find_all_neighbours();
	tree->Find_first_node();
	tree->find_initial_solutions();
	
	Field_tree* answer = backtracking(tree);

	for (int y = 0; y < answer->value.my_node.size(); ++y)
	{
		for (int x = 0; x < answer->value.my_node[y].size(); ++x)
		{
			answer->value.my_node[y][x].print2();
		}
	}    
}
