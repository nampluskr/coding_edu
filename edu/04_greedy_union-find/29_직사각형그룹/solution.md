### Solution

```cpp
/*
06_직사각형 그룹
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
struct Rect {
	int sr, sc, er, ec;
	bool isOverlap(Rect r) {
		return sr <= r.er && r.sr <= er && sc <= r.ec && r.sc <= ec;
	}
}R[3005];

int parent[3005];
int rank[3005];
int size[3005];

int groupCnt, maxSize = 1;

void swap(int&a, int&b) { int c = a; a = b; b = c; }

int find(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d%d%d", &R[i].sr, &R[i].sc, &R[i].er, &R[i].ec);

		groupCnt++;
		parent[i] = i;
		rank[i] = 0;
		size[i] = 1;

		for (int j = 0; j < i; j++) {
			if (!R[i].isOverlap(R[j])) continue;

			int a = find(i);
			int b = find(j);
			if (a == b) continue;

			if (rank[a] < rank[b]) swap(a, b);
			parent[b] = a;
			size[a] += size[b];
			if (rank[a] == rank[b]) rank[a]++;

			groupCnt--;
			if (maxSize < size[a]) maxSize = size[a];
		}

		printf("%d %d\n", groupCnt, maxSize);
	}

	return 0;
}
```