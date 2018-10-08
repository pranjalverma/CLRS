#include <bits/stdc++.h>
using namespace std;

int BottomUpFib(int n)
{
	int r[3];
	r[0] = r[1] = 1;

	for (int i = 2; i < n; i++)
		r[i%3] = r[(i - 1)%3] + r[(i - 2)%3];

	return r[(n - 1)%3];
}

int TopDownFibRecur(int n, int r[])
{
	if (r[n - 1] >= 1) return r[n - 1];

	r[n - 1] = TopDownFibRecur(n - 1, r) + TopDownFibRecur(n - 2, r);
	return r[n - 1];
}

int TopDownFib(int n)
{
	int r[n];

	r[0] = r[1] = 1;
	for (int i = 2; i < n; i++)
		r[i] = INT_MIN;

	return TopDownFibRecur(n, r);
}

int main(void)
{
	int n;
	printf("n: ");
	scanf("%d", &n);

	if (n == 0)
		printf("Error\n");
	else
		printf("nth Fibonacci number: %d\n", BottomUpFib(n));

	return 0;
}