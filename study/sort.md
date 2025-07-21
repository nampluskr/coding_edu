```cpp
#include <stdio.h>

struct Data { int id, value; };
struct Less {
	bool operator()(const Data& a, const Data& b) const { return a.value < b.value; }
};
struct Greater {
	bool operator()(const Data& a, const Data& b) const { return a.value > b.value; }
};

bool less(Data& a, Data& b) { return a.value < b.value; }
bool greater(Data& a, Data& b) { return a.value > b.value; }

// Merge Sort
Data tmp[1000];
template<typename CMP>
void mergeSort(Data arr[], int s, int e, CMP cmp) {
	if (s >= e) return;
	int m = (s + e) / 2;
	mergeSort(arr, s, m, cmp);
	mergeSort(arr, m + 1, e, cmp);

	int i = s, j = m + 1, k = s;
	while (i <= m && j <= e)
		if (cmp(arr[i], arr[j])) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];

	while (i <= m) tmp[k++] = arr[i++];
	while (j <= e) tmp[k++] = arr[j++];
	for (int i = s; i <= e; i++) arr[i] = tmp[i];
}

// Counting Sort
const int BASE = 100;
int cnt[BASE + 1];
Data sorted[1000];
void countingSort(Data arr[], int s, int e, int opt=1) {
	for (int i = 0; i <= BASE; i++) cnt[i] = 0;
	for (int i = s; i <= e; i++) cnt[arr[i].value]++;
	for (int i = 1; i <= BASE; i++) cnt[i] += cnt[i - 1];
	for (int i = e; i >= s; i--) sorted[--cnt[arr[i].value]] = arr[i];

	if (opt) for (int i = s; i <= e; i++) arr[i] = sorted[i];	// 오름차순
	else for (int i = e; i >= s; i--) arr[e - i] = sorted[i];	// 내림차순
}

void print(Data arr[], int s, int e) {
	for (int i = s; i <= e; i++)
		printf("(%d, %d) ", arr[i].id, arr[i].value);
	printf("\n");
}

int main() {
	Data arr[] = { { 4, 40},  { 1, 10 }, { 5, 50 },  { 3, 30 }, { 2, 20} };
	int n = 5;

	print(arr, 0, n - 1);
	printf("\n");

	mergeSort(arr, 0, n - 1, Less());		print(arr, 0, n - 1);	// 오름차순
	mergeSort(arr, 0, n - 1, Greater());	print(arr, 0, n - 1);	// 내림차순
	printf("\n");

	mergeSort(arr, 0, n - 1, less);			print(arr, 0, n - 1);	// 오름차순
	mergeSort(arr, 0, n - 1, greater);		print(arr, 0, n - 1);	// 내림차순
	printf("\n");

	countingSort(arr, 0, n - 1);			print(arr, 0, n - 1);	// 오름차순
	countingSort(arr, 0, n - 1, 0);			print(arr, 0, n - 1);	// 내림차순

	return 0;
}
```
