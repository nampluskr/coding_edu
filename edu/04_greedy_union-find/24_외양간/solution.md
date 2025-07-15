### Solution

```cpp
/*
01_외양간
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>

using namespace std;

int M, S, C;
int A[205], E[205];
int ans;

void insertionSort(int num, int input[])
{
	int temp;
	int i;
	int j;

	for (i = 1; i < num; i++)
	{
		temp = input[i];
		j = i - 1;

		while ((j >= 0) && (temp > input[j]))
		{
			input[j + 1] = input[j];
			j = j - 1;
		}
		input[j + 1] = temp;
	}
}

int sortedArr[205];
void countingSort(int N, int arr[], int MAX_DIGIT = S)
{
	int cnt[205] = {};
	for (int i = 0; i < N; i++) cnt[arr[i]]++;
	for (int i = 1; i <= MAX_DIGIT; i++)
		cnt[i] = cnt[i - 1] + cnt[i];
	for (int i = N - 1; i >= 0; i--)
		sortedArr[--cnt[arr[i]]] = arr[i];
	for (int i = 0; i < N; i++)
		arr[N - i - 1] = sortedArr[i];
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d%d", &M, &S, &C);
	for (int i = 0; i < C; i++) scanf("%d", A + i);
	//sort(A, A + C, greater<int>{});
	insertionSort(C, A);
	countingSort(C, A);
	ans = A[0] - A[C - 1] + 1;

	for (int i = 0; i < C - 1; i++) E[i] = A[i] - A[i + 1] - 1;
	//sort(E, E + C - 1, greater<int>{});
	insertionSort(C - 1, E);
	countingSort(C - 1, E);

	for (int i = 0; i < M - 1; i++) ans -= E[i];

	printf("%d\n", ans);
	
	return 0;
}
```