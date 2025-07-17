### Main

```cpp
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

static int station_id[MAPSIZE];				// 좌표별 역 번호? 없으면 -1?

static int cargo_num[MAPSIZE];				// 좌표별 화물 개수
static int cargo_num_bak[MAPSIZE];

static Cargo cargos[MAPSIZE][MAPSIZE];		// 좌표별 화물 리스트
static Cargo cargos_bak[MAPSIZE][MAPSIZE];

static int station_pos[MAPSIZE];
static int N, M;

struct Train
{
	int pos;			// 열차 위치
	int weight;			// 실은 무게
	int num;			// 실은 화물 개수
	Cargo cargos[MAXN];	// 실은 화물 리스트
};

static Train train;
static long long gTotalScore;

///////////////////////////////////////

extern void process(Cargo[][MAPSIZE], int[]);

bool move(int mDistance)
{
	// 거리 절대값이 맵 크기보다 크면 무시
	if (mDistance < -MAPSIZE || mDistance > MAPSIZE) {
		printf("move\n");
		return false;
	}
	
	// 기차 위치 변경(+:시계방향, -:반시계방향)
	train.pos = (train.pos + mDistance + MAPSIZE) % MAPSIZE;

	if (mDistance < 0)
		mDistance = -mDistance;

	// (기차총무게+50)*(이동거리+10)
	gTotalScore += (train.weight + 50) * (mDistance + 10);
	return true;
}

bool load(int mCargoID)
{
	int pos = train.pos;

	// 기차 위치가 역이 아닌 경우 무시
	if (station_id[pos] == -1) {
		printf("load 1\n");
		return false;
	}

	// 기차 위치에서 전체탐색
	for (int i = 0; i < cargo_num[pos]; i++) {
		// 목표화물 찾은 경우
		if (cargos[pos][i].id == mCargoID) {
			// 총무게가 100을 넘어가게된다면 무시
			if (train.weight + cargos[pos][i].weight > 100) {
				printf("load 2\n");

				return false;
			}

			// 싣기
			train.weight += cargos[pos][i].weight;
			train.cargos[train.num] = cargos[pos][i];
			train.num++;

			// 역 리스트에서 실은 화물 삭제
			cargo_num[pos]--;
			cargos[pos][i] = cargos[pos][cargo_num[pos]];

			return true;
		}
	}
	printf("load 3\n");
	return false;
}

bool unload(int mCargoID)
{
	int pos = train.pos;

	// 역이 아니거나 역에 이미 1000개의 화물이 있는 경우 무시
	if (station_id[pos] == -1 || cargo_num[pos] == MAPSIZE) {
		printf("unload 1\n");
		return false;
	}

	// 기차 화물리스트 전체탐색
	for (int i = 0; i < train.num; i++) {
		// 목표 화물 찾으면 내리기
		if (train.cargos[i].id == mCargoID) {
			cargos[pos][cargo_num[pos]++] = train.cargos[i];

			train.weight -= train.cargos[i].weight;
			train.num--;
			train.cargos[i] = train.cargos[train.num];

			return true;
		}
	}
	printf("unload 2\n");

	return false;
}

static void init()
{
	N = 0;

	// 기차 초기화
	train.pos = train.weight = train.num = 0;

	// 위치별 초기화
	for (int i = 0; i < MAPSIZE; i++) {
		station_id[i] = -1;
		cargo_num_bak[i] = cargo_num[i] = 0;
	}

	// 역 생성(0~N-1), N개(<=100)
	for (int i = 0; i < MAXN; i++) {
		// 역 위치 = 0~999
		int pos = pseudo_rand() % MAPSIZE;

		// 중복 되는 경우(역개수 100개에서부터 한개씩 감소)
		if (station_id[pos] >= 0)
			continue;

		// 위치별 역 번호(0~)
		station_id[pos] = N;

		// 역 번호별 위치
		station_pos[N] = pos;

		// 생성한 역의 화물 개수 = 30 ~ 100개
		cargo_num_bak[pos] = cargo_num[pos] = pseudo_rand() % 71 + 30;
		N++;
	}

	// 역마다 설정된 개수만큼 화물 생성 (화물 번호 = 0 ~ M-1)
	M = 0;
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < cargo_num[i]; j++) {
			Cargo new_cargo;
			new_cargo.id = M;

			// 무게 설정(75%: 1~50, 25%: 51~100)
			
			// 50% : 1~50
			if (pseudo_rand() % 2 == 0)
				new_cargo.weight = pseudo_rand() % 50 + 1;

			// 50% : 1~100(= 25% : 1~50, 25% : 51~100)
			else
				new_cargo.weight = pseudo_rand() % 100 + 1;

			// 목표 좌표 설정(목적지=역)
			new_cargo.dest = station_pos[pseudo_rand() % N];

			cargos_bak[i][j] = cargos[i][j] = new_cargo;

			M++;
		}
	}
}

static bool verify()
{
	// 패널티1. 기차에 화물이 남아있는 경우
	if (train.num > 0) {
		printf("p1\n");
		return false;
	}

	// 패널티2. 모든 화물이 목적지에 운송되지 않은 경우
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < cargo_num[i]; j++) {
			if (cargos[i][j].dest != i) {
				printf("p2\n");
				printf("%d %d %d\n", cargo_num[i], cargos[i][j].dest, i);
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	setbuf(stdout, NULL);

	gTotalScore = 0;

	for (int tc = 0; tc < MAX_TC; ++tc) {
		printf("[%d]\n", tc);
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
```
