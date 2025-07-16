### Solution

```cpp
/*
 ver2-3. X 축으로 절반 접을 때, 꼭 절반 위치가 아니라 여러 위치에서 해보기
			 ex) 2345   3456
				 1876   2187   ...

		SCORE: 108866

		ps)
		추가적으로 해볼 방법들은 많아보인다.
		ex. fold_amino() 고려해서 고밸류끼리 같은 x좌표에 놓이게 설정
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
	int len;
	int val[AMINO_LEN];
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

int gSpace[SPACE_LEN][SPACE_LEN][SPACE_LEN];

// main.cpp verify() 함수 변형
int getScore()
{
	protein(E);

	for (int z = 0; z < SPACE_LEN; z++)
		for (int y = 0; y < SPACE_LEN; y++)
			for (int x = 0; x < SPACE_LEN; x++)
				gSpace[z][y][x] = 0;

	for (int aminoIdx = 0; aminoIdx < N; aminoIdx++) {
		for (int elemIdx = 0; E[aminoIdx][elemIdx].symbol; elemIdx++) {
			int x = E[aminoIdx][elemIdx].x;
			int z = E[aminoIdx][elemIdx].z;
			int y = E[aminoIdx][elemIdx].y;

			if (x < 0 || x >= SPACE_LEN || y < 0 || y >= SPACE_LEN || z < 0 || z >= SPACE_LEN || gSpace[z][y][x]) {
				return 0;
			}

			switch (E[aminoIdx][elemIdx].symbol) {
			case 'H': gSpace[z][y][x] = 1; break;
			case 'C': gSpace[z][y][x] = 2; break;
			case 'O': gSpace[z][y][x] = 5; break;
			case 'N': gSpace[z][y][x] = 10; break;
			case 'S': gSpace[z][y][x] = 30; break;
			}
		}
	}

	int score = 0;
	for (int z = 1; z < SPACE_LEN - 1; z++)
		for (int y = 1; y < SPACE_LEN - 1; y++)
			for (int x = 1; x < SPACE_LEN - 1; x++)
				score +=
				gSpace[z][y][x] * gSpace[z - 1][y][x] + gSpace[z][y][x] * gSpace[z + 1][y][x] +
				gSpace[z][y][x] * gSpace[z][y - 1][x] + gSpace[z][y][x] * gSpace[z][y + 1][x] +
				gSpace[z][y][x] * gSpace[z][y][x - 1] + gSpace[z][y][x] * gSpace[z][y][x + 1];
	return score;
}

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
			fold_element(i, conIdx[i] + 4, back, Z, anti);
			fold_element(i, conIdx[i] + 5, back, Z, anti);
			fold_element(i, conIdx[i], front, Z, clock);

			int t = getType(i);
			for (int j = conIdx[i] - 1; j > 0; j--) {
				if (maxPath[t][j] == 1) fold_element(i, j, front, Z, clock);
				if (maxPath[t][j] == -1) fold_element(i, j, front, Z, anti);
			}
		}
	}


	/* 2. fold_amino() 절반 접기*/
	int maxScore = 0, max_i = 0;
	for (int i = 0; i < N; i++) {
		// i 기준으로 나누기
		int a = (i + 1) / 2;	// 왼쪽 접을 index
		int b = (i + N) / 2;	// 오른쪽 접을 index
		if (a >= 2) {
			fold_amino(a, front, X, clock);
			fold_amino(a - 1, front, X, clock);
		}
		if (b < N - 2) {
			fold_amino(b, back, X, anti);
			fold_amino(b + 1, back, X, anti);
		}

		int score = getScore();
		if (maxScore < score) {
			maxScore = score;
			max_i = i;
		}

		if (a >= 2) {
			fold_amino(a, front, X, anti);
			fold_amino(a - 1, front, X, anti);
		}
		if (b < N - 2) {
			fold_amino(b, back, X, clock);
			fold_amino(b + 1, back, X, clock);
		}
	}


	int i = max_i;
	int a = (i + 1) / 2;
	int b = (i + N) / 2;
	if (a >= 2) {
		fold_amino(a, front, X, clock);
		fold_amino(a - 1, front, X, clock);
	}
	if (b < N - 2) {
		fold_amino(b, back, X, anti);
		fold_amino(b + 1, back, X, anti);
	}
}
```
