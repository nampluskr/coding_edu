### Solution

```cpp
/*
02_피보나치_ver2_객체
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define pp if(0) printf

struct Matrix {
	int A[2][2];
	Matrix operator*(Matrix r) {
		Matrix res = {};
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++)
					res.A[i][j] += A[i][k] * r.A[k][j];
				res.A[i][j] %= 10000;
			}
		return res;
	}
};

Matrix I = { 1,1,1,0 };

Matrix recur(int n) {
	pp("%d", n);

	// base case
	if (n == 1) return I;

	// normal case
	Matrix res = recur(n / 2);
	if (n % 2) return res * res * I;
	else return res * res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int N;
	while (1) {
		scanf("%d", &N);
		if (N == -1) break;
		if (N == 0) printf("0\n");
		else printf("%d\n", recur(N).A[0][1]);
	}

	return 0;
}
```