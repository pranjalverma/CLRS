#include <bits/stdc++.h>
using namespace std;

void BottomUpRodCut(int p[], int n, int **res, int **pieces)
{
	int r[n + 1], s[n + 1];
	r[0] = 0;

	for (int i = 1; i <= n; i++)
	{
		int q = INT_MIN;
		for (int j = 1; j <= i; j++)
			if (q < p[j] + r[i - j])
			{
				q = p[j] + r[i - j];
				s[i] = j;
			}

		r[i] = q;
	}

	*res = r; *pieces = s;
}

int TDRodCutRecur(int p[], int n, int r[])
{
	if (r[n] >= 0) return r[n];

	int q = INT_MIN;
	for (int i = 1; i <= n; i++)
		q = max(q, p[i] + TDRodCutRecur(p, n - i, r));

	r[n] = q;
	return q;
}

int TopDownRodCut(int p[], int n)
{
	int r[n + 1];
	for (int i = 1; i <= n; i++)
		r[i] = INT_MIN;
	r[0] = 0;

	return TDRodCutRecur(p, n, r);
}

int rodCut(int p[], int n)
{
	if (n == 0)
		return 0;
	
	int q = INT_MIN;
	for (int i = 1; i <= n; i++)
		q = max(q, p[i] + rodCut(p, n - i));

	return q;
}

int main(void)
{
	int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

	int n;
	printf("Length of rod: ");
	scanf("%d", &n);

	int *res, *pieces;
	BottomUpRodCut(p, n, &res, &pieces);
	printf("Maximum Profit: %d\n", res[n]);

	printf("Pieces: ");
	while (n > 0)
	{
		printf("%d ", pieces[n]);
		n -= pieces[n];
	}

	printf("\n");
	return 0;
}