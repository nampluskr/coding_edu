### Solution

```cpp
/*
    ver1. X축 기준으로 김밥 말기
	SCORE: 88766
*/
#include<stdio.h>

static const int AMINO_LEN = 28;
static const int MAX_AMINO = 20;
static const int MAX_TC = 10;
static const int AMINO_TYPE = 20;
static const int SPACE_LEN = 100;

typedef struct {
	char symbol;
	bool connector;
	int x, y, z;
} Element;

extern int protein(Element elements[MAX_AMINO][AMINO_LEN]);
extern void fold_amino(int aminoNum, bool front, int axis, bool anticlockwise);
extern void fold_element(int aminoNum, int elementNum, bool front, int axis, bool anticlockwise);

int N;
Element E[MAX_AMINO][AMINO_LEN];

enum { X, Y, Z };
enum { back, front };
enum { clock, anti };

void process()
{
	N = protein(E);

	int idx = 0;
	int jump = 1;
	for (int i = 0; ; i++) {
		idx += jump;
		if (idx >= N) break;
		fold_amino(idx, front, X, anti);
		if (i % 2) jump++;
	}
}
```
