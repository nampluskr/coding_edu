### Solution

```cpp
/*
	ver1. 하르방이 4개 이상이 모이게 행끼리 묶어서 진행

	seed = 250517, SCORE: 87,342,638
*/
#include<algorithm>
using namespace std;

const int MAX_SIZE = 1024;

typedef struct {
	int x, y;
} Point;

extern int harubangs(Point p[]);
extern void house(Point p[]);

int N;
Point H[2000];

bool comp_y(Point l, Point r) {
	if (l.y != r.y) return l.y < r.y;
	return l.x < r.x;
}

int used[2000], ucnt;
void house(int s, int e) {
	ucnt++;
	Point points[4];
	for (int i = 0; i < 4; i++) {	// y큰값, y작은값, x큰값, x작은값
		auto&p = points[i] = { -1, -1 };
		int pick;
		for (int j = s; j <= e; j++) {
			if (used[j] == ucnt) continue;
			if (p.x != -1 && i == 0 && p.y >= H[j].y) continue;
			if (p.x != -1 && i == 1 && p.y <= H[j].y) continue;
			if (p.x != -1 && i == 2 && p.x >= H[j].x) continue;
			if (p.x != -1 && i == 3 && p.x <= H[j].x) continue;

			p = H[j];
			pick = j;
		}
		used[pick] = ucnt;
	}
	house(points);
}

void process()
{
	N = harubangs(H);
	sort(H, H + N, comp_y);
	H[N] = { -1, -1 };

	int s = 0;	// 처리 안된 첫번째 하르방 index
	int c = 0;	// 처리 안되고 쌓인 하르방 수
	for (int i = 0; i < N; i++) {
		c++;

		// 집 짓기
		//  1. 뒤에 4개 이상 남아 있으면서 쌓인 하르방이 4개 이상이고 행으로 나눠지는 경우
		//  2. 마지막인 경우
		if ((i < N - 4 && c >= 4 && H[i].y != H[i + 1].y) || i == N - 1) {
			house(s, i);
			c = 0;
			s = i + 1;
		}
	}
}
```

### Solution - ver1 (Nam)

```cpp
#include <stdio.h>
typedef struct {
	int x, y;
} Point;

extern int harubangs(Point p[]);
extern void house(Point p[]);

///////////////////////////////////////
const int MAX_SIZE = 1024;
const int MAX_HARUBANG = 2000;

int N;
Point H[2000];

Point p[4];
int vcnt, visit[2000];
int rowCnt[1024];

void _house(int sr, int er) {
	for (int i = 0; i < N; i++) visit[i] = 0;

	int maxX = 0, minX = MAX_SIZE, maxY = 0, minY = MAX_SIZE;
	int idx, x, y;
	int i;

	for (i = 0; i < N; i++)
		if (H[i].y > maxY && !visit[i] && H[i].y >= sr && H[i].y <= er) {
			idx = i, maxY = H[i].y, y = H[i].y, x = H[i].x;
		}
	visit[idx] = 1; p[0] = { x, y };

	for (i = 0; i < N; i++)
		if (H[i].y < minY && !visit[i] && H[i].y >= sr && H[i].y <= er) {
			idx = i, minY = H[i].y; y = H[i].y, x = H[i].x;
		}
	visit[idx] = 1; p[1] = { x, y };

	for (i = 0; i < N; i++)
		if (H[i].x > maxX && !visit[i] && H[i].y >= sr && H[i].y <= er) {
			idx = i, maxX = H[i].x; y = H[i].y, x = H[i].x;
		}
	visit[idx] = 1; p[2] = { x, y };

	for (i = 0; i < N; i++)
		if (H[i].x < minX && !visit[i] && H[i].y >= sr && H[i].y <= er) {
			idx = i, minX = H[i].x; y = H[i].y, x = H[i].x;
		}
	visit[idx] = 1; p[3] = { x, y };

	house(p);
}

int rowSum;
int remained;

void process()
{
	N = harubangs(H);
	remained = N;

	for (int i = 0; i < N; i++) rowCnt[i] = 0;
	for (int i = 0; i < N; i++) rowCnt[H[i].y]++;

	int start, end;
	for (start = 0; start < N && remained > 4; start++) {
		rowSum = rowCnt[start];
		for (end = start + 1; end < N; end++) {
			rowSum += rowCnt[end];
			if (rowSum >= 4) {
				_house(start, end);
				remained -= rowSum;
				start = end;
				break;
			}
		}
	}
	//printf("(%d, %d) %d\n", start, end, remained);
	if (remained > 0) _house(start, 1023);
}
```
