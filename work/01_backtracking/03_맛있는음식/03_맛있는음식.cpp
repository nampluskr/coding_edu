#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int abs(int a) { return a < 0 ? -a : a; }
int min(int a, int b) { return a < b ? a : b; }

int N;
int S[15], B[15];
int ans = 2e9;

// 조합
void recur1(int k, int s, int b) {
    // base case
    if (k == N) {
        if (b == 0) return;  // b가 0이면 선택하지 않은 경우이므로 무시
        ans = min(ans, abs(s - b));
        return;
    }

    // normal case
    recur1(k + 1, s, b);                  // 선택하지 않는 경우
    recur1(k + 1, s * S[k], b + B[k]);    // 선택하는 경우
}

// 조합을 이용한 부분집합 생성
void recur2(int k, int s, int b, int selected) {
    if (k > 0)
        ans = min(ans, abs(s - b));  // k > 0일 때만 ans 갱신
    
    for (int i = selected + 1; i < N; i++)
        recur2(k + 1, s * S[i], b + B[i], i);
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d %d", &S[i], &B[i]);

    // recur1(0, 1, 0);  // 초기값: s = 1 (곱셈이므로), b = 0 (합산)
    // printf("%d\n", ans);

    recur2(0, 1, 0, -1);  // 초기값: s = 1, b = 0, selected = -1 (아직 선택하지 않음)
    printf("%d\n", ans);

    return 0;
}