### Solution

```cpp

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
