#### Graph
```cpp
struct Node { int to, cost; };
List<Node> adjList[MAX_NUM];

// Adjacency List
void addNode(int from, int to, int cost) {
	adjList[from].push_back({ to, cost });
	adjList[to].push_back({ from, cost });
}
```

#### BFS
```cpp
bool visited[MAX_NUM];

bool bfs(int s, int e) {
	List<int> q; // Queue
	for (int i = 0; i < MAX_NUM; i++) visited[i] = false;

	visited[s] = true;
	q.push_back(s);

	while (!que.empty()) {
		int curr = que.front(); que.pop_front();
		if (curr == e) return true;

		for (Node next: adjList[curr])
			if (!visited[next.to]) {
				visited[next.to] = true;
				que.push(next.to);
			}
	}
	return false;
}
```

#### Dijkstra
```cpp
int dist[MAX_NUM];

void dijkstra(int s, int e) {
	PriorityQueue<Node, Less> pq; // Max Heap
	for (int i = 0; i < MAX_NUM; i++) dist[i] = 1e6;

	dist[s] = 0;
	pq.push({ s, 0 });

	while (!pq.empty()) {
		auto curr = pq.top(); pq.pop();
		if (curr.cost > dist[curr.to]) continue;
		if (curr.to == e) return;

		for (auto next: adjList[curr.to]) {
			if (curr.cost + next.cost < dist[next.to]) {
				dist[next.to] = curr.cost + next.cost;
				pq.push({ next.to, dist[next.to] });
			}
		}
	}
}
```

### graph.cpp

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
List<Node> adjList[MAX_SIZE];

// Adjacency List
void addEdge(int from, int to, int cost) {
	adjList[from].push_back({ to, cost });
	//adjList[to].push_back({ from, cost });
}

bool visited[MAX_SIZE];

bool bfs(int s, int e) {
	List<int> q;	// Queue
	for (int i = 0; i < MAX_SIZE; i++) visited[i] = false;

	visited[s] = true; printf("%d ", s);
	q.push_back(s);

	while (!q.empty()) {
		int curr = q.front(); q.pop_front();
		if (curr == e) return true;

		for (Node next : adjList[curr])
			if (!visited[next.to]) {
				visited[next.to] = true;  printf("%d ", next.to);
				q.push_back(next.to);
			}
	}
	return false;
}

int main() {
    // 테스트용 가중치 그래프 생성
    addEdge(0, 1, 4);  addEdge(0, 2, 2);  addEdge(0, 3, 5);
    addEdge(1, 4, 10); addEdge(1, 5, 8);
    addEdge(2, 4, 7);  addEdge(2, 6, 3);
    addEdge(3, 5, 6);  addEdge(3, 6, 12);
    addEdge(4, 7, 5);  addEdge(4, 8, 8);
    addEdge(5, 7, 9);  addEdge(5, 8, 7);
    addEdge(6, 7, 4);  addEdge(6, 8, 6);
    addEdge(7, 8, 2);

	bfs(0, 7); printf("\n");


	return 0;
}
```
