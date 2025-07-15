### Solution

```cpp
/*
 ver1
  * UE별 모든 안테나를 거리순 정렬
  * 모든 UE를 가장 가까운 안테나와의 거리(dist0) 순으로 정렬
  * dist0이 가장 큰 UE별로 가장 가까운 안테나에 할당
  * 수용 불가능하면 다음 거리 순으로 할당

 SCORE: 4117288
 FAIL
*/
#include<stdio.h>
#include<algorithm>
using namespace std;

const int MN = 100;
const int AN = 150;
const int UN = 10000;

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
}*A;

struct Data {
	int id, dist;
	bool operator<(Data r) {
		return dist < r.dist;
	}
}ueD[UN][AN], D[UN];

void init(Coordinates antennas[]) {
	A = antennas;
}

// range[aid] : 배정된 UE의 최대 거리(+4)
// connection[uid] : 배정된 안테나 번호
void scanUE(Coordinates UE[], int range[], int conn[]) {

	for (int i = 0; i < AN; i++) range[i] = 0;

	// ueD[uid] : 안테나와의 거리 오름차순 정렬
	// D : UE의 가장 가까운 안테나 거리(dist0) 오름차순 정렬
	for (int i = 0; i < UN; i++) {
		for (int j = 0; j < AN; j++)
			ueD[i][j] = { j, UE[i] - A[j] };
		sort(ueD[i], ueD[i] + AN);	// operator<

		D[i] = { i, ueD[i][0].dist };
	}
	sort(D, D + UN);

	// UE의 dist0 큰 순으로 안테나 배정
	// 가장 가까운 안테나부터 배정
	int cnt[AN] = {};
	for (int i = UN - 1; i >= 0; i--) {
		int uid = D[i].id;
		for (int j = 0; j < AN; j++) {
			int aid = ueD[uid][j].id;
			if (cnt[aid] == 100) continue;

			cnt[aid]++;
			conn[uid] = aid;
			range[aid] = max(range[aid], ueD[uid][j].dist + 4);
			break;
		}
	}
}
```