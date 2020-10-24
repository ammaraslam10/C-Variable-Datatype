#include <iostream>
#include "var.hpp"
using namespace std;

int main() {
	var operand1, operand2, operation;
	cout << "Enter number 1: ";
	cin >> operand1;
	cout << "Enter number 2: ";
	cin >> operand2;
	cout << "Enter operation (+, -, *, /): ";
	cin >> operation;
	if (operand1.isNumeric() && operand2.isNumeric()) {
		if (operation == "+") {
			cout << operand1 + operand2;
		}
		else if (operation == "-") {
			cout << operand1 - operand2;
		}
		else if (operation == "*") {
			cout << operand1 * operand2;
		}
		else if (operation == "/") {
			if (operand2 == 0) { cout << "Error, division by 0"; }
			else { cout << operand1 / operand2; }
		}
	}
	else {
		cout << "Operation on numbers only.";
	}
}
