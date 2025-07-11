### 그림판

```cpp
// pos 위치변수로 mCode의 앞에서부터 순차적으로 디코딩/인코딩

// 인코딩 길이는 1회 분할 시마다 5씩 고정적으로 증가



#include <queue>

using namespace std;



char str[200'001];

bool board[512][512];

int NN, pos, cnt;



void mDecode(int x, int y, int len)

{

	while (str[pos] == ')') pos++;



	if (str[pos] == '(') {

		pos++;

		mDecode(x, y, len / 2);

		pos++;

		mDecode(x, y + len / 2, len / 2);

		pos++;

		mDecode(x + len / 2, y, len / 2);

		pos++;

		mDecode(x + len / 2, y + len / 2, len / 2);

	}

	else {

		bool target = str[pos] == '1' ? 1 : 0;

		for (int i = x; i < x + len; i++)

			for (int j = y; j < y + len; j++)

				board[i][j] = target;

	}

}



void mEncode(int x, int y, int len)

{

	bool isunif = true;

	bool target = board[x][y];



	for (int i = x; i < x + len; i++) {

		for (int j = y; j < y + len; j++)

			if (board[i][j] != target) {

				isunif = false; break;

			}

		if (!isunif) break;

	}



	if (!isunif) {

		str[pos++] = '(';

		mEncode(x, y, len / 2);

		pos++;

		mEncode(x, y + len / 2, len / 2);

		pos++;

		mEncode(x + len / 2, y, len / 2);

		pos++;

		mEncode(x + len / 2, y + len / 2, len / 2);

		str[++pos] = ')';

		cnt += 5;

	}

	else str[pos] = target ? '1' : '0';

}



void init(int N, int L, char mCode[])

{

	NN = N;

	pos = 0;

	for (int i = 0; i < L; i++) str[i] = mCode[i];

	mDecode(0, 0, NN);

}



int encode(char mCode[])

{

	pos = 0;

	cnt = 1;

	mEncode(0, 0, NN);

	for (int i = 0; i < cnt; i++) mCode[i] = str[i];

	return cnt;

}



void makeDot(int mR, int mC, int mSize, int mColor)   // 9 by 9 영역만 전체탐색

{

	for (int i = max(0, mR - mSize + 1); i < min(NN, mR + mSize); i++)

		for (int j = max(0, mC - mSize + 1); j < min(NN, mC + mSize); j++)

			if (abs(i - mR) + abs(j - mC) < mSize) board[i][j] = mColor;

}



void paint(int mR, int mC, int mColor)    // BFS

{

	if (board[mR][mC] == (bool)mColor) return;



	int dx[] = { -1, 1, 0, 0 };

	int dy[] = { 0, 0, -1, 1 };



	queue<pair<int, int>> que;

	que.push({ mR, mC });

	board[mR][mC] = mColor;



	while (!que.empty()) {

		pair<int, int> A = que.front();

		que.pop();



		for (int k = 0; k < 4; k++) {

			int x = A.first + dx[k];

			int y = A.second + dy[k];

			if (x < 0 || y < 0 || x >= NN || y >= NN) continue;

			if (board[x][y] != (bool)mColor) {

				board[x][y] = mColor;

				que.push({ x, y });

			}

		}

	}

}



int getColor(int mR, int mC)

{

	return board[mR][mC];

}
```

### 김동현 (QuadTree)

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
using namespace std;
#define MAX_N 515
#define INF 987654321

bool map[MAX_N][MAX_N];
int idx; char head;
void decompressed(int r, int c, int size, char code[]) {
	head = code[idx++];
	while (head == ')') head = code[idx++];
	if (head == '0' || head == '1') {
		for (int dr = 0; dr < size; dr++)
			for (int dc = 0; dc < size; dc++)
				map[r + dr][c + dc] = int(head - '0');
	}
	else {
		int half = size / 2;
		decompressed(r, c, half, code);
		decompressed(r, c + half, half, code);
		decompressed(r + half, c, half, code);
		decompressed(r + half, c + half, half, code);
	}
}

int tempCnt;
void compress(int r, int c, int size, char temp[]) {
	int cnt = 0;
	for (int i = r; i < r + size; i++)
		for (int j = c; j < c + size; j++)
			cnt += map[i][j];
	if (cnt == 0) temp[tempCnt++] = '0';
	else if (cnt == size * size) temp[tempCnt++] = '1';
	else {
		int half = size / 2;
		temp[tempCnt++] = '(';
		compress(r, c, half, temp);
		compress(r, c + half, half, temp);
		compress(r + half, c, half, temp);
		compress(r + half, c + half, half, temp);
		temp[tempCnt++] = ')';
	}
}

struct Pos {
	int r, c, d;
}que[MAX_N * MAX_N];
bool visit[MAX_N][MAX_N];
int dr[] = { 0,-1,0,1 }, dc[] = { 1,0,-1,0 };
int N;
void bfs(int r, int c, int d, int color) {
	int head = 0, tail = 0;
	memset(visit, 0, sizeof(visit));
	map[r][c] = color, visit[r][c] = 1;
	que[tail].r = r, que[tail].c = c, que[tail++].d = 1;
	while (head < tail) {
		auto cur = que[head++];
		if (cur.d + 1 > d) break;
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1) continue;
			if (d == INF && map[nr][nc] == bool(color)) continue;
			if (!visit[nr][nc]) {
				que[tail].r = nr, que[tail].c = nc, que[tail++].d = cur.d + 1;
				map[nr][nc] = color, visit[nr][nc] = 1;
			}
		}
	}
}

void init(int N, int L, char mCode[]){
	::N = N, idx = 0;
	memset(map, 0, sizeof(map));
	decompressed(0, 0, N, mCode);
}

int encode(char mCode[]){
	tempCnt = 0;
	compress(0, 0, N, mCode);
	return tempCnt;
}

void makeDot(int mR, int mC, int mSize, int mColor){
	bfs(mR, mC, mSize, mColor);
}

void paint(int mR, int mC, int mColor){
	if (map[mR][mC] == bool(mColor)) return;
	bfs(mR, mC, INF, mColor);
}

int getColor(int mR, int mC){
	return map[mR][mC];
}
```
