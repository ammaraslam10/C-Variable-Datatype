# C-Variable-Datatype
Note: It isn't the most efficient in terms of space and time, but it isn't intended to be.

A class that can store data of type null, integer, double and string while keep a track of the datatype and performing operations according to the type.
Sort of like C# dynamic. Currently, array/custom types are not supported

```C++
#include <iostream>
#include "var.hpp"
using namespace std;

int main() {
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
