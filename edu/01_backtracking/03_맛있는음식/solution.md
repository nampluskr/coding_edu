### Solution

```cpp
/*
03_맛있는 음식

O(1억) => 1초

Ctrl+K,C : 주석
Ctrl+K,U : 해제

디버깅 단축키
 Ctrl+F10 : 커서위치로 이동(커서위치에서 시작)
 F10 : 한 줄 진행(함수 안들어감)
 F11 : 한 줄 진행(함수 들어감)
 Shift+F5 : 디버깅 종료
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int S[15], B[15];
int ans = 2e9;	// 2'000'000'000

int abs(int a) { return a < 0 ? -a : a; }
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

// 참조자 => 원본값도 바꿔야 할 때 or 객체 크기가 큰 경우
void swap(int&a, int&b) { int c = a; a = b; b = c; }

// c번 재료 처리해
void recur(int c, int s, int b) {
	/* base case */
	if (c == N) {
		if(b) ans = min(ans, abs(s - b));
		return;
	}

	/* normal case */
	// 1) 선택X
	recur(c + 1, s, b);

	// 2) 선택O
	recur(c + 1, s * S[c], b + B[c]);
}

// c번째 선택할 재료 골라
void recur2(int c, int s, int b, int last) {
	if (c) ans = min(ans, abs(s - b));
	for (int i = last + 1; i < N; i++) {
		recur2(c + 1, s*S[i], b + B[i], i);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d%d", S + i, &B[i]);

	//recur(0, 1, 0);
	recur2(0, 1, 0, -1);


	printf("%d\n", ans);

	return 0;
}
```