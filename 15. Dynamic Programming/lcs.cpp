#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> lcs(string s1, string s2, int lens[], int *lcsLen)
{
	vector<vector<int>> m(lens[0] + 1);
	for (int i = 0; i <= lens[0]; i++)
		m[i] = vector<int>(lens[1] + 1);

	// vector<vector<char>> s(lens[0] + 1);
	// for (int i = 0; i <= lens[0]; i++)
	// 	s[i] = vector<char>(lens[1] + 1);

	for (int i = 0; i <= lens[0]; i++)
	{
		for (int j = 0; j <= lens[1]; j++)
		{
			if (i == 0 || j == 0)
				m[i][j] = 0;

			else if (s1[i - 1] == s2[j - 1])
			{
				m[i][j] = m[i - 1][j - 1] + 1;
				// s[i][j] = 'd';
			}

			else
			{
				if (m[i - 1][j] > m[i][j - 1])
				{
					m[i][j] = m[i - 1][j];
					// s[i][j] = 'u';
				}
				else
				{
					m[i][j] = m[i][j - 1];
					// s[i][j] = 'l';
				}
			}
		}
	}

	*lcsLen = m[lens[0]][lens[1]];
	return m;
}

void printLCS(string s1, vector<vector<int>> m, int ijk[], char lcsStr[])
{
	if (ijk[0] == 0 || ijk[1] == 0) return;

	int curLen = m[ijk[0]][ijk[1]];
	if (curLen == m[ijk[0] - 1][ijk[1]])
		ijk[0]--;
	else if (curLen == m[ijk[0]][ijk[1] - 1])
		ijk[1]--;
	else
	{
		lcsStr[ijk[2]--] = s1[ijk[0] - 1];
		ijk[0]--; ijk[1]--;
	}

	printLCS(s1, m, ijk, lcsStr);
}

int lcsMemoUtil(string s1, string s2, int i, int j, vector<vector<int>> m)
{
	if (m[i][j] > INT_MIN) return m[i][j];

	else if (i == 0 || j == 0)
		m[i][j] = 0;

	else if (s1[i - 1] == s2[j - 1])
		m[i][j] = lcsMemoUtil(s1, s2, i - 1, j - 1, m) + 1;

	else
		m[i][j] = max(lcsMemoUtil(s1, s2, i - 1, j, m), lcsMemoUtil(s1, s2, i, j - 1, m));

	return m[i][j];
}

int lcsMemo(string s1, string s2, int lens[])
{
	vector<vector<int>> m(lens[0] + 1);
	for (int i = 0; i <= lens[0]; i++)
		m[i] = vector<int>(lens[1] + 1);

	for (int i = 0; i <= lens[0]; i++)
	{
		for (int j = 0; j <= lens[1]; j++)
			m[i][j] = INT_MIN;
	}

	return lcsMemoUtil(s1, s2, lens[0], lens[1], m);
}

// void printLCS(string s1, vector<vector<char>> s, int ijk[], char lcsStr[])
// {
// 	if (ijk[0] == 0 || ijk[1] == 0) return;

// 	char direction = s[ijk[0]][ijk[1]];
// 	switch (direction)
// 	{
// 		case 'd':
// 		{
// 			lcsStr[ijk[2]--] = s1[ijk[0] - 1];
// 			ijk[0]--; ijk[1]--; break;
// 		}

// 		case 'u':
// 			ijk[0]--; break;
// 		case 'l':
// 			ijk[1]--; break;
// 	}

// 	printLCS(s1, s, ijk, lcsStr);
// }

int main(void)
{
	string s1, s2;
	cout << "Enter string X: ";
	getline(cin, s1);
	cout << "Enter string Y: ";
	getline(cin, s2);

	int lens[3] = {0};
	lens[0] = s1.length();
	lens[1] = s2.length();

	// int lcsLen = lcsMemo(s1, s2, lens);
	int lcsLen = 0;
	vector<vector<int>> m = lcs(s1, s2, lens, &lcsLen);
	cout << "LCS length: " << lcsLen << endl;

	cout << "LCS: "; char lcsStr[lcsLen]; lens[2] = lcsLen - 1;
	printLCS(s1, m, lens, lcsStr);
	for (int i = 0; i < lcsLen; i++)
		cout << lcsStr[i];
	cout << endl;

	return 0;
}