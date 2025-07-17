### Solution

```cpp
/*
 ver1. 가장 가까운 곳에서 1개씩 옮기기

 SCORE: 1'424'099'050 -> SCORE: 1'423'536'450
*/
#include<stdio.h>

static const int MAPSIZE = 1000;
static const int MAXN = 100;

extern bool move(int mDistance);
extern bool load(int mCargoID);
extern bool unload(int mCargoID);

typedef struct
{
	int id;
	int weight;
	int dest;
}Cargo;

struct Train
{
	int pos;			// 열차 위치
	int weight;			// 실은 무게
	int num;			// 실은 화물 개수
	Cargo cargos[MAXN];	// 실은 화물 리스트
}train;

int *cargo_num;
Cargo(*cargos)[MAPSIZE];

void Move(int mDistance)
{
	move(mDistance);
	train.pos = (train.pos + mDistance + MAPSIZE) % MAPSIZE;
}

void Load(int mCargoID)
{
	if (!load(mCargoID)) {
		//printf("load false\n");
	}

	int pos = train.pos;
	for (int i = 0; i < cargo_num[pos]; i++) {
		if (cargos[pos][i].id == mCargoID) {
			train.weight += cargos[pos][i].weight;
			train.cargos[train.num] = cargos[pos][i];
			train.num++;

			cargo_num[pos]--;
			cargos[pos][i] = cargos[pos][cargo_num[pos]];
		}
	}
}

void Unload(int mCargoID)
{
	if (!unload(mCargoID)) {
		//printf("unload false\n");
	}


	int pos = train.pos;
	for (int i = 0; i < train.num; i++) {
		if (train.cargos[i].id == mCargoID) {
			//cargos[pos][cargo_num[pos]++] = train.cargos[i];

			train.weight -= train.cargos[i].weight;
			train.num--;
			train.cargos[i] = train.cargos[train.num];
		}
	}
}

int getDist() {
	for (int dist = 0; dist <= 500; dist++) {
		int pos1 = (train.pos + dist + MAPSIZE) % MAPSIZE;
		int pos2 = (train.pos - dist + MAPSIZE) % MAPSIZE;
		if (cargo_num[pos1]) return dist;
		if (cargo_num[pos2]) return -dist;
	}
	return MAPSIZE;
}

void process(Cargo mCargos[MAPSIZE][MAPSIZE], int mCargoNum[])
{
	cargo_num = mCargoNum;
	cargos = mCargos;

	train = {};
	while (1) {
		// 1. 옮겨야할 화물이 있는 가장 가까운 위치로 이동
		int dist = getDist();		// 가장 가까운 위치와의 distance 반환
		if (dist == MAPSIZE) break; // 없는 경우
		if (dist) Move(dist);		// 이동해야 하는 경우

		// 2. 첫번째 화물 싣기
		Cargo c = cargos[train.pos][0];
		Load(c.id);

		// 3. 목적지로 이동
		if (c.dest != train.pos) {
			int dist1 = (c.dest - train.pos + MAPSIZE) % MAPSIZE;
			int dist2 = (train.pos - c.dest + MAPSIZE) % MAPSIZE;

			if (dist1 < dist2) Move(dist1);
			else Move(-dist2);
		}

		// 4. 실은 화물 내려놓기
		Unload(c.id);
	}
}
```
