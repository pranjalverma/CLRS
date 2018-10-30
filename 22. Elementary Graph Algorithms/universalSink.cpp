#include <bits/stdc++.h>
using namespace std;

int findUniversalSink(vector<vector<int>> adjMat, int N)
{
	/*	
		O(|V|) time algorithm for finding universal sink node 
		in a directed graph, if it exists, given adjacency matrix.
	*/

	// A universal sink, i, will have it's row with all 0's
	// and it's column with all 1's except at (i, i), where it's 0.
	int i = 1, j = 1;
	while (i <= N && j <= N)
	{
		if (adjMat[i][j] == true)
			i++;
		else
			j++;
	}


	// verify if found i is indeed the universal sink or not
	int k;
	for (k = 1; k <= N; k++)
	{
		if (k != i && (adjMat[i][k] == 1 || adjMat[k][i] == 0))
			break;
		else if (k == i && adjMat[k][k] != 0)
			break;
	}

	return (k <= N)? -1: i;
}

int main(void)
{
	ifstream infile("directedGraph (universal sink).txt");
	istringstream iss;
	string line;

	getline(infile, line);
	int N = stoi(line);
	cout << endl << "Number of nodes in graph: " << N << endl << endl;

	vector<vector<int>> matrix(N + 1);
	for (int i = 0; i <= N; i++)
		matrix[i] = vector<int>(N + 1);

	int i, j;
	while (getline(infile, line))
	{
		iss.str(""); iss.clear();
		iss.str(line);

		iss >> i >> j;
		matrix[i][j] = true;
	}

	cout << "Given Adjacency Matrix: " << endl << endl;

	cout << "  ";
	for (i = 1; i <= N; i++)
		cout << i << ' ';
	cout << endl;

	for (i = 1; i <= N; i++)
	{
		cout << i << ' ';
		for (j = 1; j <= N; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}
	cout << endl;

	cout << "Universal Sink: " << findUniversalSink(matrix, N) << endl;
}
