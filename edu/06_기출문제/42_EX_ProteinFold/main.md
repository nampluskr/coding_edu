### main.cpp

```cpp
/*
                NHH(C)HHCOOH
	      NHCHHCHHCHH(C)HCOOH
	             CHHH(C)HNHHCOOH
	HNCNHHNHCHHCHHCHH(C)HNHHCOOH
	         HHNCOCHH(C)HNHHCOOH
	          HOOCCHH(C)HNHHCOOH
	            HSCHH(C)HNHHCOOH
	      HHNCOCHHCHH(C)HNHHCOOH
	       HOOCCHHCHH(C)HNHHCOOH
	      NHCHNCHCCHH(C)HNHHCOOH
	    CHHHCHHCHCHHH(C)HNHHCOOH
	    CHHHCHHHCHCHH(C)HNHHCOOH
	  HHNCHHCHHCHHCHH(C)HNHHCOOH
	      CHHHSCHHCHH(C)HNHHCOOH
	              CHH(C)HNHHCOOH
	            HOCHH(C)HNHHCOOH
	         CHHHCHOH(C)HNHHCOOH
	         NHCHCCHH(C)HNHHCOOH
	            HOCHH(C)HNHHCOOH
	        CHHHCHHCH(C)HNHHCOOH
*/

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

static unsigned long long seed = 1234;
static int pseudo_rand(void)
{
	seed = seed * 25214903917ULL + 11ULL;
	return (seed >> 16) & 0x3fffffff;
}

/* These constant variables will NOT be changed */
static const int MAX_TC = 10;
static const int AMINO_TYPE = 20;
static const int AMINO_LEN = 28;	// 아미노산 최대 길이
static const int MAX_AMINO = 20;	// 아미노산 최대 개수
static const int SPACE_LEN = 100;	// 맵 크기 : 100*100*100

typedef struct {
	char elements[AMINO_LEN];
	int connectorIdx;
} AminoType;

const static AminoType gAminoType[AMINO_TYPE] = {
	{ "CHHHCHNHHCOOH",               4 },
	{ "HNCNHHNHCHHCHHCHHCHNHHCOOH", 17 },
	{ "HHNCOCHHCHNHHCOOH",           8 },
	{ "HOOCCHHCHNHHCOOH",            7 },
	{ "HSCHHCHNHHCOOH",              5 },
	{ "HHNCOCHHCHHCHNHHCOOH",       11 },
	{ "HOOCCHHCHHCHNHHCOOH",        10 },
	{ "NHHCHHCOOH",                  3 },
	{ "NHCHNCHCCHHCHNHHCOOH",       11 },
	{ "CHHHCHHCHCHHHCHNHHCOOH",     13 },
	{ "CHHHCHHHCHCHHCHNHHCOOH",     13 },
	{ "HHNCHHCHHCHHCHHCHNHHCOOH",   15 },
	{ "CHHHSCHHCHHCHNHHCOOH",       11 },
	{ "CHHCHNHHCOOH",                3 },
	{ "NHCHHCHHCHHCHCOOH",          11 },
	{ "HOCHHCHNHHCOOH",              5 },
	{ "CHHHCHOHCHNHHCOOH",           8 },
	{ "NHCHCCHHCHNHHCOOH",           8 },
	{ "HOCHHCHNHHCOOH",              5 },
	{ "CHHHCHHCHCHNHHCOOH",         9 }
};

typedef struct {
	char symbol;	// 원소(C,N,..)
	bool connector;	// 커넥터면 1, 아니면 0
	int x, y, z;	// 좌표
} Element;

static Element gElements[MAX_AMINO][AMINO_LEN];	// 아미노산 원소별 정보(symbol, x,y,z, 커넥터여부)
static int gElementSize[MAX_AMINO];				// 아미노산별 길이
static int gAminoCount;							// 아미노산 개수

static long long gTotalScore;

static void rotate(int aminoIdx, int firstElemIdx, int lastElemIdx, Element& baseElem, int axis, bool anticlockwise)
{
	// 반시계 : 1, 시계 : -1
	int dir = (anticlockwise) ? 1 : -1;

	for (int elemIdx = firstElemIdx; elemIdx <= lastElemIdx; elemIdx++) {
		Element srcElem = gElements[aminoIdx][elemIdx];		// value copy
		Element& destElem = gElements[aminoIdx][elemIdx];	// reference copy

		// x축
		if (axis == 0) {
			destElem.y = dir * -(srcElem.z - baseElem.z) + baseElem.y;
			destElem.z = dir * (srcElem.y - baseElem.y) + baseElem.z;
		}
		
		// y축
		else if (axis == 1) {
			destElem.z = dir * -(srcElem.x - baseElem.x) + baseElem.z;
			destElem.x = dir * (srcElem.z - baseElem.z) + baseElem.x;
		}

		// z축
		else if (axis == 2) {
			destElem.x = dir * -(srcElem.y - baseElem.y) + baseElem.x;
			destElem.y = dir * (srcElem.x - baseElem.x) + baseElem.y;
		}
	}
}

////////////////////////////////////

// 1. 아미노산 개수
// 2. 아미노산 원소별 정보(symbol, x,y,z, 커넥터 여부)
//    타입X, 아미노산 길이X => 추가로직으로 확인
int protein(Element elements[MAX_AMINO][AMINO_LEN])
{
	int aminoIdx, elemIdx;

	for (aminoIdx = 0; aminoIdx < gAminoCount; aminoIdx++) {
		for (elemIdx = 0; gElements[aminoIdx][elemIdx].symbol; elemIdx++)
			elements[aminoIdx][elemIdx] = gElements[aminoIdx][elemIdx];
		elements[aminoIdx][elemIdx].symbol = 0;	// => 길이 확인 가능
	}
	return gAminoCount;
}

void fold_amino(int aminoNum, bool front, int axis, bool anticlockwise)
{
	// elementNum = aminoNum의 커넥터 index
	int elementNum;
	for (elementNum = 0; gElements[aminoNum][elementNum].connector == false; elementNum++);


	// baseElem = aminoNum 아미노산의 커넥터
	Element& baseElem = gElements[aminoNum][elementNum];

	// front=1 : 0~aminoNum-1
	// front=0 : aminoNum+1~끝
	int firstAminoIdx = (front) ? 0 : aminoNum + 1;
	int lastAminoIdx = (front) ? aminoNum - 1 : gAminoCount - 1;

	// first~last 범위 아미노산 rotate
	for (int aminoIdx = firstAminoIdx; aminoIdx <= lastAminoIdx; aminoIdx++)
		// 현재 아미노산의 전체 원소
		rotate(aminoIdx, 0, gElementSize[aminoIdx] - 1, baseElem, axis, anticlockwise);
}

void fold_element(int aminoNum, int elementNum, bool front, int axis, bool anticlockwise)
{
	Element& baseElem = gElements[aminoNum][elementNum];

	int firstElemIdx = (front) ? 0 : elementNum + 1;
	int lastElemIdx = (front) ? elementNum - 1 : gElementSize[aminoNum] - 1;

	// 접는 구간에 커넥터 포함되면 함수 무시
	for (int i = firstElemIdx; i <= lastElemIdx; i++)
	{
		if (gElements[aminoNum][i].connector == true)
			return;
	}
	rotate(aminoNum, firstElemIdx, lastElemIdx, baseElem, axis, anticlockwise);
}

////////////////////////////////////

static void init()
{
	// 아미노산 개수 = 10~19
	gAminoCount = MAX_AMINO / 2 + pseudo_rand() % (MAX_AMINO / 2);

	for (int aminoIdx = 0; aminoIdx < gAminoCount; aminoIdx++) {
		// 타입 설정 = 0 ~ 19
		int aminoType = pseudo_rand() % AMINO_TYPE;

		// 커넥터 index
		int connIdx = gAminoType[aminoType].connectorIdx;


		int x = SPACE_LEN / 2 - connIdx;	// 커넥터 원소 x=50
		int y = SPACE_LEN / 2;				// 모든 아미노산 y=50 고정
		int z = SPACE_LEN / 2 + aminoIdx;	// z=50 부터 아미노산 별로 1씩 증가

		// 모든 원소들 정보 기록
		int elemIdx;
		for (elemIdx = 0; gAminoType[aminoType].elements[elemIdx]; elemIdx++) {
			gElements[aminoIdx][elemIdx].symbol = gAminoType[aminoType].elements[elemIdx];
			gElements[aminoIdx][elemIdx].x = x + elemIdx;
			gElements[aminoIdx][elemIdx].y = y;
			gElements[aminoIdx][elemIdx].z = z;
			gElements[aminoIdx][elemIdx].connector = false;
		};
		gElements[aminoIdx][elemIdx].symbol = 0;		// 아미노산별 마지막원소 다음 위치의 symbol=0
		gElements[aminoIdx][connIdx].connector = true;
		gElementSize[aminoIdx] = elemIdx;
	}
}

static int gSpace[SPACE_LEN][SPACE_LEN][SPACE_LEN];
static bool verify()
{
	for (int z = 0; z < SPACE_LEN; z++)
		for (int y = 0; y < SPACE_LEN; y++)
			for (int x = 0; x < SPACE_LEN; x++)
				gSpace[z][y][x] = 0;

	for (int aminoIdx = 0; aminoIdx < gAminoCount; aminoIdx++) {
		for (int elemIdx = 0; gElements[aminoIdx][elemIdx].symbol; elemIdx++) {
			int x = gElements[aminoIdx][elemIdx].x;
			int y = gElements[aminoIdx][elemIdx].y;
			int z = gElements[aminoIdx][elemIdx].z;

			// 패널티1. 원소 위치가 맵을 벗어난 경우 (0,0,0) ~ (99,99,99)
			// 패널티2. 원소 위치가 중복되는 경우
			if (x < 0 || x >= SPACE_LEN || y < 0 || y >= SPACE_LEN || z < 0 || z >= SPACE_LEN
				|| gSpace[z][y][x])
				return false;

			// 원소 위치에 값 부여
			switch (gElements[aminoIdx][elemIdx].symbol) {
			case 'H': gSpace[z][y][x] = 1; break;	// H-H : +2
			case 'C': gSpace[z][y][x] = 2; break;
			case 'O': gSpace[z][y][x] = 5; break;	// O-O : +50
			case 'N': gSpace[z][y][x] = 10; break;	// N-N : +200	N-O : +100
			case 'S': gSpace[z][y][x] = 30; break;	// S-S : +1800
			}
		}
	}


	int cnt = 0;
	for (int z = 1; z < SPACE_LEN - 1; z++)
		for (int y = 1; y < SPACE_LEN - 1; y++)
			for (int x = 1; x < SPACE_LEN - 1; x++) {
				// score += 인접한 6곳 값과의 곱의 합 (점수=모든 인접한 값들의 곱*2)
				gTotalScore = gTotalScore +
					gSpace[z][y][x] * gSpace[z - 1][y][x] + gSpace[z][y][x] * gSpace[z + 1][y][x] +
					gSpace[z][y][x] * gSpace[z][y - 1][x] + gSpace[z][y][x] * gSpace[z][y + 1][x] +
					gSpace[z][y][x] * gSpace[z][y][x - 1] + gSpace[z][y][x] * gSpace[z][y][x + 1];
			}

	return true;
}

extern void process();

int main(int argc, char* argv[])
{
	setbuf(stdout, NULL);

	gTotalScore = 0;
	for (int tc = 0; tc < MAX_TC; ++tc) {

		init();

		process();

		if (verify() == false) {
			gTotalScore = 0;
			break;
		}
	}

	long long SCORE = gTotalScore;
	printf("SCORE: %lld\n", SCORE);

	/////// codepas cut이므로 실제와 다를수 있습니다. !!! /////
	if (SCORE >= 102000) {
		printf("PASS\n");
	}
	else {
		printf("FAIL\n");
	}
	///////////////////////////////////////////////////////////

	return 0;
}
```
