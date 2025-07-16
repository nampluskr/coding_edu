### Solution

```cpp
/*
   ver1-2. X축으로 김밥 말기
		   모든 경우의 수 확인
			SCORE: 94716
*/
#include<stdio.h>

static const int AMINO_TYPE = 20;
static const int AMINO_LEN = 28;
static const int MAX_AMINO = 20;
static const int SPACE_LEN = 100;

typedef struct {
	char symbol;
	bool connector;
	int x, y, z;
} Element;

extern int protein(Element elements[MAX_AMINO][AMINO_LEN]);
extern void fold_amino(int aminoNum, bool front, int axis, bool anticlockwise);
extern void fold_element(int aminoNum, int elementNum, bool front, int axis, bool anticlockwise);

enum { X, Y, Z };
enum { back, front };
enum { clock, anti };

int N;
Element E[MAX_AMINO][AMINO_LEN];
int aminoSize[MAX_AMINO];						// 아미노산 별 길이
bool map[SPACE_LEN][SPACE_LEN];					// map[z][y] = 아미노산이 있는지 표시

int dz[] = { 1,0,-1,0 }, dy[] = { 0,-1,0,1 };
int gSpace[SPACE_LEN][SPACE_LEN][SPACE_LEN];

int maxScore, maxPath[20];
int score, path[20];

void drawSpace(int id, int z, int y) {
	for (int i = 0; i < aminoSize[id]; i++) {
		int x = E[id][i].x;
		switch (E[id][i].symbol) {
		case 'H': gSpace[z][y][x] = 1; break;
		case 'C': gSpace[z][y][x] = 2; break;
		case 'O': gSpace[z][y][x] = 5; break;
		case 'N': gSpace[z][y][x] = 10; break;
		case 'S': gSpace[z][y][x] = 30; break;
		}
		score +=
			(gSpace[z][y][x] * gSpace[z - 1][y][x] + gSpace[z][y][x] * gSpace[z + 1][y][x] +
				gSpace[z][y][x] * gSpace[z][y - 1][x] + gSpace[z][y][x] * gSpace[z][y + 1][x] +
				gSpace[z][y][x] * gSpace[z][y][x - 1] + gSpace[z][y][x] * gSpace[z][y][x + 1]) * 2;
	}
}

void eraseSpace(int id, int z, int y) {
	for (int i = 0; i < aminoSize[id]; i++) {
		int x = E[id][i].x;
		score -=
			(gSpace[z][y][x] * gSpace[z - 1][y][x] + gSpace[z][y][x] * gSpace[z + 1][y][x] +
				gSpace[z][y][x] * gSpace[z][y - 1][x] + gSpace[z][y][x] * gSpace[z][y + 1][x] +
				gSpace[z][y][x] * gSpace[z][y][x - 1] + gSpace[z][y][x] * gSpace[z][y][x + 1]) * 2;
		gSpace[z][y][x] = 0;
	}
}

void recur(int id, int z, int y, int dir) {
	map[z][y] = 1;			// (z,y) 점유중임을 표시
	drawSpace(id, z, y);

	// base case
	if (id == N - 1) {
		if (maxScore < score) {
			maxScore = score;
			for (int i = 1; i < N - 1; i++) maxPath[i] = path[i];
		}
	}

	// normal case
	else {
		for (int i = -1; i <= 1; i++) {	// 반시계, 그대로, 시계
			int nd = (dir + i + 4) % 4;
			int nz = z + dz[nd];
			int ny = y + dy[nd];
			if (map[nz][ny]) continue;
			if (i == 1 && y == 50 && z == 50 + id) continue;	// 상하대칭인 상황은 한쪽만 수행하여 시간 절약

			path[id] = i;
			recur(id + 1, nz, ny, nd);
		}
	}

	map[z][y] = 0;
	eraseSpace(id, z, y);
}

void process()
{
	// 초기화
	maxScore = score = 0;
	for (int z = 0; z < SPACE_LEN; z++)
		for (int y = 0; y < SPACE_LEN; y++) {
			map[z][y] = 0;
			for (int x = 0; x < SPACE_LEN; x++)
				gSpace[z][y][x] = 0;
		}

	// 아미노산 정보 갖고오기
	N = protein(E);

	// 아미노산 길이와 커넥터 위치 찾기
	for (int i = 0; i < N; i++) {
		int j = 0;
		for (; E[i][j].symbol; j++);
		aminoSize[i] = j;
	}

	// 모든 경우의 수 탐색_0번은 (z=50,y=50), 1번은 (z=51,y=50) 고정
	map[50][50] = 1;
	drawSpace(0, 50, 50);
	recur(1, 51, 50, 0);	// +z 방향 시작

	// 최대 값일 때의 상태로 접기
	for (int i = 1; i < N - 1; i++) {
		if (maxPath[i] == -1) fold_amino(i, back, X, anti);
		if (maxPath[i] == 1) fold_amino(i, back, X, clock);
	}
}
```
