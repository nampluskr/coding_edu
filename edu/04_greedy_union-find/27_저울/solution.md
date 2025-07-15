### Solution

```cpp
/*
04_저울
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>
using namespace std;

int N;
int A[1005];

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);
	sort(A, A + N);

	int w = 0;	// 이전 추까지 사용해서 잴 수 있는 최대무게
	for (int i = 0; i < N; i++) {
		if (w < A[i] - 1) break;
		w += A[i];
	}
	printf("%d\n", w + 1);

	return 0;
}
```