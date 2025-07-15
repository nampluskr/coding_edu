### Solution

```cpp
/*
* seed=5 분석
* - 착륙 가능한 땅의 수 8814개
* - 겹쳐진 그룹의 최대 크기는 11
* - 겹쳐지지 않는 땅의 수 5684 ~ 5884
* - 착륙 가능한 땅보다 우주선의 수가 많다.

* seed=1~50 분석
* - 착륙 가능한 땅의 수는 9000개를 넘지 않는다.
* - 겹쳐진 그룹의 최대 크기는 16 (최대 크기 평균은 8)
* - 대부분은 착륙 가능한 땅보다 우주선의 수가 더 많다.
	(seed 15, 24, 30, 32, 38, 47 에서만 '살짝' 부족)
*/
#include <stdio.h>

static const int AN = 1000;		// 맵 크기
static const int SN = 10000;	// 우주선 개수

#define ABS(x, y) ((x) < 0 ? : (-(x)) : (x))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Spaceship {
	int height;
	int width;
};

int tc; // testcase
int ln;  // 땅의 수
struct Land {
	int sr, sc, er, ec;
	bool isOverlap(Land& d) {
		return sr <= d.er && sc <= d.ec && d.sr <= er && d.sc <= ec;
	}
}L[100000];

int maxGroupCnt;
int parent[100000], groupCnt[100000];

int A[1005][1005];

int Find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
	a = Find(a), b = Find(b);
	if (a == b) return;
	parent[b] = a;
	groupCnt[a] += groupCnt[b];
	maxGroupCnt = MAX(maxGroupCnt, groupCnt[a]);
}

void init(int mMap[][AN], struct Spaceship spaceships[]) {
	tc++;
	ln = 0;
	maxGroupCnt = 0;
	int spaceCnt[6][6] = {};	// spaceCnt[a][b]
	int landCnt[6][6] = {};		// landCnt[a][b]

	for (int i = 0; i < 10000; i++) {
		int h = spaceships[i].height;
		int w = spaceships[i].width;
		if (h <= w) spaceCnt[h][w]++;
		else spaceCnt[w][h]++;
	}

	for (int sr = 0; sr <= AN - 2; sr++)
		for (int sc = 0; sc <= AN - 2; sc++) {
			for (int h = 2; h <= 5; h++) {
				if (sr + h > AN) break;
				for (int w = 2; w <= 5; w++) {
					if (sc + w > AN) break;

					// (sr,sc) ~ (er,ec) 땅 확인
					int er = sr + h - 1;
					int ec = sc + w - 1;
					int lo = MIN(MIN(MIN(mMap[sr][sc], mMap[sr][ec]), mMap[er][sc]), mMap[er][ec]);
					int hi = MAX(MAX(MAX(mMap[sr][sc], mMap[sr][ec]), mMap[er][sc]), mMap[er][ec]);
					if (hi - lo <= 6) {
						if (h <= w) landCnt[h][w]++;
						else landCnt[w][h]++;

						L[++ln] = { sr, sc, er, ec };

						// union-find
						parent[ln] = ln;
						groupCnt[ln] = 1;
						for (int i = 1; i < ln; i++)
							if (L[ln].isOverlap(L[i])) Union(i, ln);

						if (tc == 1)
							for (int x = sr; x <= er; x++)
								for (int y = sc; y <= ec; y++)
									A[x][y]++;
					}
				}
			}
		}

	// 그룹 크기 1인(겹치는 땅이 없는) 개수
	int aloneCnt = 0;
	for (int i = 1; i <= ln; i++)
		if (i == parent[i] && groupCnt[i] == 1) aloneCnt++;

	if (tc == 1) {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++)
				printf("%d", A[i][j]);
			printf("\n");
		}
		printf("\n");
	}

	printf("[%d]\n", tc);
	printf("땅의 수 = %d, 최대 그룹 크기 = %d, 겹쳐지지 않는 땅의 수 = %d\n", ln, maxGroupCnt, aloneCnt);

	for (int i = 2; i <= 5; i++)
		for (int j = i; j <= 5; j++) {
			if (landCnt[i][j] <= spaceCnt[i][j]) printf("(%d,%d): %4d(l) < %4d(s)\n", i, j, landCnt[i][j], spaceCnt[i][j]);
			else printf("(%d,%d): %4d(l) > %4d(s)\n", i, j, landCnt[i][j], spaceCnt[i][j]);
		}

	printf("\n");
}

void process(int rows[], int cols[], int dirs[]) {
	return;
}
```