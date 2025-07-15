### Solution

```cpp
/*
02_피보나치_ver1_배열
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int A[2][2];
int I[2][2] = { 1,1,1,0 };

// int(*B)[2]
void mul(int B[][2]) {
	int C[2][2];
	C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
	C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
	C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
	C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];

	A[0][0] = C[0][0] % 10000;
	A[0][1] = C[0][1] % 10000;
	A[1][0] = C[1][0] % 10000;
	A[1][1] = C[1][1] % 10000;
}

// f^n을 A에 담고 return
void recur(int n) {
	if (n == 1) {
		A[0][0] = A[0][1] = A[1][0] = 1;
		A[1][1] = 0;
		return;
	}

	recur(n / 2);
	mul(A);
	if (n % 2) mul(I);
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
		else {
			recur(N);
			printf("%d\n", A[0][1]);
		}
	}

	return 0;
}
```