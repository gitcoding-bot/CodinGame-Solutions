/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Skynet Revolution
Difficulty: Medium

This solution uses the breadth first search algorithm to solve the problem.
A graph data structure is used to represent the nodes and the links. 
Using the initial spawn location of the virus the algorithm finds the shortest 
path to a gateway and blocks that route. 
This is done by creating a tree data structure for each node. The neighbouring nodes
of the node where the virus spawns is determined and added to a queue of nodes to check. Each node is checked individually
to determine whether it is a gateway. If it is, the path to that node is severed. If not, the neighbours of
that node is added to the queue. This continues until a gateway is found. 

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

	Node(int ii, bool gg);
	~Node();
};

class Tree;

class Graph
{
  // A graph data structure where the vertices represents each node
  // and the edges represent a link between two nodes.
  // Edges can either be gateways or just normal nodes.
  
  public:
	int correct_node_1 = -1; // Index of the gateway node should it be found
	int correct_node_2 = -1; // Index of the node connected to the gateway
	int node_to_consider = 0;// Current node under consideration
	Tree* tree;
	std::vector<Edge> edges;
	std::vector<Node> nodes;
	Queue<int> queue; //A queue data structure containing the nodes that have to be checked
	Queue<Tree*> tree_queue;
	Queue<int> nodes_checked; //A queue data structure containing the nodes that have been checked
	
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
  //Adds a new edge to the graph data structure

	Edge new_edge(source->index, dest->index);

	edges.push_back(new_edge);
	source->my_edges.push_back(&new_edge);
	dest->my_edges.push_back(&new_edge);
}

void Graph::add_vertex(int index, int gateway)
{
  //Adds a new vertex to the graph data structure
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
		}
	}
	return i;
}
 
Graph breadth_first_search(Graph &graph)
{
  //Implements the breadth first search algorithm

	int i = find_next_node(graph);
	graph.nodes_checked.Enqueue(i);
	
	Tree* ptr = graph.tree_queue.Dequeue();
	graph.tree = ptr;
	graph.tree->checked = true;
	Node nodes = graph.nodes[i];

	if (nodes.gateway == true)
	{
		graph.correct_node_1 = nodes.index;
		graph.correct_node_2 = graph.tree->parent->val;
	}
	else
	{
		for (Node* neighbour : nodes.adjacent_nodes)
		{
			bool found_link = false;
			for (Edge links : graph.edges)
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
				new_tree->parent = graph.tree;
				new_tree->val = neighbour->index;
				graph.tree->children.push_back(new_tree);
				graph.queue.Enqueue(neighbour->index);
				graph.tree_queue.Enqueue(new_tree);

			}
		}
	}

	if (graph.correct_node_1 > -1)
	{
		return graph;
	}

	return breadth_first_search(graph);

}
 
int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    cerr << N << L << E << endl;
    Graph graph;
    
    for (int i = 0; i < N; i++)
    {
        graph.add_vertex(i, false);   
    }
    
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        graph.add_edge(&graph.nodes[N1],&graph.nodes[N2]);
        graph.nodes[N1].adjacent_nodes.push_back(&graph.nodes[N2]);
		graph.nodes[N2].adjacent_nodes.push_back(&graph.nodes[N1]);
		
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        graph.nodes[EI].gateway = true;
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
        
        Tree *tree = new Tree;
        tree->val = SI;
        graph.tree = tree;
        graph.tree_queue.Enqueue(tree);
        
        graph.correct_node_1 = -1;
		graph.correct_node_2 = -1;
        graph = breadth_first_search(graph);

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // Example: 0 1 are the indices of the nodes you wish to sever the link between
        cout << graph.correct_node_1 << " " << graph.correct_node_2 << endl;
    }
}
