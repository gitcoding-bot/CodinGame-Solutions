#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

//Declare classes
class Node;
class Grid;
class Tree;


////////////////////////////////////////////////////////////////////////////////////////

//Class definitions

////////////////////////////////////////////////////////////////////////////////////////

class Node
{
	//class to represent each node
	//Every x and y coordinate will be represented by the Node class 

	//If the class variable is_node_val == false it is actually not a node and none of the other
	//variables and member functions apply, but the existence of that specific object
	//is still necessary since it is used to determine whether links from other nodes cross

public:
	int x = -1; //x coordinate
	int y = -1; //y coordinate
	int no_links = 0; //total number of current links (maximum 8)
	int no_unique_links = 0; //Number of unique links to neighbours (maximum of 4)
	int no_req_links; //number of links required (maximum 8)
	bool is_node_val; //True if coordinate (X,y) is node, false if not

	//True if a link between two nodes occupy these coordinates, false if not
	bool link_in_use = false; //Only applicable when class is not a node


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

	//number of links to neighbours
	int link_up_no = 0;
	int link_down_no = 0;
	int link_left_no = 0;
	int link_right_no = 0;

	Node(int xx, int yy, int zz);
	bool link_possible_check(Node* linking_node, Grid &my_field); //Check if it is possible to link the two nodes
	void linking(Node* linking_node, Grid &my_field); //Links two nodes
	bool check_saturated(); //Check if no_req_links == no_links
	bool is_node();

	//heuristics
	bool heuristic_one(Grid &my_field);
	bool heuristic_two(Grid &my_field);
	bool heuristic_three(Grid &my_field);

	bool heuristic_one_test(Grid &my_field);
	bool check_neighbours_isolated();
	int number_of_neighbours_not_isolated();

	//print answer
	void print_answer();
	void print();
};

Node::Node(int xx, int yy, int links_req)
	:x{ xx }, y{ yy }, no_req_links{ links_req }
	//Initialise Node class with x and y coordinates and the number of links required
{
	is_node_val = is_node(); //Check if coordinates represents a valid node
}


class Grid
{
public:
	vector<vector<Node>> my_node = {}; //Contains all the nodes and not nodes
	vector<Node> nodes_to_check = {}; //Contains only the actual nodes
	
	bool is_solution_val = true; //
	int number_of_nodes = 0;
	int number_of_nodes_saturated = 0;

	Grid(vector<string> field_string);
	Grid();
	void generate_grid(vector<string> field_string); //generates the Grid given the input strings
	void find_neighbouring_nodes(); //Find the neighbours of all nodes
	void is_solution(); //Check if current grid is a viable solution to problem

private:
	void find_neighbours(int x, int y);
};

Grid::Grid(vector<string> field_string)
{
	generate_grid(field_string); //generates the Grid given the input strings
	find_neighbouring_nodes(); //Find the neighbours of all nodes
}

Grid::Grid()
{

}

class Tree
{
public:
	Grid grid;
	bool possible_sol = true; //Is the current grid still a possible solution
	bool definite_sol = false; //Is the current grid a definite solution
	bool made_change = true;
	bool first_node = false;

	Tree* parent = nullptr;

	Tree* left = nullptr;
	bool left_check = false;

	Tree* right = nullptr;
	bool right_check = false;

	Tree* up = nullptr;
	bool up_check = false;

	Tree* down = nullptr;
	bool down_check = false;

	Node node_to_check{ 0, 0, 0 };
	bool already_checked = false;

	Tree();
	bool implement_heuristics();
	bool check_solution(Node* current_node, int no_nodes_checked, vector<Node*> nodes_checked, queue<Node*> nodes_to_check);

};

Tree::Tree()
{

}


////////////////////////////////////////////////////////////////////////////////////////

//NODE CLASS MEMBER FUNCTIONS

////////////////////////////////////////////////////////////////////////////////////////


bool Node::check_saturated()
{
	//Check if node is saturated (in other words can't link to any other nodes anymore)
	if (no_links == no_req_links) // Node is saturated if number of links equals number of required links
	{
		return true;
	}
	return false;
}

bool Node::is_node()
{
	//checks if coordinates represent a node
	if (no_req_links == 0) //if it requires no links it is not a node
	{
		return false;
	}
	return true;
}


bool Node::check_neighbours_isolated()
{
	//Can only link to neighbours who need more than 1 link if current node only needs 1 link

	if (not(is_node()) || (no_req_links - no_links) > 1)
	{
		return false;
	}

	int cnt = 0;
	if (bool_neighbour_up)
	{
		if (neighbour_up->no_req_links > 1)
		{
			++cnt;
		}
	}
	if (bool_neighbour_down)
	{
		if (neighbour_down->no_req_links > 1)
		{
			++cnt;
		}
	}
	if (bool_neighbour_left)
	{
		if (neighbour_left->no_req_links > 1)
		{
			++cnt;
		}
	}
	if (bool_neighbour_right)
	{
		if (neighbour_right->no_req_links > 1)
		{
			++cnt;
		}
	}

	if (cnt > 1)
	{
		return false;
	}

	return true;

}


bool Node::link_possible_check(Node* linking_node, Grid &my_field)
{
	//checks if link between two nodes are possible
	//Returns true if it is and false if not

	int no_links_node1 = -1;
	int inc_x = 0;
	int inc_y = 0;

	//Check if "linking node" is actually a neighbour
	if (linking_node == neighbour_up)
	{
		no_links_node1 = link_up_no;
		inc_x = 0;
		inc_y = -1; //Coordinates (0,0) start at top left, so down is actually + direction and up - direction
	}
	else if (linking_node == neighbour_down)
	{
		no_links_node1 = link_down_no;
		inc_x = 0;
		inc_y = 1; //Coordinates (0,0) start at top left, so down is actually + direction and up - direction
	}
	else if (linking_node == neighbour_left)
	{
		no_links_node1 = link_left_no;
		inc_x = -1;
		inc_y = 0;
	}
	else if (linking_node == neighbour_right)
	{
		no_links_node1 = link_right_no;
		inc_x = 1;
		inc_y = 0;
	}
	else //If it is not a neighbour it can't link to it
	{
		return false;
	}

	//Check if both nodes have 1 maximum link possible, can't link to one another
	if (no_req_links == 1 && linking_node->no_req_links == 1 && not(number_of_neighbours == 1 && linking_node->number_of_neighbours == 1))
	{
		return false;
	}

	//Check if one of the two nodes are saturated
	if (check_saturated() || linking_node->check_saturated()
		|| not(is_node()) || not(linking_node->is_node()))
	{
		return false;
	}

	//If the number of links exceed 2, linking is not possible
	if (no_links_node1 >= 2)
	{
		return false;
	}

	int current_x = x + inc_x;
	int current_y = y + inc_y;

	//Only need to check if links cross the first time a link is created between the same two nodes
	if (no_links_node1 == 0) 
	{

		//Check if links from other connected nodes cross the new link
		while (current_y != linking_node->y || current_x != linking_node->x)
		{
			if (my_field.my_node[current_y][current_x].link_in_use)//If links cross, linking is not possible
			{
				return false;
			}
			current_x = current_x + inc_x;
			current_y = current_y + inc_y;
		}
	}
	
	return true;
}


void Node::linking(Node* linking_node, Grid &my_field)
{
	//Need to update the number of links for both nodes
	++no_links;
	linking_node->no_links += 1;

	if (this->check_saturated())
	{
		++my_field.number_of_nodes_saturated;
	}
	if (linking_node->check_saturated())
	{
		++my_field.number_of_nodes_saturated;
	}

	int* no_links_node1 = nullptr;
	int* no_links_node2 = nullptr;
	int inc_x = 0;
	int inc_y = 0;

	//Assign variables based on which neighour it connects to
	if (linking_node == neighbour_up)
	{
		no_links_node1 = &link_up_no;
		no_links_node2 = &linking_node->link_down_no; //The link direction for the other node is the opposite

		inc_x = 0;
		inc_y = -1; //Coordinates (0,0) start at top left, so down is actually + direction and up - direction
	}
	else if (linking_node == neighbour_down)
	{
		no_links_node1 = &link_down_no;
		no_links_node2 = &linking_node->link_up_no; //The link direction for the other node is the opposite
		inc_x = 0;
		inc_y = 1; //Coordinates (0,0) start at top left, so down is actually + direction and up - direction
	}
	else if (linking_node == neighbour_left)
	{
		no_links_node1 = &link_left_no;
		no_links_node2 = &linking_node->link_right_no; //The link direction for the other node is the opposite

		inc_x = -1;
		inc_y = 0;
	}
	else if (linking_node == neighbour_right)
	{
		no_links_node1 = &link_right_no;
		no_links_node2 = &linking_node->link_left_no; //The link direction for the other node is the opposite

		inc_x = 1;
		inc_y = 0;
	}

	//Check if it has a link to this node
	if (*no_links_node1 == 0)
	{
		no_unique_links += 1; //If no link exists for node 1, increment number of unique links
		linking_node->no_unique_links += 1; //If no link exists for node 2, increment number of unique links
	}

	//Increment the number of links in the applicable direction for both nodes
	++*no_links_node1;
	++*no_links_node2;

	int current_x = x + inc_x;
	int current_y = y + inc_y;

	//Flag all applicable coordinates as containing a link to avoid crossing links
	while (current_y != linking_node->y || current_x != linking_node->x)
	{
		my_field.my_node[current_y][current_x].link_in_use = true;
		
		//Increment movement
		current_x = current_x + inc_x;
		current_y = current_y + inc_y;
	}

}


void Node::print_answer()
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


bool Node::heuristic_one(Grid &my_field)

	//Heuristic one: If an unsaturated node can only connect to one other node
	//it has to connect to that node for a valid solution.
	//It connects to that node once if it requires one link and
	//twice if it requires two links.
{

	if (bool_neighbour_down
		&& (link_down_no < 2 && not(neighbour_down->check_saturated())))
	{
		if (link_possible_check(neighbour_down, my_field))
		{
			linking(neighbour_down, my_field);
			if (no_links < no_req_links && link_possible_check(neighbour_down, my_field))
			{
				linking(neighbour_down, my_field);
				return true;
			}
			return true;
		}
	}
	if (bool_neighbour_up
		&& (link_up_no < 2 && not(neighbour_up->check_saturated())))
	{
		if (link_possible_check(neighbour_up, my_field))
		{
			linking(neighbour_up, my_field);
			if (no_links < no_req_links && link_possible_check(neighbour_up, my_field))
			{
				linking(neighbour_up, my_field);
				return true;
			}
			return true;
		}
	}
	if (bool_neighbour_right
		&& (link_right_no < 2 && not(neighbour_right->check_saturated())))
	{
		if (link_possible_check(neighbour_right, my_field))
		{
			linking(neighbour_right, my_field);
			if (no_links < no_req_links && link_possible_check(neighbour_right, my_field))
			{
				linking(neighbour_right, my_field);
				return true;
			}
			return true;
		}
	}
	if (bool_neighbour_left
		&& (link_left_no < 2 && not(neighbour_left->check_saturated())))
	{
		if (link_possible_check(neighbour_left, my_field))
		{
			linking(neighbour_left, my_field);
			if (no_links < no_req_links && link_possible_check(neighbour_left, my_field))
			{
				linking(neighbour_left, my_field);
				return true;
			}
			return true;
		}
	}
	return false;
}

bool Node::heuristic_two(Grid &my_field)

{

	bool made_change = false;
	if (bool_neighbour_down)
	{
		if (link_possible_check(neighbour_down, my_field) && link_down_no == 0)
		{
			linking(neighbour_down, my_field);
			linking(neighbour_down, my_field);
			made_change = true;
		}
		
	}
	if (bool_neighbour_up)
	{
		if (link_possible_check(neighbour_up, my_field) && link_up_no == 0)
		{
			linking(neighbour_up, my_field);
			linking(neighbour_up, my_field);
			made_change = true;
		}
	}
	if (bool_neighbour_right)
	{
		if (link_possible_check(neighbour_right, my_field) && link_right_no == 0)
		{
			linking(neighbour_right, my_field);
			linking(neighbour_right, my_field);
			made_change = true;
		}
	}
	if (bool_neighbour_left)
	{
		if (link_possible_check(neighbour_left, my_field) && link_left_no == 0)
		{
			linking(neighbour_left, my_field);
			linking(neighbour_left, my_field);
			made_change = true;
		}
	}

	return made_change;
}

bool Node::heuristic_three(Grid &my_field)
{
	//Heuristic three: A node that requires just 1 link and has only 1 neighbour that
	//requires more than one link needs to connect to that neighbour for a valid solution,
	//since it can't connect to other neigbours that also just require 1 link. This will cause
	//isolation.

	bool made_change = false; //Can only link once

	//Check for the existence of a neighbour above 
	//and if link to another neighbour has already been made

	if (bool_neighbour_up && not(made_change)) 
	{
		if (neighbour_up->no_req_links > 1) //Check how many links the neighbour requires
		{
			if (link_possible_check(neighbour_up, my_field))
			{
				//If link is possible, link the two nodes and flag a change as being made
				linking(neighbour_up, my_field);
				made_change = true;
			}
			else
			{
				return false;
			}
		}
	}

	//Check for the existence of a neighbour below 
	//and if link to another neighbour has already been made
	if (bool_neighbour_down && not(made_change))
	{
		if (neighbour_down->no_req_links > 1) //Check how many links the neighbour requires
		{
			if (link_possible_check(neighbour_down, my_field))
			{
				//If link is possible, link the two nodes and flag a change as being made
				linking(neighbour_down, my_field);
				made_change = true;
			}
			else
			{
				return false;
			}
		}
	}

	//Check for the existence of a neighbour to the left 
	//and if link to another neighbour has already been made
	if (bool_neighbour_left && not(made_change))
	{
		if (neighbour_left->no_req_links > 1) //Check how many links the neighbour requires
		{
			if (link_possible_check(neighbour_left, my_field))
			{
				//If link is possible, link the two nodes and flag a change as being made
				linking(neighbour_left, my_field);
				made_change = true;
			}
			else
			{
				return false;
			}
		}
	}
	//Check for the existence of a neighbour to the right 
	//and if link to another neighbour has already been made
	if (bool_neighbour_right && not(made_change))
	{
		if (neighbour_right->no_req_links > 1) //Check how many links the neighbour requires
		{
			if (link_possible_check(neighbour_right, my_field))
			{
				//If link is possible, link the two nodes and flag a change as being made
				linking(neighbour_right, my_field);
				made_change = true;
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

bool Node::heuristic_one_test(Grid &my_field)
{

	//Heuristic one: If an unsaturated node can only connect to one other node
	//it has to connect to that node for a valid solution.
	//It connects to that node once if it requires one link and
	//twice if it requires two links.

	int no_unique_links_possible = 0; //Counts the number of unique links to neighbours

	if (bool_neighbour_up) //Check for the existence of a neighbour above
	{
		if (link_possible_check(neighbour_up, my_field)) //Check if link to neighbour is possible
		{
			++no_unique_links_possible;
		}
	}

	if (bool_neighbour_down) //Check for the existence of a neighbour below
	{
		if (link_possible_check(neighbour_down, my_field)) //Check if link to neighbour is possible
		{
			++no_unique_links_possible;
		}
	}

	if (bool_neighbour_left) //Check for the existence of a neighbour to the left
	{
		if (link_possible_check(neighbour_left, my_field)) //Check if link to neighbour is possible
		{
			++no_unique_links_possible;
		}
	}

	if (bool_neighbour_right) //Check for the existence of a neighbour to the right
	{
		if (link_possible_check(neighbour_right, my_field)) //Check if link to neighbour is possible
		{
			++no_unique_links_possible;
		}
	}

	//If node can only link to one neighbour it has to link to that neighbour
	if (no_unique_links_possible == 1)
	{
		return true;
	}

	return false;
}


int Node::number_of_neighbours_not_isolated()
{
	//Heuristic two: If an unsaturated node's number of viable neighbours it
	//can link to equals exactly two times the number of links it requires. It
	//has to link to those neighbours for a valid solution

	int cnt = 0; //Counts the number of neighbours requiring 2 or more links
	int cnt2 = 0; //Counts the number of neighbours requiring exactly 1 more link
	if (bool_neighbour_up) //Check for the existence of a neighbour above
	{
		if ((neighbour_up->no_req_links - neighbour_up->no_links) > 1)
		{
			++cnt;
		}
		else if ((neighbour_up->no_req_links - neighbour_up->no_links) == 1)
		{
			++cnt2;
		}
	}
	if (bool_neighbour_down) //Check for the existence of a neighbour below
	{
		if ((neighbour_down->no_req_links - neighbour_down->no_links) > 1)
		{
			++cnt;
		}
		else if ((neighbour_down->no_req_links - neighbour_down->no_links) == 1)
		{
			++cnt2;
		}
	}
	if (bool_neighbour_left) //Check for the existence of a neighbour to the left
	{
		if ((neighbour_left->no_req_links - neighbour_left->no_links) > 1)
		{
			++cnt;
		}
		else if ((neighbour_left->no_req_links - neighbour_left->no_links) == 1)
		{
			++cnt2;
		}
	}
	if (bool_neighbour_right) //Check for the existence of a neighbour to the right
	{
		if ((neighbour_right->no_req_links - neighbour_right->no_links) > 1)
		{
			++cnt;
		}
		else if ((neighbour_right->no_req_links - neighbour_right->no_links) == 1)
		{
			++cnt2;
		}
	}

	//If the combined number of links the neighbours require (2 per neighbour)
	//equal the number of links the node requires
	//The node needs to link to all applicable neighbours (with two links)
	if (cnt*2 == (no_req_links - no_links) && no_req_links != 2 && cnt2 == 0)
	{
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////

//GRID CLASS MEMBER FUNCTIONS

////////////////////////////////////////////////////////////////////////////////////////


void Grid::generate_grid(vector<string> field_string)
{
	//generates the Grid given the input strings

	int y = 0;
	int x = 0;
	int req_links = 0;

	for (string x_string : field_string)
	{
		x = 0;
		vector<Node> x_vector = {};
		for (char c : x_string)
		{
			//Convert char to integer and create Grid
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
				this->nodes_to_check.push_back(temp_node); //Add all nodes which are actually nodes to vector nodes_to_check
			}
			x_vector.push_back(temp_node); //Create a vector<Node> which contains all nodes for each y coordinate
			++x;
		}
		my_node.push_back(x_vector); //Create a vector<vector<Node>> which contains all nodes for each x & y coordinates
		++y;
	}
}

void Grid::is_solution()
{
	//check if solution to the problem has been found
	for (vector<Node> x_vector : my_node)
	{
		for (Node my_node : x_vector)
		{
			if (not(my_node.check_saturated()))
			{
				is_solution_val = true;
				return;
			}
		}
	}
}


void Grid::find_neighbouring_nodes()
{
	//Find the neighbours of all nodes
	number_of_nodes = (number_of_nodes > 0) ? 0 : number_of_nodes;

	//Check for each x & y coordinate
	for (int y = 0; y < my_node.size(); ++y)
		for (int x = 0; x < my_node[0].size(); ++x)
		{
			if (my_node[y][x].is_node()) //Only need to find neighbours for nodes
			{
				++number_of_nodes; //Increment number of nodes in the grid
				find_neighbours(x, y); //Find the neighbours for this node
			}
		}
}


void Grid::find_neighbours(int x, int y)
{

	//Finds the neighbours for an individual Node with x and y coordinates

	int max_y = my_node.size() - 1; //Max y size of grid
	int max_x = my_node[0].size() - 1; //Max x size of grid

	if (my_node[y][x].number_of_neighbours > 0) //If the current number of neighbours > 0, reset to 0
	{
		my_node[y][x].number_of_neighbours = 0;
	}

	//Check if node has any neighbours below itself
	for (int y_check = y + 1; y_check <= max_y; ++y_check)
	{
		Node node_test = my_node[y_check][x];
		if (node_test.is_node()) //Neighbour also has to be a node
		{
			my_node[y][x].neighbour_down = &my_node[y_check][x];
			my_node[y][x].bool_neighbour_down = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}

	//Check if node has any neighbours above itself
	for (int y_check = y - 1; y_check >= 0; --y_check)
	{
		Node node_test = my_node[y_check][x];
		if (node_test.is_node()) //Neighbour also has to be a node
		{
			my_node[y][x].neighbour_up = &my_node[y_check][x];
			my_node[y][x].bool_neighbour_up = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}

	//Check if node has any neighbours to the right of itself
	for (int x_check = x + 1; x_check <= max_x; ++x_check)
	{
		Node node_test = my_node[y][x_check];
		if (node_test.is_node()) //Neighbour also has to be a node
		{
			my_node[y][x].neighbour_right = &my_node[y][x_check];
			my_node[y][x].bool_neighbour_right = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}

	//Check if node has any neighbours to the left of itself
	for (int x_check = x - 1; x_check >= 0; --x_check)
	{
		Node node_test = my_node[y][x_check];
		if (node_test.is_node()) //Neighbour also has to be a node
		{
			my_node[y][x].neighbour_left = &my_node[y][x_check];
			my_node[y][x].bool_neighbour_left = true;
			my_node[y][x].number_of_neighbours += 1;
			break;
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////

//TREE CLASS MEMBER FUNCTIONS

////////////////////////////////////////////////////////////////////////////////////////

bool Tree::check_solution(Node* current_node, int no_nodes_checked, vector<Node*> nodes_checked, queue<Node*> nodes_to_check)
{
	//Check if no of current links are equal to no of required links
	if (not(current_node->no_links == current_node->no_req_links))
	{
		return false; //If it is not then this is not a solution
	}
	else
	{
		//If current node has a neighbour above it and it is linked to that neighbour add neighbour to nodes_to_check queue
		if (current_node->bool_neighbour_up && current_node->link_up_no > 0) 
		{
			bool node_checked = false;
			for (Node* this_node : nodes_checked) // Has this node been checked before
			{
				if (this_node->x == current_node->neighbour_up->x && 
					this_node->y == current_node->neighbour_up->y) //Check if x and y coordinates match
				{
					node_checked = true; //If the x and y coordinates match a node in the nodes_checked vector, then this node has been checked
					break;
				}
			}

			if (node_checked == false)
			{
				nodes_to_check.push(current_node->neighbour_up);
				nodes_checked.push_back(current_node->neighbour_up);
			}
		}

		//If current node has a neighbour below it and it is linked to that neighbour add neighbour to nodes_to_check queue
		if (current_node->bool_neighbour_down && current_node->link_down_no > 0)
		{
			bool node_checked = false;
			for (Node* this_node : nodes_checked) // Has this node been checked before
			{
				if (this_node->x == current_node->neighbour_down->x &&
					this_node->y == current_node->neighbour_down->y) //Check if x and y coordinates match
				{
					node_checked = true; //If the x and y coordinates match a node in the nodes_checked vector, then this node has been checked
					break;
				}
			}

			if (node_checked == false)
			{
				nodes_to_check.push(current_node->neighbour_down);
				nodes_checked.push_back(current_node->neighbour_down);
			}
		}

		//If current node has a neighbour left of it and it is linked to that neighbour add neighbour to nodes_to_check queue
		if (current_node->bool_neighbour_left && current_node->link_left_no > 0)
		{
			bool node_checked = false;
			for (Node* this_node : nodes_checked) // Has this node been checked before
			{
				if (this_node->x == current_node->neighbour_left->x && 
					this_node->y == current_node->neighbour_left->y) //Check if x and y coordinates match
				{
					node_checked = true; //If the x and y coordinates match a node in the nodes_checked vector, then this node has been checked
					break;
				}
			}

			if (node_checked == false)
			{
				nodes_to_check.push(current_node->neighbour_left);
				nodes_checked.push_back(current_node->neighbour_left);
			}
		}

		//If current node has a neighbour right of it and it is linked to that neighbour add neighbour to nodes_to_check queue
		if (current_node->bool_neighbour_right && current_node->link_right_no > 0)
		{
			bool node_checked = false;
			for (Node* this_node : nodes_checked) // Has this node been checked before
			{
				if (this_node->x == current_node->neighbour_right->x &&
					this_node->y == current_node->neighbour_right->y) //Check if x and y coordinates match
				{
					node_checked = true; //If the x and y coordinates match a node in the nodes_checked vector, then this node has been checked
					break;
				}
			}

			if (node_checked == false)
			{
				nodes_to_check.push(current_node->neighbour_right);
				nodes_checked.push_back(current_node->neighbour_right);
			}
		}

		if (nodes_to_check.size() > 0)
		{
			Node* next_node_to_check = nodes_to_check.front(); //Find next node to check
			nodes_to_check.pop(); //Remove from queue
			return check_solution(next_node_to_check, ++no_nodes_checked, nodes_checked, nodes_to_check);
		}
	}

	if (not(no_nodes_checked == grid.number_of_nodes))
	{
		return false;
	}

	definite_sol = true;
	return true;
}

bool Tree::implement_heuristics()
{
	bool found_change = false;
	bool found_change_temp = false;

	for (vector<Node> node_v : grid.my_node)
	{
		for (Node this_node : node_v)
		{

			if (this_node.is_node() && not(grid.my_node[this_node.y][this_node.x].check_saturated()))
			{
				if (grid.my_node[this_node.y][this_node.x].heuristic_one_test(grid))
				{
					//Heuristic one: If an unsaturated node can only connect to one other node
					//it has to connect to that node for a valid solution.
					//It connects to that node once if it requires one link and
					//twice if it requires two links.
					found_change_temp = grid.my_node[this_node.y][this_node.x].heuristic_one(grid);
				}
				else if (this_node.no_req_links > 0
					&& (this_node.number_of_neighbours * 2 == this_node.no_req_links
						|| grid.my_node[this_node.y][this_node.x].number_of_neighbours_not_isolated()))
				{
					//Heuristic two: If an unsaturated node's number of viable neighbours it
					//can link to equals exactly two times the number of links it requires. It
					//has to link to those neighbours for a valid solution

					found_change_temp = grid.my_node[this_node.y][this_node.x].heuristic_two(grid);
				}
				else if (grid.my_node[this_node.y][this_node.x].check_neighbours_isolated())
				{
					//Heuristic three: A node that requires just 1 link and has only 1 neighbour that
					//requires more than one link needs to connect to that neighbour for a valid solution,
					//since it can't connect to other neigbours that also just require 1 link. This will cause
					//isolation.
					found_change_temp = grid.my_node[this_node.y][this_node.x].heuristic_three(grid);
				}
				if (found_change_temp)
				{
					found_change = true;
				}
			}

		}
	}

	return found_change;
}


Tree* backtracking(Tree* tree)
{
	//If solution has already been found don't continue with algorithm return solution
	if (tree->definite_sol)
	{
		return tree;
	}

	//If it is not a possible solution backtrack
	if (not(tree->possible_sol))
	{
		Tree* pointer = tree->parent;
		delete tree;
		return backtracking(pointer);
	}

	//Check if solution has been found
	int node_counter = 0;
	vector<Node*> nodes_checked;
	queue<Node*> nodes_to_check;
	
	//Number of nodes check must = number of nodes for solution to be valid
	if (tree->grid.number_of_nodes_saturated == tree->grid.number_of_nodes) 
	{
		//Find first node to check
		Node* next_node_to_check = &tree->grid.my_node[tree->grid.nodes_to_check[0].y][tree->grid.nodes_to_check[0].x];
		nodes_checked.push_back(next_node_to_check);

		//Check if solution satisfies all conditions
		if (tree->check_solution(next_node_to_check, 1, nodes_checked, nodes_to_check))
		{
			return tree;
		}
	}

	
	//Next node to check
	int x = tree->node_to_check.x;
	int y = tree->node_to_check.y;
	
	
	bool test1 = false; //Check if heuristics were implemented
	bool heuristic_change = true; //Check if heuristics were implemented
	while (heuristic_change && 	tree->made_change) //Check if heuristics were implemented, if so, check for changes again
	{
		heuristic_change = tree->implement_heuristics();
		if (heuristic_change)
		{
			test1 = true;
		}
	}
	
	if (test1) //If any changes were implemented go back to start, since it must check if solution has been found
	{
		return backtracking(tree);
	}
	
	//Reset made changes back to false
	tree->made_change = false;

	//If node to check is saturated find new node to check
	Grid field = tree->grid;
	if (tree->grid.my_node[y][x].check_saturated())
	{
		for (Node next_node : tree->grid.nodes_to_check)
		{
			if (not(tree->grid.my_node[next_node.y][next_node.x].check_saturated())
				&& (tree->grid.my_node[next_node.y][next_node.x].no_links > 0 || tree->first_node)) //Only considers nodes that already have connections
			{
				tree->node_to_check.x = next_node.x;
				tree->node_to_check.y = next_node.y;
				x = tree->node_to_check.x;
				y = tree->node_to_check.y;
				break;
			}
		}
	}

	//If node to check is still saturated, no unsaturated node was found and solution is not possible
	if (tree->grid.my_node[y][x].check_saturated())
	{
		tree->possible_sol = false;
		
		return backtracking(tree);
	}

	if (tree->left_check == false)
	{
		Node temp_node = tree->grid.my_node[tree->node_to_check.y][tree->node_to_check.x];

		//Check if Node has a neighbour left of itself
		if (temp_node.bool_neighbour_left)
		{
			//Check if Node can link to neighbour left of itself
			if (temp_node.link_possible_check(temp_node.neighbour_left, field))
			{
				Tree* new_tree = new Tree; //Create new tree for next iteration
				new_tree->grid = tree->grid; //Copy current grid to new tree
				new_tree->parent = tree; //Specify parent tree for backtracking
				tree->left = new_tree; //Specify child of current tree
				new_tree->node_to_check = tree->node_to_check; //Specify which node to check
				new_tree->grid.find_neighbouring_nodes(); //Find the neighbouring nodes for new tree

				//In the new tree link the Node to the neighbour right
				new_tree->grid.my_node[y][x].linking(new_tree->grid.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_left, new_tree->grid);
				tree->left_check = true;

				//Start new iteration with new tree
				return backtracking(new_tree);
			}
		}
		tree->left_check = true;
	}
	else if (tree->right_check == false)
	{
		Node temp_node = tree->grid.my_node[tree->node_to_check.y][tree->node_to_check.x];

		//Check if Node has a neighbour right of itself
		if (temp_node.bool_neighbour_right)
		{
			//Check if Node can link to neighbour right of itself
			if (temp_node.link_possible_check(temp_node.neighbour_right, field))
			{
				Tree* new_tree = new Tree; //Create new tree for next iteration
				new_tree->grid = tree->grid; //Copy current grid to new tree
				new_tree->parent = tree; //Specify parent tree for backtracking
				tree->right = new_tree; //Specify child of current tree
				new_tree->node_to_check = tree->node_to_check; //Specify which node to check
				new_tree->grid.find_neighbouring_nodes(); //Find the neighbouring nodes for new tree

				//In the new tree link the Node to the neighbour right
				new_tree->grid.my_node[y][x].linking(new_tree->grid.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_right, new_tree->grid);
				tree->right_check = true;

				//Start new iteration with new tree
				return backtracking(new_tree);
			}
		}
		tree->right_check = true;
	}
	else if (tree->up_check == false)
	{
		Node temp_node = tree->grid.my_node[tree->node_to_check.y][tree->node_to_check.x];

		//Check if Node has a neighbour above itself
		if (temp_node.bool_neighbour_up)
		{
			//Check if Node can link to neighbour above itself
			if (temp_node.link_possible_check(temp_node.neighbour_up, field))
			{
				Tree* new_tree = new Tree; //Create new tree for next iteration
				new_tree->grid = tree->grid; //Copy current grid to new tree
				new_tree->parent = tree; //Specify parent tree for backtracking
				tree->up = new_tree; //Specify child of current tree
				new_tree->node_to_check = tree->node_to_check; //Specify which node to check
				new_tree->grid.find_neighbouring_nodes(); //Find the neighbouring nodes for new tree

				//In the new tree link the Node to the neighbour above
				new_tree->grid.my_node[y][x].linking(new_tree->grid.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_up, new_tree->grid);
				tree->up_check = true;

				//Start new iteration with new tree
				return backtracking(new_tree);
			}
		}
		tree->up_check = true;
	}
	else if (tree->down_check == false)
	{
		Node temp_node = tree->grid.my_node[tree->node_to_check.y][tree->node_to_check.x];
		//Check if Node has a neighbour below itself
		if (temp_node.bool_neighbour_down)
		{
			//Check if Node can link to neighbour below itself
			if (temp_node.link_possible_check(temp_node.neighbour_down, field))
			{
				
				Tree* new_tree = new Tree; //Create new tree for next iteration
				new_tree->grid = tree->grid; //Copy current grid to new tree
				new_tree->parent = tree; //Specify parent tree for backtracking
				tree->down = new_tree; //Specify child of current tree
				new_tree->node_to_check = tree->node_to_check; //Specify which node to check
				new_tree->grid.find_neighbouring_nodes(); //Find the neighbouring nodes for new tree

				//In the new tree link the Node to the neighbour below
				new_tree->grid.my_node[y][x].linking(new_tree->grid.my_node[new_tree->node_to_check.y][new_tree->node_to_check.x].neighbour_down, new_tree->grid);
				tree->down_check = true;

				//Start new iteration with new tree
				return backtracking(new_tree);
			}
		}
		tree->down_check = true;
	}
	else
	{
		//If it can't connect to any neighbours a solution for this iteration is not possible
		tree->possible_sol = false; 
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

	//Initialise the grid using the input strings
	Grid first_field(field_v);

	//Create the first tree data structure
	Tree* tree = new Tree;

	//Input the generated grid into the tree data structure
	tree->grid = first_field;

	//Find all the neighbouring nodes for each node
	tree->grid.find_neighbouring_nodes();

	//Specify first node to check
	tree->grid.nodes_to_check[0];
	tree->first_node = true; //Indicates that this is the first node it is checking

	//Call backtracking recursive function
	Tree* answer = backtracking(tree);

	//Print answer
	for (int y = 0; y < answer->grid.my_node.size(); ++y)
	{
		for (int x = 0; x < answer->grid.my_node[y].size(); ++x)
		{
			answer->grid.my_node[y][x].print_answer();
		}
	}
}
