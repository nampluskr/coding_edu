#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, M;       // N: 주사위의 개수, M: 합의 목표값
int dice[10];
int cnt;

void print() {
    for (int i = 0; i < N; i++) printf("%d ", dice[i]);
    printf("\n");
}

// 중복 순열 (완전 탐색)
// N개의 주사위를 던져서 합이 M이 되는 경우의 수를 찾는 문제
void recur1(int k, int sum) {
    cnt++; // 호출 횟수 카운트
    // base case
    if (k == N) {
        if (sum == M) print();
        return;
    }

    // normal case
    for (int i = 1; i <= 6; i++) {
        dice[k] = i;                // 선택
        recur1(k + 1, sum + i);     // 다음 단계로 이동
        // dice[k] = 0;                // 선택 취소 (필요 없음, 덮어쓰므로)
    }
}

// 중복 순열 (최적화 - 가지치기)
void recur2(int k, int sum) {
    cnt++; // 호출 횟수 카운트
    // base case
    if (k == N) { print(); return; }

    // normal case
    for (int i = 1; i <= 6; i++) {
		// 남은 주사위 개수
		int remain = N - k - 1;
		
		// 가능한 합 최소값 = sum + i + remain * 1
		int minSum = sum + i + remain * 1;

		// 가능한 합 최대값 = sum + i + remain * 6
		int maxSum = sum + i + remain * 6;

		if (M < minSum) break;
		if (maxSum < M) continue;

        dice[k] = i;                // 선택
        recur2(k + 1, sum + i);     // 다음 단계로 이동
        // dice[k] = 0;                // 선택 취소 (필요 없음, 덮어쓰므로)
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    scanf("%d %d", &N, &M);                     // 3 10

    cnt = 0;
    recur1(0, 0); // 시작 단계, 현재 합은 0
    printf("Total combinations: %d\n", cnt);    // 259

    cnt = 0;
    recur2(0, 0); // 시작 단계, 현재 합은 0
    printf("Total combinations with pruning: %d\n", cnt);   // 61

    return 0;
}