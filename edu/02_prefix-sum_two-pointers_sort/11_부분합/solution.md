### Solution

```cpp
/*
04_부분합
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, S;
int A[100005];

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &S);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	int l = 0, r = 0;
	int sum = A[0];
	int ans = N + 1;
	while (r < N) {
		if (sum >= S) {
			if (ans > r - l + 1) ans = r - l + 1;
			sum -= A[l++];
		}
		else {
			sum += A[++r];
		}
	}
	printf("%d\n", ans == N + 1 ? 0 : ans);

	return 0;
}
```