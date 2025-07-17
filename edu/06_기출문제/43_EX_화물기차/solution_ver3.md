### Solution

```cpp
/*
ver3. ver2 + 특정 우선순위로 싣기

* WEIGHT	작은 순	SCORE: 1'040'515'930
* DISTANCE	작은 순	SCORE: 1'019'734'850
* SCORE		작은 순	SCORE: 1'025'921'170
* WEIGHT	높은 순	SCORE: 1'015'180'280
* DISTANCE	높은 순	SCORE: 1'006'686'260
* SCORE		높은 순	SCORE: 1'001'650'740
*/

#include<stdio.h>

static const int MAXN = 100;
static const int MAPSIZE = 1000;

typedef struct
{
	int id;
	int weight;
	int dest;
}Cargo;

struct Train
{
	int pos;
	int weight;
	int num;
	int dir;
	Cargo cargos[MAXN];
};

extern bool move(int mDistance);
extern bool load(int mCargoID);
extern bool unload(int mCargoID);

/////////////////////////////////////

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
int abs(int a) { return a < 0 ? -a : a; }

Train train;
Cargo(*cargos)[MAPSIZE];
int* cargo_num;
int dists[10000];

void Move(int mDistance)
{
	move(mDistance);
	train.pos = (train.pos + mDistance + MAPSIZE) % MAPSIZE;
}

void Load(int mCargoID)
{
	load(mCargoID);

	int pos = train.pos;
	for (int i = 0; i < cargo_num[pos]; i++) {
		if (cargos[pos][i].id == mCargoID) {
			train.weight += cargos[pos][i].weight;
			train.cargos[train.num] = cargos[pos][i];
			train.num++;

			cargo_num[pos]--;
			cargos[pos][i] = cargos[pos][cargo_num[pos]];
			return;
		}
	}
}

void Unload(int mCargoID)
{
	unload(mCargoID);

	// 목적지 도착한 화물 추가X
	int pos = train.pos;
	for (int i = 0; i < train.num; i++) {
		if (train.cargos[i].id == mCargoID) {
			train.weight -= train.cargos[i].weight;
			train.num--;
			train.cargos[i] = train.cargos[train.num];
			return;
		}
	}
}

void init() {
	train.pos = train.weight = train.num = 0;

	// 이미 목적지인 화물 제거, 목적지 방향 거리 설정
	for (int i = 0; i < MAPSIZE; i++) {
		int num = cargo_num[i];
		cargo_num[i] = 0;
		for (int j = 0; j < num; j++) {
			auto cargo = cargos[i][j];
			if (i != cargo.dest) {
				cargos[i][cargo_num[i]++] = cargo;

				int ldist = (i - cargo.dest + MAPSIZE) % MAPSIZE;
				int rdist = (cargo.dest - i + MAPSIZE) % MAPSIZE;
				dists[cargo.id] = ldist < rdist ? -ldist : rdist;
			}
		}
	}
}

// 화물이 있는 가장 가까운 위치 찾기
int getDist() {
	for (int i = 0; i <= MAPSIZE / 2; i++) {
		int l = (train.pos - i + MAPSIZE) % MAPSIZE;
		int r = (train.pos + i) % MAPSIZE;
		if (cargo_num[l]) return -i;
		if (cargo_num[r]) return i;
	}
	return MAPSIZE;
}

// 특정 기준으로 한 개 선택하기
Cargo pickCargo() {
	Cargo maxCargo = { -1 };
	int maxVal = 0;

	Cargo minCargo = { -1 };
	int minVal = 1e9;

	for (int i = 0; i < cargo_num[train.pos]; i++) {
		auto cargo = cargos[train.pos][i];
		if (train.num && dists[cargo.id] * train.dir < 0) continue;
		if (train.weight + cargo.weight > 100) continue;

		int val;
		val = cargo.weight;											// 무게
		val = abs(dists[cargo.id]);									// 거리
		val = (cargo.weight + 50) * (abs(dists[cargo.id]) + 10);	// 점수
		if (maxVal < val) maxCargo = cargo, maxVal = val;
		if (minVal > val) minCargo = cargo, minVal = val;
	}
	return minCargo;	// 최소
	return maxCargo;	// 최대
}

void process(Cargo mCargos[MAPSIZE][MAPSIZE], int mCargoNum[])
{
	cargos = mCargos;
	cargo_num = mCargoNum;

	init();
	while (1) {
		// train이 비어있으면 화물이 있는 가장 가까운 곳으로 이동
		if (!train.num) {
			int dist = getDist();
			if (dist == MAPSIZE) break;
			if (dist) Move(dist);
		}

		// 같은 방향 최대한 load
		while (1) {
			auto cargo = pickCargo();
			if (cargo.id == -1) break;

			Load(cargo.id);
			if (train.num == 1) train.dir = dists[cargo.id] / abs(dists[cargo.id]);	// 1 or -1
		}

		// 가장 가까운 목적지로 이동
		int dist = MAPSIZE + 1;
		for (int i = 0; i < train.num; i++) {
			int dest = train.cargos[i].dest;
			if (train.dir > 0) dist = min(dist, (dest - train.pos + MAPSIZE) % MAPSIZE);
			else dist = min(dist, (train.pos - dest + MAPSIZE) % MAPSIZE);
		}
		Move(dist * train.dir);

		// 목적지인 화물 unload
		for (int i = train.num - 1; i >= 0; i--) {
			if (train.cargos[i].dest == train.pos)
				Unload(train.cargos[i].id);
		}
	}
}
```
