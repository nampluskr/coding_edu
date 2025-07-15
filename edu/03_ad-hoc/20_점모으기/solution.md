### Solution

```cpp
/*
05_점모으기
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>
using namespace std;

int N, M;
int rows[100005], cols[100005];

int abs(int a) { return a < 0 ? -a : a; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) scanf("%d%d", rows + i, cols + i);
	sort(rows, rows + M);
	sort(cols, cols + M);

	int R = rows[M / 2];
	int C = cols[M / 2];
	int ans = 0;
	for (int i = 0; i < M; i++)
		ans += abs(R - rows[i]) + abs(C - cols[i]);
	printf("%d\n", ans);

	return 0;
}
```