### Solution

```cpp
/*
[ver2]
 ver1에서 전처리로 그룹 크기가 1인 땅 우선 배정
 대부분은 우주선 재고가 남기 때문에 큰 영향 없음
 seed 1~50 중, 15, 24, 30, 32, 38, 47의 경우만 우주선 재고 부족 가능성 있음
 결과에 영향 미치는 경우는 seed=32 마지막 tc 뿐, +306

 seed=5,  SCORE: 2994878
 seed=32, SCORE: 3004866
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

static const int AN = 1000;
#define ABS(x, y) ((x) < 0 ? : (-(x)) : (x))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Spaceship {
	int height;
	int width;
}*S;

int ln;
struct Land {
	int r, c, h, w, score;
	bool operator<(Land& r) {
		return score > r.score;
	}
}L[10000];

int slist[6][6][10000], sn[6][6];

bool A[1005][1005];

void swap(int& a, int& b) { int t = a; a = b; b = t; }
void init(int mMap[][AN], struct Spaceship spaceships[]) {
	ln = 0;
	S = spaceships;
	for (int i = 2; i <= 5; i++)
		for (int j = 2; j <= 5; j++)
			sn[i][j] = 0;

	for (int i = 0; i < AN; i++)
		for (int j = 0; j < AN; j++)
			A[i][j] = 0;

	for (int i = 0; i < 10000; i++) {
		int a = S[i].height, b = S[i].width;
		if (a > b) swap(a, b);
		slist[a][b][sn[a][b]++] = i;
	}

	for (int sr = 0; sr < AN; sr++)
		for (int sc = 0; sc < AN; sc++) {
			for (int h = 2; h <= 5; h++) {
				if (sr + h > AN) break;
				for (int w = 2; w <= 5; w++) {
					if (sc + w > AN) break;
					int min = MIN(MIN(MIN(mMap[sr][sc], mMap[sr][sc + w - 1]), mMap[sr + h - 1][sc]), mMap[sr + h - 1][sc + w - 1]);
					int max = MAX(MAX(MAX(mMap[sr][sc], mMap[sr][sc + w - 1]), mMap[sr + h - 1][sc]), mMap[sr + h - 1][sc + w - 1]);
					if (max - min <= 6) {
						int a = h, b = w;
						if (a > b) swap(a, b);
						L[++ln] = { sr, sc, h, w, a*a*b };
					}
				}
			}
		}

	sort(L + 1, L + 1 + ln);
}

bool isOverlap(Land& l) {
	for (int i = 0; i < l.h; i++)
		for (int j = 0; j < l.w; j++)
			if (A[l.r + i][l.c + j]) return 1;
	return 0;
}

void fill(Land& l) {
	for (int i = 0; i < l.h; i++)
		for (int j = 0; j < l.w; j++)
			A[l.r + i][l.c + j] = 1;
}

// 전체 탐색으로 겹치는 땅이 없는지 확인
bool isAlone(int i) {
	int sr = L[i].r, sc = L[i].c;
	int er = sr + L[i].h - 1;
	int ec = sc + L[i].w - 1;
	for (int j = 1; j <= ln; j++) {
		if (i == j) continue;
		int sr2 = L[j].r, sc2 = L[j].c;
		int er2 = sr2 + L[j].h - 1;
		int ec2 = sc2 + L[j].w - 1;
		if (sr <= er2 && sc <= ec2 && sr2 <= er && sc2 <= ec) return 0;
	}
	return 1;
}

void process(int rows[], int cols[], int dirs[]) {
	// 그룹 크기 1인 땅 우선 매칭
	for (int i = 1; i <= ln; i++) {
		if (isAlone(i)) {
			int a = L[i].h, b = L[i].w;
			if (a > b) swap(a, b);
			if (sn[a][b] == 0) continue;

			int j = slist[a][b][--sn[a][b]];
			rows[j] = L[i].r;
			cols[j] = L[i].c;
			dirs[j] = L[i].h != S[j].height;

			L[i].h = 0;
		}
	}

	// 남은 땅 점수 높은 순으로 매칭
	for (int i = 1; i <= ln; i++) {
		if (L[i].h == 0) continue;

		int a = L[i].h, b = L[i].w;
		if (a > b) swap(a, b);

		if (sn[a][b] == 0) continue;
		if (isOverlap(L[i])) continue;

		int j = slist[a][b][--sn[a][b]];
		rows[j] = L[i].r;
		cols[j] = L[i].c;
		dirs[j] = L[i].h != S[j].height;
		fill(L[i]);
	}
}
```