### Solution

```cpp
//  heap 정렬
//  O(N log N) 정렬이지만 실질적인 비교 횟수는 더 많다.

extern int orderCheck(int left, int right);

int heapSize;
int heap[100005];

void push(int value) {
	heap[heapSize] = value;

	int current = heapSize;
	while (current > 0 && orderCheck(heap[current], heap[(current - 1) / 2]))
	{
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;
}

void pop() {
	heapSize = heapSize - 1;

	heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = orderCheck(heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
		}

		if (orderCheck(heap[current], heap[child]))
		{
			break;
		}

		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
}

void swap(int &a, int &b) { int c = a; a = b; b = c; }
void array_restore(int N, int dat[]) {
	for (int i = 0; i < N; i++) push(i);
	for (int i = 1; i <= N; i++) {
		int id = heap[0];
		dat[id] = i;
		pop();
	}
}
```