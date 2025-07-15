### Solution

```cpp
/*
02_구간의합2D
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
using ll = long long;
using ull = unsigned long long;

int N;
int A[1005][1005];
ll P[1005][1005];

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

	int q;
	scanf("%d", &q);
	while (q--) {
		int sr, sc, er, ec;
		scanf("%d%d%d%d", &sr, &sc, &er, &ec);
		ull sum = P[er][ec] - P[sr - 1][ec] - P[er][sc - 1] + P[sr - 1][sc - 1];
		printf("%lld\n", sum);
	}

	return 0;
}
```