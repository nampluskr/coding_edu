### 문제


N개의 정수를 입력받아 오름차순으로 정렬하고

Q개의 질의에 응답하는 프로그램을 작성하시오.

질의는 정렬된 결과에서 idx에 위치하는 값이 무엇인지에 응답하는 것이다.



아래 main 코드는 사용자의 코드작성을 돕기 위한것으로

실제 채점시에는 다른 방법으로 채점될 수 있다.​



사용자는 user.cpp파일만 완성하여 제출한다.

user.cpp에는 변수와 함수를 추가할 수 있으나, 헤더파일은 사용할 수 없다.

### [CPP code template]

```cpp
// main.cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define MAX_SIZE (1000000)

static int N, Q, A[MAX_SIZE];

extern void countingSort(int, int*);
extern int query(int);

static void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", A + i);
	}
	countingSort(N, A);
}

static void run() {
	int i, idx;
	scanf("%d", &Q);
	for (i = 0; i < Q; ++i) {
		scanf("%d", &idx);
		int userAns = query(idx);
		printf("%d\n", userAns);
	}
}

int main() {
	// freopen("input.txt", "r", stdin);
	input();
	run();
	return 0;
}

// user.cpp
void countingSort(int arraySize, int *arr) {
	return;
}

int query(int idx) {
	return 0;
}
```

### 입력
첫 행에 N이 주어진다. ( 10,000 <= N <= 1,000,000)

다음 행에 N개의 정수 ai 가 공백을 구분하여 입력된다. (-32,768 <= ai <= 32,767)

다음 행에 질의 수 Q가 입력된다. ( 10,000 <= Q <= 1,000,000)

다음 행에 Q개의 idx가 공백으로 구분되어 주어진다. ( 0 <= idx < N)


### 출력
Q개의 질의에 대한 결과를 행으로 구분하여 출력한다.


### 예제
입력
```
7
4 2 7 5 3 1 6
5
2 3 5 0 1
```

출력
```
3
4
6
1
2
```