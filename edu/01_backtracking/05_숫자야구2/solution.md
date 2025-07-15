### Solution

```cpp
struct Data {
	int strike;
	int ball;
};

extern Data query(int supose[]);

int *ans;
int arr[4];
bool used[10];

int n;
struct Result {
	int arr[4];
	int s, b;
}R[20];

bool isPossible() {
	for (int i = 0; i < n; i++) {
		int s = 0, b = 0;
		for (int j = 0; j < 4; j++) {
			// 같은 위치 같은 경우
			if (R[i].arr[j] == arr[j]) s++;

			// 같은 위치 다른 경우
			else
				for (int k = 0; k < 4; k++)
					if (R[i].arr[j] == arr[k]) b++;
		}
		if (s != R[i].s || b != R[i].b) return 0;
	}
	return 1;
}

bool recur(int c) {
	if (c == 4) {
		if (isPossible()) {
			Data ret = query(arr);
			if (ret.strike == 4) {
				for (int i = 0; i < 4; i++) ans[i] = arr[i];
				return 1;
			}
			for (int i = 0; i < 4; i++)
				R[n].arr[i] = arr[i];
			R[n].s = ret.strike;
			R[n++].b = ret.ball;
		}
		return 0;
	}

	for (int i = 0; i < 10; i++) {
		if (used[i]) continue;
		arr[c] = i;
		used[i] = 1;
		int ret = recur(c + 1);
		used[i] = 0;
		if (ret) return 1;
	}
	return 0;
}

void tryBest(int suppose[]) {
	n = 0;
	ans = suppose;
	recur(0);
}
```