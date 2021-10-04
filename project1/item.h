#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// "struct" is just like "class" except that everything is public by default
// You need to define the four functions listed below to use this function.
// You will not be able to use a priority queue without defining the operator function.

struct Item {
	string name;
	double value;
	double weight;
	
	Item (double, double);	
	double ratio() const;
	void print() const;
	bool operator<(const Item &) const;
};

// Compares one item's ratio to another
bool Item::operator<(const Item & right) const {
    // Fill this in here!
}