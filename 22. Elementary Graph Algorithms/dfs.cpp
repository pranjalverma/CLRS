#include <bits/stdc++.h>
using namespace std;

#define TWOENDL endl << endl

// classification done using CLRS pg 611, ex22.3-5
void DFSVisit(vector<vector<int>>& G, vector<pair<int, int>>& T, 
	vector<int>& P, int curNode, int* Time, bool* cycleFound)
{
	(*Time)++;
	T[curNode].first = *Time;

	for (auto i = G[curNode].begin(); i != G[curNode].end(); i++)
	{
		if (T[*i].first == 0)
		{
			cout << "Tree Edge encountered...(" << curNode << ", " << *i << ")" << endl; 
			P[*i] = curNode;
			DFSVisit(G, T, P, *i, Time, cycleFound);
		}

		// cycle is present if node (*i) if encountered from curNode
		// such that (*i) hasn't yet finished, meaning (*i) has been
		// encountered again in the current DFS traversal, thus
		// edge (curNode, *i) is a back edge which completes the cycle
		else if (T[*i].second == 0)
		{
			cout << "Back Edge encountered...(" << curNode << ", " << *i << ")" << endl;  
			*cycleFound = true;
		}
		else
		{
			// only specifying condition for discovery times
			// is enough here because T&B edges have already
			// classified above, and for C-edges, *i needs to
			// be discovered first.
			if (T[curNode].first < T[*i].first)
				cout << "Forward Edge encountered...(" << curNode << ", " << *i << ")" << endl;
			else
				cout << "Cross Edge encountered...(" << curNode << ", " << *i << ")" << endl; 
		}
	}

	(*Time)++;
	T[curNode].second = *Time;
}

void hasCycleDFS(vector<vector<int>>& G, vector<pair<int, int>>& T,
	vector<int>& P, int N, bool* cycleFound)
{
	int Time = 0;
	for (int u = 1; u <= N; u++)
	{
		if (T[u].first == 0)
			DFSVisit(G, T, P, u, &Time, cycleFound);
	}
}

void stackDFS(vector<vector<int>>& G, vector<pair<int, int>>& T,
	vector<int>& P, int N, bool* cycleFound)
{
	stack<int> nodes;
	stack<int> currentDFSPath;
	int Time = 0;

	int u, v;
	for (u = 1; u <= N; u++)
	{
		if (T[u].first == 0)
		{
			nodes.push(u);
			while (!nodes.empty())
			{
				v = nodes.top();
				nodes.pop();

				if (T[v].first == 0)
				{
					T[v].first = ++Time;

					// we push it back before expanding it's children
					// so it can be popped again and it's
					// finishing time can be added in "else if".
					// if it's popped from stack and it's already been
					// discovered, then by OUR stack's logic, it's children
					// have already been expanded, so it's fin-time can
					// now be added.
					nodes.push(v);
					if (!currentDFSPath.empty())
						P[v] = currentDFSPath.top();
					currentDFSPath.push(v);

					for (auto w = G[v].begin(); w != G[v].end(); w++)
					{
						if (T[*w].first == 0)
						{
							// cout << "Tree Edge encountered...(" << v << ", " << *w << ")" << endl;
							nodes.push(*w);
						}

						// this is different from the else-if condition below
						// here, edges are being examined, and if a back-edge
						// is found, we say there's a cycle.

						// Back-Edge: v.d < u.d < u.f < v.f
						// 			  for an edge u --> v
						else if (T[*w].second == 0)
						{
							// cout << "Back Edge encountered...(" << v << ", " << *w << ")" << endl;  
							*cycleFound = true;
						}
						// else
						// {
						// 	if (T[v].first < T[*w].first)
						// 		cout << "Forward Edge encountered...(" << v << ", " << *w << ")" << endl;
						// 	else
						// 		cout << "Cross Edge encountered...(" << v << ", " << *w << ")" << endl; 
						// }
					}
				}

				// don't wanna re-update finish-times again and again
				// cuz that would be wrong computations.
				// A node can be pushed multiple times on stack if 
				// current DFS-path has edges to it from multiple nodes
				// and our node is still marked undiscovered.
				// Eg- node s in graph from CLRS pg 611, fig22.6, ex22.3-2
				// Thus, only update fin-time once, when node finishes
				// for the first time.
				else if (T[v].second == 0)
				{
					T[v].second = ++Time;
					currentDFSPath.pop();
				}
			}
		}
	}
}

int main(void)
{
	// this graph is NOT connected; refer def of connected graph on google
	// ifstream infile("directedGraph (cyclic).txt");

	// graph from CLRS pg 611, fig22.6, ex22.3-2
	ifstream infile("directedGraph (cyclic, edge classification).txt");
	istringstream iss;
	string line;

	getline(infile, line);
	int N = stoi(line);
	cout << endl << "Number of Nodes in Graph: " << N << TWOENDL;

	vector<vector<int>> Graph(N + 1);
	for (int i = 1; i <= N; i++)
		Graph[i] = vector<int>();

	int u, v;
	while(getline(infile, line))
	{
		iss.str(""); iss.clear();
		iss.str(line);

		iss >> u >> v;
		if (find(Graph[u].begin(), Graph[u].end(), v) == Graph[u].end())
			Graph[u].push_back(v);
	}

	cout << "Graph as Adjacency Lists:" << TWOENDL;

	for (u = 1; u <= N; u++)
	{
		cout << u << ": ";
		for (auto i = Graph[u].begin(); i != Graph[u].end(); i++)
			cout << *i << " -> ";
		cout << "NULL" << endl;
	}
	// cout << endl;

	vector<pair<int, int>> Timestamps(N + 1, make_pair(0, 0));
	vector<int> Parents(N + 1, 0);
	bool cycleFound = false;

	// cout << "Edge Classification:" << TWOENDL;
	stackDFS(Graph, Timestamps, Parents, N, &cycleFound);

	cout << endl <<  "Analysis Result: ";
	if(cycleFound)
		cout << "Cycle Detected!" << TWOENDL;
	else
		cout << "No cycle." << TWOENDL;

	cout << "Depth-First Search analysis information:" << TWOENDL;

	cout << "Nodes of Graph:     ";
	for (u = 1; u <= N; u++)
		cout << u << " ";
	cout << endl;

	cout << "Discovery Times:    ";
	for (u = 1; u <= N; u++)
		cout << Timestamps[u].first << " ";
	cout << endl;

	cout << "Finishing Times:    ";
	for (u = 1; u <= N; u++)
		cout << Timestamps[u].second << " ";
	cout << endl;

	cout << "Parent Information: ";
	for (u = 1; u <= N; u++)
		cout << Parents[u] << " ";
	cout << endl;
}