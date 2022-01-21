#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// "struct" is just like "class" except that everything is public by default
// You need to define the four functions listed below to use this function.
// You will not be able to use a priority queue without defining the operator function.

struct item {
	string name;
	double value;
	double weight;

	item (double, double);
	item();	
	double ratio() const;
	void print() const;
	bool operator<(const item &) const;
};

//this could all go in item.cpp, but whatevs
item::item(double x, double y)
{
    value =x;
    weight=y;
}

item::item()
{
	name = " ";
	value=0;
	weight=0;
}

double item::ratio() const
{
    return value/weight;
}

void item::print() const
{
    cout<<name<<" "<<value<<" "<<weight<<endl;
}

bool item::operator<(const item & right) const {
    return ratio() < right.ratio(); 
}