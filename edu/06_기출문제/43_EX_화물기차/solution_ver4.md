### Solution

```cpp
/*
ver4. ver3 + 매번 모든 화물 unload

* WEIGHT 큰 순
	SCORE: 1'002'395'300	(seed=5)
	SCORE: 50'417'167'098	(seed=1~50)

* DISTANCE 큰 순
	SCORE: 976'288'190		(seed=5)
	SCORE: 49'152'518'548	(seed=1~50)

* SCORE 큰순
	SCORE: 967'774'110		(seed=5)
	SCORE: 48'729'335'158	(seed=1~50)
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

	// 목적지 도착하지 않은 화물만 추가, dists[] 재설정
	int pos = train.pos;
	for (int i = 0; i < train.num; i++) {
		if (train.cargos[i].id == mCargoID) {
			auto cargo = train.cargos[i];

			/****** 목적지 아닌 화물 cargos 추가, dists 재설정 *******/
			if (pos != cargo.dest) {
				cargos[pos][cargo_num[pos]++] = cargo;
				int ldist = (train.pos - cargo.dest + MAPSIZE) % MAPSIZE;
				int rdist = (cargo.dest - train.pos + MAPSIZE) % MAPSIZE;
				dists[cargo.id] = ldist < rdist ? -ldist : rdist;
			}

			train.weight -= cargo.weight;
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

// 특정 기준으로 한 개 화물 선택하기
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
		val = (cargo.weight + 50) * (abs(dists[cargo.id]) + 10);	// 점수
		val = abs(dists[cargo.id]);									// 거리
		val = cargo.weight;											// 무게
		if (maxVal < val) maxCargo = cargo, maxVal = val;
		if (minVal > val) minCargo = cargo, minVal = val;
	}
	return maxCargo;	// 최대
	return minCargo;	// 최소
}

void process(Cargo mCargos[MAPSIZE][MAPSIZE], int mCargoNum[])
{
	cargos = mCargos;
	cargo_num = mCargoNum;

	init();
	while (1) {
		// 화물이 있는 가장 가까운 곳으로 이동
		int dist = getDist();
		if (dist == MAPSIZE) break;
		if (dist) Move(dist);

		// 같은 방향 최대한 load
		while (1) {
			auto cargo = pickCargo();
			if (cargo.id == -1) break;

			Load(cargo.id);
			if (train.num == 1) train.dir = dists[cargo.id] / abs(dists[cargo.id]);	// 1 or -1
		}

		// 가장 가까운 목적지로 이동
		dist = MAPSIZE + 1;
		for (int i = 0; i < train.num; i++) {
			int dest = train.cargos[i].dest;
			if (train.dir > 0) dist = min(dist, (dest - train.pos + MAPSIZE) % MAPSIZE);
			else dist = min(dist, (train.pos - dest + MAPSIZE) % MAPSIZE);
		}
		Move(dist * train.dir);

		// 화물 전부 unload
		while (train.num)
			Unload(train.cargos[0].id);
	}
}
```
