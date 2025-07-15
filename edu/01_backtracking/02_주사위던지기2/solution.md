### Solution

```cpp
/*
 * Ctrl+Shift+A : 파일추가
 * Ctrl+D : 줄 복제
 * Ctrl+X : 줄 잘라내기(삭제)
 * 코드 조각 등록 : 도구 -> 코드조각관리자 -> 가져오기
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int N, M;
int dice[10];

void recur(int c, int sum) {
	// base case
	if (c == N) {
		for (int i = 0; i < N; i++)
			printf("%d ", dice[i]);
		printf("\n");

		return;
	}
	
	// normal case
	for (int i = 1; i <= 6; i++) {
		// 남은 주사위 개수
		int remain = N - c - 1;
		
		// 가능한 합 최소값 = sum + i + remain * 1
		int minSum = sum + i + remain * 1;

		// 가능한 합 최대값 = sum + i + remain * 6
		int maxSum = sum + i + remain * 6;

		if (M < minSum) break;
		if (maxSum < M) continue;

		dice[c] = i;
		recur(c + 1, sum + i);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &M);

	recur(0, 0);

	return 0;
}
```