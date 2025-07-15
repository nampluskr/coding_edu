### Solution

```cpp
/*
08_오리무전기_ver1_parametric search + dfs_ O(N^2 * log(e-s))

* 0 <= price 범위 <= 25000^2 * 2
* 특정 price 가능하면 그 이상은 다 가능
  특정 price 불가능하면 그 이하는 다 불가능
  xxxxxxxx|ooooooooo
* binary search로 limit설정해보기
* 조건 만족 여부(dfs/bfs)
  (diffx^2+diffy^2) <= limit 이하인 간선만 사용하여 전체 정점 방문 여부 체크
*/

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

int N;
struct Coord {
	int x, y;
	int operator-(Coord r) {
		return (x - r.x)*(x - r.x) + (y - r.y)*(y - r.y);
	}
}A[1005];

int limit;
int visit[1005], vcnt;
int dfs(int v) {
	int cnt = 1;
	visit[v] = vcnt;
	for (int u = 0; u < N; u++) {
		if (visit[u] == vcnt) continue;
		if (A[v] - A[u] > limit) continue;
		cnt += dfs(u);
	}
	return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d%d", &A[i].x, &A[i].y);

	int s = 0, e = 25000 * 25000 * 2;
	while (s <= e) {
		limit = (s + e) / 2;
		vcnt++;
		if (dfs(0) == N) e = limit - 1;
		else s = limit + 1;
	}
	printf("%d\n", s);

	return 0;
}

```