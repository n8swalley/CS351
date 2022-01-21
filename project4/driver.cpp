//---------------------------------------------------
// 
// Author: N8 Swalley & Adam Crozier 
// Date: The date in which it is due
//
// Branch and Bound approach to the 0-1 knapsack problem 
//
//---------------------------------------------------

#include "item.h"
#include "pq.h"

using namespace std;

bool * bestSet(nullptr); 
bool * include(nullptr); 

float bound (item u, int numItems, int capacity, const item * items);

int knapsack(int numItems, const item * items, int capacity);

int main()
{
    // item data
    double weight(0);
    double value(0);
    double ratio(0);
    string nameOfItem(" ");

    // knapsack data
    int numItems(0);
    int profitSoFar(0);
    int weightSoFar(0);
    int capacity(0);

    // file io and user input data
    ifstream fileToReadIn;
    string inputFile = " ";
    cout<<"Please enter the filename you'd like to read from: ";
    cin>>inputFile;

    fileToReadIn.open(inputFile.c_str()); 

    if (fileToReadIn.fail())
    {
        cout<< "ERROR: file not found" <<endl;
        return 0;
    }
    fileToReadIn >> numItems >> capacity;

    // Array initialization
    item * items = new item [numItems];
    include = new bool[numItems];
    bestSet = new bool[numItems];

    // priority queue to store item objects 
    //pq<item> pQueue;

    // create item objects and read in their values from a file
    for(int loopVar1=0; loopVar1< numItems; loopVar1++)
    {
        fileToReadIn >> nameOfItem >> value >> weight; 
        item itemObj = item(value, weight);
        itemObj.name = nameOfItem;
        //pQueue.enqueue(itemObj);
        items[loopVar1] = itemObj;
    }

    // sorting the items based on ratio
    for (int i=0; i<numItems-1; i++)
    {
        for(int j=0; j< numItems-i-1; j++)
        {
            if (items[j].ratio() < items[j+1].ratio())
            {
                item tempItem = items[j];
                items[j] = items[j+1];
                items[j+1] = tempItem; 
            }
        }
    }

    fileToReadIn.close();

    // Let's Backtrack the Knapsack!

    int maximumProfit(0);
    maximumProfit = knapsack(numItems,items,capacity);

    cout<< "Maxiumum profit of optimal solution = " << maximumProfit <<endl;

    return 0;
}

float bound(item u, int numItems, int capacity, const item * items)
{
    int j(0);
    int k(0);
    int totweight(0);
    float result(0);
    
    if (u.weight >= capacity)
    {
        return 0;
    }

    int profitBound = u.value;
    for(int x=0; x<numItems; x++)
    {
        bestSet[x] = include[x];
    }

    j = u.level + 1;

    totweight = u.weight;

    while ((j < numItems) && (totweight + items[j].weight <= capacity))
    {
        totweight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    if (j < numItems)
    {
        profitBound += (capacity -totweight) * items[j].ratio();
    }
    return profitBound;
}

// Best-First Search with Branch and Bound from the book
int knapsack(int numItems, const item * items, int capacity)
{
    pq<item> pQueue;
    item u,v;

    // initalize include array
    for(int x=0; x<numItems; x++)
    {
        include[x] = false;
    }

    u.level = -1; // dumby node
    u.value = 0;
    u.weight = 0;

    int maxProfit(0);
    pQueue.enqueue(u);
    //include[u.level] = true;
    //cout<<"u level0 " <<u.level<<endl;

    while (!pQueue.empty())
    {
        u = pQueue.dequeue();

        if (u.level == -1)
        {
            v.level = 0;
        }
        if (u.level == numItems - 1)
        {
            continue;
        }
        v.level = u.level + 1;
        //include[u.level] = true;
        //cout<<"u level1 " <<u.level<<endl;

        v.weight = u.weight + items[v.level].weight;
        v.value = u.value + items[v.level].value;

        if (v.weight <= capacity && v.value > maxProfit)
        {
            maxProfit = v.value;
        }

        v.bound = bound(v, numItems, capacity, items);

        if (v.bound > maxProfit)
        {
            pQueue.enqueue(v);
            //cout<<"u level " <<u.level<< " true" <<endl;
            //include[u.level] = true;
        }

        v.weight = u.weight;
        v.value = u.value;
        v.bound = bound(v, numItems, capacity, items);

        if (v.bound > maxProfit)
        {
            pQueue.enqueue(v);
        }
            // cout<<"u level " <<u.level<< " false" <<endl;
            // include[u.level] = true;
            // //v.print();
    }


    // printing solution: 
    int numSacked(0);
    int totalWeight(0);
    int totalValue(0);

    cout<< "\nNumber of items total: "<<numItems<<endl;
    cout<<"Knapsack capactiy: "<< capacity<<endl;

    // // print optimal items from bestSet
    // cout <<"\nOptimal Knapsack Items: "<<endl;
    //     for(int i=0; i<numItems;i++)
    // {
    //     if(bestSet[i] == true)
    //     {
    //         numSacked++;
    //         items[i].print();
    //         totalWeight += items[i].weight;
    //         totalValue += items[i].value;
    //     }
    // }

    //     // print knapsack data
    // cout<< "\nNumber of knapsack items: " << numSacked << endl;
    // cout<< "Total weight: " << totalWeight<< " lbs" << endl;
    // cout<< "Total profit: " << totalValue<< " pesos" << endl;


    return maxProfit;
 
}
