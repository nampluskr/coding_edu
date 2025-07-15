## EX 우주선착륙

### 문제


**[문제 설명]**

main.cpp를 분석하고

init(), process() 함수를 작성하여 SCORE를 최대화 하시오.




**[제한 사항]**

* 메모리 : heap, global, stack 등을 모두 합쳐 256MB까지 사용 가능. ( 단, stack size = 1MB 까지 사용가능)

* 실행시간 : 20초

* 제출 횟수 제한 : 10회





**[주의 사항]**

1. User Code 안에는 malloc.h 외에 어떤 헤더파일도 추가할 수 없다.

2. 채점시 main.cpp 는 그대로 사용된다. ( 단, 치팅 방지를 위한 방어 코드가 추가 될 수 있다.)

3. 제출한 코드에 대하여 엄격한 코드 리뷰를 실시한다. 따라서 main.cpp의 변수에 직접 접근할 수 없다.

4. 본 검정은 c++만 지원한다.





**[API]**

* user.cpp에서 구현해야 하는 API함수는 다음과 같다.


```cpp
void init(int mMap[][1000], struct Spaceship spaceships[10000])
```
: 행성 표면의 이차원 지도가 mMap[1000][1000]으로 주어진다.

: 우주선의 가로, 세로 정보가 spaceship[10000]으로 주어진다.

: 우주선의 4다리는 각각 125~131범위에서 조절 가능하다.


```cpp
void process(int rows[10000], int cols[10000], int dirs[10000])
```
: i번 우주선이 착륙한 좌상단 행좌표를 rows[i]에 기록한다.

: i번 우주선이 착륙한 좌상단 열좌표를 cols[i]에 기록한다.

: i번 우주선을 90도 회전시킨 경우 1을 그렇지 않은 경우 0을 dirs[i]에 기록한다.


**[Code template]**

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
static const long long PENALTY = 0LL;
static const int MAX_TC = 10;

static const int MAP_SIZE = 1000;
static const int SPACESHIP_NUM = 10000;

static int map_org[MAP_SIZE][MAP_SIZE];
static int map_bak[MAP_SIZE][MAP_SIZE];
static bool occupied[MAP_SIZE][MAP_SIZE];


struct Spaceship {
	int height;
	int width;
};

static struct Spaceship spaceship_org[SPACESHIP_NUM];
static struct Spaceship spaceship_bak[SPACESHIP_NUM];

static int rows[SPACESHIP_NUM];
static int cols[SPACESHIP_NUM];
static int dirs[SPACESHIP_NUM];

static long long SCORE = 0;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

//////////////////////////

static void make_tc()
{
	for (register int y = 0; y < MAP_SIZE; y++)
	{
		for (register int x = 0; x < MAP_SIZE; x++)
		{
			map_org[y][x] = map_bak[y][x] = pseudo_rand() % 125;
			occupied[y][x] = false;
		}
	}

	for (int i = 0; i < SPACESHIP_NUM; i++)
	{
		spaceship_org[i].height = spaceship_bak[i].height = pseudo_rand() % 4 + 2;
		spaceship_org[i].width = spaceship_bak[i].width = pseudo_rand() % 4 + 2;
		rows[i] = cols[i] = dirs[i] = -1;
	}
}

static bool verify()
{
	for (int i = 0; i < SPACESHIP_NUM; i++)
	{
		if (rows[i] == -1 || cols[i] == -1 || dirs[i] == -1)
			continue;

		int y1 = rows[i], x1 = cols[i], y2, x2;

		if (dirs[i] == 0)
		{
			y2 = y1 + spaceship_org[i].height - 1;
			x2 = x1 + spaceship_org[i].width - 1;
		}
		else
		{
			y2 = y1 + spaceship_org[i].width - 1;
			x2 = x1 + spaceship_org[i].height - 1;
		}

		if (y1 < 0 || x1 < 0 || y2 >= MAP_SIZE || x2 >= MAP_SIZE)
			return false;


		int lo = MIN(MIN(MIN(map_org[y1][x1], map_org[y1][x2]), map_org[y2][x1]), map_org[y2][x2]);
		int hi = MAX(MAX(MAX(map_org[y1][x1], map_org[y1][x2]), map_org[y2][x1]), map_org[y2][x2]);

		if (hi - lo > 6)
			return false;

		for (int y = y1; y <= y2; y++)
		{
			for (int x = x1; x <= x2; x++)
			{
				if (occupied[y][x] == true)
					return false;

				occupied[y][x] = true;
			}
		}

		SCORE += (spaceship_org[i].height * spaceship_org[i].width * MIN(spaceship_org[i].height, spaceship_org[i].width));
	}

	return true;
}

extern void init(int[][MAP_SIZE], struct Spaceship[]);
extern void process(int[], int[], int[]);

int main()
{
	setbuf(stdout, NULL);

	SCORE = 0;
	for (int tc = 0; tc < MAX_TC; ++tc) {
		make_tc();
		init(map_bak, spaceship_bak);
		process(rows, cols, dirs);

		if (verify() == false) {
			SCORE = PENALTY;
			break;
		}
	}

	printf("SCORE: %lld\n", SCORE);

	/////////////////////////////////////////////////////////////////////////////////////////////
	if (SCORE >= 3001673) puts("PASS");
	else puts("FAIL");
	/////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}


// user.cpp
static const int MAP_SIZE = 1000;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Spaceship {
	int height;
	int width;
};

void init(int mMap[][MAP_SIZE], struct Spaceship spaceships[]) {
	return;
}

void process(int rows[], int cols[], int dirs[]) {
	return;
}
```