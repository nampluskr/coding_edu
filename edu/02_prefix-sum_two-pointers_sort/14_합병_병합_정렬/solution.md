### Solution

```cpp
/*
07_merge sort
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int A[1005], tmp[1005];

void merge(int s, int e) {
	// base case
	if (s == e) return;

	// normal case
	int m = (s + e) / 2;
	merge(s, m);
	merge(m + 1, e);

	int i = s, j = m + 1, k = s;
	while (i <= m && j <= e) {
		if (A[i] < A[j]) tmp[k++] = A[i++];
		else tmp[k++] = A[j++];
	}
	while (i <= m) tmp[k++] = A[i++];
	while (j <= e) tmp[k++] = A[j++];

	for (int i = s; i <= e; i++) A[i] = tmp[i];

	for (int i = 0; i < N; i++) printf("%d ", A[i]);
	printf("\n");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	merge(0, N - 1);

	return 0;
}
```