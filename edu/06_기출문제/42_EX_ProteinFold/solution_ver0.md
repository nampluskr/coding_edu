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

void process()
{
	N = protein(E);
	fold_amino(N / 2, front, X, anti);
	fold_amino(N / 2 - 1, front, X, anti);
}
```
