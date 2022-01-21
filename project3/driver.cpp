//---------------------------------------------------
// 
// Author: N8 Swalley & Adam Crozier 
// Date: 12/2/2021
//
// Backtracking approach to the 0-1 knapsack problem 
//
//---------------------------------------------------

#include "item.h"
#include "pq.h"

using namespace std;

// global variables as instructed by the book (pg 243)
int maxProfit(0); 
int numItems(0);
int profitSoFar(0);
int weightSoFar(0);
int capacity(0);

item * items(nullptr);
bool * bestSet(nullptr); 
bool * include(nullptr); 

// Pseudocode found on page 242 in the book
bool promising(int i, int profitSoFar, int weightSoFar)
{
    int j(0); 
    int k(0);
    int totWeight(0);
    float bound(0);

    // Node is promising only if we should expand to its children. There must be some capacity left for children. 
    if (weightSoFar >= capacity)
    {
        return false;
    }
    else
    {
        j = i+1;
        bound = profitSoFar;
        totWeight = weightSoFar;

        while ((j <= numItems) && (totWeight + items[j].weight <= capacity)) 
        {
            totWeight += items[j].weight;
            bound += items[j].value;
            j++;
        }
        k = j;

        if (k <= numItems)
        {
            bound = bound + (capacity - totWeight)*(items[k].ratio());
        }
        return bound > maxProfit; 
   }
 }

// Pseudocode found on page 242 in the book
void knapsack(int i, int profitSoFar, int weightSoFar)
{
    if (weightSoFar <= capacity && profitSoFar > maxProfit)
    {
        maxProfit = profitSoFar;
        for (int x=0; x <= numItems; x++)
        {
            bestSet[x] = include[x];
        }
    }

    if (promising(i, profitSoFar, weightSoFar))
    {
        include[i] = true;
        knapsack(i+1, profitSoFar + items[i+1].value, weightSoFar + items[i+1].weight);
        include[i] = false;
        knapsack (i+1, profitSoFar, weightSoFar);
     }
}

int main()
{
    // item data
    double weight(0);
    double value(0);
    double ratio(0);
    string nameOfItem(" ");

    // file io and user input data
    ifstream fileToReadIn;
    string inputFile = " ";
    cout<<"Please enter the filename you'd like to read from: ";
    cin>>inputFile;

    fileToReadIn.open(inputFile.c_str()); 

    // error handling for if file not found
    if (fileToReadIn.fail())
    {
        cout<< "ERROR: file not found" <<endl;
        return 0;
    }

    fileToReadIn >> numItems >> capacity;

    // Array initialization
    items = new item [numItems+1];
    include = new bool [numItems];
    bestSet = new bool [numItems];

    // priority queue to store item objects 
    pq<item> pQueue;

    // create item objects and read in their values from a file
    for(int loopVar1=0; loopVar1< numItems; loopVar1++)
    {
        fileToReadIn >> nameOfItem >> value >> weight; 
        item itemObj = item(value, weight);
        itemObj.name = nameOfItem;
        pQueue.enqueue(itemObj);
    }

    fileToReadIn.close();

    // sort items in PQ in nonincreasing order based on ratio (value/weight)
    for(int loopVar2=1; loopVar2<= numItems; loopVar2++)
    {
        items[loopVar2] = pQueue.dequeue();
    }

    // Let's Backtrack the Knapsack!
    knapsack(0,0,0);

//    // print values in bestSet
//     cout << "\nBest Set:" << endl;
//     for(int i=0; i<numItems;i++)
//     {
//         cout<< items[i+1].name << " best set: " << bestSet[i]<<endl;
//     }

    // knapsack data
    int numSacked(0);
    int totalWeight(0);
    int totalValue(0);

    // print numItems and capcaity
    cout<< "\nNumber of items considered: "<<numItems<<endl;
    cout<<"Knapsack capactiy: "<< capacity<<endl;

    // print optimal items from bestSet
    cout <<"\nOptimal Knapsack Items: "<<endl;
    
    for(int loopVar3 = 0; loopVar3 < numItems; loopVar3++)
    {
        if(bestSet[loopVar3]==true)
        {
            items[loopVar3+1].print();
            totalWeight += items[loopVar3+1].weight;
            totalValue += items[loopVar3+1].value;
            numSacked++;
        }
    }

    // print knapsack data
    cout<< "\nNumber of knapsack items: " << numSacked << endl;
    cout<< "Total weight: " << totalWeight<< " lbs" << endl;
    cout<< "Total profit: " << totalValue<< " pesos" << endl;

    return 0;
}