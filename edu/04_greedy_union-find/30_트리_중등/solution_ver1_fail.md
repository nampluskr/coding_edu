### Solution

```cpp
/*
07_트리(중등)_ver1
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, Q;
int parent[200005];	// root는 0

int find(int a) {
	if (parent[a] == 0) return a;
	return find(parent[a]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &Q);
	for (int i = 2; i <= N; i++)
		scanf("%d", parent + i);

	Q += N - 1;
	while (Q--) {
		int cmd, a, b;
		scanf("%d%d", &cmd, &a);
		if (cmd) {
			scanf("%d", &b);
			if (find(a) == find(b)) printf("YES\n");
			else printf("NO\n");
		}
		else {
			parent[a] = 0;
		}
	}

	return 0;
}
```