### Solution

```cpp
/*
   ver4. 진행 방향을 네 방향(+y, -y, +x, -y)으로 각각 해보기

   seed = 250517,	SCORE: 143,036,051
   seed = 64,		SCORE: 176,518,078
   seed = 12345,	SCORE: 232,198,175
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
Point orgH[2000];

struct MyPoint {
	int x, y;
	int orgx, orgy;
}H[2000];

// 진행방향별 집 기록
int dir;
struct Record {
	int n;
	Point points[2000][4];
}R[4];

bool comp_y(MyPoint l, MyPoint r) {
	if (l.y != r.y) return l.y < r.y;
	return l.x < r.x;
}

bool comp_x(MyPoint l, MyPoint r) {
	if (l.x != r.x) return l.x < r.x;
	return l.y < r.y;
}

int used[2000], ucnt;

void house(MyPoint H[], int s, int e) {
	ucnt++;
	int&n = R[dir].n;
	Point *points = R[dir].points[n];
	for (int i = 0; i < 4; i++) {
		auto&p = points[i] = { -1, -1 };
		int pick;
		for (int j = s; j <= e; j++) {
			if (used[j] == ucnt) continue;
			if (p.x != -1 && i == 0 && p.y >= H[j].orgy) continue;
			if (p.x != -1 && i == 1 && p.y <= H[j].orgy) continue;
			if (p.x != -1 && i == 2 && p.x >= H[j].orgx) continue;
			if (p.x != -1 && i == 3 && p.x <= H[j].orgx) continue;

			p = { H[j].orgx, H[j].orgy };
			pick = j;
		}
		used[pick] = ucnt;
	}
	n++;
}

MyPoint H2[2000];
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

void houseRemain(int s, int e) {
	int n = 0;
	for (int i = s; i <= e; i++) H2[n++] = H[i];
	sort(H2, H2 + n, comp_x);
	H2[n] = { 10000, 10000 };

	s = 0;
	for (int i = 0; i < n; i++) {
		if ((i - s + 1 >= 4 && i < n - 4 && H2[i].x != H2[i + 1].x) || i == n - 1) {
			house(H2, s, i);
			s = i + 1;
		}
	}
}

void pro() {
	R[dir].n = 0;
	sort(H, H + N, comp_y);

	int c = 0, s = 0;
	for (int i = 0; i < N; i++) {
		c++;
		if (i < N - 4 && c % 4 == 0 && H[i].y != H[i + 1].y) {
			if (houseIfPossible(s, i)) {
				c = 0;
				s = i + 1;
			}
		}
	}
	if (c) houseRemain(s, N - 1);

}

void process()
{
	N = harubangs(orgH);
	H[N] = { 10000, 10000 };

	// +y 방향
	dir = 0;
	for (int i = 0; i < N; i++)	H[i] = { orgH[i].x, orgH[i].y, orgH[i].x, orgH[i].y };
	pro();

	// -y 방향
	dir = 1;
	for (int i = 0; i < N; i++)	H[i] = { orgH[i].x, -orgH[i].y, orgH[i].x, orgH[i].y };
	pro();

	// +x 방향
	dir = 2;
	for (int i = 0; i < N; i++)	H[i] = { orgH[i].y, orgH[i].x, orgH[i].x, orgH[i].y };
	pro();

	// -x 방향
	dir = 3;
	for (int i = 0; i < N; i++)	H[i] = { orgH[i].y, -orgH[i].x, orgH[i].x, orgH[i].y };
	pro();

	int maxn = 0;
	for (int i = 0; i < 4; i++) if (maxn < R[i].n) maxn = R[i].n;
	for (int i = 0; i < 4; i++) {
		if (R[i].n == maxn) {
			for (int j = 0; j < R[i].n; j++) house(R[i].points[j]);
			break;
		}
	}
}
```
