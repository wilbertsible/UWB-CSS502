//--------------------poly.cpp----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: January 21, 2019
//Date of Last Modification: February 3, 2019
//--------------------------------------------------------------
// This is the header file of the bintree class. This lists all the
// functions and operator overloads that were implemented in the
// .cpp file. A struct Node was given to provide for the node class.
// Helper functions were also used to perform recursive algorithm.
//--------------------------------------------------------------

#include "nodedata.h"
class BinTree
{
private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree
public:

	//Constructors
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	//Destructor
	~BinTree();								// destructor, calls makeEmpty	
	
	//Operator Overloads
	BinTree& operator=(const BinTree &);
	bool operator==(const BinTree &) const;
	bool operator!=(const BinTree &) const;
	friend ostream &operator <<(ostream &, const BinTree &);

	//Functions
	
	bool retrieve(const NodeData&, NodeData *&);
	int getHeight(const NodeData &);
	void bstreeToArray(NodeData*[]);
	void arrayToBSTree(NodeData*[]);
	bool insert(NodeData*);
	

	//Helper Functions
	void preorderHelper(Node*&, Node*);
	void makeEmpty();						// make the tree empty so isEmpty returns true
	void deleteTreePostorder(Node*&);
	bool isEqual(Node*, Node*)const;
	void inorderHelper(Node*) const;
	bool isEmpty() const;					// true if tree is empty, otherwise false
	bool retrieveHelper(Node *&, const NodeData &, NodeData *&)const;			
	void getNode(Node *&, const NodeData &);
	int getHeightHelper(Node *&curr, const NodeData &nodedata)const;
	int bstreeToArrayHelper(Node*, NodeData*[]) const;
	
	void arrayToBSTreeHelper(NodeData * array[], int first, int last, Node *& root);
	


	void displaySideways() const;			// provided below, displays the tree sideways
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()

};