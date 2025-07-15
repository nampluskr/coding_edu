### Solution

```cpp
/*
08_비용_ver2_정렬:O(M log M), 검색:O(M)
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>
using namespace std;
using ll = long long;

int N, M;
struct Edge {
	int a, b, c;
	bool operator<(Edge&r) {
		return c > r.c;
	}
}E[100005];

int parent[100005], cnt[100005];

int find(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &M);

	ll edgeSum = 0;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &E[i].a, &E[i].b, &E[i].c);
		edgeSum += E[i].c;
	}

	sort(E, E + M);

	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		cnt[i] = 1;
	}

	ll totalCost = 0;
	ll cost = edgeSum;
	for (int i = 0; i < M; i++) {
		int a = find(E[i].a);
		int b = find(E[i].b);
		if (a != b) {
			totalCost = (totalCost + cost * cnt[a] * cnt[b]) % (int)1e9;
			parent[b] = a;
			cnt[a] += cnt[b];
		}
		cost -= E[i].c;
	}

	printf("%d\n", totalCost);

	return 0;
}
```