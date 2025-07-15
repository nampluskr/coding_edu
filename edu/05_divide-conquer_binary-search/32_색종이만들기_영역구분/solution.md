### Solution

```cpp
/*
01_색종이만들기
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int A[130][130], P[130][130];
int cnt[2];

bool isSame(int r, int c, int n) {
	// O(1)
	int er = r + n - 1;
	int ec = c + n - 1;
	int sum = P[er][ec] - P[er][c - 1] - P[r - 1][ec] + P[r - 1][c - 1];
	return sum == 0 || sum == n * n;

	// O(n^2)
	for (int i = r; i < r + n; i++)
		for (int j = c; j < c + n; j++)
			if (A[i][j] != A[r][c]) return 0;
	return 1;
}

void recur(int r, int c, int n) {
	// base case
	if (isSame(r, c, n)) {
		cnt[A[r][c]]++;
		return;
	}

	// normal case
	int hn = n / 2;
	recur(r, c, hn);
	recur(r, c + hn, hn);
	recur(r + hn, c, hn);
	recur(r + hn, c + hn, hn);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
			P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + A[i][j];
		}

	recur(1, 1, N);

	printf("%d\n%d\n", cnt[0], cnt[1]);

	return 0;
}
```