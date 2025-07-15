### Solution

```cpp
/*
04_n개의 합
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
using ll = long long;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	ll S;
	scanf("%lld", &S);

	// O(log(e-s))
	// xxxx|oooo
	//    e s
	ll s = 1, e = 2e9;
	while (s <= e) {
		ll mid = (s + e) / 2;
		if ((1 + mid)*mid / 2 >= S) e = mid - 1;
		else s = mid + 1;
	}
	printf("%lld\n", s);

	return 0;
}
```