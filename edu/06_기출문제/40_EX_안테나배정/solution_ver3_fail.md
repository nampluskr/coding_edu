### Solution

```cpp
/*
 ver3
  * 안테나 배정시, maxRange를 넘기지 않는 안테나 중
	할당된 UE 개수가 가장 적은 안테나 선택
  * 없으면 할당 가능한 가장 가까운 안테나 선택

 SN=5,	SCORE: 3198311 => 2993847
 SN=10, SCORE: 3153940 => 2979653
 SN=20, SCORE: 3250007 => 3076946
 FAIL
*/
#include<stdio.h>
#include<algorithm>
using namespace std;

const int MN = 100;
const int AN = 150;
const int UN = 10000;
const int SN = 5;

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
}*A, *UE;

struct Data {
	int id, dist;
	bool operator<(Data r) {
		return dist < r.dist;
	}
}ueD[UN][AN], D[UN];

void init(Coordinates antennas[]) {
	A = antennas;
}

void scanUE(Coordinates UE_list[], int range[], int conn[]) {
	UE = UE_list;

	for (int i = 0; i < AN; i++) range[i] = 0;

	// ueD[uid] : 안테나와의 거리 오름차순 정렬
	// D : UE의 가장 가까운 안테나 distSum[=SN개의 (거리*거리) 합] 오름차순 정렬
	for (int i = 0; i < UN; i++) {
		for (int j = 0; j < AN; j++)
			ueD[i][j] = { j, UE[i] - A[j] };
		sort(ueD[i], ueD[i] + AN);	// operator<

		int dist = 0;
		for (int j = 0; j < SN; j++)
			dist += ueD[i][j].dist*ueD[i][j].dist;
		D[i] = { i, dist };
	}
	sort(D, D + UN);

	// UE의 distSum 큰 순으로 안테나 배정
	// 가장 가까운 안테나부터 배정
	int acnt[AN] = {};
	for (int i = UN - 1; i >= 0; i--) {
		int uid = D[i].id;
		Data s = { -1, 0 };	// 선택한 안테나 {id, dist}
		for (int j = 0; j < AN; j++) {
			int aid = ueD[uid][j].id;
			int dist = ueD[uid][j].dist + 4;
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
}
```