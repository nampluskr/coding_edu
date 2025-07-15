### Solution

```cpp
/*
05_힙정렬_0base_reference

변수,함수명 변경 : Ctrl+R,R
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N;
int heap[500005];
int hn;

// maxheap push
void push(int value)
{
	heap[hn] = value;
	int current = hn;
	
	// 우선순위
	while (current > 0 && heap[current] > heap[(current - 1) / 2])
	{
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}
	hn = hn + 1;
}

// maxheap pop
void pop()
{
	hn = hn - 1;

	int tmp = heap[0];
	heap[0] = heap[hn];
	heap[hn] = tmp;

	int current = 0;
	while (current * 2 + 1 < hn)
	{
		int child;
		if (current * 2 + 2 == hn)
		{
			child = current * 2 + 1;
		}
		else
		{
			// 우선순위
			child = heap[current * 2 + 1] > heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}

		// 우선순위
		if (heap[current] > heap[child])
		{
			break;
		}

		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
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

	for (int i = 0; i < N; i++) printf("%d ", heap[i]);
	printf("\n");

	for (int i = 0; i < N; i++) pop();

	for (int i = 0; i < N; i++) printf("%d ", heap[i]);
	printf("\n");

	return 0;
}
```