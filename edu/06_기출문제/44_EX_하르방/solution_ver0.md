### Solution

```cpp
/*
  ver0. 집 한개로 전부 포함시키기
  
  SCORE = 0
*/

typedef struct {
	int x, y;
} Point;

extern int harubangs(Point p[]);
extern void house(Point p[]);

int N;
Point H[2000];

Point p[4];
int vcnt, visit[2000];

void house() {
	vcnt++;
	
	for (int i = 0; i < 4; i++) { // miny, minx, maxy, maxx
		p[i] = { -1, -1 };
		for (int j = 0; j < N; j++) {
			if (visit[j] == vcnt) continue;

			if (i==0 && p[i].x != -1 && p[i].y <= H[j].y) continue;
			if (i==1 && p[i].x != -1 && p[i].x <= H[j].x) continue;
			if (i==2 && p[i].x != -1 && p[i].y >= H[j].y) continue;
			if (i==3 && p[i].x != -1 && p[i].x >= H[j].x) continue;

			p[i] = H[j];
			visit[j] = vcnt;
		}
	}

	house(p);
}

void process()
{
	N = harubangs(H);
	house();
}
```

### Solution - ver0 (Nam)

```cpp
/*
  ver0. 집 한개로 전부 포함시키기

  SCORE = 0
*/

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

void process()
{
	N = harubangs(H);
	for (int i = 0; i < N; i++)
		rowCnt[H[i].y]++;

	int i = 0;
	for (i = 0; i < 100; i++)
		_house(i * 10, (i + 1) * 10 - 1);
	_house(i * 10, 1024);

}
```
