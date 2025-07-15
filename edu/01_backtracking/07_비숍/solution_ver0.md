### Solution

```cpp
/*
07_비숍_ver0
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int A[15][15];
bool ltop[30], rtop[30];
int ans;

// (num/N, num%N)을 처리해!
void recur(int num, int cnt) {
	// 가지치기
	if (cnt + N * N - num <= ans) return;

	// base case
	if (num == N * N) {
		if (ans < cnt) ans = cnt;
		return;
	}

	// normal case
	int r = num / N;
	int c = num % N;

	// 놓고 넘기기
	if (A[r][c] && !ltop[r-c+N] && !rtop[r+c]) {
		ltop[r - c + N] = rtop[r + c] = 1;
		recur(num + 1, cnt + 1);
		ltop[r - c + N] = rtop[r + c] = 0;
	}

	// 안놓고 넘기기
	recur(num + 1, cnt);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &A[i][j]);

	recur(0, 0);
	printf("%d\n", ans);

	return 0;
}
```