### Solution

```cpp
/*
   ver0. 
    아무것도 안하는 경우:	SCORE: 67108
	절반 접기:				SCORE: 84014

    기본전략 : 인접한 원소들이 많아지게.. 
	=> 김밥처럼 말면 8만 후반 가능	
*/

static const int AMINO_LEN = 28;
static const int MAX_AMINO = 20;

typedef struct {
	char symbol;
	bool connector;
	int x, y, z;
} Element;


extern int protein(Element elements[MAX_AMINO][AMINO_LEN]);
extern void fold_amino(int aminoNum, bool front, int axis, bool anticlockwise);
extern void fold_element(int aminoNum, int elementNum, bool front, int axis, bool anticlockwise);

enum { X, Y, Z };
enum { back, front };
enum { clock, anti };

int N;
Element E[MAX_AMINO][AMINO_LEN];
int len[MAX_AMINO];

void rotate(int aminoIdx, int firstElemIdx, int lastElemIdx, Element& baseElem, int axis, bool anticlockwise)
{
	int dir = (anticlockwise) ? 1 : -1;

	for (int elemIdx = firstElemIdx; elemIdx <= lastElemIdx; elemIdx++) {
		Element srcElem = E[aminoIdx][elemIdx];		// value copy
		Element& destElem = E[aminoIdx][elemIdx];	// reference copy

		if (axis == 0) {
			destElem.y = dir * -(srcElem.z - baseElem.z) + baseElem.y;
			destElem.z = dir * (srcElem.y - baseElem.y) + baseElem.z;
		}
		else if (axis == 1) {
			destElem.z = dir * -(srcElem.x - baseElem.x) + baseElem.z;
			destElem.x = dir * (srcElem.z - baseElem.z) + baseElem.x;
		}
		else if (axis == 2) {
			destElem.x = dir * -(srcElem.y - baseElem.y) + baseElem.x;
			destElem.y = dir * (srcElem.x - baseElem.x) + baseElem.y;
		}
	}
}

void my_fold_amino(int aminoNum, bool front, int axis, bool anticlockwise)
{
	fold_amino(aminoNum, front, axis, anticlockwise);

	int elementNum;
	for (elementNum = 0; E[aminoNum][elementNum].connector == false; elementNum++);

	Element& baseElem = E[aminoNum][elementNum];
	
	int firstAminoIdx = (front) ? 0 : aminoNum + 1;
	int lastAminoIdx = (front) ? aminoNum - 1 : N - 1;

	for (int aminoIdx = firstAminoIdx; aminoIdx <= lastAminoIdx; aminoIdx++)
		rotate(aminoIdx, 0, len[aminoIdx] - 1, baseElem, axis, anticlockwise);
}

void my_fold_element(int aminoNum, int elementNum, bool front, int axis, bool anticlockwise)
{
	fold_element(aminoNum, elementNum, front, axis, anticlockwise);

	Element& baseElem = E[aminoNum][elementNum];

	int firstElemIdx = (front) ? 0 : elementNum + 1;
	int lastElemIdx = (front) ? elementNum - 1 : len[aminoNum] - 1;

	for (int i = firstElemIdx; i <= lastElemIdx; i++)
	{
		if (E[aminoNum][i].connector == true)
			return;
	}
	rotate(aminoNum, firstElemIdx, lastElemIdx, baseElem, axis, anticlockwise);
}

void process()
{
	N = protein(E);
	for (int i = 0; i < N; i++) {
		int j = 0;
		for (; E[i][j].symbol; j++);
		len[i] = j;
	}

	my_fold_amino(N / 2, front, X, anti);
	my_fold_amino(N / 2 - 1, front, X, anti);
}
```
