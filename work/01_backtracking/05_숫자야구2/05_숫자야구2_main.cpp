// *** main.cpp ***
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX          4
#define MAX_COUNT 2520

static int baseballNumbers[MAX];
static int numbersCheck[10];

extern void tryBest(int suppose[]); ////************

static int queryCallCount;
static const int queryLimit = 10;

struct Data {
    int strike;
    int ball;
};

static unsigned long long seed = 123;
int rand(void) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed >> 16) & 65535;
}

static bool isAble(int suppose[]) {
    int supposeCheck[10];

    for (int count = 0; count < 10; ++count)
        supposeCheck[count] = 0;

    // 0~9 외의 값 or 중복된 값이 있는 경우
    for (int idx = 0; idx < MAX; ++idx) {
        if (suppose[idx] < 0 || suppose[idx] >= 10 || supposeCheck[suppose[idx]] > 0)
            return false;
        supposeCheck[suppose[idx]]++;
    }
    return true;
}

Data query(int suppose[]) {
    Data result;

    // 이미 제한 횟수 넘긴 경우 -> 수행 안함
    if (queryCallCount > MAX_COUNT) {
        result.strike = -1;
        result.ball = -1;
        return result;
    }

    queryCallCount++;

    // suppose[] 값이 유효하지 않은 경우 => 수행 안함 (0~9 범위, 중복 없어야함)
    if (!isAble(suppose)) {
        result.strike = -1;
        result.ball = -1;
        return result;
    }

    result.strike = 0;  // 같은 위치 같은 값 개수
    result.ball = 0;    // 다른 위치 같은 값 개수

    for (int idx = 0; idx < MAX; ++idx)
        if (suppose[idx] == baseballNumbers[idx])
            result.strike++;
        else if (numbersCheck[suppose[idx]] > 0)
            result.ball++;

    return result;
}

static void initialize() {
    for (int count = 0; count < 10; ++count)
        numbersCheck[count] = 0;

    // 0~9 범위 수를 중복되지 않게 4개 생성/기록
    for (int idx = 0; idx < MAX;) {
        int c = rand() % 10;    // 0 ~ 9

        if (numbersCheck[c] == 0) {
            baseballNumbers[idx] = c;
            numbersCheck[c]++;
            idx++;
        }
    }
    queryCallCount = 0;
}

static bool check(int suppose[]) {
    // 순서, 값 일치
    for (int idx = 0; idx < MAX; ++idx) {
        if (suppose[idx] != baseballNumbers[idx])
            return false;
    }
    return true;
}

int main() {
    int score = 100;

    setbuf(stdout, NULL);
    int sd = 123, TC = 50;

    seed = sd;
    for (int testcase = 1; testcase <= TC; ++testcase) {

        initialize();

        int suppose[MAX] = { 0 };
        queryCallCount = 0;

        tryBest(suppose);

        // Debugging output
        printf(">> TC[%2d]: %d (%d)\n", testcase, score, queryCallCount);

        if (!check(suppose))
            queryCallCount = MAX_COUNT;

        // if (queryCallCount > queryLimit) {
        //     score = 0;
        //     break;
        // }
    }
    printf("%d\n", score);

    return 0;
}