#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, M;
int dice[10];
bool used[10];

void print() {
    for (int i = 0; i < N; i++) printf("%d ", dice[i]);
    printf("\n");
}

// 중복 순열
void recur1(int k) {
    // base case
    if (k == N) { print(); return; }

    // normal case
    for (int i = 1; i <= 6; i++) {
        dice[k] = i;        // 선택
        recur1(k + 1);      // 다음 단계로 이동
        // dice[k] = 0;     // 선택 취소 (필요 없음, 덮어쓰므로)
    }
}

// 중복 조합
void recur2(int k) {
    // base case
    if (k == N) { print(); return; }

    // normal case
    for (int i = 1; i <= 6; i++) {
        if (k > 0 && dice[k - 1] > i) continue; // 이전 값보다 작으면 건너뛰기
        dice[k] = i;                            // 선택
        recur2(k + 1);                          // 다음 단계로 이동
        // dice[k] = 0;                         // 선택 취소 (필요 없음, 덮어쓰므로)
    }
}

// 순열
void recur3(int k) {
    // base case
    if (k == N) { print(); return; }

    // normal case
    for (int i = 1; i <= 6; i++) {
        if (used[i]) continue;  // 이미 사용된 숫자는 건너뛰기
        used[i] = true;         // 선택
        dice[k] = i;            // 선택
        recur3(k + 1);          // 다음 단계로 이동
        // dice[k] = 0;            // 선택 취소 (필요 없음, 덮어쓰므로)
        used[i] = false;        // 선택 취소
    }
}

// 조합
void recur4(int k, int start) {
    // base case
    if (k == N) { print(); return; }

    // normal case
    for (int i = start; i <= 6; i++) {
        dice[k] = i;            // 선택
        recur4(k + 1, i + 1);   // 다음 단계로 이동
        // dice[k] = 0;         // 선택 취소 (필요 없음, 덮어쓰므로)
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &N, &M);

    if (M == 1) recur1(0);          // 3 1
    else if (M == 2) recur2(0);     // 3 2
    else if (M == 3) recur3(0);     // 3 3
    else if (M == 4) recur4(0, 1);  // 3 4

    return 0;
}