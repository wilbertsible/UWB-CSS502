//--------------------graphl.cpp----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: February 4, 2019
//Date of Last Modification: February 19, 2019
//--------------------------------------------------------------
// This is the implementation of the graphm.cpp. In this file,
// a txt file (data31.txt) was given. Two different graphs were
// described in the txt file. The file contains the number of 
// nodes followed by places that the nodes represent, and lastly,
// the adjacency list of each node. The adjacency list also 
// includes the weights of each edge. In this class, the task 
// was to get all the possible shortest path from each node
// to all the other nodes. Dijkstra's algorithm was used in
// finding the sortest path. Using an adjacency matrix, the 
// table was filled up and used to determine the shortest path.
//--------------------------------------------------------------
// ***Specifications: The table should be able to describe going 
// from each of the nodes to all the other nodes in the graph.
// ***Assumptions: 
// 1. There would be no more than 100 nodes maximum that will be
// on the file.
// 2. The program only handles the format that is used in the 
// txt file. Other organizations of the txt file cannot be used 
// in  the program.
// 3. Infinty is set to 1 million. Any weight higher than that
// will not work with this program.
//--------------------------------------------------------------
#include "graphm.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <queue>
using namespace std;

//----------GraphM constructor----------------------
// This constructor takes in no parameters. It sets the size
// to MAXNODES, and initializes both multidimensional arrays to
// the default which is infinity for the distances, false for 
// visited, and 0 for path. It also sets the default for the 
// adjacency table to infinity for the weights of all the edges.
//--------------------------------------------------------------
GraphM::GraphM()
{
	for (int i = 1; i < MAXNODES; i++) {
		for (int j = 1; j < MAXNODES; j++)
		{
			T[i][j].dist = INF;
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
	for (int i = 1; i < MAXNODES; i++) {
		for (int j = 1; j < MAXNODES; j++)
		{
			C[i][j] = INF;
		}
	}
	size = MAXNODES;
} // End of GraphM constructor

//----------buildGraph------------------------------------------
// This is the buildGraph function. This function takes in an 
// infile stream which is the txt file. The txt file contains
// the following in order: how many nodes are in the graph,
// the representation of the nodes, and the adjacency list
// of all the nodes. The buildGraph function takes all of those
// inputs in and sets them into their corresponding variables in
// C array. To be consistent, the data starts at 1.
//--------------------------------------------------------------
void GraphM::buildGraph(ifstream &infile) 
{
	infile >> size;
	if (infile.eof())
	{
		return;
	}
	string s;
	getline(infile, s); // Discards the line of the size
	for (int i = 1; i <= size; i++) 
	{
		getline(infile, s);
		if (infile.eof()) break;
		NodeData *ptr = new NodeData(s);
		data[i] = *ptr;
		delete ptr;
		ptr = nullptr;
	}
	int node1, node2, weight;
	infile >> node1;
	infile >> node2;
	infile >> weight;
	while (node1 != 0)
	{
		C[node1][node2] = weight;
		infile >> node1;
		infile >> node2;
		infile >> weight;
	}
} // End of buildGraph function

//----------insertEdge------------------------------------------
// This is the insertEdge function. It adds another weighted 
// edge into the graph. To do this, the C array table jst needs
// to be updated. The weight at node[1][2] is changed from infinity
// to the weight given.
//--------------------------------------------------------------
void GraphM::insertEdge(int node1, int node2, int weight)
{
	C[node1][node2] = weight;
} // End of insertEdge function

//----------removeEdge------------------------------------------
// This is the removeEdge function. It removes an edge from the 
// graph. To do this, given the nodes that make up the edge,
// the weight of that edge must be turned back to infinity
//--------------------------------------------------------------
void GraphM::removeEdge(int node1, int node2)
{
	C[node1][node2] = INF;
} // End of removeEdge function

//----------findShortestPath------------------------------------------
// The findShortestPath function employs Dijkstra's algorithm
// by updating the multidimensional array T. Each row represents
// one node. For that row, the TableType values visited, path, 
// and distance were updated. This was done to all the rows,
// thus giving the shortest distance from that row to all
// the other nodes. 
//--------------------------------------------------------------
void GraphM::findShortestPath()
{
	
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;
		
		for (int i = 1; i <= size; i++)
		{
			int v=source;
			int lowestDistance = INF;
			for (int j = 1; j <= size; j++)
			{
				if (T[source][j].dist < lowestDistance && T[source][j].visited == false)
				{
					lowestDistance = T[source][j].dist;
					v = j;
				}
			}
			T[source][v].visited = true;
			for (int w = 1; w <= size; w++)
			{
				if (T[source][w].visited == false)
				{
					if (T[source][w].dist > T[source][v].dist + C[v][w])
					{
						T[source][w].dist = T[source][v].dist + C[v][w];
						T[source][w].path = v;
					}
				}
			}
		}
	}
}

//----------displayGraph------------------------------------------
// This function iteratively goes through the TableType T and
// prints out each node that is adjacent to the index. The getPath
// function is used to get the shortest path from one node to another.
//--------------------------------------------------------------
void GraphM::displayAll()
{
	cout << "Description" << setw(24) << "From node" << setw(9) << "To node" << setw(12) << "Dijkstra's" << setw(6) << "Path" << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << data[i] << endl;
		for (int j = 1; j <= size; j++)
		{
			if (i != j)
			{
				cout << setw(32) << i << setw(8) << j;
				if (T[i][j].dist < INF)
				{
					cout << setw(8) << T[i][j].dist << setw(11);
				}
				else
				{
					cout << setw(9) << "---" ;
				}
				queue<int> q = getPath(i, j);
				while (!q.empty())
				{
					cout << q.front() << " ";
					q.pop();
				}
				cout << endl;
			}
		}
	}
}

//----------getPath------------------------------------------
// This helper function is used to get the shortest path from
// one node to another. A stack is used to push the destination
// from the destination, back to its source since the path 
// variable of TableType kept track of the path taken.
// To display the right order, a queue was used to return the
// values in the right order.
//--------------------------------------------------------------
queue<int> GraphM::getPath(int source, int destination)
{
	stack<int>s;
	queue<int>q;
	if (T[source][destination].path != 0)
	{
		s.push(destination);
	}
	while (T[source][destination].path != 0)
	{
		
		destination = T[source][destination].path;
		s.push(destination);
	}
	while (!s.empty())
	{
		q.push(s.top());
		s.pop();
	}
	return q;
}// End of getPath helper function

//----------display------------------------------------------
// This function displays the shortest path between two nodes.
// The queue returned by getPath was used alongside another
// queue to print the literal location of the nodes. 
//--------------------------------------------------------------
void GraphM::display(int source, int destination)
{
	cout << source << setw(8) << destination;
	if (T[source][destination].dist < INF)
	{
		cout << setw(8) << T[source][destination].dist << setw(12);
	}
	else
	{
		cout << setw(9) << "---";
	}
	queue<int> q = getPath(source, destination);
	queue<int> printLocation = getPath(source, destination);
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
	while (!printLocation.empty())
	{
		cout << data[printLocation.front()] <<endl;
		printLocation.pop();
	}
}



