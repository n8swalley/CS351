#include <fstream>
#include <ctime>
#include <iostream>

using namespace std;

//NOTE: this program is currently already in the driver as a function. 
//NOTE: this program is designed to be compiled and ran before the driver.cpp
//NOTE: for this to work, comment out lines 63-89 in driver.cpp, then change the filename to "test.txt" where the file is opened.  
//NOTE: then compile createInputFile.cpp and then driver.cpp

int main()
{
    ofstream myFile;
    myFile.open("test.txt");

    int numItems(0);
    int knapCapacity(0);
    int itemName(0); //item name is a number based on numItems;
    int itemValue(0);
    int itemWeight(0);

    while(knapCapacity<=0||numItems<=0)
    {
        cout<<"\n";
        cout<< "Please enter the number of items: ";
        cin>> numItems;
        cout<<"\n";
        cout<< "Please enter the Knapsack capacity: ";
        cin>> knapCapacity;
        cout<<"\n";
    }

    myFile<<numItems<<" "<<knapCapacity<<"\n"; //inserts first 2 values in first line of file
    srand(time(NULL)); //random num generation

    for(int i=0; i<numItems; i++)
    {
        itemName = i+1; //change this to strings in future?
        itemWeight = rand()%(3*numItems) +1; // random values from 1 to 3n
        itemValue = rand()%(numItems*2) + 1; // random values from 1 to 2n
        myFile << itemName << " " << itemValue << " " << itemWeight << endl;
    }
    myFile.close();
    //return nameOfInputFile;
    return 0;
}
