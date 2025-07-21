#### Merge Sort
```cpp
struct Data { int id, value; };
bool cmp(const Data& a, const Data&b) { return a.value < b.value; }
Data tmp[1000];

template<typename CMP>
void mergeSort(Data arr[], int s, int e, CMP cmp) {
	if (s >= e) return;
	int m = (s + e) / 2;
	mergeSort(arr, s, m, cmp);
	mergeSort(arr, m + 1, e, cmp);

	int i = s, j = m + 1, k = s;
	while(i <= m && j <= e)
		if (cmp(arr[i], arr[j])) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];

	while (i <= m) tmp[k++] = arr[i++];
	while (j <= e) tmp[k++] = arr[j++];
	for(int i = s; i <= e; i++) arr[i] = tmp[i];
}
```

#### Counting Sort
```cpp
const int BASE = 100;
int cnt[BASE + 1];
int tmp[1000];

void countingSort(int arr[], int s, int e) {
	for (int i = 0; i <= BASE; i++) cnt[i] = 0;
	for (int i = s; i <= e; i++) cnt[arr[i]]++;
	for (int i = 1; i <= BASE; i++) cnt[i] += cnt[i - 1];
	for (int i = e; i >= s; i--) sorted[--cnt[arr[i]]] = arr[i];
	for (int i = s; i <= e; i++) arr[i] = tmp[i];
}
```
