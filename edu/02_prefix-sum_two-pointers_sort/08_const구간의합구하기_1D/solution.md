### Solution

```cpp
/*
01_구간의합1D
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int A[1000005];
long long P[1000005];

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);
		P[i] = P[i - 1] + A[i];
	}

	// O(Q)
	int Q;
	scanf("%d", &Q);
	while (Q--) {
		int s, e;
		scanf("%d%d", &s, &e);
		printf("%lld\n", P[e] - P[s - 1]);
	}

	return 0;
}
```