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
