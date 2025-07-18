### Main

```cpp
/*
- 전체 하르방을 집에 포함시켜야 한다.
- 집은 중복되면 안된다.
- 서로다른 4개의 하르방을 이용해서 집을 짓고
  그 영역에 포함되는 하르방은 사용처리된다.
- 점수
   1) 1*1+2*2+..+(집개수-1)^2	최대화  (최대 500개)
   2) (면적평균과차이/10) 의 합	최소화 <= 없다고 생각해도 됨..


1. 무조건 집 많이 짓는 전략 => 가능한 4개씩 짓기
2. 행,열당 평균 1~2개의 하르방만 존재한다.
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* seed and pseudo_rand function will be changed */
static unsigned long long seed = 250517;

static int pseudo_rand(void) {
	seed = seed * 25214903917ULL + 11ULL;
	return (seed >> 16) & 0x3fffffff;
}

/* These constant variables will NOT be changed */
static const int MAX_TC = 10;
static const int MAX_SIZE = 1024;
static const int MAX_HARUBANG = 2000;

typedef struct {
	int x, y;
} Point;

enum {
	EMPTY = 0, HARUBANG = 1, HOUSE = 2
};

static int gIsland[MAX_SIZE][MAX_SIZE];	// 맵 1024*1024 : EMPTY, HARUBANG, HOUSE
static Point gHarubang[MAX_HARUBANG];	// 하르방 위치 정보, 최대 2000개
static int gHarubangCnt;
static int gUsedHarubangCnt;
static int gHouseArea[MAX_HARUBANG / 4];
static int gHouseIdx;
static int gTotalScore;

////////////////////////////////////

int harubangs(Point p[]) {
	for (int harubangCnt = 0; harubangCnt < gHarubangCnt; harubangCnt++) {
		p[harubangCnt].x = gHarubang[harubangCnt].x;
		p[harubangCnt].y = gHarubang[harubangCnt].y;
	}
	return gHarubangCnt;
}

void house(Point p[]) {	// p[0] ~ p[3] => "서로 다른" 하르방 위치
	int maxX = 0, minX = MAX_SIZE, maxY = 0, minY = MAX_SIZE;

	for (int i = 0; i < 4; i++) {
		// 무시: 맵 범위 벗어나는 경우
		if (p[i].y < 0 || p[i].y >= MAX_SIZE || p[i].x < 0 || p[i].x >= MAX_SIZE)
			return;

		// 무시: 하르방이 아닌 경우
		if (gIsland[p[i].y][p[i].x] != HARUBANG)
			return;

		// p[] 하르방 삭제
		gIsland[p[i].y][p[i].x] = EMPTY;

		// 하르방 사용했음으로 처리
		gUsedHarubangCnt++;
	}

	// 보내진 4개 하르방을 포함하는 최소 직사각형 설정 => 집 짓기
	for (int i = 0; i < 4; i++)
		if (p[i].y > maxY) maxY = p[i].y;
	for (int i = 0; i < 4; i++)
		if (p[i].y < minY) minY = p[i].y;
	for (int i = 0; i < 4; i++)
		if (p[i].x > maxX) maxX = p[i].x;
	for (int i = 0; i < 4; i++)
		if (p[i].x < minX) minX = p[i].x;

	for (int y = minY; y <= maxY; y++)
		for (int x = minX; x <= maxX; x++) {
			// 패널티1: 다른 집과 겹치는 경우
			if (gIsland[y][x] == HOUSE) {
				gHarubangCnt = -1;
				return;
			}

			// 하르방인 경우 => 사용했음으로 처리
			else if (gIsland[y][x] == HARUBANG) {
				gUsedHarubangCnt++;
			}

			// 집으로 표시
			gIsland[y][x] = HOUSE;
		}

	// 집별로 넓이 기록
	gHouseArea[gHouseIdx] = (maxX - minX + 1) * (maxY - minY + 1);
	gHouseIdx++;
}

////////////////////////////////////

static void init() {
	for (int y = 0; y < MAX_SIZE; y++)
		for (int x = 0; x < MAX_SIZE; x++)
			gIsland[y][x] = EMPTY;
	gHouseIdx = 0;

	// 하르방 개수 = 1000 ~ 1999
	gHarubangCnt = MAX_HARUBANG / 2 + pseudo_rand() % (MAX_HARUBANG / 2);
	gUsedHarubangCnt = 0;

	// 하르방 위치 중복없이 설정
	for (int harubangIdx = 0; harubangIdx < gHarubangCnt; harubangIdx++) {
		int tx, ty;
		do {
			tx = pseudo_rand() % MAX_SIZE;
			ty = pseudo_rand() % MAX_SIZE;

			if (gIsland[ty][tx] == EMPTY)
				break;
		} while (1);
		gHarubang[harubangIdx].x = tx;
		gHarubang[harubangIdx].y = ty;
		gIsland[ty][tx] = HARUBANG;
	}
}

static bool score() {
	float areaSum = 0;

	// 패널티2. 사용되지 않은(집에 포함되지 않은) 하르방이 존재하는 경우
	if (gUsedHarubangCnt != gHarubangCnt)
		return false;

	// 점수 = 0*0 + 1*1 + 2*2 + .. + (gHouseIdx-1)^2
	// => 집 개수가 많아야 함.
	for (int houseIdx = 0; houseIdx < gHouseIdx; houseIdx++) {
		gTotalScore += houseIdx * houseIdx;
		areaSum += gHouseArea[houseIdx];
	}

	// 집 면적 평균
	int areaAvg = (int)(areaSum / (float)gHouseIdx);

	// 점수 = 모든 집 면적과 평균과의 차이/10 만큼 차감
	// => 집 면적을 비슷하게??
	for (int houseIdx = 0; houseIdx < gHouseIdx; houseIdx++)
		gTotalScore -= ABS(areaAvg - gHouseArea[houseIdx]) / 10;

	return true;
}

extern void process();

int main(int argc, char* argv[]) {
	setbuf(stdout, NULL);

	bool result;

	gTotalScore = 0;

	/////////  codepass judge  ////////////////
	long long cut = 142000000;
	// scanf("%llu %lld", &seed, &cut);
	///////////////////////////////////////////

	for (int tc = 0; tc < MAX_TC; ++tc) {
		init();
		process();
		if ((result = score()) == false)
			break;
	}
	long long SCORE = (result) ? gTotalScore : -1;
	printf("SCORE: %lld\n", SCORE);

	/////////  codepass judge  ////////////////
	if (SCORE < cut) puts("FAIL");
	else puts("PASS");
	///////////////////////////////////////////

	return 0;
}
```
