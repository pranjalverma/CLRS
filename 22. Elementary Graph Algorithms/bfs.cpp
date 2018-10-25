#include <bits/stdc++.h>
using namespace std;

#define TWOENDL endl << endl

// inline functions have no function call overhead!
inline bool not_in(int x, set<int> S){ return (S.find(x) == S.end()); }

// In C++, a reference (&) can be thought of as a pointer with 
// automatic indirection, ie the compiler will apply 
// the * operator for you. This is different from C's '&'.
void BFS(vector<vector<int>>& Graph, vector<int>& SD, vector<int>& P, int N)
{
	/*
		O(V + E) time, as every node is discovered only once, and
		all lists are scaned only once. 'V' is included also because
		scanning an empty list still takes a constant amount of time.

		O(V) extra space to store SDs and the "discovered" set.
		"Queue" only takes O(breath) space where,
		
		breath = Breath of BFS-Tree,
		breath <= V;
	*/

	if (N == 0) return;

	queue<int> Queue;
	Queue.push(1);

	set<int> discovered;
	discovered.insert(1);

	SD[1] = 0;
	int curNode; vector<int> curList;

	// All nodes that have been in Queue once have already been
	// marked discovered. 
	while (!Queue.empty())
	{
		curNode = Queue.front();
		Queue.pop();

		curList = Graph[curNode];
		for (auto i = curList.begin(); i != curList.end(); i++)
		{
			if (not_in(*i, discovered))
			{
				discovered.insert(*i);
				SD[*i] = SD[curNode] + 1;
				P[*i] = curNode;
				Queue.push(*i);
			}
		}
	}

	return;
}

// O(V) as a Shortest Path can have max V - 1 edges.
void printPath(int source, int destination, vector<int>& P)
{
	if (source == destination)
		cout << source << " -> ";

	else if (P[destination] == -1)
		cout << "No path!";

	else
	{
		printPath(source, P[destination], P);
		cout << destination << " -> ";
	}

	return;
}

int main(void)
{
	ifstream infile("directedGraph (cyclic, edge classification).txt");
	istringstream iss;
	string line;

	getline(infile, line);
	int N = stoi(line);
	cout << endl << "Number of nodes in Graph: " << N << TWOENDL;

	// "vector<type> var", here var is just a vector pointer variable.
	// var isn't actually pointing to an actual vector yet, when
	// you call "push_back()" on var with some data, a vector is 
	// constructed as "push_back()" is a function with a call (with "()")
	// This is why if we specify a name, a statement like the above is
	// legal, since a pointer variable pointing to garbage is legal in C++.

	// But "vector<int>" is not legal as this is just a object-type but
	// nothing has been declared as no name is specified, so we must 
	// type "vector<type>()", to actually call the Vector Class's 
	// constructor and actually construct a vector object that can be 
	// declared and assigned!

	// Thus, a statement like "vector<type> var" will create a pointer
	// variable that points to garbage, but "vector<type> var(N, data)"
	// will actually declare a pointer variable "var" that actually points
	// to a vector object of size N, all entries filled with <data>, since
	// the Construct function call syntax "()" is used! 
	vector<vector<int>> Graph(N + 1);
	for (int i = 1; i <= N; i++)
		Graph[i] = vector<int>(); // read above

	int i, j;
	while (getline(infile, line))
	{
		iss.str(""); iss.clear();
		iss.str(line);

		iss >> i >> j;
		Graph[i].push_back(j);
	}

	cout << "Given Adjacency Lists:" << TWOENDL;

	for (i = 1; i <= N; i++)
	{
		cout << i << ": ";
		for (auto itr = Graph[i].begin(); itr != Graph[i].end(); itr++)
			cout << *itr << " -> ";
		cout << "NULL" << endl;
	}
	cout << endl;

	vector<int> ShortestDistances(N + 1, INT_MAX);
	vector<int> Predecessors(N + 1, -1);
	BFS(Graph, ShortestDistances, Predecessors, N);

	cout << "Considering source as 1:" << TWOENDL;
	for (i = 1; i <= N; i++)
	{
		cout << i << "'s Shortest Distances from 1: " << ShortestDistances[i] << endl;
		cout << "Shortest Path from 1 to " << i << ": ";
		printPath(1, i, Predecessors); cout << "NULL" << TWOENDL;
	}
}