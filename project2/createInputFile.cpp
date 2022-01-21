#include <fstream>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    //variables for input items
    int numItems(0);
    int knapCapacity(0);
    int itemName(0); 
    int itemValue(0);
    int itemWeight(0);
    srand(time(NULL)); //random num generation
    //
    //variables for input file
    ofstream myFile;
    string filename=" ";

    cout<<"Please enter the filename you'd like to create: ";
    cin>>filename;
    cout<<"\n"; 
    
    myFile.open(filename.c_str());

    while(knapCapacity<=0||numItems<=0) //forces user to input something greater than 0
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

    for(int i=0; i<numItems; i++)
    {
        //Gupta: you didn't say names had to be chars or strings... so it's an int :)
        itemName++;
        itemWeight = rand()%(3*numItems) +1; // random values from 1 to 3n
        itemValue = rand()%(numItems*2) + 1; // random values from 1 to 2n
        myFile << itemName << " " << itemValue << " " << itemWeight << endl;
    }
    myFile.close();
    return 0;
}
