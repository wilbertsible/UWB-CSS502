//--------------------graphl.cpp----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: February 4, 2019
//Date of Last Modification: February 19, 2019
//--------------------------------------------------------------
// This is the implementation of the graphl.cpp. In this file,
// a txt file (data32.txt) was given. Two different graphs were
// described in the txt file. The file contains the number of 
// nodes followed by places that the nodes represent, and lastly,
// the adjacency list of each node. This .cpp reads through the
// file and sets it in an adjacency list. After that, the graph
// is displayed in a sepcific format. Then, the program performs 
// a depth first traversal on the graph, showing the final result.
//--------------------------------------------------------------
// ***Specifications: An adjacency list has to be used in this
// program. An array should hold the GraphNode struct that 
// describes the node. The GraphNode struct holds the EdgeNode
// struct which creates the linked list in the array. The second
// specification is that the nodes are given in reverse order.
// The nodes should not be sorted. Therefore, the nodes should 
// be inserted on the head of the linked list. Then, a depth-
// first search is to be used to traverse through the graph.
// ***Assumptions: 
// 1. There would be no more than 100 nodes maximum that will be
// on the file.
// 2. The program only handles the format that is used in the 
// txt file. Other organizations of the txt file cannot be used 
// in  the program.
//--------------------------------------------------------------

#include "graphl.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <queue>
using namespace std;

//----------GraphL constructor----------------------
// This constructor takes in no parameters. It sets the size
// to 100, then initialize the adjacencyList to its default values.
//--------------------------------------------------------------
GraphL::GraphL()
{
	size = 100;
	for (int i = 0; i <= size; i++)
	{
		adjacencyList[i].edgeHead = nullptr;
		adjacencyList[i].data = nullptr;
		adjacencyList[i].visited = false; 
	}
} // End of GraphL constructor

//----------buildGraph------------------------------------------
// This is the buildGraph function. This function takes in an 
// infile stream which is the txt file. The txt file contains
// the following in order: how many nodes are in the graph,
// the representation of the nodes, and the adjacency list
// of all the nodes. The buildGraph function takes all of those
// inputs in and sets them into their corresponding variables in
// GraphNode. The EdgeNode struct was then used to create a linked
// list inside each index of the array. The array starts at 1.
//--------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile)
{
	infile >> size;
	if (infile.eof())
	{
		return;
	}
	string s;
	getline(infile, s);
	for (int i = 1; i <= size; i++)
	{
		getline(infile, s);
		if (infile.eof()) break;
		GraphNode *node = new GraphNode();
		node->data = new NodeData(s);
		node->edgeHead = nullptr;
		node->visited = false;
		adjacencyList[i] = *node;
		delete node;
		node = nullptr;
	}
	int vertex, node;
	infile >> vertex;
	infile >> node;
	while (vertex != 0)
	{
		EdgeNode *newNode = new EdgeNode();
		if (adjacencyList[vertex].edgeHead == nullptr)
		{
			adjacencyList[vertex].edgeHead = newNode;
			newNode->adjGraphNode = node;
			newNode->nextEdge = nullptr;
		}
		else
		{
			newNode->nextEdge = adjacencyList[vertex].edgeHead;
			adjacencyList[vertex].edgeHead = newNode;
		}
		infile >> vertex;
		infile >> node;
	}
} // End of buildGraph

//----------displayGraph------------------------------------------
// This function iteratively goes through adjacencyList and
// prints out each node that is adjacent to the index. 
//--------------------------------------------------------------

void GraphL::displayGraph()
{
	
	cout << "Graph:" << endl;
	for (int i = 1; i <= size; i++)
	{
		EdgeNode *curr = adjacencyList[i].edgeHead;
		cout << "Node " <<  left << setw(7) << i << *adjacencyList[i].data << endl;
		if (adjacencyList[i].edgeHead != nullptr)
		{
			while (curr != nullptr)
			{
				cout << right <<setw(7) << "edge " << i << setw(2) << curr->adjGraphNode << endl;
				curr = curr->nextEdge;
			}
		}
	}
} // End of displayGraph

//----------depthFirstSearch------------------------------------------
// The depthFirstSearch function goes through the graph using 
// depth-first search algorithm. In this function, the search was
// done iteratively using a stack to backtrack to a previous node, 
// and a queue to mark the nodes that are visited. In the stack,
// the first node is pushed, and then the first adjacent node is pushed.
// The variable node was then set to the top of the stack and the
// first adjacent node not visited was then obtained. If the node does
// not have an adjacent node, the node is popped and then the first
// adjacent node that was not yet visited was then taken.
// This goes on until the stack is empty which means that all
// possible nodes have been exhausted. The queue stores anything that
// has been pushed to the stack, which means that it will not take
// the duplicates. This allows the program to print the depth-first
// traversal of the graph.
//--------------------------------------------------------------
void GraphL::depthFirstSearch()
{	
	int node = 1;
	bool found = false;
	EdgeNode *curr = adjacencyList[node].edgeHead;
	stack<int> s;
	queue<int> q;
	s.push(node);
	q.push(node);
	adjacencyList[node].visited = true;
	while (!s.empty())
	{
		node = s.top();
		curr = adjacencyList[node].edgeHead;
		found = false;
		while (curr != nullptr && !found)
		{
			if (!adjacencyList[curr->adjGraphNode].visited)
			{
				s.push(curr->adjGraphNode);
				q.push(curr->adjGraphNode);
				adjacencyList[curr->adjGraphNode].visited = true;
				found = true;
			}
			else
			{
				curr = curr->nextEdge;
			}
		}
		if (!found)
		{
			s.pop();
		}
	}
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
} // End of depthFirstSearch function

//----------Destructor-----------------------------------------------
// This is the destructor of the class. The array is traversed. Then,
// the nodedata that contains the location is deallocated. After that,
// each linkedlist is deallocated one by one. Thus finally deallocating
// memory that was dynamically allocated in the program.
//-------------------------------------------------------------------
GraphL::~GraphL()
{	
	EdgeNode *curr, *next;
	for (int i = 0; i < size; i++)
	{
		delete adjacencyList[i+1].data;
		adjacencyList[i+1].data = nullptr;
		curr = adjacencyList[i+1].edgeHead;
		if (curr != nullptr) {
			next = curr->nextEdge;
			delete curr;
			curr = nullptr;
			while (next != nullptr)
			{
				curr = next;
				next = curr->nextEdge;
				delete curr;
				curr = nullptr;
			}
		}
	}
} // End of destructor
