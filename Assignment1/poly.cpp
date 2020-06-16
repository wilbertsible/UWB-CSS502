//--------------------poly.cpp----------------------------------
//Wilbert Lim Sible CSS502A
//Creation Date: January 12, 2019
//Date of Last Modification: January 20, 2019
//--------------------------------------------------------------
// This is the implementation file of the polynomial program. 
// The program takes in a pair of numbers. The first represents
// the coefficient of the polynomial, and the second takes the 
// power of the polynomial. The program does operations on the 
// polynomial objects such that operations such as addition, 
// subtraction and multiplication can be done on the polynomial
// objects. 
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

#include<iostream>
#include "poly.h"
using namespace std;


//----------Poly constructor(2 parameters)----------------------
// This constructor takes in two parameters, the coefficient and
// the power of the polynomial. It sets the arraySize to 0 and
// calls the setCoefficient to create the polynomial.
//--------------------------------------------------------------
Poly::Poly(int coeff, int power)
{	
	arraySize = 0;
	setCoeff(coeff, power);
}// End of Poly constructor(2 parameters)

//----------Poly constructor(1 parameters)----------------------
// This constructor takes in one parameters, the coefficient and
// sets the power of the polynomial to zero. It sets the arraySize 
// to 0 and calls the setCoefficient to create the polynomial.
//--------------------------------------------------------------
Poly::Poly(int coeff)
{
	arraySize = 0;
	setCoeff(coeff, 0);
}// End of Poly constructor(1 parameters)


//----------Poly constructor(No parameters)----------------------
// This constructor overloads the default constructor. It sets 
// sets coefficient and the power of the polynomial to zero. It 
// sets the arraySize to 0 and calls the setCoefficient to 
// create the polynomial.
//--------------------------------------------------------------
Poly::Poly()
{
	arraySize = 0;
	setCoeff(0, 0);
}// End of Poly constructor(2 parameters)

//----------Copy constructor-------------------------------------
// This is the copy constructor. It initializes te arraySize to
// zero, then traverses through arr to copy each polynomial term.
//---------------------------------------------------------------
Poly::Poly(const Poly &orig)
{
	arraySize = 0;
	for (int i = orig.arraySize - 1; i >= 0; i--)
	{
		setCoeff(orig.arr[i], i);
	}
}// End of copy constructor


//----------getCoeff--------------------------------------------
// This method returns the coefficent of a polynomial at a given
// power. Since the polynomial does not have negative
// exponents, if the power provided is negative, the method will
// return 0.
//--------------------------------------------------------------
int Poly::getCoeff(int power) const
{
	if (power < 0) 
	{
		return 0;
	}
		return arr[power];
}//End of getCoeff

//----------setCoeff--------------------------------------------
// The setCoeff method sets the coefficient at the index of 
// power. If the power given is negative, then it exits the 
// function. If the arraySize is 0 (unpopulated) or is less than 
// or equal to the arraySize, the array is expanded. Then the
// coefficient at that power to the given coefficient is set to
// the given value.
//--------------------------------------------------------------
void Poly::setCoeff(int coeff, int power) 
{
	if (power < 0) 
	{
		return;
	}
	if (arraySize == 0 || power >=arraySize)
	{
		expandArray(power + 1);
	}
	arr[power] = coeff;
}// End of setCoeff

//----------expandArray-----------------------------------------
// The expandArray function sets the size of the array to the 
// new size. If the arraySize is 0, new array with size newSize 
// is created and all available indexes are set to 0. If there 
// is an existing array, a new array is created and the contents
//of the old array is transfered to the new array.
//--------------------------------------------------------------
void Poly::expandArray(int newSize)
{
	if (arraySize == 0) //Empty array
	{
		arraySize = newSize;
		arr = new int[newSize];
		for (int i = 0; i < arraySize; i++)
		{
			arr[i] = 0;
		}
	}
	else
	{
		int originalSize = arraySize;
		arraySize = newSize;
		int *newArr = arr;
		arr = new int[newSize];
		for (int i = 0; i < arraySize; i++)
		{
			arr[i] = 0;
		}
		for (int i = 0; i < originalSize; i++)
		{
			arr[i] = newArr[i];
		}
		delete[] newArr;
	}
} // End of expandArray

//----------Additon Operator Overload---------------------------
// Overloads the addition operator. This adds two polynomials.
// A variable newPoly is first declared. Then the function 
// checks to see if the arraySize of the second addend is bigger
// than the size of the first addend. If so, expand the array of
//  newPoly to the size of the second addend, copy the coefficient 
// of the second array with indexes greater than the index of the
// first addend, then add the coefficients of the arrays at 
// the specific index. If the arraySize of the first addend is
// bigger, then just add the coefficients per index and place 
// the resulting values to newPoly. Lastly, return newPoly.
//--------------------------------------------------------------
Poly Poly::operator +(const Poly &addend)
{
	Poly newPoly;
	if(addend.arraySize > this->arraySize)
	{
		newPoly.expandArray(addend.arraySize);
		for (int i = addend.arraySize-1; i > this->arraySize-1; i--)
		{
			newPoly.setCoeff(addend.arr[i], i);
		}
		
		for (int i = this->arraySize-1; i >= 0; i--)
		{
			int sum = addend.arr[i] + this->arr[i];
			newPoly.setCoeff(sum, i);
		}
	}
	else
	{
		for (int i = this->arraySize-1; i > addend.arraySize-1; i--) 
		{
			newPoly.setCoeff(this->arr[i], i);
		}
		for (int i = addend.arraySize-1; i >= 0; i--)
		{
			int sum = addend.arr[i] + this->arr[i];
			newPoly.setCoeff(sum, i);
		}
	}
	return newPoly;

} //Ends Addition operator overload

//----------Subtraction Operator Overload---------------------------
// Overloads the subtraction operator. This subtracts two 
// polynomials. A variable newPoly is first declared. Then the 
// function checks to see if the arraySize of the subtrahend is 
// bigger than the size of the minuend. If so, expand the array 
// of newPoly to the size of the subtrahend, copy the coefficient 
// of the second array with indexes greater than the index of the
// minuend and set to negative, then subtract the coefficients of 
// the arrays at the specific index. If the arraySize of the  
// minuend is bigger, then just subtract the coefficients per index 
// and place the resulting values to newPoly. Lastly, return newPoly.
//------------------------------------------------------------------
Poly Poly::operator -(const Poly &subtrahend)
{
	Poly newPoly;
	if (subtrahend.arraySize > this->arraySize)
	{
		newPoly.expandArray(subtrahend.arraySize);
		for (int i = subtrahend.arraySize - 1; i > this->arraySize - 1; i--)
		{
			newPoly.setCoeff(-subtrahend.arr[i], i);
		}

		for (int i = this->arraySize - 1; i >= 0; i--)
		{
			int diff = this->arr[i] - subtrahend.arr[i];
			newPoly.setCoeff(diff, i);
		}
	}
	else
	{
		for (int i = this->arraySize - 1; i > subtrahend.arraySize - 1; i--)
		{
			newPoly.setCoeff(this->arr[i], i);
		}
		for (int i = subtrahend.arraySize - 1; i >= 0; i--)
		{
			int diff = this->arr[i] - subtrahend.arr[i];
			newPoly.setCoeff(diff, i);
		}
	}
	return newPoly;

}//Ends the Subtraction Operator Overload

//----------Multiplication Operator Overload-------------------------
// Operator overload for the multiplication operation. This multiplies
// two polynomials. When multiplying two polynomials, the highest
// power is the addition of the highest power of both polynomial 
// -1. This was done using the expandArray. Then one polynomial was
// traversed while multiplying with one term of the second polynomial.
// This was done to each of the second polynomial and the resulting 
// products were added together. 
//-------------------------------------------------------------------
Poly Poly::operator *(const Poly &factor)
{
	Poly newPoly;
	newPoly.expandArray(this->arraySize + factor.arraySize - 1);
	for (int i = 0; i < this->arraySize; i++) 
	{
		Poly tempPoly;
		tempPoly.expandArray(this->arraySize + factor.arraySize - 1);
		for (int j = 0; j < factor.arraySize; j++) 
		{
			int newCoeff = this->arr[i] * factor.arr[j];
			int newPower = i + j;
			tempPoly.setCoeff(newCoeff, newPower);
		}
		for (int k = 0; k < tempPoly.arraySize; k++) 
		{
			int newCoeff2 = tempPoly.arr[k] + newPoly.arr[k];
			newPoly.setCoeff(newCoeff2, k);
		}
	}

	return newPoly;
}// End of multiplication operator

//----------Equality Operator Overload-------------------------------
// Operator overload for the equality operation. This checks if two
// polynomials are equal or the same. The method first checks if 
// both polynomials have the same arraySize. If they are not then
// return false, else, check each term if they are the same.
// If they are all the same, then return true, else return false.
//-------------------------------------------------------------------
bool Poly::operator ==(const Poly &term) const
{
	if (this->arraySize != term.arraySize)
	{
		return false;
	}
	for (int i = 0; i < this->arraySize; i++)
	{
		if (this->arr[i] != term.arr[i])
		{
			return false;
		}
	}
	return true;
} //End Equality Operator Overload

//----------Inequality Operator Overload-----------------------------
// Operator overload for the inequality operation. This checks if two
// polynomials are not equal. The method first checks if 
// both polynomials have different arraySize. If they are not then
// return true, else, check each term if they are not the same.
// If they are all the same, then return false, else return true.
//-------------------------------------------------------------------
bool Poly::operator !=(const Poly &term) const
{
	if (this->arraySize != term.arraySize)
	{
		return true;
	}
	for (int i = 0; i < this->arraySize; i++)
	{
		if (this->arr[i] != term.arr[i])
		{
			return true;
		}
	}
	return false;
} //End Inequality Operator Overload


//----------Assignment Operator Overload-----------------------------
// Operator overload for the assignment operation. This assigns the 
// values of a polynomial to a Polynomial variable. The method first 
// uses the inequality operator overload to check if the polynomial
// to be assigned is not equal to the variable being assigned. This
// saves on computing operations. If they are not the same, then
// change the variable's array to the array size of the rvalue
// and copy each coefficients of the rvalue to the variable.
//-------------------------------------------------------------------
Poly &Poly::operator =(const Poly &term) 
{
	if (*this != term) {
		this->expandArray(term.arraySize);
		for (int i = 0; i < term.arraySize; i++) 
		{
			this->setCoeff(term.arr[i], i);
		}
	}
	return *this;
} // Ends Assignment Operator Overload

//----------Addition Assignment Operator Overload--------------------
// Operator overload for the addition assignment operator. It adds
// the lvalue to the rvalue and sets the lvalue to the result of that
// operation. Since the additon operator was already overloaded, it
// can be used to perform the operation.
//-------------------------------------------------------------------
Poly Poly::operator +=(const Poly &addend)
{
	*this = *this + addend;
	return *this;
} // Ends Addition Assignment Operator Overload

//----------Subtraction Assignment Operator Overload-----------------
// Operator overload for the subtraction assignment operator. It 
// subtracts the lvalue to the rvalue and sets the lvalue to the 
// result of that operation. Since the subtraction operator was  
// already overloaded, it can be used to perform the operation.
//-------------------------------------------------------------------
Poly Poly::operator -=(const Poly &addend)
{
	*this = *this - addend;
	return *this;
} // Ends Subtraction Operator Overload

//----------Multiplication Assignment Operator Overload--------------
// Operator overload for the multiplication assignment operator. It 
// multiplies the lvalue to the rvalue and sets the lvalue to the 
// result of that operation. Since the multiplication operator was  
// already overloaded, can be used to perform the operation.
//-------------------------------------------------------------------
Poly Poly::operator *=(const Poly &addend)
{
	*this = *this * addend;
	return *this;
} // Ends Multiplication Operator Overload

//----------Instream Operator Overload------------------------------
// Overloads the instream operator. The instream operator gets a 
// pair of numbers, then checks to see if both are not equal to -1
// (sentinel value). If both numbers are not -1, the secon number is
// checked to see if it is negative. If it is, the number is 
// multiplied by -1 to change it to a positive number. Then both 
// numbers are entered using the setCoeff function.
//-------------------------------------------------------------------
istream &operator >> (istream &in, Poly &polynomial)
{
	
	int num1, num2;
	in >> num1;
	in >> num2;
	
	while (!(num1 == -1 && num2 == -1)){ // Sentinel Value
		if (num2 < -2) 
		{
			num2 = num2 * -1;
		}
		polynomial.setCoeff(num1, num2);
		cin >> num1;
		cin >> num2;
	}
	return in;
} // Ends Instream Operator Overload

//----------Outstream Operator Overload------------------------------
// Overloads the outstream operator. Firs, the polynomial is checked
// to see if it contains aanything. If it doesn't, the output given
// is 0. Otherwise, the array is traversed and anything other than 
// index one and zero are set to the format Ax^n, where A is an 
// integer and n is the power. If n = 1 or the index 1 of the array
// is printed, it is printed in the format Ax. Lastly, if n = 0 or
// the index is at 0, then only A is printed.
//-------------------------------------------------------------------

ostream &operator <<(ostream &out, const Poly &polynomial) 
{
	if (polynomial.arraySize == 1 && polynomial.arr[0] == 0) {
		out << "0";
	}
	else
	{
		for (int i = polynomial.arraySize - 1; i >= 0; i--)
		{
			if (i > 1 && polynomial.arr[i] != 0)
			{
				if (polynomial.arr[i] > 0)
				{
					cout << " +";
				}
				else
				{
					cout << " ";
				}
				out << polynomial.arr[i];
				out << "x^";
				out << i;
				
			}
			else if (i == 1 && polynomial.arr[1] != 0)
			{
				if (polynomial.arr[1] > 0)
				{
					cout << " +";
				}
				else
				{
					cout << " ";
				}
				out << polynomial.arr[1];
				out << "x";
				
			}
			else if (i == 0 && polynomial.arr[0] != 0)
			{
				if (polynomial.arr[0] > 0)
				{
					cout << " +";
				}
				else
				{
					cout << " ";
				}
				out << polynomial.arr[0];
			}
			
		}
	}
	return out;
} // End Outstream Operator Overload

//----------Destructor-----------------------------------------------
// This is the destructor of the class. If the fuction goes out of 
// scope or the delete []arr is invoked, then the destructor is
// called which frees up the array.
//-------------------------------------------------------------------
Poly::~Poly()
{
	delete[] arr;
} // End Destructor





