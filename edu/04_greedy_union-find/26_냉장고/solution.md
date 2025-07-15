### Solution

```cpp
/*
03_냉장고
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>
using namespace std;

int N;
struct Data {
	int l, h;
	bool operator<(Data r) {
		return h < r.h;
	}
}A[105];

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &A[i].l, &A[i].h);
	sort(A, A + N);	// operator<

	int ans = 1;
	int last = A[0].h;
	for (int i = 1; i < N; i++) {
		if (last < A[i].l) {
			ans++;
			last = A[i].h;
		}
	}
	printf("%d\n", ans);

	return 0;
}
```