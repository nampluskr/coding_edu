### Solution

```cpp
/*
05_종교
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, M;

int parent[50005], rank[50005], cnt[50005];

int find(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

void swap(int&a, int&b) { int c = a; a = b; b = c; }
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &M);

	// 초기화
	int ans = N;
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		rank[i] = 0;
		cnt[i] = 1;
	}

	int a, b;
	while (M--) {
		scanf("%d%d", &a, &b);
		// 루트로 설정
		a = find(a);
		b = find(b);

		// 같은 그룹(같은 루트) 인 경우
		if (a == b) continue;

		// 다른 그룹인 경우 => union(b->a)

		// b의 rank가 작거나 같게
		if (rank[a] < rank[b]) swap(a, b);

		ans--;
		parent[b] = a;
		cnt[a] += cnt[b];
		if (rank[a] == rank[b]) rank[a]++;
	}

	printf("%d\n", ans);

	return 0;
}
```