### Solution

```cpp
/*
06_스도쿠
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int A[10][10];

bool usedRow[9][10];	// usedRow[r][i] = 1 : r행에 i값을 사용중이야
bool usedCol[9][10];	// usedCol[c][i] = 1 : c열에 i값을 사용중이야
bool usedSub[9][10];	// usedSub[R*3+C][i] = 1 : R*3+C 부분사각형에 i값을 사용중이야
//bool usedSub[3][3][10];	// usedSub[R][C][i] = 1 : (R,C) 부분사각형에 i값을 사용중이야

int n;
struct Coord {
	int r, c;
}empty[100];

// empty[idx] 처리해!
bool recur(int idx) {
	// base case
	if (idx == n) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				printf("%d ", A[i][j]);
			printf("\n");
		}
		return 1;
	}

	// normal case
	int r = empty[idx].r;
	int c = empty[idx].c;
	int s = (r / 3) * 3 + (c / 3);
	for (int i = 1; i <= 9; i++) {
		if (usedRow[r][i] || usedCol[c][i] || usedSub[s][i]) continue;

		A[r][c] = i;
		usedRow[r][i] = 1;
		usedCol[c][i] = 1;
		usedSub[s][i] = 1;

		if (recur(idx + 1)) return 1;

		usedRow[r][i] = 0;
		usedCol[c][i] = 0;
		usedSub[s][i] = 0;
	}
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			scanf("%d", &A[i][j]);
			if (!A[i][j]) empty[n++] = { i,j };
			else {
				int num = A[i][j];
				int s = i / 3 * 3 + j / 3;
				usedRow[i][num] = 1;
				usedCol[j][num] = 1;
				usedSub[s][num] = 1;
			}
		}

	recur(0);

	return 0;
}
```