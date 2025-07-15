### Solution

```cpp
// merge sort
// 실질적인 비교 횟수는 worst case 에도 N log N  을 넘을 수 없다.
extern int orderCheck(int left, int right);

int ids[100005], tmp[100005];

void swap(int &a, int &b) { int c = a; a = b; b = c; }

void merge(int s, int e) {
	if (s == e) return;

	int m = (s + e) / 2;
	merge(s, m);
	merge(m + 1, e);

	int i = s, j = m + 1, k = s;
	while (i <= m && j <= e) {
		if (orderCheck(ids[i], ids[j])) tmp[k++] = ids[i++];
		else tmp[k++] = ids[j++];
	}
	while (i <= m) tmp[k++] = ids[i++];
	while (j <= e) tmp[k++] = ids[j++];

	for (; s <= e; s++) ids[s] = tmp[s];
}

void array_restore(int N, int dat[]) {
	for (int i = 0; i < N; i++) ids[i] = i;

	merge(0, N - 1);

	for (int i = 0; i < N; i++) {
		int id = ids[i];
		dat[id] = i + 1;
	}
}
```