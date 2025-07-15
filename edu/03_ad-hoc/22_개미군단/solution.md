### Solution

```cpp
/*
07_개미군단
        충돌이 발생해도 두 개미의 진행경로는 동일하다.
        방향 전환을 하지 않고 진행방향 그대로 이동하는 관점으로 접근한다.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int L, N;
	scanf("%d%d", &L, &N);

	int minT = 0, maxT = 0;
	for (int i = 0; i < N; i++) {
		int x;
		scanf("%d", &x);
		minT = max(minT, min(x, L - x));
		maxT = max(maxT, max(x, L - x));
	}
	printf("%d %d\n", minT, maxT);

	return 0;
}
```