### List
```cpp
const int MAX_SIZE = 1000;

template<typename T>
struct List {
	T arr[MAX_SIZE] = {};
	int head = 0, tail = -1;

	void clear() { head = 0, tail = -1; }
	void push_back(const T& data) { arr[++tail] = data; }
	void pop_front() { head++; }
	void pop_back() { tail--; }
	bool empty() { return tail + 1 == head; }
	int size() { return tail + 1 - head; }

	T front() { return arr[head]; }
	T back() { return arr[tail]; }

	T* begin() { return arr; }
	T* end() { return arr + tail + 1; }
};
```


### Max Heap
```cpp
const int MAX_SIZE = 1000;
struct Data { int id, value; }
bool less(const Data& a, const Data& b) { return a.value < b.value; }
bool greater(const Data& a, const Data& b) { return a.value > b.value; }

// PriorityQueue<Data, less> maxHeap;
// PriorityQueue<Data, greater> minHeap;
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
			if (c < heapSize && heap[c] < heap[c + 1]) c++;
			if (cmp(heap[c], heap[c / 2])) break;
			swap(heap[c], heap[c / 2]);
		}
	}
	T top() { return heap[1]; }
	int empty() { return heapSize == 0; }
	void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
};
```
