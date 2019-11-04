/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Skynet Revolution
Difficulty: Hard
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class Queue
{
public:

	std::vector<T> list = {};

	void Enqueue(T i);
	T Dequeue();
	void clear();
	T Priority_enqueue(T i);

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
	//list = std::vector<T>(list.begin() + 1, list.end());
	list.erase(list.begin());
	return val;

}

template <typename T>
T Queue<T>::Priority_enqueue(T i)
{
	list.insert(0, i);
}

template <typename T>
void Queue<T>::clear()
{
	list.clear();
}


class Edge
{
public:
	int src = -1; //index of source node
	int dest = -1; //index of destination node
	bool link_severed = false;
	Edge(int ss, int dd);
	~Edge();
};

class Node
{
public:

	int index = -1;
	bool gateway = false;
	std::vector<Node*> adjacent_nodes;
	std::vector<Edge*> my_edges;
	int number_of_gateway_neighbour = 0;

	Node(int ii, bool gg);
	~Node();
};

class Tree;

class Graph
{
public:
	int correct_node_1 = -1;
	int correct_node_2 = -1;
	int node_to_consider = 0;
	Tree* tree;
	std::vector<Edge> edges;
	std::vector<Node> nodes;
	Queue<int> queue;
	Queue<Tree*> tree_queue;
	Queue<int> nodes_checked;
	Queue<Edge> links_severed;
	bool found_solution = false;
	std::vector<Edge> solution_list;


	Graph();
	~Graph();
	void add_edge(Node* source, Node* dest);
	void add_vertex(int index, int gateway);
};



Edge::Edge(int ss, int dd)
	:src{ ss }, dest{ dd }
{
}


Edge::~Edge()
{
}

Graph::Graph()
{
}


Graph::~Graph()
{
}


void Graph::add_edge(Node* source, Node* dest)
{
	Edge new_edge(source->index, dest->index);

	edges.push_back(new_edge);
	source->my_edges.push_back(&new_edge);
	dest->my_edges.push_back(&new_edge);
}

void Graph::add_vertex(int index, int gateway)
{
	Node new_node(index, gateway);

	nodes.push_back(new_node);
}



Node::Node(int ii, bool gg)
	:index{ ii }, gateway{ gg }
{
}


Node::~Node()
{
}

class Tree
{
public:

	int val;
	bool checked = false;
	Tree* parent;
	int parent_val;
	std::vector<Tree*> children;

	Tree();
	~Tree();
};

Tree::Tree()
{
}


Tree::~Tree()
{
}

int find_next_node(Graph &graph)
{
	int i = graph.queue.Dequeue();
	if (graph.nodes_checked.list.empty())
	{
		return i;
	}
	for (int x : graph.nodes_checked.list)
	{
		if (i == x)
		{
			i = find_next_node(graph);
			break;
		}
	}
	return i;
}

Tree* find_next_tree(Graph &graph)
{
	Tree* i = graph.tree_queue.Dequeue();
	if (graph.nodes_checked.list.empty())
	{
		return i;
	}
	for (int x : graph.nodes_checked.list)
	{
		if (i->val == x)
		{
			i = find_next_tree(graph);
			break;
		}
	}
	return i;
}

Graph breadth_first_seach(Graph &graph)
{

	int i = find_next_node(graph);
	Tree* tree_ptr = find_next_tree(graph);
	graph.nodes_checked.Enqueue(i);

	cerr << "looking at node: " << i << endl;

	Node nodes = graph.nodes[i];
  
	bool is_link_severed = false;

	if (nodes.gateway == true)
	{

		for (Edge links : graph.links_severed.list)
		{
			if ((links.dest == nodes.index && links.src == tree_ptr->parent->val) || links.src == nodes.index && links.dest == tree_ptr->parent->val)
			{
				is_link_severed = true;
				break;
			}
		}
	}

	if (nodes.gateway == true && not(is_link_severed))
	{

		graph.correct_node_1 = nodes.index;
		graph.correct_node_2 = tree_ptr->parent->val;
		Edge temp_edge(graph.correct_node_1, graph.correct_node_2);
		temp_edge.link_severed = true;
		graph.links_severed.Enqueue(temp_edge);
		graph.solution_list.push_back(temp_edge);
		graph.found_solution = true;
	}
	else if (not(graph.found_solution))
	{

		for (Node* neighbour : nodes.adjacent_nodes)
		{

			bool found_link = false;
			for (Edge links : graph.links_severed.list)
			{
				if (links.link_severed)
				{
					if ((links.dest == neighbour->index && links.src == nodes.index) || (links.dest == nodes.index && links.src == neighbour->index))
					{
						found_link = true;
						break;
					}
				}
			}
			if (not(found_link))
			{

				Tree *new_tree = new Tree;
				new_tree->parent = tree_ptr;
				new_tree->val = neighbour->index;
				new_tree->parent_val = nodes.index;

				tree_ptr->children.push_back(new_tree);
				graph.queue.Enqueue(neighbour->index);
				graph.tree_queue.Enqueue(new_tree);

			}
		}
	}

	//if (graph.correct_node_1 > -1 && graph.queue.list.empty())
	if (graph.correct_node_1 > -1)
	{
		return graph;
	}

	return breadth_first_seach(graph);

}

int main()
{
	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways
	cin >> N >> L >> E; cin.ignore();

	Graph graph;

	for (int i = 0; i < N; i++)
	{
		graph.add_vertex(i, false);
	}
  
	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();

		graph.add_edge(&graph.nodes[N1], &graph.nodes[N2]);
		graph.nodes[N1].adjacent_nodes.push_back(&graph.nodes[N2]);
		graph.nodes[N2].adjacent_nodes.push_back(&graph.nodes[N1]);
	}

	for (int i = 0; i < E; i++) {
		int EI; // the index of a gateway node
		cin >> EI; cin.ignore();
		graph.nodes[EI].gateway = true;

		for (Node* temp_node : graph.nodes[EI].adjacent_nodes)
		{
			temp_node->number_of_gateway_neighbour += 1;
		}

	}

	// game loop
	while (1) {
		int SI; // The index of the node on which the Skynet agent is positioned this turn
		cin >> SI; cin.ignore();
		graph.queue.clear();
		graph.tree_queue.clear();
		graph.queue.Enqueue(SI);
		graph.nodes_checked.clear();
		graph.nodes_checked.Enqueue(212);
		graph.found_solution = false;
		graph.solution_list.clear();

		Tree *tree = new Tree;
		tree->val = SI;
		graph.tree = tree;
		graph.tree_queue.Enqueue(tree);

		graph.correct_node_1 = -1;
		graph.correct_node_2 = -1;
		graph = breadth_first_seach(graph);

		cout << graph.correct_node_1 << " " << graph.correct_node_2 << endl;

	}
}
