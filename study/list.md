```cpp
#include <stdio.h>

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

struct Node { int to, cost; };

List<Node> queue;
List<Node> stack;

int main() {
	queue.push_back({ 1, 10 });
	queue.push_back({ 2, 20 });
	queue.push_back({ 3, 30 });
	queue.push_back({ 4, 40 });
	queue.push_back({ 5, 50 });

	while (!queue.empty()) {
		Node curr = queue.front(); queue.pop_front();
		printf("(%d, %d) ", curr.to, curr.cost);
	}
	printf("\n\n");

	stack.push_back({ 1, 10 });
	stack.push_back({ 2, 20 });
	stack.push_back({ 3, 30 });
	stack.push_back({ 4, 40 });
	stack.push_back({ 5, 50 });

	while (!stack.empty()) {
		Node curr = stack.back(); stack.pop_back();
		printf("(%d, %d) ", curr.to, curr.cost);
	}
	printf("\n");

	return 0;
}

```
