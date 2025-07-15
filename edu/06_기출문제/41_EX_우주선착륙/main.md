### Solution

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

static long long SCORE = 0, tscore;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

//////////////////////////

static void make_tc()
{
	// 맵 생성, 각 셀 = 0 ~ 124
	for (register int y = 0; y < MAP_SIZE; y++)
	{
		for (register int x = 0; x < MAP_SIZE; x++)
		{
			map_org[y][x] = map_bak[y][x] = pseudo_rand() % 125;
			occupied[y][x] = false;
		}
	}

	// 우주선 크기 생성 2*2 ~ 5*5
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
		// 우주선을 사용 안한 경우
		if (rows[i] == -1 || cols[i] == -1 || dirs[i] == -1)
			continue;

		// 우주선 좌상단 좌표
		int y1 = rows[i], x1 = cols[i], y2, x2;

		// 회전 안한 경우 : h*w
		if (dirs[i] == 0)
		{
			y2 = y1 + spaceship_org[i].height - 1;
			x2 = x1 + spaceship_org[i].width - 1;
		}

		// 회전 한 경우 : w*h
		else
		{
			y2 = y1 + spaceship_org[i].width - 1;
			x2 = x1 + spaceship_org[i].height - 1;
		}

		// 패널티1. 우주선이 맵 범위 벗어나는 겨우
		if (y1 < 0 || x1 < 0 || y2 >= MAP_SIZE || x2 >= MAP_SIZE) {
			printf("p1\n");
			return false;
		}


		// 우주선 네 귀퉁이 가장 작은값, 큰값 설정
		int lo = MIN(MIN(MIN(map_org[y1][x1], map_org[y1][x2]), map_org[y2][x1]), map_org[y2][x2]);
		int hi = MAX(MAX(MAX(map_org[y1][x1], map_org[y1][x2]), map_org[y2][x1]), map_org[y2][x2]);

		// 패널티2. 최대,최소 차이가 6 보다 큰 경우
		if (hi - lo > 6) {
			printf("p2\n");
			return false;
		}

		// 패널티3. 우주선끼리 겹치는 경우
		for (int y = y1; y <= y2; y++)
		{
			for (int x = x1; x <= x2; x++)
			{
				if (occupied[y][x] == true) {
					printf("p3\n");
					return false;
				}

				occupied[y][x] = true;
			}
		}

		// h*w*min(h,w) : 8 ~ 125
		SCORE += (spaceship_org[i].height * spaceship_org[i].width * MIN(spaceship_org[i].height, spaceship_org[i].width));
		tscore += (spaceship_org[i].height * spaceship_org[i].width * MIN(spaceship_org[i].height, spaceship_org[i].width));
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
		printf("[%d] ", tc);
		tscore = 0;
		make_tc();
		init(map_bak, spaceship_bak);
		process(rows, cols, dirs);

		if (verify() == false) {
			SCORE = PENALTY;
			break;
		}
		printf("%lld\n", tscore);
	}

	printf("SCORE: %lld\n", SCORE);

	/////////////////////////////////////////////////////////////////////////////////////////////
	if (SCORE >= 3001673) puts("PASS");
	else puts("FAIL");
	/////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}
```