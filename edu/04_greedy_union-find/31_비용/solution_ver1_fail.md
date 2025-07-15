### Solution

```cpp
/*
08_비용_ver1_O(N^2 * M)
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

int parent[100005];

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



	ll totalCost = 0;
	for (int u = 1; u <= N; u++) {
		for (int v = u + 1; v <= N; v++) {
			// 초기화
			ll cost = edgeSum;
			for (int i = 1; i <= N; i++)
				parent[i] = i;

			// cost(u,v) 계산
			for (int i = 0; i < M; i++) {
				// E[i] 두 정점 연결
				int a = find(E[i].a);
				int b = find(E[i].b);
				if (a != b) parent[b] = a;

				// E[i] 추가시, (u,v)가 연결되면 종료
				a = find(u);
				b = find(v);
				if (a == b) break;

				// 연결 안된 경우
				cost -= E[i].c;
			}
			printf("(%d,%d):%d\n", u, v, cost);
			totalCost = (totalCost + cost) % (int)1e9;
		}
	}

	printf("%d\n", totalCost);

	return 0;
}
```