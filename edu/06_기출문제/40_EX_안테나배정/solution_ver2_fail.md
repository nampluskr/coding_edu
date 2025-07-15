### Solution

```cpp
// ver2
//  UE 선택 순서를 (dist0)^2 + (dist1)^2 +..+ (distSN)^2 이 큰 순으로 배정 (또는 dist의 합)
//  SN=5, SCORE: 3198311
//  SN=10, SCORE: 3153940
//  SN=20, SCORE: 3250007

#include<algorithm>
using namespace std;

const int SN = 5;

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
	int id, dist;
	bool operator<(Data&r) { return dist < r.dist; }
};

Data ueD[UN][AN];	// ueD[uid] = { {aid, dist} }유닛별 안테나 거리순 
Data D[UN];			// {uid, dist} : 유닛 가장 가까운 안테나 거리순 

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
		int dist = 0;
		for (int i = 0; i < SN; i++) dist += ueD[uid][i].dist*ueD[uid][i].dist;
		D[uid] = { uid, dist };
	}
	sort(D, D + UN);

	int acnt[AN] = {};
	for (int i = UN - 1; i >= 0; i--) {
		int uid = D[i].id;
		for (int j = 0; j < AN; j++) {
			int aid = ueD[uid][j].id;
			if (acnt[aid] == 100) continue;
			conn[uid] = aid;
			range[aid] = max(range[aid], ueD[uid][j].dist + 4);
			acnt[aid]++;
			break;
		}
	}
}
```