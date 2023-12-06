//https://cplusplus.com/reference/map/map/
//https://cplusplus.com/reference/unordered_map/unordered_map/
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class AdjacencyList
{
private:
	//m1 is the map with the key as the website and the int as the outdegree
	map<string, int> m1;
	//vector to store the pointers
	vector<pair<string, string>> v;
	//aL is the adjacency list, stores the to website as the key and vector of pairs which holds the from website and the from website's 1/outdegree.
	unordered_map<string, vector<pair<string, double>>> aL;
	//m2 is the map which will store the old ranks of each node
	map<string, double> m2;
	//m3 is the map which will store the website and its rank
	map<string, double> m3;
	//a temporary vector used in the checkoutdegree funciton
	vector<string> v2;

public:
	//checks the input and counts the outdegrees of each website
	void countOutDegree(string from, string to, int i) {
		//starts checking the next line of input where the websites start
		if (i != 0) {
			//pushes back the websites to their vectors
			v.push_back(pair<string, string>(to, from));
			v2.push_back(to);
			v2.push_back(from);
			//loops through the first map and stores each pair if the website is not already in the map
			map<string, int>::iterator it;
			it = m1.find(from);
			if (it == m1.end()) {
				m1.insert(pair<string, int>(from, 1));
			}
			//if the website is already in the map it increments the outdegree
			else {
				m1[from]++;
			}
			//also checks for websites not pointing to anything and setting their outdegree to 0
			map<string, int>::iterator it2;
			it2 = m1.find(to);
			if (it == m1.end()) {
				m1.insert(pair<string, int>(to, 0));
			}
		}
	}

	//sets the default pageranks
	void defaultPageRanks() {
		//goes through m1 to find each unique website
		for (auto it : m1) {
			//stores every default rank in m2 and m3
			map<string, double>::iterator it2;
			it2 = m2.find(it.first);
			if (it2 == m2.end()) {
				m2.insert(pair<string, double>(it.first, 1.0 / m1.size()));
				m3.insert(pair<string, double>(it.first, 1.0 / m1.size()));
			}
		}
	}

	//creates the adjacency list
	void insertList() {
		//loops through the vector v
		for (auto it : v) {
			//loops through the list
			unordered_map<string, vector<pair<string, double>>>::iterator it2;
			it2 = aL.find(it.first);
			//if the list doesn't contain already said website, it inserts it and pushes back it's vector
			if (it2 == aL.end()) {
				vector<pair<string, double>> v1;
				aL.insert(pair<string, vector<pair<string, double>>>(it.first, v1));
				aL[it.first].push_back(pair<string, double>(it.second, 1.0 / m1[it.second]));
			}
			//if the list does contain the website it pushes back it's other vector
			else {
				aL[it.first].push_back(pair<string, double>(it.second, 1.0 / m1[it.second]));
			}
		}
	}

	//used to check if a certain website has an outdegree of 0 therefore making its rank 0
	void checkZero() {
		//does so by looping through the outdegree map and checking if it exists in the adjacency list
		for (auto it : m1) {
			unordered_map<string, vector<pair<string, double>>>::iterator it2;
			it2 = aL.find(it.first);
			//if it doesn't it inserts it into the map containing the ranks with a rank of 0
			if (it2 == aL.end()) {
				m3.erase(it.first);
				m3.insert(pair<string, double>(it.first, 0.0));
			}
		}
	}

	//used to check if a website has no outdegree and therefore storing it in m1 with an outdegree of 0
	void checkOutDegree() {
		for (auto it : v2) {
			map<string, int>::iterator it2;
			it2 = m1.find(it);
			if (it2 == m1.end()) {
				m1.insert(pair<string, int>(it, 0));
			}
		}
	}

	//the pagerank algorithm function
	void PageRank() {
		//loops through the adjacency list
		for (auto it : aL) {
			double rank = 0.0;
			//calculates the rank of a website using the values of the previous rank and outdegree
			for (auto it2 : it.second) {
				rank += it2.second * m2[it2.first];
			}
			//it then inserts the website and its rank into m3
			m3.erase(it.first);
			m3.insert(pair<string, double>(it.first, rank));
		}
		//calls these helper functions to update the map containing the ranks
		checkZero();
		updateRanks();
	}

	//updates the ranks in m2 which stores the previous ranks so it can be used in the page rank algorithm
	void updateRanks() {
		for (auto it : m1) {
			m2.erase(it.first);
			m2.insert(pair<string, double>(it.first, m3[it.first]));
		}
	}

	//loops through m3 to print the output, uses setprecision to round the decimal
	void testing() {
		for (auto it : m3) {
			cout << it.first << " " << setprecision(2) << fixed << it.second << endl;
		}
	}
};