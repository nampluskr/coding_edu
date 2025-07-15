### Solution

```cpp
/*
07_비숍_ver1_좌상대각선별로 한개씩 선택하기
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int A[15][15];
bool ltop[30], rtop[30];
int ans;

// num번 좌상 대각선에서 한개 선택해! (or 선택 안하고 넘겨)
void recur(int num, int cnt) {
	// 가지치기
	if (cnt + 2 * N - 1 - num <= ans) return;

	if (num == 2 * N - 1) {
		if (ans < cnt) ans = cnt;
		return;
	} 

	int r = num < N ? num : N - 1;
	int c = num < N ? 0 : num - (N - 1);

	// num 대각에서 하나씩 놔보기
	bool flag = 0;
	for (; r >= 0 && c < N; r--, c++) {
		if (!A[r][c]) continue;
		if (ltop[r - c + N]) continue;
		if (rtop[r + c]) continue;
		flag = 1;
		ltop[r - c + N] = rtop[r + c] = 1;
		recur(num + 1, cnt + 1);
		ltop[r - c + N] = rtop[r + c] = 0;
	}

	// 안놓기
	if(!flag) recur(num + 1, cnt);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &A[i][j]);

	recur(0, 0);
	printf("%d\n", ans);

	return 0;
}

```