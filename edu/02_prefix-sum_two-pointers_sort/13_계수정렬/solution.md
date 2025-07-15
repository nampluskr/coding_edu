### Solution

```cpp
const int BASE = 32768;

int sorted[1000005];
int C[BASE * 2];

struct Data {
	int id, score;
}A[100000];

void countingSort_0(int n, int *arr) {
	for (int i = 0; i < n; i++) C[arr[i] + BASE]++;

	int idx = 0;
	for (int i = 0; i < BASE * 2; i++)
		while (C[i]--) sorted[idx++] = i - BASE;
}

void countingSort(int n, int *arr) {
	for (int i = 0; i < n; i++) C[arr[i] + BASE]++;
	for (int i = 1; i < BASE * 2; i++) C[i] += C[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		int idx = --C[arr[i] + BASE];
		sorted[idx] = arr[i];
	}
}

int query(int idx) {
	return sorted[idx];
}
```