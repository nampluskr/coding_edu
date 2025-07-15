### Solution

```cpp
/*
[ver3]
 그룹별로 선택 가능한 모든 조합 확인하여 최대 점수 선택하기
 조합 확인 하는 과정에서 used[] 활용

 seed=5,  SCORE: 3001673
 seed=32, SCORE: 3011261
*/
#include <stdio.h>

static const int AN = 1000;
#define ABS(x, y) ((x) < 0 ? : (-(x)) : (x))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
void swap(int& a, int& b) { int t = a; a = b; b = t; }

struct Spaceship {
	int height;
	int width;
}*S;

int n;
struct Land {
	int sr, sc, er, ec, h, w, a, b, score;
	bool isOverlap(Land& d) {
		return sr <= d.er && sc <= d.ec && d.sr <= er && d.sc <= ec;
	}
}L[10000];

int parent[10000];

int slist[6][6][10000], sn[6][6];           // (a,b)별 우주선 번호 리스트, 개수
int glist[10000][20], gn[10000];            // 그룹 번호별 땅 리스트, 개수

int Find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
	a = Find(a), b = Find(b);
	if (a == b) return;
	parent[b] = a;
}

void init(int mMap[][AN], struct Spaceship spaceships[]) {
	n = 0;
	S = spaceships;
	for (int i = 2; i <= 5; i++)
		for (int j = 2; j <= 5; j++)
			sn[i][j] = 0;

	for (int i = 0; i < 10000; i++) {
		int a = S[i].height, b = S[i].width;
		if (a > b) swap(a, b);
		slist[a][b][sn[a][b]++] = i;
	}

	for (int sr = 0; sr < AN; sr++)
		for (int sc = 0; sc < AN; sc++) {
			for (int h = 2; h <= 5; h++) {
				int er = sr + h - 1;
				if (er >= AN) break;
				for (int w = 2; w <= 5; w++) {
					int ec = sc + w - 1;
					if (ec >= AN) break;

					int lo = MIN(MIN(MIN(mMap[sr][sc], mMap[sr][ec]), mMap[er][sc]), mMap[er][ec]);
					int hi = MAX(MAX(MAX(mMap[sr][sc], mMap[sr][ec]), mMap[er][sc]), mMap[er][ec]);
					if (hi - lo <= 6) {
						int a = MIN(h, w), b = MAX(h, w);
						L[++n] = { sr, sc, er, ec, h, w, a, b, a*a*b };
						parent[n] = n;
						for (int i = 1; i < n; i++)
							if (L[n].isOverlap(L[i])) Union(i, n);
					}
				}
			}
		}

	for (int i = 1; i <= n; i++) gn[i] = 0;
	for (int i = 1; i <= n; i++) {
		int gid = Find(i);
		glist[gid][gn[gid]++] = i;
	}
}

int gid, maxScore, maxUsed[20]; // 처리중인 그룹번호, 최대 점수와 그 상태
bool used[20];					// 현재 상태 used[i] = 1 : glist[gid][i] 를 사용함

// 현재까지 선택한 땅과 한개라도 겹치면 true
bool isOverlap(int c, Land&l) {
	for (int i = 0; i < c; i++) {
		if (used[i]) {
			Land&l2 = L[glist[gid][i]];
			if (l.isOverlap(l2)) return 1;
		}
	}
	return 0;
}

// glist[gid]의 c번 index 처리 : 선택안하기 or 선택하기
// score : 지금까지 점수
void recur(int c, int score) {
	// base case
	if (c == gn[gid]) {
		if (maxScore < score) {
			maxScore = score;
			for (int i = 0; i < c; i++)
				maxUsed[i] = used[i];
		}
		return;
	}

	// normal case
	// 1. c번을 선택 안하는 경우
	recur(c + 1, score);

	// 2. c번을 선택 하는 경우
	Land&l = L[glist[gid][c]];
	if (sn[l.a][l.b] && !isOverlap(c, l)) {
		sn[l.a][l.b]--;
		used[c] = 1;
		recur(c + 1, score + l.score);
		sn[l.a][l.b]++;
		used[c] = 0;
	}
}

void process(int rows[], int cols[], int dirs[]) {
	for (gid = 1; gid <= n; gid++) {
		if (gid == parent[gid]) {
			// 초기화
			maxScore = 0;
			for (int i = 0; i < gn[gid]; i++) used[i] = 0;

			// 최대 점수, 상태 찾기
			recur(0, 0);

			// 매칭
			for (int i = 0; i < gn[gid]; i++) {
				if (maxUsed[i]) {
					Land&l = L[glist[gid][i]];
					int sid = slist[l.a][l.b][--sn[l.a][l.b]];
					rows[sid] = l.sr;
					cols[sid] = l.sc;
					dirs[sid] = l.h != S[sid].height;
				}
			}
		}
	}
}
```