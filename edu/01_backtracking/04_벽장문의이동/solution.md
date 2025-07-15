### Solution

```cpp
/*
04_벽장문 이동
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int a, b;
int M, order[25];
int ans = 400;	// 20*20 이상

int abs(int a) { return a < 0 ? -a : a; }
void recur(int c, int d1, int d2, int move) {
	// 가지치기
	if (ans <= move) return;

	// base case
	if (c == M) {
		ans = move;
		return;
	}
	
	// normal case
	recur(c + 1, order[c], d2, move + abs(d1 - order[c]));
	recur(c + 1, d1, order[c], move + abs(d2 - order[c]));
}

void recur2(int c, int left, int right, int move) {
	if (ans <= move) return;
	if (c == M) { ans = move; return; }

	if (order[c] <= left)
		recur2(c + 1, order[c], right, move + left - order[c]);

	else if (right <= order[c])
		recur2(c + 1, left, order[c], move + order[c] - right);

	else {
		recur2(c + 1, order[c], right, move + order[c] - left);
		recur2(c + 1, left, order[c], move + right - order[c]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d%d%d", &N, &a, &b, &M);
	for (int i = 0; i < M; i++) scanf("%d", order + i);

	// recur(0, a, b, 0);

        // 입력받은 a,b가 a<b 라는 보장이 없으므로 추가 필요
        if(a>b) { int c = a; a=b; b=c; }
	recur2(0, a, b, 0);

	printf("%d\n", ans);

	return 0;
}
```