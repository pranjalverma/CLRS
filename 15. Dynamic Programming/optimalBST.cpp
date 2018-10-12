// #include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

vector<vector<int>> optimalBST(float p[], float q[], int n, float *minESC)
{
	vector<vector<float>> esc(n + 2);
	vector<vector<int>> roots(n + 2);
	vector<vector<float>> probSums(n + 2);

	for (int i = 0; i < n + 2; i++)
	{
		esc[i] = vector<float>(n + 1);
		roots[i] = vector<int>(n + 1);
		probSums[i] = vector<float>(n + 1);
	}

	for (int i = 1; i <= n + 1; i++)
	{
		probSums[i][i - 1] = q[i - 1];
		esc[i][i - 1] = q[i - 1]; // 1*q[i - 1]
	}

	int l, i, j, k; float r;
	for (l = 1; l <= n; l++)
	{
		for (i = 1; i <= n - l + 1; i++)
		{
			j = i + l - 1;
			esc[i][j] = 1000.0;
			probSums[i][j] = probSums[i][j - 1] + p[j] + q[j];

			for (k = i; k <= j; k++)
			{
				r = esc[i][k - 1] + esc[k + 1][j] + probSums[i][j];
				if (r < esc[i][j])
				{
					esc[i][j] = r;
					roots[i][j] = k;
				}
			}
		}
	}

	*minESC = esc[1][n];
	return roots;
}

typedef struct node
{
	int data;
	struct node *left, *right;
} Node;

Node* newNode(int data)
{
	Node* n = new Node;
	n->data = data;
	n->left = NULL; n->right = NULL;
	return n;
}

Node* constructOBST(vector<vector<int>> roots, int i, int j)
{
	if (i > j) return NULL;
	else if (i == j) return newNode(i);

	Node* n = newNode(roots[i][j]);
	n->left = constructOBST(roots, i, roots[i][j] - 1);
	n->right = constructOBST(roots, roots[i][j] + 1, j);
	
	return n;
}

void printInorder(Node* root)
{
	if (!root) return;

	printInorder(root->left);
	cout << root->data << ' ';
	printInorder(root->right);
	return;
}

int main(void)
{
	int n;
	cout << "Enter number of keys: ";
	cin >> n; cin.ignore();

	string line;
	cout << "Enter key probabilities: ";
	getline(cin, line);

	istringstream iss(line);

	float p[n + 1]; int i = 0;
	while (getline(iss, line, ' '))
		p[i++] = stof(line);
	iss.str(""); iss.clear();

	cout << "Enter dummy probabilities: ";
	getline(cin, line); iss.str(line);

	float q[n + 1]; i = 0;
	while (getline(iss, line, ' '))
		q[i++] = stof(line);

	float minESC = 1000.0;
	vector<vector<int>> roots = optimalBST(p, q, n, &minESC);
	cout << "Minimum Expected Search Cost: " << minESC << endl;

	Node* rootOBST = constructOBST(roots, 1, n);
	cout << "Optimal BST: ";
	printInorder(rootOBST); cout << endl;

	return 0;
}