### Solution

```cpp
/*
05_힙정렬_1base

변수,함수명 변경 : Ctrl+R,R
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int heap[500005];
int hn;

void swap(int&a, int&b) { int c = a; a = b; b = c; }

// maxheap push
void push(int value) {
	heap[++hn] = value;
	for (int c = hn; c > 1; c /= 2) {
		if (heap[c / 2] < heap[c]) break;
		swap(heap[c], heap[c / 2]);
	}
}

// maxheap pop
void pop() {
	swap(heap[1], heap[hn--]);
	for (int c = 2; c <= hn; c *= 2) {
		if (c < hn && heap[c] < heap[c + 1]) c++;
		if (heap[c] < heap[c / 2]) break;
		swap(heap[c], heap[c / 2]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int val;
		scanf("%d", &val);
		push(val);
	}

	for (int i = 1; i <= N; i++) printf("%d ", heap[i]);
	printf("\n");

	for (int i = 0; i < N; i++) pop();

	for (int i = 1; i <= N; i++) printf("%d ", heap[i]);
	printf("\n");

	return 0;
}
```