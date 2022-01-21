//---------------------------------------------------
// 
// Author: N8 Swalley & Adam Crozier 
// Date: 11/5/2021
//
// Dynamic and refinement programing approach to the 0-1 knapsack problem 
//
//---------------------------------------------------

#include "item.h"

int max(int a, int b) {
    if(a>=b) {
        return a;
    }
    return b;
}

int refine(int n, int W, item * items, int ** matrix)
{
    // base case
    if (n == 0 || W == 0)
    {
        return 0;
    }
    if(W < items[n-1].weight)
    {
        matrix[n][W] = refine(n-1, W, items, matrix);
        return matrix[n][W];
    }
    else
    {
        matrix[n][W] =  max(refine(n-1, W, items, matrix), 
            (refine(n-1, W - items[n-1].weight, items, matrix) + items[n-1].value));
        return matrix[n][W];
        
    }
}

int main()
{
    // variable initialization for items
    int numItems(0);
    int sackCapacity(0);
    double weight(0);
    double value(0);
    double ratio(0);
    string nameOfItem=" ";

    // variables for knapsack
    int numSack=0; 
    int totalValue=0;
    int totalWeight=0;
    int knapSkip=0;

    // variables for file i/o
    ifstream fileToReadIn;
    string nameOfFile = " ";
    cout << "Enter file name and extension: ";
    cin >> nameOfFile;

    // Read in values from file
    fileToReadIn.open(nameOfFile); 
    fileToReadIn >> numItems>> sackCapacity;

    // Arrays to store pointers of type item
    item * items = new item [numItems];
    item * knapsack = new item[numItems];

    for(int i=0; i< numItems; i++)
    {
        fileToReadIn >> nameOfItem >> value >> weight;
        item itemObj = item(value, weight); 
        itemObj.name = nameOfItem;
        ratio = itemObj.ratio();
        items[i] = itemObj;
    }
    
    int ** matrix = new int * [numItems+1];
    
    // Dynamic Approach for the 0-1 knapsack
    for (int i=0; i<= numItems; i++)
    {
        // creates 2D array with dimensions numItems x sackCapacity 
        matrix[i] = new int [sackCapacity+1]; // each i-th pointer is now pointing to dynamic array (size sackCapacity)

        for(int j=0; j<=sackCapacity;j++)
        {
            if (i == 0 || j == 0)
            {
                continue;
            }
            else if (items[i-1].weight <= j)
            {
                // Formula from 192 in the book!
                matrix[i][j] = max(matrix[i-1][j], matrix[i-1][j - ((int)items[i-1].weight)] + items[i-1].value);
            }
            else
            { 
                matrix[i][j] = matrix[i-1][j];
            }
        }
    }

    // Select optimal solutions to store in knapsack array
    for (int i=numItems; i > 0; i--)
    {
        if(matrix[i][sackCapacity - knapSkip] == matrix[i-1][sackCapacity - knapSkip])
        {
            continue;
        }
        knapsack[numSack] = items[i-1];
        totalValue += knapsack[numSack].value;
        totalWeight += knapsack[numSack].weight;
        knapSkip += knapsack[numSack++].weight;
    }    

    // print results in console
    cout<<"\n";
    cout << "Dynamic Programming Approach for 0-1 Knapsack:" << "\n";
    cout<< "Total number of items in knapsack: " << numSack << endl;
    cout<< "Knapsack capacity: " << sackCapacity <<" lbs" << endl;
    cout<< "Total weight: " << totalWeight << " lbs" << endl;
    cout<< "Total profit: " << totalValue << " pesos" << endl;
    cout<<"\n";
    cout<<"Items in the knapsack: "<<endl;

    for(int i = 0; i < numSack; i++)
    {
        knapsack[i].print();
    }

    // reset matrix values to 0 for refinement
    for(int i=0; i<numItems+1; i++)
    {
        for(int j=0; j<sackCapacity+1; j++)
        {
            matrix[i][j] = 0;
        }
    }

    // Refinement of Dynamic Programming Approach
    refine(numItems, sackCapacity, items, matrix); 

    numSack=0;
    totalValue=0;
    totalWeight=0;
    knapSkip=0;

    item * knapRefined = new item[numItems];

    // select optimal solutions for refined knapsack
    for (int i=numItems; i > 0; i--)
    {
        if(matrix[i][sackCapacity - knapSkip] == matrix[i-1][sackCapacity - knapSkip])
        {
            continue; 
        }
        knapRefined[numSack] = items[i-1];
        totalValue += knapRefined[numSack].value;
        totalWeight += knapRefined[numSack].weight;
        knapSkip += knapRefined[numSack++].weight;
    } 

    // print resuts in console
    cout<<"\n";
    cout << "Refinement of Dynamic Programming Approach for 0-1 Knapsack:" << "\n";
    cout<< "Total number of items in knapsack: " << numSack << endl;
    cout<< "Knapsack capacity: " << sackCapacity << " lbs" << endl;
    cout<< "Total weight: " << totalWeight<< " lbs" << endl;
    cout<< "Total profit: " << totalValue << " pesos" << endl;
    cout<<"\n";
    cout<<"Items in the knapsack: "<<endl;

    for(int i = 0; i < numSack; i++)
    {
        knapRefined[i].print();
    }

    return 0;

}
