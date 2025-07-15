### Solution

```cpp
extern int orderCheck(int left, int right);

int N;
int arr[100005];

void insertionSort(void)
{
	int temp;
	int i;
	int j;
	for (i = 1; i < N; i++)
	{
		temp = arr[i];
		j = i - 1;

		while ((j >= 0) && orderCheck(temp, arr[j]))
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = temp;
	}
}

void array_restore(int N, int dat[]) {
	::N = N;
	for (int i = 0; i < N; i++) arr[i] = i;
	insertionSort();
	for (int i = 0; i < N; i++)
		dat[arr[i]] = i + 1;
}
```