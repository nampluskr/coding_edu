### Solution

```cpp
/*
	ver2. 하르방을 4의 배수로 선택(1.행작은순, 2.열작은순)
		  1. 행으로 쪼갤수 있는지 확인
		  2. 열 단위로 정확히 4개씩 나눌 수 있는지 확인
		  가능 하면 진행, 불가능하면 4개씩 계속 추가

		  마지막 남는 하르방들은 통째로 짓기

	seed = 250517, SCORE: 141,547,749
*/

#include<stdio.h>
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

bool comp_x(Point l, Point r) {
	if (l.x != r.x) return l.x < r.x;
	return l.y < r.y;
}

int used[2000], ucnt;
void house(Point H[], int s, int e) {
	ucnt++;
	Point points[4];
	for (int i = 0; i < 4; i++) {
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

Point H2[2000];
bool houseIfPossible(int s, int e) {
	int n = 0;
	for (int i = s; i <= e; i++) H2[n++] = H[i];
	sort(H2, H2 + n, comp_x);
	H2[n] = { -1,-1 };

	for (int i = 0; i < n; i += 4)
		if (H2[i + 3].x == H2[i + 4].x) return 0;

	for (int i = 0; i < n; i += 4)
		house(H2, i, i + 3);

	return 1;
}

void process()
{
	N = harubangs(H);
	sort(H, H + N, comp_y);
	H[N] = { -1, -1 };

	int maxc = 0;
	int c = 0, s = 0;
	for (int i = 0; i < N; i++) {
		c++;
		if (i < N - 4 && c % 4 == 0 && H[i].y != H[i + 1].y) {
			if (houseIfPossible(s, i)) {
				if (maxc < c) maxc = c;
				c = 0;
				s = i + 1;
			}
		}
	}
	if (c) house(H, s, N - 1);
}
```
