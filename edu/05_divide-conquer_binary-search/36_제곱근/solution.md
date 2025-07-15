### Solution

```cpp
/*
05_제곱근
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
using ull = unsigned long long;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	ull N;
	scanf("%llu", &N);

	// ooooo|xxxx
	//     e|s  

	ull s = 1, e = 3037000499;
	//ull s = 1, e = N;
	while (s <= e) {
		ull mid = (s + e) / 2;

		if (mid*mid <= N) s = mid + 1;
		//if (mid <= N / mid) s = mid + 1;
		else e = mid - 1;
	}
	printf("%llu\n", e);

	return 0;
}
```