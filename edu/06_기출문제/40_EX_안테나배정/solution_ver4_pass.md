### Solution

```cpp
/*
 ver4
  * merge sort 구현
  * subtask=2 부터는 실제 이동에 따른 거리 측정

  SN=5,  SCORE: 1913153
  SN=10, SCORE: 1889684
  PASS
*/
#include<stdio.h>
#include<algorithm>
using namespace std;

const int MN = 100;
const int AN = 150;
const int UN = 10000;
const int SN = 5;

int subtask;

#define ABS(x) (((x)<0)?(-(x)):(x))
struct Coordinates {
	int y, x;
	Coordinates() {
		y = x = 0;
	}
	Coordinates(int _y, int _x) {
		y = _y;
		x = _x;
	}
	int operator-(Coordinates& param) {
		return ABS(y - param.y) + ABS(x - param.x);
	}
}*A, *UE, ue0[UN];

int ueDir[UN];	// 0=위, 1=오른쪽, 2=아래, 3=왼쪽, 4=X
int dy[4] = { 1,0,-1,0 };
int dx[4] = { 0,1,0,-1 };

struct Data {
	int id, dist;
	bool operator<(Data r) {
		return dist < r.dist;
	}
}ueD[UN][AN], D[UN];

void init(Coordinates antennas[]) {
	A = antennas;
	subtask = 0;
}

Data tmp[UN];
void merge(Data a[], int s, int e) {
	if (s == e) return;
	int m = (s + e) / 2;
	merge(a, s, m), merge(a, m + 1, e);
	int i = s, j = m + 1, k = s;
	while (i <= m && j <= e) {
		if (a[i].dist <= a[j].dist) tmp[k++] = a[i++];
		else tmp[k++] = a[j++];
	}
	while (i <= m) tmp[k++] = a[i++];
	while (j <= e) tmp[k++] = a[j++];
	for (i = s; i <= e; i++) a[i] = tmp[i];
}

int getDir(Coordinates s, Coordinates e) {
	// 같은 위치라면 방향 없음
	if (s - e == 0) return 4;

	// 4방향으로 각각 5번씩 이동해보고 목적지와 같으면 해당 방향 반환
	// 방향전환이 된다면 전환된 방향 반환
	for (int i = 0; i < 4; i++) {
		int dir = i, y = s.y, x = s.x;
		for (int j = 0; j < 5; j++) {
			int ny = y + dy[dir], nx = x + dx[dir];
			if (ny < 0 || ny >= 100 || nx < 0 || nx >= 100) dir = (dir + 2) % 4;
			y += dy[dir], x += dx[dir];
		}

		// 5칸 이동 후 현재 위치와 같다면 방향 확정
		if (x == e.x && y == e.y) return dir;
	}
}

// 움직이는 UE, i를 5칸 이동시켜 보며
// 1) 방향 전환 수행
// 2) 모든 안테나 j에 대해 0~4칸 이동한 거리 중 최대 거리를 ueD[i][j]에 기록
void updateDist(int i) {
	Coordinates ue[5];	// 1~5 칸 이동 좌표 기록
	int&dir = ueDir[i];	// 방향
	int y = UE[i].y, x = UE[i].x;
	for (int j = 0; j < 5; j++) {
		int ny = y + dy[dir], nx = x + dx[dir];
		if (ny < 0 || ny >= 100 || nx < 0 || nx >= 100) dir = (dir + 2) % 4;
		y += dy[dir], x += dx[dir];
		ue[j] = { y,x };
	}

	// 0~4칸 이동한 좌표들과 안테나 거리 중 큰 값으로 기록
	for (int j = 0; j < AN; j++) {
		ueD[i][j] = { j, UE[i] - A[j] };
		for (int k = 0; k < 4; k++) {
			if (ueD[i][j].dist < ue[k] - A[j])
				ueD[i][j].dist = ue[k] - A[j];
		}
	}

	// dist 오름차순 정렬
	merge(ueD[i], 0, AN - 1);
}

// range[aid] : 배정된 UE의 최대 거리(+4)
// connection[uid] : 배정된 안테나 번호
void scanUE(Coordinates UE_list[], int range[], int conn[]) {
	subtask++;
	UE = UE_list;

	for (int i = 0; i < AN; i++) range[i] = 0;

	// 첫번째인 경우, ue0[]에 좌표 기록
	if (subtask == 1) {
		// ueD[uid] : 안테나와의 거리 오름차순 정렬
		// D : UE의 가장 가까운 안테나 distSum[=SN개의 (거리*거리) 합] 오름차순 정렬
		for (int i = 0; i < UN; i++) {
			ue0[i] = UE[i];
			for (int j = 0; j < AN; j++)
				ueD[i][j] = { j, UE[i] - A[j] };
			merge(ueD[i], 0, AN - 1);
		}
	}

	// 두번째 이상인 경우,
	else {
		// 두번째인 경우만 5칸 이동 정보를 기반으로 실제 방향 판별
		if (subtask == 2)
			for (int i = 0; i < UN; i++)
				ueDir[i] = getDir(ue0[i], UE[i]);

		// 움직이는 UE에 대해서만 ueD[], ueDir 업데이트
		for (int i = 0; i < UN; i++) {
			if (ueDir[i] < 4) updateDist(i); // dist는 4번까지 정확한 이동을 고려하여 설정
		}
	}

	// UE 별 우선순위 설정
	for (int i = 0; i < UN; i++) {
		int dist = 0;
		for (int j = 0; j < SN; j++)
			dist += ueD[i][j].dist*ueD[i][j].dist;
		D[i] = { i, dist };
	}
	merge(D, 0, UN - 1);

	// UE의 distSum 큰 순으로 안테나 배정
	// 가장 가까운 안테나부터 배정
	int acnt[AN] = {};
	for (int i = UN - 1; i >= 0; i--) {
		int uid = D[i].id;
		Data s = { -1, 0 };	// 선택한 안테나 {id, dist}
		for (int j = 0; j < AN; j++) {
			int aid = ueD[uid][j].id;
			int dist = ueD[uid][j].dist;
			if (acnt[aid] == 100) continue;

			// 수용 가능한 가장 가까운 안테나이거나
			// maxRange가 커지지 않으면서 할당UE수가 가장 적은 안테나
			if (s.id == -1 || (dist <= range[aid] && acnt[aid] < acnt[s.id]))
				s = { aid, dist };
		}

		// i번 UE를 aid번 안테나에 할당
		acnt[s.id]++;
		conn[uid] = s.id;
		if (range[s.id] < s.dist)
			range[s.id] = s.dist;
	}

	// 첫번째에만 정확하지 않은 움직임을 고려하여 range+4
	if (subtask == 1)
		for (int i = 0; i < AN; i++) range[i] += 4;
}
```