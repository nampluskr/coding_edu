### Solution

```cpp
/*
02_발전소짓기
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, K;
int A[100005];

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	int ans = 0;
	int left = 0;	// 전력 공급 안된 첫번째 위치
	int right = -1;	// left에 공급 가능한 가장 오른쪽 위치

	for (int i = 0; i < N && left < N; i++) {
		if (A[i]) right = i;

		if (i == left + K - 1 || i == N-1) {
			if (right == -1) {
				ans = -1;
				break;
			}

			ans++;
			left = right + K;
			right = -1;
		}
	}

	printf("%d\n", ans);

	return 0;
}
```