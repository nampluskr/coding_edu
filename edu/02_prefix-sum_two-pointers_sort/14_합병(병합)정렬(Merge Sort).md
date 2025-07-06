## Tutorial : 합병(병합)정렬(Merge Sort)


### [합병(병합)정렬 (Merge Sort)]

머지소트는 폰 노이만(John von Neumann)이 1945년 개발한 알고리즘이다.

원소들간의 비교을 통하여 정렬하는 비교기반정렬 알고리즘이다.​​

원소들 중에 같은 값이 있는 경우 정렬후에도 이들의 순서가 유지되는 안정 정렬에 속한다.​

N개의 데이터를 정렬할 때, 시간복잡도는 O(N * logN)이 보장된다.

정렬의 각 과정은 분할 -> 정복 -> 결합과정으로 이루어진다.​



### [합병정렬(오름차순) 알고리즘 프로세스]

정렬할 배열을 A[], 구간의 시작 인덱스(배열번호)를 low, 끝 인덱스를 high 라고 하자.​

1. low >= high 라면 현재 구간은 정렬된것으로 본다. 그렇지 않은 경우

2. 분할(Divide) 과정 :​ 구간의 중앙을 구한다. mid = (low + high) / 2;

3. 정복(Conquer) 과정 :​ 나누어진 두 구간을 각각 재귀적으로 정렬한다.

4. 결합(Merge) 과정 : 정렬된 두 구간을 이용하여 정렬된 하나의 구간을 만들어 임시 배열 B[]에 저장한다.

5. 복사(Copy)과정 : 결합이 완성된 임시 배열 B[]를 A[]에 복사한다.



### [합병정렬(오름차순) 의사(pseudo-code)코드 1]​

```cpp
// A[] : 정렬할 배열
// B[] : 임시배열
// 정렬구간 [low, high]
mergeSort(A[], low, high, B[]):
    // 1. base condition
    if low >= high: 
        return
 
    // 2. 분할(divide) 및 정복(conquer)
    mid ← (low + high) / 2
    mergeSort(A, low, mid, B)
    mergeSort(A, mid + 1, high, B)
 
    // 3. 결합(merge)
    i ← low, j ← mid + 1, k ← low
    while i <= mid and j <= high:
        if A[i] <= A[j]: 
            B[k++] ← A[i++]
        else:
            B[k++] ← A[j++]

    while i <= mid:  
            B[k++] ← A[i++]
    while j <= high: 
            B[k++] ← A[j++]
 
 
    // 4. 복사(copy)
    for i ← low;i <= high;i ← i +1:
         A[i] = B[i]
// *** 출력 하는 위치 ***
```

### [합병정렬(오름차순) 의사(pseudo-code)코드 2]​

```cpp
// A[] : 정렬할 배열
// B[] : 임시배열
// 정렬구간 [low, high]
mergeSort(A[], low, high, B[]):
    // 1. base condition
    if low >= high: 
        return
 
    // 2. 분할(divide) 및 정복(conquer)
    mid ← (low + high) / 2
    mergeSort(A, low, mid, B)
    mergeSort(A, mid + 1, high, B)
 
    // 3. 결합(merge)
    i ← low, j ← mid + 1
    for k ← low;k <= high; k ← k + 1 :
        if j > high:  
            B[k] ← A[i++]
        else if i > mid: 
            B[k] ← A[j++]
        else if A[i] <= A[j]: 
            B[k] ← A[i++]
        else:
            B[k] ← A[j++]
 
 
    // 4. 복사(copy)
    for i ← low;i <= high;i ← i +1:
         A[i] = B[i]
// *** 출력 하는 위치 ***
```

### [문제]

N개의 정수를 입력받아 합병정렬의 매 과정에서 복사 단계 이후 A[]의 상태를 행단위로 출력하는 프로그램을 작성하시오.

위에서 설명한 프로세스를 기준으로 각 단계의 상태를 출력한다.

### 입력
첫 행에 N을 입력받는다. ( 10 <= N <= 1000) 다음 행에 N개의 정수 ai가 입력된다. ( 0 <= ai <= 100,000)


### 출력
합병정렬의 매 과정에서 복사 단계 이후 전체 A[]의 상태를 행단위로 출력한다.


### 예제
입력
```
7
5 9 7 1 3 8 2
```

출력
```
5 9 7 1 3 8 2
5 9 1 7 3 8 2
1 5 7 9 3 8 2
1 5 7 9 3 8 2
1 5 7 9 2 3 8
1 2 3 5 7 8 9
```