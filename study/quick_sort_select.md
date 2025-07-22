### Quick Sort O(NlogN) and Quick Select O(N)

```cpp
#include <stdio.h>

void quickSort(int arr[], int first, int last)
{
    int pivot;
    int i;
    int j;
    int temp;

    if (first < last)
    {
        pivot = first;  //pivot = (first + last) / 2;
        i = first;
        j = last;

        while (i < j)
        {
            while (arr[i] <= arr[pivot] && i < last)
            {
                i++;
            }
            while (arr[j] > arr[pivot])
            {
                j--;
            }
            if (i < j)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        quickSort(arr, first, j - 1);
        quickSort(arr, j + 1, last);
    }
}

int quickSelect(int arr[], int first, int last, int k)
{
    int pivot;
    int i;
    int j;
    int temp;

    if (first < last)
    {
        pivot = first;  //pivot = (first + last) / 2;
        i = first;
        j = last;

        while (i < j)
        {
            while (arr[i] <= arr[pivot] && i < last)
            {
                i++;
            }
            while (arr[j] > arr[pivot])
            {
                j--;
            }
            if (i < j)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        if (k < j) return quickSelect(arr, first, j - 1, k);
        else if (j < k) return quickSelect(arr, j + 1, last, k);
        else return arr[j];
    }
    return arr[first];
}

void print(int arr[], int s, int e) {
    for (int i = s; i <= e; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = { 3, 2, 10, 45, 33, 56, 23, 47 };
    int n = 8;
    print(arr, 0, n - 1);

    //quickSort(arr, 0, n - 1);
    //print(arr, 0, n - 1);

    printf("%d\n", quickSelect(arr, 0, n - 1, 4));
    print(arr, 0, n - 1);

    return 0;
}
```
