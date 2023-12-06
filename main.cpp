//Project 2 Overview Video by TAs
#include <iostream>
#include <string>
#include <sstream>
#include "AdjacencyList.h"
using namespace std;

int main()
{
    //gets the number of lines
    int n;
    cin >> n;

    //gets the number of power iterations
    int p;
    cin >> p;

    //creates adjacencylist object;
    AdjacencyList list;

    //loops through the input 
    for (int i = 0; i < n+1; i++) {
        string line;
        getline(cin, line);
        istringstream in(line);

        //gets from vertex
        string from;
        in >> from;

        //gets to vertex
        string to;
        in >> to;

        //stores the outdegrees of each website
        list.countOutDegree(from, to, i);
    }
    
    //calls helper functions described in the header file
    list.checkOutDegree();
    list.insertList();
    list.defaultPageRanks();
    
    //loops from 1 to less than the number of power iterations and performs the page rank algorithm
    for (int i = 1; i < p; i++) {
        list.PageRank();
    }

    //skips a line and calls the output
    cout << endl;
    list.testing();

}

