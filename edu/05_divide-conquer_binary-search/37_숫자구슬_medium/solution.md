### Solution

```cpp
/*
06_숫자구슬
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
//#include <limits.h>	// INT_MAX, INT_MIN
using ll = long long;

const int INT_MAX = (1 << 31) - 1;
//const int INT_MAX = 2147483647;		// 2^31-1
//const int INT_MIN = -2147483648;		// -2^31
//const int UINT_MAX = 4294967295;		// 2^32-1

int N, M;
int A[100005];

bool isPossible(ll limit) {
	int gcnt = 1;
	ll gsum = 0;
	for (int i = 0; i < N; i++) {
		if (A[i] > limit) return 0;

		if (gsum + A[i] <= limit) {
			gsum += A[i];
		}
		else {
			gcnt++;
			gsum = A[i];
			if (gcnt > M) return 0;
		}
	}
	return 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &M);
	ll sum = 0, max = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", A + i);
		max = max > A[i] ? max : A[i];
		sum += A[i];
	}

	ll s = 1, e = 1e13;
	//ll s = max, e = sum;
	while (s <= e) {
		ll mid = (s + e) / 2;
		if (isPossible(mid)) e = mid - 1;
		else s = mid + 1;
	}
	printf("%lld\n", s);

	return 0;
}
```