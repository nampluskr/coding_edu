### Solution

```cpp
/*
 ver2. 아미노산 별로 +y 로 쌓아올리고
	   X 축으로 절반 접기
	   +y 로 올릴때 (C) 기준 오른쪽은 4개를 올려서 N-O 가 만나게 해보자.
	   왼쪽은 임의로 올려보자.

		SCORE: 98762
*/

#include<stdio.h>

const int AMINO_TYPE = 20;
const int AMINO_LEN = 28;
const int MAX_AMINO = 20;
const int SPACE_LEN = 100;

typedef struct {
	char symbol;
	bool connector;
	int x, y, z;
} Element;

extern int protein(Element elements[MAX_AMINO][AMINO_LEN]);
extern void fold_amino(int aminoNum, bool front, int axis, bool anticlockwise);
extern void fold_element(int aminoNum, int elementNum, bool front, int axis, bool anticlockwise);

int N;
Element E[20][28];
int aminoSize[20], conIdx[20];

enum { back, front };
enum { X, Y, Z };
enum { clock, anti };

void process()
{
	N = protein(E);
	for (int i = 0; i < N; i++) {
		int j = 0;
		for (; E[i][j].symbol; j++)
			if (E[i][j].connector) conIdx[i] = j;
		aminoSize[i] = j;
	}

	for (int i = 0; i < N; i++) {
		// NHH(C)HHCOOH
		if (aminoSize[i] == 10) {
			// H-H-N O-O
			// |     | |
			// C-H-H-C H
			fold_element(i, 3, front, Z, clock);
			fold_element(i, 2, front, Z, clock);
			fold_element(i, 6, back, Z, anti);
			fold_element(i, 8, back, Z, anti);
		}

		// NHCHHCHHCHH(C)HCOOH	
		else if (aminoSize[i] - conIdx[i] - 1 == 5) {
			// dehi
			// cfgj
			// bHCk
			// aCOOH
			fold_element(i, conIdx[i], back, Z, anti);
			fold_element(i, conIdx[i] + 1, back, Z, clock);
			fold_element(i, conIdx[i] + 2, back, Z, clock);
			fold_element(i, conIdx[i] + 3, back, Z, anti);

			fold_element(i, conIdx[i] - 1, front, Z, clock);
			fold_element(i, conIdx[i] - 4, front, Z, anti);
			fold_element(i, conIdx[i] - 5, front, Z, anti);
			fold_element(i, conIdx[i] - 6, front, Z, clock);
			fold_element(i, conIdx[i] - 7, front, Z, clock);
			fold_element(i, conIdx[i] - 8, front, Z, anti);
			fold_element(i, conIdx[i] - 9, front, Z, anti);
		}

		// *(C)HNHHCOOH
		else {
			// 오른쪽:
			//    HOOC
			// (C)HNHH
			fold_element(i, conIdx[i] + 4, back, Z, anti);
			fold_element(i, conIdx[i] + 5, back, Z, anti);

			// 왼쪽:
			//   (C) 왼쪽에 존재하지 않도록 전체 접어올리기
			//   3,4,5칸으로 각각 쌓아봤을 때 4칸이 가장 나음
			//
			//   hijk
			//   bcde
			//   aHOOC
			//   CHNHH
			fold_element(i, conIdx[i], front, Z, clock);
			fold_element(i, conIdx[i] - 2, front, Z, clock);
			if (conIdx[i] > 5) fold_element(i, conIdx[i] - 5, front, Z, anti);
			if (conIdx[i] > 6) fold_element(i, conIdx[i] - 6, front, Z, anti);
			if (conIdx[i] > 9) fold_element(i, conIdx[i] - 9, front, Z, clock);
			if (conIdx[i] > 10) fold_element(i, conIdx[i] - 10, front, Z, clock);
			if (conIdx[i] > 13) fold_element(i, conIdx[i] - 13, front, Z, anti);
			if (conIdx[i] > 14) fold_element(i, conIdx[i] - 14, front, Z, anti);
			if (conIdx[i] > 17) fold_element(i, conIdx[i] - 17, front, Z, clock);
		}
	}

	fold_amino(N / 2, front, X, clock);
	fold_amino(N / 2 - 1, front, X, clock);
}
```
