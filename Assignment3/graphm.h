//--------------------graphm.h----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: February 4, 2019
//Date of Last Modification: February 19, 2019
//--------------------------------------------------------------
// This is the header file of the GraphM class. This lists the
// functions that were used in this class. The MAXNODES was
// initialized and declared as 101. A global static variable INF is
// used to define infinity as 1 million. A TableType struct is 
// given to set markers for Dijkstra's algorithm. The dist and
// the path variable is used to keep track of the shortest distance
// and the path taken. An array of NodeData was used to store the
// values/ locations corresponding to each node. A multidimensional
// array C was used to keep track of the weights of the edges.
// Another multidimensional array that contains a TableType
// object keeps track of Dijkstra's algorithm from each node
// to all other nodes. 
//-------------------------------------------------------------
#include "nodedata.h"
#include <queue>
#ifndef GRAPHM_H
#define GRAPHM_H
class GraphM {
private:
	static const int MAXNODES = 101;
	static const int INF = 1000000;
	struct TableType {
		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist
	};
	NodeData data[MAXNODES];              // data for graph nodes 
	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
	int size;                             // number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
public:
	GraphM();
	void buildGraph(ifstream&);
	void insertEdge(int, int, int);
	void removeEdge(int, int);
	void findShortestPath();
	void displayAll();
	queue<int> getPath(int, int);
	void display(int, int);
};
#endif
