## EX 하르방

## 문제


**[제한 사항]**

* 메모리 : heap + global + stack = 256MB    단, stack size = 1MB

* 제한시간 10초

* 제출 횟수 제한 10회



**[ 주의 사항 ]**

1. User Code 안에는 어떠한 헤더 파일도 추가할 수 없다.

2. Main 은 실제 채점 시에도 그대로 사용된다.단, seed 값은 변경될 수 있다.

(단, malloc.h 사용 가능)

3. 본 검정은 엄격한 코드 리뷰를 실시한다.

Main 에서 사용하는 변수에 직접적으로 접근하는 행위를 금지한다.

4. 본 검정은 C++ 언어만 지원한다.



**[문제 설명]**

▶ process() 함수를 작성하여, SCORE 를 최대화 하시오.

기타 자세한 사항은 주어진 코드를 분석하여 파악하라.


**[C++ Template Code]**

```cpp
// main.cpp
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

static int gIsland[MAX_SIZE][MAX_SIZE];
static Point gHarubang[MAX_HARUBANG];
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

void house(Point p[]) {
	int maxX = 0, minX = MAX_SIZE, maxY = 0, minY = MAX_SIZE;

	for (int i = 0; i < 4; i++) {
		if (p[i].y < 0 || p[i].y >= MAX_SIZE || p[i].x < 0 || p[i].x >= MAX_SIZE)
			return;
		if (gIsland[p[i].y][p[i].x] != HARUBANG)
			return;
		gIsland[p[i].y][p[i].x] = EMPTY;
		gUsedHarubangCnt++;
	}

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
			if (gIsland[y][x] == HOUSE) {
				gHarubangCnt = -1;
				return;
			}
			else if (gIsland[y][x] == HARUBANG) {
				gUsedHarubangCnt++;
			}
			gIsland[y][x] = HOUSE;
		}
	gHouseArea[gHouseIdx] = (maxX - minX + 1) * (maxY - minY + 1);
	gHouseIdx++;
}

////////////////////////////////////

static void init() {
	for (int y = 0; y < MAX_SIZE; y++)
		for (int x = 0; x < MAX_SIZE; x++)
			gIsland[y][x] = EMPTY;
	gHouseIdx = 0;

	gHarubangCnt = MAX_HARUBANG / 2 + pseudo_rand() % (MAX_HARUBANG / 2);
	gUsedHarubangCnt = 0;

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

	if (gUsedHarubangCnt != gHarubangCnt)
		return false;

	for (int houseIdx = 0; houseIdx < gHouseIdx; houseIdx++) {
		gTotalScore += houseIdx * houseIdx;
		areaSum += gHouseArea[houseIdx];
	}
	int areaAvg = (int)(areaSum / (float)gHouseIdx);
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
        long long cut = 143000000;
        // scanf("%llu %lld", &seed, &cut);
        ///////////////////////////////////////////

	for (int tc = 0; tc < MAX_TC; ++tc) {
		init();
		process();
		if ((result = score()) == false)
			break;
	}
	long long SCORE = (result) ? gTotalScore : 0;
	printf("SCORE: %lld\n", SCORE);

	/////////  codepass judge  ////////////////
	if (SCORE < cut) puts("FAIL");
	else puts("PASS");
	///////////////////////////////////////////

	return 0;
}

// user.cpp
typedef struct {
	int x, y;
} Point;

extern int harubangs(Point p[]);
extern void house(Point p[]);

void process()
{
}
```