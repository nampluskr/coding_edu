### Solution

```cpp
/*
 * 로컬, 서버 결과 다른 경우(or 디버그 릴리즈 모드 결과 다른 경우)
   => 불확실한 코드 존재
 
   1) 잘못된 배열 범위 접근
   2) 반환값이 있는 함수에서 모든분기에 반환값을 반환하지 않을 때
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
using ll = long long;

long long ans;

int N, M;
char dir[200005];
int E[200005];

int prev(int x, int c=1) { return (x - c + N) % N; }
int next(int x, int c=1) { return (x + c) % N; }
ll min(ll a, ll b) { return a < b ? a : b; }

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d%d", &N, &M);
	scanf("%s", dir);
	for (int i = 0; i < N; i++) {
		scanf("%d", E + i);
		ans += E[i];
	}

	for (int i = 0; i < N; i++) {
		if (dir[i] == 'R' && dir[(i + 1) % N] == 'L') {
			//if (i == 17) {
			//	i = i;
			//}
			//printf("i=%d ", i);
			ll sum = 0;
			for (int j = prev(i); dir[j] == 'R'; j = prev(j))
				sum += E[j];
			ans -= min(sum, M);
			//printf("R=%d ", sum);

			sum = 0;
			for(int j=next(i,2); dir[j]=='L'; j=next(j))
				sum += E[j];
			ans -= min(sum, M);
			//printf("L=%d\n", sum);
		}
	}

	printf("%lld\n", ans);


	return 0;
}
```