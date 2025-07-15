### Solution

```cpp
/*
08_오리무전기_ver2_union-find+greedy

* edge[] = { (id1, id2, dist^2), ... } : dist^2 기준 오름차순 정렬
  => O(N^2 log (N^2))
* 비용 작은 간선부터 연결하면서 최초로 N개 정점이 연결되는(같은 그룹이 되는) 간선의 비용을 출력
  => union-find 로 같은 그룹 판별/합치기
	   O(N^2)

*/
/*
03_오리무전기_ver2_union-find + greedy _ O((N^2) log (N^2))
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <algorithm>
using namespace std;

int N;
struct Coord {
	int x, y;
	int operator-(Coord r) {
		return (x - r.x)*(x - r.x) + (y - r.y)*(y - r.y);
	}
}A[1005];

int M;
struct Edge {
	int a, b, c;    // c=dist^2
	bool operator<(Edge r) { return c < r.c; }
}edge[1000005];

int parent[1005];

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &A[i].x, &A[i].y);
		parent[i] = i;
		for (int j = 0; j < i; j++)
			edge[M++] = { i, j, A[i] - A[j] };
	}
	sort(edge, edge + M);

	for (int i = 0; i < M; i++) {
		int a = find(edge[i].a);
		int b = find(edge[i].b);
		if (a == b) continue;
		parent[b] = a;
		N--;    // 그룹 개수 감소
		if (N == 1) {
			printf("%d\n", edge[i].c);
			break;
		}
	}

	return 0;
}
```