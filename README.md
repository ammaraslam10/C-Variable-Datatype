# C-Variable-Datatype
Note: It isn't the most efficient in terms of space and time, but it isn't intended to be.

A C++ class that can store data of type null, integer, double and string while keep a track of the datatype and performing operations according to the type.
Sort of like C# dynamic. Currently, array/custom types are not supported

```C++
#include <iostream>
#include "var.hpp"
using namespace std;

int main() {
	/*
	Features: 		* Non-strict variable type, can cin or cout any string, integer, double, float and it will 
				  automatically detect and assign type.
				* Regular operators +, -, /, *, %, +=, -=, /=, *=, %=, ++, -- all work as expected without a care for the types
				  on left and right hand side. (Strings will not subtract).
				* Can compare var with any other type including var (<, >, ==, >=, <=, !=), "1.1" is equal to 1.1
				* Can typecast var into other types and other types into var.
				* [] notation works for var (If var is stored as a double, a single character can be obtained through 
				  this but this will not allow the editing of a double (i.e. var a = 10; a[1] = 2; (a is still 10)))
	Functions: 	
				.equals()		Strict check, "1.1" is not equal to 1.1
				.type()			Returns a character representing type ('n', 'i', 'd', 's')
				.isInt()		Check whether var is int (string that is integer or int)
				.isNumeric()		Check whether var is numeric (string that contains number or double/float/int)
				.toString()		Get the string representation
				.convertInt()		Forces var to be int, sets it to 0 if it isn't double
				.convertDouble()	Forces var to be a double, sets it to 0 if it isn't double
				.convertString()	Forces var to be a string, sets "null" in case of null
				.clear()		Empty the var and set it to null
				.parseInt()		Return int from var, "112a1d2" will be parsed as 11212, 
				.parseFloat()	Return float from var, "11.2a1.d2" will be parsed as 11.212, 
				.parseString()	Return string from var, 11.212 will be parsed as "11.212", 
	*/
	var a = 10; 
	var b = "10"; 

	if (a == b) { 
		// They are equal by regular comparison
		cout << "10 == 10" << endl; 
	} 	

	if (a.equals(b)) { 
		// They are not equal by strict comparison
		cout << "10 is 10 with matching datatype" << endl; 
	} 	

	// a is internally integer, a+1 = 11
	cout << "10 + 1 = " << a + 1 << " (" << a.type() << ")" << endl; 
	// b is internally string, b+1= 101
	cout << "10 + 1 = " << b + 1 << " (" << b.type() << ")" << endl;

	// b is now internally an integer, b+1= 11
	b.convertInt();
	cout << "10 + 1 = " << b + 1 << " (" << b.type() << ")" << endl;

	// Automatic input type
	var c;
	cin >> c;
	cout << c.type();
}
```
