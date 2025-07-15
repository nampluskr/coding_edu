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
int P[505];		// P[i] = C[0]~C[i] 합
int P2[505];	// P2[i] = 0*C[0]~i*C[i] 합

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

	// prefix sum
	P[0] = C[0];
	P2[0] = 0 * C[0];
	for (int i = 1; i <= 256; i++) {
		P[i] = P[i - 1] + C[i];
		P2[i] = P2[i - 1] + i * C[i];
	}

	int ansT = 1e9, ansH;
	for (int h = 256; h >= 0; h--) {
		// a, b 개수 세기 
		int a = h * P[h] - P2[h];							// 0~h
		int b = (P2[256] - P2[h]) - h * (P[256] - P[h]);	// h+1~256

		if (B + b < a) continue;

		int t = b * 2 + a;
		if (ansT > t) ansT = t, ansH = h;
	}
	printf("%d %d\n", ansT, ansH);
	return 0;
}
```