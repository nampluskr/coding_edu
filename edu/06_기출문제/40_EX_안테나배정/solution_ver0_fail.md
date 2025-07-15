### Solution

```cpp
/*
 ver0. 순차적으로 배정
       4번 이동으로 멀어질 수 있음을 고려하여 현재 range+4 기록
*/
#define ABS(x) (((x)<0)?(-(x)):(x))

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }
void swap(int &a, int &b) { int c = a; a = b; b = c; }

struct Coordinates {
	int y, x;
	Coordinates() {
		y = x = 0;
	}
	Coordinates(int _y, int _x) {
		y = _y;
		x = _x;
	}
	int operator-(Coordinates& param) {
		return ABS(y - param.y) + ABS(x - param.x);
	}
};

Coordinates *A;

void init(Coordinates antennas[]) {
	A = antennas;
}

void scanUE(Coordinates UE_list[], int range[], int conn[]) {
	// 초기화 중요!
	for (int i = 0; i < 150; i++) range[i] = 0;

	for (int uid = 0; uid < 10000; uid++) {
		int aid = uid % 150;
		conn[uid] = aid;
		range[aid] = max(range[aid], A[aid] - UE_list[uid] + 4);
	}
}
```