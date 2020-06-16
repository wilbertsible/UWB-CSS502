//--------------------poly.cpp----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: January 12, 2019
//Date of Last Modification: January 20, 2019
//--------------------------------------------------------------
// This is the header file of the poly class. This lists all the
// functions and operator overloads that were implemented in the
// .cpp file. Also the arr pointer and arraySize properties were
// declared here and set as private. 
//--------------------------------------------------------------

#include <iostream>
using namespace std;
#ifndef POLY_H
#define POLY_H

class Poly
{
private:
	int *arr;
	int arraySize;
public: 
	//Default Constructor
	Poly();

	//Constructor Overloads
	Poly(int coeff, int power);
	Poly(int coeff);
	
	// Copy Constructor
	Poly(const Poly &orig);
	
	// Operator overloads
	Poly operator +(const Poly &addend);
	Poly operator -(const Poly &subtrahend);
	Poly operator *(const Poly &factor);
	
	//Assignment Operator Overloads
	Poly &operator =(const Poly &term);
	Poly operator +=(const Poly &addend);
	Poly operator -=(const Poly &subtrahend);
	Poly operator *=(const Poly &factor);
	
	//Equality and Inequality Operator Overload
	bool operator ==(const Poly &term) const;
	bool operator !=(const Poly &term) const;
	
	//Getters and Setters
	int getCoeff(int power) const;
	void setCoeff(int coeff, int power);
	
	//Helper function
	void expandArray(int size);

	//Stream Operator Friend Function Overloads 
	friend ostream &operator <<(ostream &out, const Poly &polynomial);
	friend istream &operator >>(istream &in, Poly &polynomial);
	
	//Destructor
	~Poly();
};

#endif




