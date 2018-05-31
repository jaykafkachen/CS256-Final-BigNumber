#ifndef _BIGNUMBER_H
#define _BIGNUMBER_H

#include <vector>
using namespace std;
#include <iostream>
using namespace std;

/** @ BigNumber class used for calculations with numbers larger than standard int size.

@author Jay Chen 
@course CS 256 
@professor Nima Davarpanah
@date May 30, 2018
*/

class BigNumber
{
  private:
	/**< vector of digits, each index storing one digit*/
    vector<int> numbers; 
	/**< stores the number of digits in the BigNumber*/
    int size; 
  public:
	  /**no argument constructor*/
    BigNumber(); 
	/**pass in a long and a size for the digits to quickly create a BigNumber*/
    BigNumber(long num, int sz); 
	/**Copy constructor, given one BigNumber copy the values into the newly constructed one*/
    BigNumber(const BigNumber& bn); 
	/**construct a BigNumber from an existing vector of int digits and the desired size*/
    BigNumber(vector<int> nums, int digits); 
	/**sets the parameters numbers and size to the new values copied from the passed argument*/
    BigNumber operator = (BigNumber const &num); 

	/**returns true if this == num*/
    bool operator ==(BigNumber const &num); 
	/**returns true if this > num*/
    bool operator > (BigNumber const &num); 
	/**returns true if this < num*/
    bool operator < (BigNumber const &num); 
	/**returns true if this >= num*/
    bool operator >= (BigNumber const &num); 
	/**returns true if this <= num*/
    bool operator <= (BigNumber const &num); 

	/**loops through numbers backwards, prints digits in correct order*/
    void print(); 
	/**access the element of numbers[i] from outside the original BigNumber object*/
    int at(int i) const; 
	/**returns this->numbers*/
    vector<int> digits() const;
	/**returns this->size*/
    int getSize() const; 
	/**returns the most significant (nonzero) digit*/
    int sigDigit(); 
	/**sets the digit at numbers[index] to the int value*/
    bool set(int value, int index); 
	/**sets numbers to the new vector<int> newval*/
    void setVector(vector<int> newval);
	/**sets this->size to int newsize*/
    void setSize(int newsize); 

	/**overloaded unary operator for basic addition*/
    BigNumber operator + (BigNumber const &num); 
	/**overloaded unary operator for basic subtraction. does not support negative numbers, returns 0 instead*/
	BigNumber operator - (BigNumber const &num);
	/**overloaded unary operator for basic multiplication*/
	BigNumber operator * (BigNumber const &num);
	/**overloaded unary operator for basic division. generates and prints a division by zero error if the denominator num = 0. will return 0 if num>*this*/
	BigNumber operator / (BigNumber const &num);
	/**overloaded unary operator for basic modulo function*/
	BigNumber operator % (BigNumber const &num); 
};


/**
Big Numbers Library

The creators of C++ have created primitive data types to allow developers to store numbers of various size they expect most users to need. Such as short and int. 

In our case we want to expand on these primitive data types and allow users to store big numbers that can be up to 10,000 digits long. In order to do this you will create a BigNumbers class that will use vectors from the STL to store the digits. BigNumbers should have the same functionality as other numerical storing data types. Hence they should be able to:

Add / Subtract / Multiply / Divide / Mod

All of the operations listed above should be completed using operator overloading, ADD “+” operator, SUBTRACT “-”…etc.
*/

#endif