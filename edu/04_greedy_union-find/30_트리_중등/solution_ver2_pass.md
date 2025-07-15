### Solution

```cpp
/*
07_트리(중등)_ver1
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, Q;
int input[200005];	// 입력받은 트리 부모노드
int A[400005], B[400005];
bool ans[200005];

// union-find
int parent[200005];


int find(int a) {
	if (parent[a] == a) return a;
	return parent[a] = find(parent[a]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &Q);
	for (int i = 2; i <= N; i++)
		scanf("%d", input + i);

	Q += N - 1;
	for(int i=0; i<Q; i++) {
		int cmd;
		scanf("%d%d", &cmd, &A[i]);
		if (cmd) scanf("%d", &B[i]);
	}

	// union-find 초기화
	for (int i = 1; i <= N; i++) parent[i] = i;

	int an = 0;
	for (int i = Q - 1; i >= 0; i--) {
		// cmd=1 : 연결 판별
		if (B[i]) {
			ans[an++] = find(A[i]) == find(B[i]);
		}

		// cmd=0 : 간선 삭제(=>역순이므로 연결)
		else {
			int a = A[i];
			int b = input[A[i]];
			a = find(a);
			b = find(b);
			parent[b] = a; 
		}
	}

	for (int i = an - 1; i >= 0; i--)
		printf("%s\n", ans[i] ? "YES" : "NO");

	return 0;
}
```