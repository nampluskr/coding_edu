### 중복순열, 순열, 중복조합, 조합: for 문

```cpp
#include <stdio.h>

const int SIZE = 10;
int arr[SIZE] = { 1, 2, 3 };
int n = 3;

// 중복 순열: 선택 + 배치 (중복 가능),  3*3*3
void select1() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			printf("%d%d ", arr[i], arr[j]);
		}
	printf("\n");
}

// 순열: 선택 + 배치 (중복 불가): 3*2*1 or 3C2*3!
void select2() { 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i != j) 
				printf("%d%d ", arr[i], arr[j]);
		}
	printf("\n");
}

// 중복 조합: 선택 (중복 가능), 3C2 + 3
void select3() {
	//for (int i = 0; i < n; i++)
	//	for (int j = 0; j < n; j++) {
	//		if (i <= j)
	//			printf("%d%d ", arr[i], arr[j]);
	//	}
	//printf("\n");

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) {
			printf("%d%d ", arr[i], arr[j]);
		}
	printf("\n");
}

// 조합: 선택 (중복 불가), 3C2
void select4() {
	//for (int i = 0; i < n; i++)
	//	for (int j = 0; j < n; j++) {
	//		if (i < j)
	//			printf("%d%d ", arr[i], arr[j]);
	//	}
	//printf("\n");

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			printf("%d%d ", arr[i], arr[j]);
		}
	printf("\n");
}


int main()
{
	select1();
	select2();
	select3();
	select4();

	return 0;
}
```

### 중복순열, 순열, 중복조합, 조합: 재귀함수

```cpp
#include <stdio.h>

const int SIZE = 10;
int arr[SIZE] = { 1, 2, 3 };
int n = 3;
int r = 2;
int res[SIZE];

// 중복 순열: 선택 + 배치 (중복 불가)
void recur1(int k) {
	if (k == r) {
		for (int i = 0; i < r; i++) printf("%d", res[i]);
		printf(" ");
		return;
	};

	for (int i = 0; i < n; i++) {
		res[k] = arr[i];
		recur1(k + 1);
	}
}

// 순열: 선택 + 배치 (중복 불가)
int used[SIZE];
void recur2(int k) {
	if (k == r) {
		for (int i = 0; i < r; i++) printf("%d", res[i]);
		printf(" ");
		return;
	};

	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		used[i] = 1;
		res[k] = arr[i];
		recur2(k + 1);
		used[i] = 0;
	}
}

// 중복 조합: 선택 (중복 가능)
void recur3(int k, int start) {
	if (k == r) {
		for (int i = 0; i < r; i++) printf("%d", res[i]);
		printf(" ");
		return;
	};

	for (int i = start; i < n; i++) {
		res[k] = arr[i];
		recur3(k + 1, i);	// i 부터 다시 시작 (중복 허용)
	}
}

// 중복 조합: 선택 (중복 가능)
void recur4(int k, int start) {
	if (k == r) {
		for (int i = 0; i < r; i++) printf("%d", res[i]);
		printf(" ");
		return;
	};

	for (int i = start; i < n; i++) {
		res[k] = arr[i];
		recur4(k + 1, i + 1);	// i + 1 부터 다시 시작 (중복 방지)
	}
}

int main() {

	recur1(0);    printf("\n");
	recur2(0);    printf("\n");
	recur3(0, 0); printf("\n");
	recur4(0, 0); printf("\n");

	return 0;
}
```

### 중복조합, 조합: 재귀함수 (선택/미선택)

```cpp
#include <stdio.h>

const int SIZE = 10;
int arr[SIZE] = { 1, 2, 3 };
int n = 3;
int r = 2;
int res[SIZE];
int used[SIZE];


// 중복 조합
void recur3(int idx, int cnt) {
	if (cnt == r) {
		for (int i = 0; i < r; i++) printf("%d", res[i]);
		printf(" ");
		return;
	};
	if (idx == n) return;

	// 선택하는 경우
	res[cnt] = arr[idx];
	recur3(idx, cnt + 1);

	// 선택하지 않는 경우
	recur3(idx + 1, cnt);
}

// 조합
void recur4(int idx, int cnt) {
	if (cnt == r) {
		for (int i = 0; i < r; i++) printf("%d", res[i]);
		printf(" ");
		return;
	};
	if (idx == n) return;

	// 선택하는 경우
	res[cnt] = arr[idx];
	recur4(idx + 1, cnt + 1);

	// 선택하지 않는 경우
	recur4(idx + 1, cnt);
}


int main() {
	recur3(0, 0); printf("\n");
	recur4(0, 0); printf("\n");

	return 0;
}
```
