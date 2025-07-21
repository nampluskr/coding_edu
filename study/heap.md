```cpp
#include <stdio.h>

const int MAX_SIZE = 1000;
struct Data { int id, value; };
struct Less {
    bool operator()(const Data& a, const Data& b) const { return a.value < b.value; }
};
struct Greater {
    bool operator()(const Data& a, const Data& b) const { return a.value > b.value; }
};

template<typename T, typename CMP>
struct PriorityQueue {
	T heap[MAX_SIZE] = {};
	int heapSize = 0;
	CMP cmp;

	void clear() { heapSize = 0; }
	void push(const Data& data) {
		heap[++heapSize] = data;
		for (int c = heapSize; c > 1; c /= 2) {
			if (cmp(heap[c], heap[c / 2])) break;
			swap(heap[c], heap[c / 2]);
		}
	}
	void pop() {
		swap(heap[1], heap[heapSize--]);
		for (int c = 2; c <= heapSize; c *= 2) {
			if (c < heapSize && cmp(heap[c], heap[c + 1])) c++;
			if (cmp(heap[c], heap[c / 2])) break;
			swap(heap[c], heap[c / 2]);
		}
	}
	T top() { return heap[1]; }
	int empty() { return heapSize == 0; }
	void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
};

void print(Data arr[], int s, int e) {
	for (int i = s; i <= e; i++)
		printf("(%d, %d) ", arr[i].id, arr[i].value);
	printf("\n");
}

int main() {
	Data arr[] = { { 4, 40},  { 1, 10 }, { 5, 50 },  { 3, 30 }, { 2, 20} };
	int n = 5;

	// Max Heap
	PriorityQueue<Data, Less> maxHeap;
	for (int i = 0; i < n; i++) maxHeap.push(arr[i]);
	print(maxHeap.heap, 1, n);

    while (!maxHeap.empty()) {
        Data top = maxHeap.top(); maxHeap.pop();
		printf("(%d, %d) ", top.id, top.value);
    }
	printf("\n\n");

	// Min Heap
	PriorityQueue<Data, Greater> minHeap;
	for (int i = 0; i < n; i++) minHeap.push(arr[i]);
	print(minHeap.heap, 1, n);

	while (!minHeap.empty()) {
		Data top = minHeap.top(); minHeap.pop();
		printf("(%d, %d) ", top.id, top.value);
	}
	printf("\n");

    return 0;
}
```
