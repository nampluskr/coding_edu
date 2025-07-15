### Solution

```cpp
/*
03_binary search
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, A[500005];
int Q, B[500005];

int bisearch(int val) {
	int s = 0, e = N - 1;
	while (s <= e) {
		int mid = (s + e) / 2;
		if (A[mid] == val) return mid;
		else if (A[mid] < val) s = mid + 1;
		else e = mid - 1;
	}
	return -1;
}

// 조건 : val 이상
// xxxxx|oooooo
//     e|s

// xxxxxxxx|
//        e|s          
int lower_bound(int val) {
	int s = 0, e = N - 1;
	while (s <= e) {
		int mid = (s + e) / 2;

		// 조건 만족
		if (val <= A[mid]) e = mid - 1;
		
		// 조건 불만족
		else s = mid + 1;
	}
	if (s == N) return -1;
	else return s;
}

// 조건 : val 미만
// ooooo|xxxx
//     e|s  

//  |xxxxxx
// e|s
int rev_lower_bound(int val) {
	int s = 0, e = N - 1;
	while (s <= e) {
		int mid = (s + e) / 2;

		// 조건 만족
		if (A[mid] < val) s = mid + 1;

		// 조건 불만족
		else e = mid - 1;
	}
	//if (e == -1) return -1;
	return e;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) scanf("%d", B + i);


	// 1. binary search
	for (int i = 0; i < Q; i++)
		printf("%d ", bisearch(B[i]));
	printf("\n");

	// 2. lower_bound(x) : x이상인 최소값 위치
	for (int i = 0; i < Q; i++)
		printf("%d ", lower_bound(B[i]));
	printf("\n");

	// 2. rev_lower_bound(x) : x미만인 최대값 위치
	for (int i = 0; i < Q; i++)
		printf("%d ", rev_lower_bound(B[i]));
	printf("\n");
	return 0;
}
```