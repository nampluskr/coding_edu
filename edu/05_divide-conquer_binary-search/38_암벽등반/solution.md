### Solution

```cpp
/*
07_암벽등반
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int A[505][505];
int visit[505][505], vcnt;
int h;

int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

int abs(int a) { return a < 0 ? -a : a; }

int dfs(int r, int c) {
	visit[r][c] = vcnt;

	int cnt = 1;
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
		if (visit[nr][nc] == vcnt) continue;
		if (abs(A[r][c] - A[nr][nc]) > h) continue;
		cnt += dfs(nr, nc);
	}
	return cnt;
}

struct Coord {
	int r, c;
}que[500 * 500];
int head, tail;

int bfs(int sr, int sc) {
	// queue 초기화
	head = tail = 0;

	// 시작점 등록
	que[tail++] = { sr,sc };
	visit[sr][sc] = vcnt;	// queue에 등록과 동시에 visit 체크

	// bfs
	while (head < tail) {
		Coord cur = que[head++];
		for (int i = 0; i < 4; i++) {
			int r = cur.r + dr[i];
			int c = cur.c + dc[i];
			if (r < 0 || r >= N || c < 0 || c >= N) continue;
			if (visit[r][c] == vcnt) continue;
			if (abs(A[r][c] - A[cur.r][cur.c]) > h) continue;

			que[tail++] = { r,c };
			visit[r][c] = vcnt;
		}
	}

	// 방문 개수(=head=tail)
	return tail;
}

bool isPossible() {
	vcnt++;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == vcnt) continue;
			//int cnt = dfs(i, j);
			int cnt = bfs(i, j);
			if (cnt >= N * N * 3 / 4) return 1;
		}
	}
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &A[i][j]);

	// xxxxx|ooooo
	//     e|s
	int s = 0, e = 1e6;
	while (s <= e) {
		h = (s + e) / 2;
		if (isPossible()) e = h - 1;
		else s = h + 1;
	}
	printf("%d\n", s);

	return 0;
}
```