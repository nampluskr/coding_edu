### main

```cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define ABS(x) (((x)<0)?(-(x)):(x))

static unsigned long long seed = 5;

static int psuedo_rand(void)
{
	seed = seed * 25214903917ULL + 11ULL;
	return (seed >> 16) & 0x3fffffff;
}

/* These constant variables will NOT be changed */
static const int MAP_SIZE = 100;
static const int ANTENNA_NUM = 150;
static const int ANTENNA_CAPA = 100;
static const int UE_NUM = 10'000;
static const int TC_COUNT = 10;
static const int SUBTASK_COUNT = 10;
static const int DIR_NUM = 20;
static const long long PENALTY = 1'000'000'000;
static const int dy[DIR_NUM] = { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0 };
static const int dx[DIR_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 };

// 보통 y를 먼저 씀
struct Coordinates
{
	int y, x;

	Coordinates()
	{
		y = x = 0;
	}
	Coordinates(int _y, int _x)
	{
		y = _y;
		x = _x;
	}

	// operator- overloading
	// struct Coordinates A, B; => A-B 연산 가능
	// 맨허튼 거리
	int operator-(Coordinates& param)
	{
		return ABS(y - param.y) + ABS(x - param.x);
	}
};

extern void init(Coordinates[]);
extern void scanUE(Coordinates[], int[], int[]);

static long long SCORE = 0;

static Coordinates antenna_list[ANTENNA_NUM];
static Coordinates antenna_list_bak[ANTENNA_NUM];
static int antenna_range[ANTENNA_NUM];
static int antenna_ref_count[ANTENNA_NUM];

static Coordinates UE_list[UE_NUM];
static Coordinates UE_list_bak[UE_NUM];
static int UE_move_direction[UE_NUM];
static int antenna_UE_connection[UE_NUM];

static bool run()
{
	// byte 단위로 배열 초기화
	// antenna_ref_count[] 전체 0으로 초기화
	memset(antenna_ref_count, 0, sizeof(antenna_ref_count));

	// 안테나 위치 생성 : (0,0) ~ (99,99)
	for (int i = 0; i < ANTENNA_NUM; i++)
		antenna_list_bak[i] = antenna_list[i] = Coordinates(psuedo_rand() % MAP_SIZE, psuedo_rand() % MAP_SIZE);

	// user에 생성된 안테나 위치 전달
	// 백업을 보내서 원본 유지
	init(antenna_list_bak);

	// 유닛 위치 생성 : (0,0) ~ (99,99) 
	// 유닛 방향 생성 : 0~19 => 80%는 정지, 20%만 방향 존재?
	// 유닛,안테나 중복 허용
	for (int k = 0; k < UE_NUM; k++)
	{
		UE_list[k] = Coordinates(psuedo_rand() % MAP_SIZE, psuedo_rand() % MAP_SIZE);
		UE_move_direction[k] = psuedo_rand() % DIR_NUM;
	}

	// 10번의 subtask 수행
	for (int t = 0; t < SUBTASK_COUNT; t++)
	{
		// 유닛 위치 백업에 담고
		for (int k = 0; k < UE_NUM; k++)
			UE_list_bak[k] = UE_list[k];

		// user에 유닛 위치 전달 (방향 전달X)
		scanUE(UE_list_bak, antenna_range, antenna_UE_connection);
		// antenna_range[] : 안테나별 최대 범위 설정
		// antenna_UE_connection[] : 유닛별 배정된 안테나 번호 기록


		for (int i = 0; i < ANTENNA_NUM; ++i)
		{
			// 패널티1. 설정된 안테나 최대범위 200 넘어가는 경우
			if (antenna_range[i] > 200) {
				printf("antenna_range[i] > 200\n");
				return false;
			}

			antenna_ref_count[i] = 0;
		}

		for (int k = 0; k < UE_NUM; k++)
		{
			// i = k번 유닛의 할당된 안테나 번호
			int i = antenna_UE_connection[k];

			// 패널티2. 할당된 안테나 번호가 범위(0~149) 벗어나는 경우
			if (i < 0 || i >= ANTENNA_NUM) {
				printf("i < 0 || i >= ANTENNA_NUM\n");
				return false;
			}

			// 안테나별 할당된 유닛 개수
			antenna_ref_count[i]++;
		}

		for (int i = 0; i < ANTENNA_NUM; i++)
		{
			// 패널티3. 안테나에 할당된 유닛 개수가 100개 넘어가는 경우
			if (antenna_ref_count[i] > ANTENNA_CAPA) {
				printf("antenna_ref_count[i] > ANTENNA_CAPA\n");
				return false;
			}
		}

		// 5번 반복
		// 1) 패널티 확인 => 설정된 안테나 최대 범위와 유닛과의 거리 비교
		// 2) 한 칸 이동
		// => 0~4번 이동까지 고려한 antenna_range[] 설정 필요!!
		for (int minutes = 0; minutes < 5; minutes++)
		{
			for (int k = 0; k < UE_NUM; k++)
			{
				// i = k번 유닛에 할당된 안테나 번호
				int i = antenna_UE_connection[k];

				// 참조자로 각 유닛, 안테나 위치 갖고옴
				// 1) 복사비용줄일 때
				// 2) 원본 변경할 때
				Coordinates& antenna = antenna_list[i];
				Coordinates& ue = UE_list[k];

				// 패널티4. 연결된 유닛,안테나의 맨하튼 거리가 설정한 안테나의 최대 범위 보다 큰 경우
				// => antenna_range[]를 할당된 가장 먼 유닛과의 거리 이상으로 설정해야 한다!
				if (antenna_range[i] < antenna - ue) {
					printf("antenna_range[i] < antenna - ue\n");
					return false;
				}
			}


			for (int k = 0; k < UE_NUM; k++)
			{
				// 유닛에 설정된 방향 갖고오기
				int& dir = UE_move_direction[k];

				// 둘 다 0인 경우 => 방향이 없는 경우
				if (dy[dir] == dx[dir])
					continue;

				// 맵 끝에 도달하면 반대방향으로 전환
				if (UE_list[k].y + dy[dir] < 0 || UE_list[k].x + dx[dir] < 0 || UE_list[k].y + dy[dir] >= MAP_SIZE || UE_list[k].x + dx[dir] >= MAP_SIZE)
				{
					dir = (dir + 10) % DIR_NUM;
				}

				// 설정된 방향으로 한 칸 이동
				UE_list[k].y += dy[dir];
				UE_list[k].x += dx[dir];
			}
		}

		// score += 안테나최대범위^2
		for (int i = 0; i < ANTENNA_NUM; i++)
			SCORE += (antenna_range[i] * antenna_range[i]);
	}
	return true;
}

int main()
{
	setbuf(stdout, NULL);
	//////////////////////////////////////
	int sd = 5;
	//scanf("%d", &sd);
	seed = sd;
	//////////////////////////////////////

	for (int tc = 1; tc <= TC_COUNT; ++tc)
	{
		printf("[tc=%d]\n", tc);
		if (run() == false)
		{
			printf("SCORE: %lld\n", PENALTY);
			return 0;
		}
	}

	printf("SCORE: %lld\n", SCORE);

	//////////////////////////////////////
	int cut = 2100000;
	//scanf("%d", &cut);
	if (cut < SCORE) puts("FAIL");
	else puts("PASS");
	//////////////////////////////////////
	return 0;
}
```