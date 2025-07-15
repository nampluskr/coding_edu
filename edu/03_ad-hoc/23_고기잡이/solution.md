### Solution

```cpp
/*
00_고기잡이
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, L, M;
struct Coord {
	int r, c;
}A[105];

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int ans = 1;
	scanf("%d%d%d", &N, &L, &M);
	for (int i = 0; i < M; i++) scanf("%d%d", &A[i].r, &A[i].c);

	L /= 2;
	for (int h = 1; h < L; h++) {
		int w = L - h;
		for (int i = 0; i < M; i++) {
			for (int j = i + 1; j < M; j++) {
				int sr = min(A[i].r, A[j].r);
				int sc = min(A[i].c, A[j].c);
				int er = sr + h;
				int ec = sc + w;

				int cnt = 0;
				for (int k = 0; k < M; k++)
					if (sr <= A[k].r && A[k].r <= er && sc <= A[k].c && A[k].c <= ec)
						cnt++;

				ans = max(ans, cnt);
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}
```