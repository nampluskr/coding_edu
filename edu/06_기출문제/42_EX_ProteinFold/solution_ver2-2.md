### Solution

```cpp
/*
 ver2-2. 커넥터 왼쪽을 더 좋은 점수로 올리기 위해 타입별 전체탐색 => 타입별 제일 좋은 점수 상태 기록

		SCORE: 107814
*/
#include<stdio.h>

const int AMINO_TYPE = 20;
const int AMINO_LEN = 28;
const int MAX_AMINO = 20;
const int SPACE_LEN = 100;

typedef struct {
	char symbol;
	bool connector;
	int x, y, z;
} Element;

typedef struct {
	char elements[AMINO_LEN];
	int connectorIdx;
	int len;					// 추가
	int val[AMINO_LEN];			// 추가
} AminoType;

AminoType types[AMINO_TYPE] = {
	{ "CHHHCHNHHCOOH",               4 },
	{ "HNCNHHNHCHHCHHCHHCHNHHCOOH", 17 },
	{ "HHNCOCHHCHNHHCOOH",           8 },
	{ "HOOCCHHCHNHHCOOH",            7 },
	{ "HSCHHCHNHHCOOH",              5 },
	{ "HHNCOCHHCHHCHNHHCOOH",       11 },
	{ "HOOCCHHCHHCHNHHCOOH",        10 },
	{ "NHHCHHCOOH",                  3 },
	{ "NHCHNCHCCHHCHNHHCOOH",       11 },
	{ "CHHHCHHCHCHHHCHNHHCOOH",     13 },
	{ "CHHHCHHHCHCHHCHNHHCOOH",     13 },
	{ "HHNCHHCHHCHHCHHCHNHHCOOH",   15 },
	{ "CHHHSCHHCHHCHNHHCOOH",       11 },
	{ "CHHCHNHHCOOH",                3 },
	{ "NHCHHCHHCHHCHCOOH",          11 },
	{ "HOCHHCHNHHCOOH",              5 },
	{ "CHHHCHOHCHNHHCOOH",           8 },
	{ "NHCHCCHHCHNHHCOOH",           8 },
	{ "HOCHHCHNHHCOOH",              5 },
	{ "CHHHCHHCHCHNHHCOOH",			 9 }
};

extern int protein(Element elements[MAX_AMINO][AMINO_LEN]);
extern void fold_amino(int aminoNum, bool front, int axis, bool anticlockwise);
extern void fold_element(int aminoNum, int elementNum, bool front, int axis, bool anticlockwise);

int N;
Element E[20][28];
int aminoSize[20], conIdx[20];
int map[100][100];

enum { back, front };
enum { X, Y, Z };
enum { clock, anti };

int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };
int score, maxScore, path[30], maxPath[30][30], tid;
void recur(int idx, int y, int x, int dir) {
	map[y][x] = types[tid].val[idx];
	score += (map[y][x] * map[y - 1][x] + map[y][x] * map[y + 1][x]
		+ map[y][x] * map[y][x - 1] + map[y][x] * map[y][x + 1]) * 2;

	if (idx == 0) {
		if (maxScore < score) {
			maxScore = score;
			for (int i = 0; i < types[tid].connectorIdx; i++) maxPath[tid][i] = path[i];
		}
	}
	else {
		for (int i = -1; i <= 1; i++) {
			int nd = (dir + i + 4) % 4;
			int nr = y + dy[nd];
			int nc = x + dx[nd];
			if (map[nr][nc]) continue;
			if (nr > 50) continue;
			path[idx] = i;
			recur(idx - 1, nr, nc, nd);
		}
	}

	score -= (map[y][x] * map[y - 1][x] + map[y][x] * map[y + 1][x]
		+ map[y][x] * map[y][x - 1] + map[y][x] * map[y][x + 1]) * 2;
	map[y][x] = 0;
}

void setTypeScore() {
	for (int i = 0; i < AMINO_TYPE; i++) {
		maxScore = score = 0;
		for (int j = 0; types[i].elements[j]; j++) {
			switch (types[i].elements[j]) {
			case 'H': types[i].val[j] = 1; break;
			case 'C': types[i].val[j] = 2; break;
			case 'O': types[i].val[j] = 5; break;
			case 'N': types[i].val[j] = 10; break;
			case 'S': types[i].val[j] = 30; break;
			}
			types[i].len++;
		}
		tid = i;
		for (int j = 0; j < 100; j++)
			for (int k = 0; k < 100; k++)
				map[j][k] = 0;

		int r = 50, c = 50, idx = types[i].connectorIdx;
		for (int j = 0; j <= 4; j++)
			map[r][c + j] = types[i].val[idx++];
		for (int j = 4; idx < types[i].len; j--)
			map[r - 1][c + j] = types[i].val[idx++];

		recur(types[i].connectorIdx - 1, 49, 50, 0);
	}
}

int getType(int id) {
	for (int t = 0; t < AMINO_TYPE; t++) {
		int i = 0;
		for (i = 0; i < aminoSize[id]; i++)
			if (types[t].elements[i] != E[id][i].symbol) break;
		if (i == aminoSize[id]) return t;
	}
}

int tc;
void process()
{
	// 처음일때만 아미노산 타입별 말아올릴 때 좋은 점수 구하기
	tc++;
	if (tc == 1) setTypeScore();

	N = protein(E);

	// 아미노산 길이, 커넥터 위치 기록
	int elemIdx;
	for (int i = 0; i < N; i++) {
		for (elemIdx = 0; E[i][elemIdx].symbol; elemIdx++)
			if (E[i][elemIdx].connector) conIdx[i] = elemIdx;
		aminoSize[i] = elemIdx;
	}

	/* 1. 아미노산 별로 접어 올리기 */
	for (int i = 0; i < N; i++) {
		// NHH(C)HHCOOH
		if (aminoSize[i] == 10) {
			fold_element(i, 3, 1, 2, 0);
			fold_element(i, 2, 1, 2, 0);
			fold_element(i, 6, 0, 2, 1);
			fold_element(i, 8, 0, 2, 1);
		}

		else {
			// 오른쪽
			fold_element(i, conIdx[i] + 4, back, Z, anti);
			fold_element(i, conIdx[i] + 5, back, Z, anti);
			fold_element(i, conIdx[i], front, Z, clock);

			// 왼쪽
			int t = getType(i);
			for (int j = conIdx[i] - 1; j > 0; j--) {
				if (maxPath[t][j] == 1) fold_element(i, j, front, Z, clock);
				if (maxPath[t][j] == -1) fold_element(i, j, front, Z, anti);
			}
		}
	}

	// x축으로 절반 접기
	fold_amino(N / 2, front, X, clock);
	fold_amino(N / 2 - 1, front, X, clock);
}
```
