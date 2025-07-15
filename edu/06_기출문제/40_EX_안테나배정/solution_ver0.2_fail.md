### Solution

```cpp
// ver0.2
//   UE 번호 순서대로 가장 가까운 안테나에 배정
//   SCORE: 4902411

#include<algorithm>
using namespace std;

static const int MAP_SIZE = 100;
static const int AN = 150;
static const int ANTENNA_CAPA = 100;
static const int UN = 10'000;

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
};

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

Coordinates *A, *UE;

struct Data {
	int aid, dist;
	bool operator<(Data&r) { return dist < r.dist; }
}ueD[UN][AN];

void init(Coordinates antennas[]) {
	A = antennas;
}

void scanUE(Coordinates UE_list[], int range[], int conn[]) {
	for (int i = 0; i < AN; i++) range[i] = 0;

	UE = UE_list;
	for (int uid = 0; uid < UN; uid++) {
		for (int aid = 0; aid < AN; aid++)
			ueD[uid][aid] = { aid, A[aid] - UE[uid] };
		sort(ueD[uid], ueD[uid] + AN);	// operator<
	}

	int acnt[AN] = {};
	for (int uid = 0; uid < UN; uid++) {
		for (int i = 0; i < AN; i++) {
			int aid = ueD[uid][i].aid;
			if (acnt[aid] == ANTENNA_CAPA) continue;
			conn[uid] = aid;
			range[aid] = max(range[aid], ueD[uid][i].dist + 4);
			acnt[aid]++;
			break;
		}
	}
}
```