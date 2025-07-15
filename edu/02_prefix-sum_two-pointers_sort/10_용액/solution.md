### Solution

```cpp
/*
03_용액
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int A[100005];

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	int ans = 21e8, a, b;
	int l = 0, r = N - 1;
	while (l < r) {
		int sum = A[l] + A[r];
		int abs = sum < 0 ? -sum : sum;
		if (ans > abs) {
			ans = abs;
			a = A[l], b = A[r];
		}
		if (sum < 0) l++;
		else r--;
	}
	printf("%d %d\n", a, b);
	return 0;
}
```