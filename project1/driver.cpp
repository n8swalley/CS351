#include "item.h"
#include "pq.h"
#include <ctime>

using namespace std;

int main()
{
    //variable initialization for PQ and items
    int numItems(0);
    int sackCapacity(0);
    double weight(0);
    double value(0);
    double ratio(0);
    string nameOfItem=" ";
    pq<item> priorityQueue;
    item pqItem; //item added to PQ

    //variables for knapsack
    int numSack(0); // not numb sack ;)
    int totalValue(0);
    int totalWeight(0);
    pq<item> knapsack;
    item knapItem; // item dequeued from PQ and enqueued to knapsack PQ
    item sackItem; //item dequeue from knapsack PQ

    //variables for file io and user input
    ifstream fileToReadIn;
    string inputFile = " ";
    ofstream fileToOutput;
    string outputFile=" ";
    
    cout<<"Please enter the filename you'd like to read from: ";
    cin>>inputFile;
    cout<<"\n"; 
    
    fileToReadIn.open(inputFile.c_str()); 

    if(fileToReadIn.fail()) //error handling for file 
    {
        cout << "ERROR: file not found" <<endl;
    }
    else
    {
        fileToReadIn >> numItems>> sackCapacity;        
        for(int i=0; i< numItems; i++)
        {
            fileToReadIn >> nameOfItem >> value >> weight; 
            pqItem = item(value, weight);
            pqItem.name = nameOfItem;
            ratio = pqItem.ratio();
            priorityQueue.enqueue(pqItem);
        }
        // prints the sorted priority queue
        // cout << "\n******SORTED******" << endl;
        // for(int i=0; i< numItems; i++){
        //     item objItem = priorityQueue.dequeue();
        //     objItem.print(); 
        // }
        fileToReadIn.close();
    }
    //let's get greedy!
    for(int i=0;i<numItems;i++)
    {
        knapItem = priorityQueue.dequeue();
        if(totalWeight + knapItem.weight <= sackCapacity)
        {
            knapsack.enqueue(knapItem);
            totalValue = totalValue + knapItem.value;
            totalWeight = totalWeight + knapItem.weight;
            numSack++;
            //knapItem.print();
        }
    }

    //NOTE: you must comment out either the file output or console output:

    // //Want output into a file? Here you go:
    // cout<<"Please enter a filename to store the output: ";
    // cin>>outputFile;
    // fileToOutput.open(outputFile.c_str()); 
    // fileToOutput<<"Number of items in knapsack: "<<numSack<<"\n";
    // fileToOutput<<"Total Weight: "<< totalWeight<<"\n";
    // fileToOutput<<"Total Profit: "<<totalValue<<"\n";
    // fileToOutput<<"\n";
    // fileToOutput<<"Items in the knapsack: "<<"\n";

    // for(int i=0; i<numSack;i++)
    // {
    //     sackItem = knapsack.dequeue();
    //     fileToOutput<<sackItem.name<<" "<<sackItem.value<<" "<<sackItem.weight<<"\n";
    // }

    //Want output in the console? Here you go: 
    cout<<numSack<<endl;
    cout<<totalWeight<<endl;
    cout<<totalValue<<endl;
    cout<<"\n";
    cout<<"Items in the knapsack: "<<endl;
    for(int i=0; i<numSack;i++)
    {
        sackItem = knapsack.dequeue();
        sackItem.print();
    }

    return 0;
}