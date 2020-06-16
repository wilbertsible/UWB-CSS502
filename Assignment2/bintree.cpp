//--------------------poly.cpp----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: January 12, 2019
//Date of Last Modification: January 20, 2019
//--------------------------------------------------------------
// This is the implementation file of the bintree program. 
// The program creates a binary search tree that takes in 
// nodedata objects. The strings in the nodedata objects
// are sorted into the binary search tree. Several other functions
// such as retrieving a nodedata, getting the height of a node
// parsing the tree into an array and parsing the array back into
// a tree.
//--------------------------------------------------------------
// ***Specifications: The porgram requires that the constructor be 
// overloaded to handle several different constructor inputs.
// The copy constructor was also created to copy a polynomial
// The addition, subtraction, and multiplication operators are 
// also overloaded. Several getter and setter functions such as 
// the getCoeff (to get the coefficient of a term raised to a 
// specific exponenet) and the setCoeff (to set the coefficient 
// of a term raised to a specific exponent) were also utilized.
// The instream was also overloaded to handle a sentinel value 
// of -1 -1 to terminate input. The outstream was overloaded to
// print out the polynomial in the form "Ax^m +Bx^n +... +C"
// where A, B, and C are whole numbers, and m and n are the
// exponents. The program also requires that there should be
// no memory leaks. To help with this, a function called 
// expandArray is created to take care of expanding and
// shrinking of the array when operations are done.
// ***Special algorithms: Sentinel value was used to terminate
// user input.
// ***Assumptions: 
// 1. The coefficients are of the type integer. Any decimal 
// number will be rounded down to its integer equivalent.
// 2. All the exponents are whole numbers. Any decimal number 
// will be rounded down to the nearest whole number. Any 
// negative integer will be converted to its positive 
// counterpart.
//--------------------------------------------------------------

#include "bintree.h"
#include <iostream>
using namespace std;

//----------BinTree constructor-----------------------------------
// This constructor overloads the default constructor. It sets the
// root node to a null pointer.
//----------------------------------------------------------------
BinTree::BinTree()
{
	root = nullptr;
}// End of BinTree constructor

//----------preorderHelper Function--------------------------------------
// This is a helper function which performs preorder traversal of the
// binary search tree. This was used to copy two different bintree objects
// such as the copy constructor and the equality operator. First it checks to
// see if the object to be copied is empty. If it is, then do nothing.
// If there is something to copy, a new NodeData object is created 
// and the tree is filled by traversing the object to be copied and 
// setting the new node to the same place on the new tree.
//----------------------------------------------------------------
void BinTree::preorderHelper(Node* &root, Node *other)
{
	if (other == nullptr)
	{
		return;
	}
	NodeData *nodedata = new NodeData(*other->data);
	Node *newNode = new Node();
	newNode->data = nodedata;
	root = newNode;  
	preorderHelper(root->left, other->left);
	preorderHelper(root->right, other->right);
} // End of preorderHelper function

//----------Copy constructor--------------------------------------
// This is the copy constructor of the BinTree class. It uses the 
// preorderHelper function to perform preorder traversal on both
// objects.
//----------------------------------------------------------------
BinTree::BinTree(const BinTree &orig)
{
	preorderHelper(this->root, orig.root);
}// End of Copy constructor

//----------makeEmpty Function-------------------------------------
// This function calls on the deleteTreePostorder function that 
// traverses the tree and deletes each node in a postorder traversal.
//----------------------------------------------------------------
void BinTree::makeEmpty()
{
	deleteTreePostorder(this->root);
} // End of makeEmpty function

//----------deleteTreePostorder Helper Function----------------------------
// This function does a postorder traversal on the tree. It first check
// if the node where it is at is not null, then it traverses the tree
// and deletes the data if there is an object in it. It then proceeds
// to delete the node itself and set its pointer to null.
//----------------------------------------------------------------
void BinTree::deleteTreePostorder(Node*& curr)
{
	if (curr != nullptr)
	{
		deleteTreePostorder(curr->left);
		deleteTreePostorder(curr->right);
		if (curr->data != nullptr) {
			delete curr->data;
			curr->data = nullptr;
		}
		delete curr;
		curr = nullptr;
	}
} // End of deleteTreePostorder Function

//----------Assignment Operator Overload----------------------------
// This is the equality operator overload of the BinTree class.
// To set this lvalue to the rvalue, first, both the lvalue and the 
// rvalue were check to see if they are the same. If they are, then
// there is no need to change anythng. However, if they are not 
// the same, the lvalue obect was emptied out using the makeEmpty
// function and then the preorderHelper function was used to fill
// in the tree. Then the tree was returned.
//----------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree& other)
{
	if (this != &other)
	{
		makeEmpty();  // deallocate left-hand side
		preorderHelper(this->root, other.root);  // copy right-hand side
	}
	return *this;
}// End of Assignment Operator Overload


//----------isEqual Helper Function----------------------------
// This is the isEqual function that checks whether two trees are
// equal. The first if statement checks if both trees are nullptrs
// If they are, there is nothing to check and they are equal.
// If not then if either one is null and the other is not, then
// they are automatically not equal and false is returned. Then,
// the preorder traversal of the tree is done to check whether 
// the data on the same nodes are equal. If they are not, then the
// function returns false. 
//----------------------------------------------------------------
bool BinTree::isEqual(Node* root, Node* other)const
{
	if (root == nullptr && other == nullptr) return true;
	if (root != nullptr && other == nullptr) return false; 
	if (root == nullptr && other != nullptr) return false;  

	if (*root->data != *other->data) return false;  
	bool isLeftEqual = isEqual(root->left, other->left);
	bool isRightEqual = isEqual(root->right, other->right);
	return (isLeftEqual && isRightEqual);
} // End isEqual Helper Function

//----------Equality Operator Overload----------------------------
// This is the equality operator overoload for the BinTree class.
// The operator overload checks whether two BinTree objects are equal
// The function first checks if both are null. If they are, then there
// is nothing to check and the function returns true since they are 
// equal. If not, the isEqual helper function is called to evaluate
// the two trees using preorder traversal.
//----------------------------------------------------------------
bool BinTree::operator==(const BinTree& other)const
{
	if (root == nullptr && other.root == nullptr) 
	{
		return true;
	}
	else
	{
		return isEqual(root, other.root); 
	}
} // End Equality Operator Overload

//----------Inequality Operator Overload----------------------------
// This is the inequality operator overoload for the BinTree class.
// Since the equality operator is already established, and the
// inequality operator is just the opposite of the equality operator,
// then the equality operator is negated and the result is returned.
//----------------------------------------------------------------
bool BinTree::operator!=(const BinTree& other)const
{
	return !(*this == other);
}// End Inequality Operator Overload

//----------inorderHelper Function----------------------------
// This is the inorderHelper function. It is used in the outstream
// operator overload to printout the tree in an inorder traversal.
// The function first checks to see if the root is null which means
// that there is no tree present and nothing to print. Then, the 
// function is recursively called inorder traversal to print out the 
// function. 
//----------------------------------------------------------------
void BinTree::inorderHelper(Node* root)const
{
	if (root == nullptr)
	{
		return;
	}
	inorderHelper(root->left);
	cout << *root->data << " ";
	inorderHelper(root->right);
} // End inorderHelper Function

//----------Ostream Operator Overload----------------------------
// This is the ostream operator overload. It calls the inorderHelper
// function to printout the tree in an inorder traversal.
//----------------------------------------------------------------
ostream &operator <<(ostream &out, const BinTree &binTree)
{
	binTree.inorderHelper(binTree.root);
	out << endl;
	return out;
}

//----------isEmpty Helper Function----------------------------
// This function checks a tree to see if the root is null which
// means that the tree is empty.
//----------------------------------------------------------------
bool BinTree::isEmpty() const
{
	if (this->root == nullptr)
	{
		return true;
	}
	return false;
} // End isEmpty Helper Function

//----------insert Function----------------------------
// This function inserts the node into the tree. A new node is
// created and the data is set into the node. The tree is then 
// traversed via binary search. If the root is empty, then the 
// new node becomes the root. If not, the data inside the node is
// compared to the root node and traversed left or right depending
// on the parent node until it can find an empty position. A boolean
// value is then returned to indicate that the insert action is 
// successful.
//----------------------------------------------------------------
bool BinTree::insert(NodeData* nodeData)
{
	bool isSet = false;
	Node *curr = root;
	Node *newNode = new Node();
	newNode->data = nodeData;
	if (isEmpty())
	{
		root = newNode;
	}
	else
	{
		while (!isSet)
		{
			if (*newNode->data < *curr->data)
			{
				if (curr->left == nullptr) {
					curr->left = newNode;
					isSet = true;
					newNode = nullptr;
					delete newNode;
					return isSet;
				}
				else
				{
					curr = curr->left;
				}
			}
			else if (*newNode->data > *curr->data)
			{
				if (curr->right == nullptr) {
					curr->right = newNode;
					isSet = true;
					newNode = nullptr;
					delete newNode;
					return isSet;
				}
				else
				{
					curr = curr->right;
				}
			}
			else
			{
				delete newNode;
				return isSet;
			}
		}
	}
	return true;
} // End insert function

//----------retrieve Function----------------------------
// This function retrieves a specific object in the tree and returns
// if the object is present. It uses the retrieveHelper to traverse
// the tree using binary search algorithm.
//----------------------------------------------------------------
bool BinTree::retrieve(const NodeData& object, NodeData *& result)
{
	return retrieveHelper(this->root, object, result);
}// End retrieve Function

//----------retrieveHelper Function----------------------------
// This function traverses the tree in a binary search algorithm 
// to search for a specific object in the tree. The fuction first 
// checks to see if there is a tree by checking the root. If there
// is not, then the result is set to null and the boolean returned
// is false. If there is a tree present, then the tree is traversed
// until the object is found. If it is then a true boolean is 
// returned. Otherwise, a false boolean is returned.
//----------------------------------------------------------------
bool BinTree::retrieveHelper(Node *&curr, const NodeData &object, NodeData *& result)const
{
	if (curr == nullptr)
	{
		result = nullptr;
		return false;
	}
	if (*curr->data == object)
	{
		result = curr->data;
		return true;
	}
	else if (*curr->data > object)
	{
		retrieveHelper(curr->left, object, result);
	}
	else if (*curr->data < object)
	{
		retrieveHelper(curr->right, object, result);
	}
} // End retrieveHelper function

//----------getHeight Function----------------------------
// This function obtains the height of a specific node in a tree.
// This function uses the getNode function to get the node of the
// object and then it uses the getHeightHelper function to check 
// each branches of the tree to find the height.
//----------------------------------------------------------------
int BinTree::getHeight(const NodeData &nodedata)
{
	Node *curr = root;
	getNode(curr, nodedata);
	return getHeightHelper(curr, nodedata);
}

//----------getHeightHelper Function----------------------------
// This function obtains the length from a specific node to the 
// longest branch that it can form to one of the leaves. The 
// function first checks if the tree is empty. If not, then it 
// recursively checks to see whether the left node or the right
// node will produce the bigger number. It returns that number + 1
// to account for the leaf being 1.
//----------------------------------------------------------------
int BinTree::getHeightHelper(Node *&curr, const NodeData &nodedata)const
{
	if (curr == nullptr)
	{
		return 0;
	}
	else
	{
		int leftHeight = getHeightHelper(curr->left, nodedata);
		int rightHeight = getHeightHelper(curr->right, nodedata);
		if (leftHeight > rightHeight)
		{
			return(leftHeight + 1);
		}
		else
		{
			return(rightHeight + 1);
		}
	}
} // End getHeightHelper function

//----------getNode Helper Function----------------------------
// This function obtains the node with the specific object and
// sets the curr variable to it. It uses binary search tree 
// algorithm to traverse through the tree.
//----------------------------------------------------------------
void BinTree::getNode(Node *&curr, const NodeData &nodedata)
{
	if (curr == nullptr)
	{
		return;
	}
	else if (*curr->data == nodedata)
	{
		return;
	}
	else if (*curr->data > nodedata)
	{
		curr = curr->left;
		getNode(curr, nodedata);
	}
	else if (*curr->data < nodedata)
	{
		curr = curr->right;
		getNode(curr, nodedata);
	}
} // End of getNode Helper

//----------bstreeToArrayHelper Function----------------------------
// This function traverses through the tree in an inorder traversal
// to put the values of the tree into an array. The function uses 
// pointer arithmetic to set the index of the array. The function 
// returns the value of the left and the right to count the number of
// element already in the array and + 1 to move the index 1 step forward.
//----------------------------------------------------------------
int BinTree::bstreeToArrayHelper(Node* root, NodeData* nodedata[])const
{
	if (root == nullptr)
	{
		return 0;   
	}

	int left = bstreeToArrayHelper(root->left, nodedata);
	NodeData *temp;
	temp = root->data;
	root->data = nullptr; 
	*(nodedata + left) = temp; 
	temp = nullptr;
	int right = bstreeToArrayHelper(root->right, nodedata + left + 1);
	return left + right + 1; 
} // End of bstreeToArrayHelper function

//----------bstreeToArray Function----------------------------
// This function calls the bstreeToArrayHelper function to do inorder
// traversal on the tree to put each element in an array. Then, the 
// function empties the tree.
//----------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* nodedata[])
{
	bstreeToArrayHelper(this->root, nodedata);
	this->makeEmpty();
} // End bstreeToArray Function

//----------arrayToBSTree Function----------------------------
// This function converts an array of elements and arranges it 
// as a balanced tree. Given an array of 100, the function looks
// for the indexes of the first and the last non-null element of 
// the array. Then, they are used as parameters for the 
// arrayToBSTreeHelper function.
//----------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData * array[])
{
	makeEmpty(); 
	int last = 0;
	int arraySize = 100;
	while (last < arraySize && array[last] != nullptr)
	{
		last++;
	}
	arrayToBSTreeHelper(array, 0, last - 1, root);
} // End arrayToBSTree Function

//----------arrayToBSTree Function----------------------------
// This function takes in as parameters the array, the first and
// last element of the array that are not null values, and a root
// variable for the root of the tree. The function first sets the 
// base case which is when the first and last become the same. Then,
// it takes a median value of the first and last, which is the middle
// of the array. The function then sets the root to a new node and
// sets the data of the node to the value of the array in the middle.
// After this, the function recursively calls backward to get all the
// left of the tree, and then the right of the tree.
//----------------------------------------------------------------

void BinTree::arrayToBSTreeHelper(NodeData * array[], int first, int last,
	Node *& root)
{
	if (first > last) return;
	int median = (first + last) / 2; 
	root = new Node();
	root->data = array[median];
	array[median] = nullptr;

	arrayToBSTreeHelper(array, first, median - 1, root->left);
	arrayToBSTreeHelper(array, median + 1, last, root->right);
} // End arrayToBSTreeHelper function



void BinTree::displaySideways() const
{
	sideways(root, 0);
}


void BinTree::sideways(Node* current, int level)const
{
	if (current != nullptr)
	{
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

//----------Destructor-----------------------------------------------
// This function is the destructor for the BinTree class. It calls
// the makeEmpty function to delete the tree. 
//----------------------------------------------------------------

BinTree::~BinTree()
{
	this->makeEmpty();
}