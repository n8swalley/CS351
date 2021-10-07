#include "item.h"
#include "pq.h"
#include <ctime>

using namespace std;


//NOTE: this function is also its own program in createInputFile.cpp
//NOTE: it is designed to be compiled and ran before the driver.cpp
//NOTE: for this to work, comment out lines 63-89 in driver.cpp, then change the filename to "test.txt" where the file is opened.  

string createInputFile() //creates input file with n items and W capacity. creates random values and weights to items and returns the filename
{
    int numItems(0);
    int knapCapacity(0);
    int itemName(0); 
    int itemValue(0);
    int itemWeight(0);
    //allow user to input filename cuz why not
    ofstream myFile;
    string nameOfInputFile = "";
    cout<<"\n";
    cout<<"Please enter the filename you'd like to create: ";
    cin>>nameOfInputFile;
    myFile.open(nameOfInputFile.c_str());

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
        itemName = i+1; //easy way to get an item name... maybe think of a better way to get strings
        itemWeight = rand()%(3*numItems) +1;
        itemValue = rand()%(numItems + 100) + 1; // random values from 1 to (n+100)
        myFile << itemName << " " << itemValue << " " << itemWeight << endl;
    }
    myFile.close();
    return nameOfInputFile;
}

int main()
{
    //variable initialization for Knapsack items
    int numOfItems(0);
    int sackCapacity(0);
    double weight(0);
    double value(0);
    double ratio(0);
    string nameOfItem=" ";

    //variable initialization for user inputs
    char userChoice =  ' ';
    ifstream fileToReadIn;
    string inputFile = " ";

    //gives user option to create new file or read from existing
    cout<< "Would you like to: "<<endl;
    cout<<"    a.) generate an input file" <<endl;
    cout<<"    b.) read from an existing file"<<endl;
    cout<<"Please enter your choice (a/b): ";
    cin>> userChoice;

    if (userChoice=='a') //create input file
    {
        inputFile = createInputFile(); //this function creates input items & returns the name of the file
    }
    else if(userChoice=='b') //read existing file
    {
        cout<<"\n";
        cout<<"Please enter the filename you'd like to read from: ";
        cin>>inputFile;
        cout<<"\n";
    }
    else
    {
        //create input file by default
        cout<<"ERROR: invalid input. By default, a new file will be generated."<<endl;
        inputFile = createInputFile();
        cout<<"\n";
    } 
    
    fileToReadIn.open(inputFile.c_str()); //replace with "test.txt" if u want to run createInputFile.cpp

    if(fileToReadIn.fail()) //error handling for file 
    {
        cout << "ERROR: file not found" <<endl;
    }
    else
    {
        //read in first two values for num items and sack capacity;
        fileToReadIn >> numOfItems>> sackCapacity;

        // //just checking the values
        // cout << "Number of items in file: " << numOfItems;
        // cout<<"\n";
        // cout << "Knapsack Capacity: "<< sackCapacity;
        // cout<<"\n";
        
        //initialize a priority queue
        pq<item> myPQ;
        
        for(int i=0; i< numOfItems; i++)
        {
            fileToReadIn >> nameOfItem >> value >> weight; 
            item myItem = item(value, weight);
            myItem.name = nameOfItem;
            ratio = myItem.ratio(); 

            //prints the item info
            //myItem.print();

            myPQ.enqueue(myItem);

            //prints items in priority queue 
            node<item> * nodePtr = new node<item>(myItem);
            myPQ.print(nodePtr);
        }
        fileToReadIn.close();
    }
    //let's get greedy! <implement greedy algorithm>>
    /* 1. Make a knapsack */
        pq<item> knapsack;
    /* Int to keep track of items in sack*/
        int numSack=0;
        int totalValue=0;
        int totalWeight=0;

        //N8's failed attempt: how tf do I use item.operator<(crap)??????
        
    // pq<item> knapsack;
    // item knapItem;
    // cout<<"\n";
    // cout<<"Knapsack: "<<endl;
    // for(int i=0;i<numOfItems;i++)
    // {
    //     item dequeueItem;
    //     dequeueItem = myPQ.dequeue();
    //     if(totalWeight + dequeueItem.weight < sackCapacity)
    //     {
    //         //if(dequeueItem.operator<()) // help here pls?
    //          {
    //             knapsack.enqueue(dequeueItem);
    //             totalValue = totalValue + dequeueItem.value;
    //             totalWeight = totalWeight + dequeueItem.weight;
    //             numItemSack++;
    //             cout<<"numSack: "<<numItemSack<<endl;
    //             node<item> * nodePtr = new node<item>(dequeueItem);
    //             knapsack.print(nodePtr);
    //         }

    //     }
    // }

    return 0;
}