## EX화물기차

### 문제


**[제한 사항]**

* 메모리 : heap + global + stack = 256MB    단, stack size = 1MB

* 제한시간 10초

* 제출 횟수 제한 10회




**[주의 사항]**

User Code 안에는  malloc.h 외에 어떤 헤더파일도 추가할 수 없다.

채점시 main.cpp 는 그대로 사용된다. 단, seed는 변경될 수 있다.

치팅 방지를 위한 코드가 추가될 수 있다.

제출한 코드에 대하여 엄격한 코드 리뷰를 실시한다.

Main 에서 사용하는 변수에 직접적으로 접근하는 행위를 금지한다.

본 검정은 c++만 지원한다.



**[문제 설명]**

길이 1000의 원형으로 만들어진 철도 위에 최대 100개의 기차역이 주어진다.

초기 각 역에는 최대 100개의 화물이 존재한다.

당신은 주어진 API를 이용해 기차를 시계 방향, 시계 반대방향으로 움직일 수 있고,
화물을 싣거나 내릴 수 있다.



**[API]**

* user.cpp에서 구현해야 하는 API함수는 다음과 같다.

```cpp
void process(Cargo mCargos[MAPSIZE][MAPSIZE], int mCargoNum[])
```
응시자가 구현하는 함수이다.

현재 기차는 좌표 0에 위치해 있다.

mCargos 에는 화물의 정보가 저장되어 있다.

화물의 정보는 화물의 ID, 무게, 목적지 좌표 값이 저장되어 있다.

mCargoNum 에는 각 좌표에 존재하는 화물의 갯수 값이 저장되어 있다.

이 값이 1 이상일 경우 그 좌표는 역이고, 그렇지 않을 경우 역이 아니다.

역이 아닌 곳에는 화물을 unload 할 수 없다.

move(), load(), unload() 함수를 적절히 사용하여 SCORE 를 최소화 하라.



* main.cpp에서 제공하는 API함수는 다음과 같다.

```cpp
bool move(int mDistance)
```
기차의 현재 위치를 mDistance 만큼 이동시킨다.

mDistance는 음수값도 가능하다.


```cpp
bool load(int mCargoID)
```
ID 값이 mCargoID 인 화물을 기차에 싣는다.

기차에 실을 수 있는 화물 무게의 합은 100 이다.

무게의 합이 100이 넘을 경우 실을 수 없다.


```cpp
bool unload(int mCargoID)
```
ID 값이 mCargoID 인 화물을 현재 위치에 내려 놓는다.

현재 위치가 역이 아닐 경우 내려놓을 수 없다.

※ 기타 자세한 내용은 주어진 코드를 분석하라.

### Code Template

```cpp
// main.cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

static unsigned long long seed = 5;
static int pseudo_rand(void)
{
	seed = seed * 25214903917ULL + 11ULL;
	return (seed >> 16) & 0x3fffffff;
}

/* These constant variables will NOT be changed */
static const int MAX_TC = 10;
static const int MAXN = 100;
static const int MAPSIZE = 1000;
static const long long PENALTY = 100000000000000;

typedef struct
{
	int id;
	int weight;
	int dest;
}Cargo;

static int station_id[MAPSIZE];

static int cargo_num[MAPSIZE];
static int cargo_num_bak[MAPSIZE];

static Cargo cargos[MAPSIZE][MAPSIZE];
static Cargo cargos_bak[MAPSIZE][MAPSIZE];

static int station_pos[MAPSIZE];
static int N, M;

struct Train
{
	int pos;
	int weight;
	int num;
	Cargo cargos[MAXN];
};

static Train train;
static long long gTotalScore;

///////////////////////////////////////

extern void process(Cargo[][MAPSIZE], int[]);

bool move(int mDistance)
{
	if (mDistance < -MAPSIZE || mDistance > MAPSIZE)
		return false;

	train.pos = (train.pos + mDistance + MAPSIZE) % MAPSIZE;

	if (mDistance < 0)
		mDistance = -mDistance;

	gTotalScore += (train.weight + 50) * (mDistance + 10);
	return true;
}

bool load(int mCargoID)
{
	int pos = train.pos;

	if (station_id[pos] == -1)
		return false;

	for (int i = 0; i < cargo_num[pos]; i++) {
		if (cargos[pos][i].id == mCargoID)	{
			if (train.weight + cargos[pos][i].weight > 100)
				return false;

			train.weight += cargos[pos][i].weight;
			train.cargos[train.num] = cargos[pos][i];
			train.num++;

			cargo_num[pos]--;
			cargos[pos][i] = cargos[pos][cargo_num[pos]];

			return true;
		}
	}
	return false;
}

bool unload(int mCargoID)
{
	int pos = train.pos;

	if (station_id[pos] == -1 || cargo_num[pos] == MAPSIZE)
		return false;

	for (int i = 0; i < train.num; i++)	{
		if (train.cargos[i].id == mCargoID)	{
			cargos[pos][cargo_num[pos]++] = train.cargos[i];

			train.weight -= train.cargos[i].weight;
			train.num--;
			train.cargos[i] = train.cargos[train.num];

			return true;
		}
	}
	return false;
}

static void init()
{
	N = 0;
	train.pos = train.weight = train.num = 0;

	for (int i = 0; i < MAPSIZE; i++) {
		station_id[i] = -1;
		cargo_num_bak[i] = cargo_num[i] = 0;
	}

	for (int i = 0; i < MAXN; i++) {
		int pos = pseudo_rand() % MAPSIZE;

		if (station_id[pos] >= 0)
			continue;

		station_id[pos] = N;
		station_pos[N] = pos;
		cargo_num_bak[pos] = cargo_num[pos] = pseudo_rand() % 71 + 30;
		N++;
	}

	M = 0;
	for (int i = 0; i < MAPSIZE; i++)	{
		for (int j = 0; j < cargo_num[i]; j++) {
			Cargo new_cargo;
			new_cargo.id = M;

			if (pseudo_rand() % 2 == 0)
				new_cargo.weight = pseudo_rand() % 50 + 1;
			else
				new_cargo.weight = pseudo_rand() % 100 + 1;

			new_cargo.dest = station_pos[pseudo_rand() % N];
			cargos_bak[i][j] = cargos[i][j] = new_cargo;

			M++;
		}
	}
}

static bool verify()
{
	if (train.num > 0)
		return false;

	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < cargo_num[i]; j++)	{
			if (cargos[i][j].dest != i)
				return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	setbuf(stdout, NULL);

	gTotalScore = 0;

	for (int tc = 0; tc < MAX_TC; ++tc) {
		init();

		process(cargos_bak, cargo_num_bak);

		if (verify() == false) {
			gTotalScore = PENALTY;
			break;
		}
	}

       printf("SCORE: %lld\n", gTotalScore);

	//////////////////////////////////////////////////////////////////////////////////
	if (gTotalScore > 998'000'000) puts("FAIL"); 
	else puts("PASS");
	//////////////////////////////////////////////////////////////////////////////////

	return 0;
}

// user.cpp
static const int MAPSIZE = 1000;

typedef struct
{
	int id;
	int weight;
	int dest;
}Cargo;

extern bool move(int mDistance);
extern bool load(int mCargoID);
extern bool unload(int mCargoID);

void process(Cargo mCargos[MAPSIZE][MAPSIZE], int mCargoNum[])
{
}
```
