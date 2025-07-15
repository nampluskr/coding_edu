### Solution

```cpp
/*
[ver1]
 점수 큰 순으로 배정

 seed=5,  SCORE: 2994878
 seed=32, SCORE: 3600045
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

static const int AN = 1000;
#define ABS(x, y) ((x) < 0 ? : (-(x)) : (x))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
void swap(int& a, int& b) { int t = a; a = b; b = t; }

struct Spaceship {
	int height;
	int width;
}*S;

int ln;			// L[1 ~ ln]
struct Land {
	int r, c, h, w, score;
	bool operator<(Land& r) {
		return score > r.score;
	}
}L[10000];

// a <= b
// sn[a][b] = (a,b) 모양 우주선 개수
// slist[a][b] = { ids, .. }
int slist[6][6][10000], sn[6][6];

bool A[1005][1005];

void init(int mMap[][AN], struct Spaceship spaceships[]) {
	ln = 0;
	S = spaceships;
	for (int i = 2; i <= 5; i++)
		for (int j = i; j <= 5; j++)
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
				int er = sr + h - 1;
				if (er >= AN) break;
				for (int w = 2; w <= 5; w++) {
					int ec = sc + w - 1;
					if (ec >= AN) break;
					int lo = MIN(MIN(MIN(mMap[sr][sc], mMap[sr][ec]), mMap[er][sc]), mMap[er][ec]);
					int hi = MAX(MAX(MAX(mMap[sr][sc], mMap[sr][ec]), mMap[er][sc]), mMap[er][ec]);
					if (hi - lo <= 6) {
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

void process(int rows[], int cols[], int dirs[]) {
	for (int i = 1; i <= ln; i++) {
		int a = L[i].h, b = L[i].w;
		if (a > b) swap(a, b);
		if (sn[a][b] == 0) continue;		// 재고 부족한 경우
		if (isOverlap(L[i])) continue;		// 다른 우주선과 겹치는 경우

		int j = slist[a][b][--sn[a][b]];
		rows[j] = L[i].r;
		cols[j] = L[i].c;
		dirs[j] = L[i].h != S[j].height;

		fill(L[i]);
	}
}
```