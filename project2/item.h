#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct item 
{
	string name;
	double value;
	double weight;

	item (double, double);
	item();	
	double ratio() const;
	void print() const;
	bool operator<(const item &) const;
};

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

bool item::operator<(const item & right) const 
{
    return ratio() < right.ratio(); 
}