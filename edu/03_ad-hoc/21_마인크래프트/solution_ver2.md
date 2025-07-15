### Solution

```cpp
/*
06_마인크래프트_ver2_O(H*H)
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, M, B;
int A[505][505];
int C[505];

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d%d", &N, &M, &B);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			scanf("%d", &A[i][j]);
			C[A[i][j]]++;
		}

	int ansT = 1e9, ansH;
	for (int h = 256; h >= 0; h--) {
		// a, b 개수 세기 
		int a = 0, b = 0;
		for (int i = 0; i < h; i++) a += (h - i)*C[i];
		for (int i = h; i <= 256; i++) b += (i - h)*C[i];

		if (B + b < a) continue;

		int t = b * 2 + a;
		if (ansT > t) ansT = t, ansH = h;
	}
	printf("%d %d\n", ansT, ansH);
	return 0;
}
```