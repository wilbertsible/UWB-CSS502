//--------------------graphl.h----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: February 4, 2019
//Date of Last Modification: February 19, 2019
//--------------------------------------------------------------
// This is the header file of the graphl class. This lists all the
// functions and operator overloads that were implemented in the
// .cpp file. The structs GraphNode and EdgeNode were given.
// The array adjacencyList that will hold the GraphNode was also
// initialized. The size of adjacencyList was initially set to 
// 101. Also the int size was initialized that will set the
// size that is being occupied. 
//-------------------------------------------------------------
#include "nodedata.h"
#ifndef GRAPHL_H
#define GRAPHL_H
class GraphL
{
	
private:
	static const int MAXNODES = 101;
	struct EdgeNode{      // forward reference for the compiler
		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};
	struct GraphNode{    // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // data information about each node
		bool visited;
	};
	GraphNode adjacencyList[MAXNODES];
	int size;
public:
	GraphL();
	void buildGraph(ifstream&);
	void displayGraph();
	void depthFirstSearch();
	~GraphL();
};
#endif

