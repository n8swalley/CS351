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
	item(){};	
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

double item::ratio() const
{
    return value/weight;
}

void item::print() const
{
    cout<<name<<" "<<value<<" "<<weight<<endl;
}

/* Compares one item's ratio to another
Function we have to use to choose the max ratio
 10/6/2021: What parameter do we put in there?
 What do we pass it? Ratio.
When we call operator, we have to give it a parameter. What does Gupta have in mind?
We should be able to go through and just sort them
TO pass by reference, do we make a new item and compare it to that?
*/

/*****HERE IS MINE (and the tutor's) IDEA*****/
/*
Conceptual stuff: 

Let's suppose we had two queues: queue1 and queue2.
The positions in queue1 and queue2 go from 0--> n.
For the purpsoes of this example, let's suppose n=2.
So we are only worried about three positions (0,1,2).

At the outset, queue1{3,7,8} and queue2{}

1.)  
	We compare the first two ratios, 3 and 7
		3 is less than 7, so return true.
		Pull 3 out and place in queue2.
			Thus, queue1{7,8} and queue2{3}

2.) 
	Now we have queue1{7,8} and queue2{3}
		7 is less than 8, so return true.
		Pop 3 out and place 7 in queue2
		Place 3 back into queue2
		Pull 7 out and place in queue2.
			Thus, queue1{8} and queue2{7,3}
3.)
	For the last step, there is nothing to compare 8 to, so return false
		... I now realize this whole example is redundant because we are 
		just essentially sorting queue2 regardless of the value we return for queue1
	.... Can't explain it, but the pseudo code should be more correct


I will finish the pseudocode tonight!
Pseudocode:
if(return is false){


}




*/

/*
//Already compares the ratios for us, but having the node tells you how to compare items
item is a struct, so it cannot compare the user-defined struct until you have the bool function
*/
bool item::operator<(const item & right) const {
    return ratio() < right.ratio(); 
/*
	return false;
	return true;
*/
}