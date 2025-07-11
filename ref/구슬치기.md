### 김동현

```cpp
// 이전 동선추적에 비하여 난이도가 급격히 올라갔고 시험시간내에 이런 문제를 빨리 풀기가 어려운거 같습니다.
// 아이디어는 현위치에서 8가지 방향별 다음 위치를 우큐로 정하여 이동하였습니다.

#include <set>
#include <queue>
#include <unordered_map>
using namespace std;

#define MAXN 3000
#define NORMAL 0
#define LD 1
#define RD 2

int r, c, cnt;
bool front, back;
struct DB {
	int r, c;
	bool closed;
}db[33003];

struct Pos {
	int r, c;
	bool operator==(const Pos& re)const {
		return r == re.r && c == re.c;
	}
	bool operator<(const Pos& re)const {
		if (r != re.r) return r < re.r;
		return c < re.c;
	}
};

set<Pos> ver[MAXN], ld[MAXN * 2], hor[MAXN], rd[MAXN * 2];
set<Pos>::iterator it;
int getHash(int r, int c) {
	return r * 10000 + c;
}

unordered_map<int, int> holeMap;

struct Pos2 {
	int minr, maxr, minc, maxc;
};

Pos2 ldRange[MAXN * 2], rdRange[MAXN * 2];

void init(int N) {
	holeMap.clear();
	for (int i = 0; i < MAXN; i++) ver[i].clear(), hor[i].clear();
	for (int i = 0; i < MAXN * 2; i++) ld[i].clear(), rd[i].clear(), ldRange[i] = rdRange[i] = {};
}

void addDiagonal(int mARow, int mACol, int mBRow, int mBCol) {
	int minr, maxr, minc, maxc;
	if (mARow + mACol == mBRow + mBCol) { // left diagonal
		if (mARow > mBRow) minr = mBRow, maxr = mARow, minc = mACol, maxc = mBCol;
		else minr = mARow, maxr = mBRow, minc = mBCol, maxc = mACol;
		ldRange[mARow + mACol] = { minr, maxr, minc, maxc };
	}
	else { // right diagonal
		if (mARow < mBRow) minr = mARow, maxr = mBRow, minc = mACol, maxc = mBCol;
		else minr = mBRow, maxr = mARow, minc = mBCol, maxc = mACol;
		rdRange[MAXN + mARow - mACol] = { minr, maxr, minc, maxc };
	}
}

void addHole(int mRow, int mCol, int mID) {
	db[mID] = { mRow, mCol, false };
	holeMap[getHash(mRow, mCol)] = mID;
	ver[mCol].insert({ mRow, mCol }), hor[mRow].insert({ mRow, mCol });
	ld[mRow + mCol].insert({ mRow, mCol }), rd[mRow - mCol + MAXN].insert({ mRow, mCol });
}

void eraseHole(int mRow, int mCol) {
	int hash = getHash(mRow, mCol);
	if (holeMap.count(hash)) {
		ver[mCol].erase({ mRow, mCol }), hor[mRow].erase({ mRow, mCol });
		ld[mRow + mCol].erase({ mRow, mCol }), rd[mRow - mCol + MAXN].erase({ mRow, mCol });
		holeMap.erase(hash);
	}
}

struct Info {
	int mid, d;
	bool operator<(const Info& re)const {
		if (d != re.d) return d > re.d;
		if (db[mid].r != db[re.mid].r) return db[mid].r > db[re.mid].r;
		return db[mid].c > db[re.mid].c;
	}
};
priority_queue<Info> pq;

int normal_dist(int mid, int r, int c) {
	return abs(db[mid].r - r) * 10 + abs(db[mid].c - c) * 10;
}

int diagonal_dist(int mid, int r, int c) {
	return abs(db[mid].r - r) * 14;
}

void dir(set<Pos>& s) {
	front = back = false;
	it = s.lower_bound({ r,c });
	if (it == s.end()) front = true; // 앞으로 전진
	if (it == s.begin()) back = true; // 뒤로 전진
	if (it != s.end() && it != s.begin()) front = back = true;
}

bool range(Pos2& p, int r, int c) {
	return p.minr <= r && p.maxr >= r && p.minc <= c && p.maxc >= c;
}

void frontGo(set<Pos>& s, int opt) {
	while (front && it != s.begin()) {
		it--;
		int mid = holeMap[getHash(it->r, it->c)];
		if (db[mid].closed) continue;
		if (opt == NORMAL) {
			pq.push({ mid , normal_dist(mid, r, c) }); return;
		}
		else if(opt == LD) {
			if (range(ldRange[r + c], it->r, it->c)) {
				pq.push({ mid , diagonal_dist(mid, r, c) }); return;
			}
		}
		else {
			if (range(rdRange[MAXN + r - c], it->r, it->c)) {
				pq.push({ mid , diagonal_dist(mid, r, c) }); return;
			}
		}
	}
}

void backGo(set<Pos>& s, int opt) {
	it = s.lower_bound({ r,c });
	while (back) {
		int mid = holeMap[getHash(it->r, it->c)];
		if (opt == NORMAL) {
			if (!db[mid].closed) {
				pq.push({ mid , normal_dist(mid, r, c) }); return;
			}
		}
		else if (opt == LD) {
			if (!db[mid].closed && range(ldRange[r + c], it->r, it->c)) {
				pq.push({ mid , diagonal_dist(mid, r, c) }); return;
			}
		}
		else {
			if (!db[mid].closed && range(rdRange[MAXN + r - c], it->r, it->c)) {
				pq.push({ mid , diagonal_dist(mid, r, c) }); return;
			}
		}
		if (it == --s.end()) return;
		it++;
	}
}

int hitMarble(int mRow, int mCol, int mK) {
	cnt = 0, r = mRow, c = mCol;
	vector<Info> tmp; int mid, ret = -1;
	while (cnt++ < mK) {
		while (!pq.empty()) pq.pop();
		if (hor[r].size()) dir(hor[r]), frontGo(hor[r], NORMAL), backGo(hor[r], NORMAL);
		if (ver[c].size()) dir(ver[c]), frontGo(ver[c], NORMAL), backGo(ver[c], NORMAL);
		if (ld[r + c].size() && range(ldRange[r + c], r, c))
			dir(ld[r + c]), frontGo(ld[r + c], LD), backGo(ld[r + c], LD);
		if (rd[MAXN + r - c].size() && range(rdRange[MAXN + r - c], r, c))
			dir(rd[MAXN + r - c]), frontGo(rd[MAXN + r - c], RD), backGo(rd[MAXN + r - c], RD);
		if (pq.empty()) break;
		tmp.push_back(pq.top()); ret = pq.top().mid;
		r = db[ret].r, c = db[ret].c, db[ret].closed = true;
	}
	for (auto nx : tmp) db[nx.mid].closed = false;
	return ret;
}
```

### 김경태 (시간초과)

```cpp
/*	처음 queue, vector로 만들어서 처리했는데 속도가 느려서 Linked_List로 바꿨더니 조금 빨라졌습니다.
        통과가 가능한지 체크 부탁드립니다. 
*/

#ifndef _CRT_SECURE_NO_WARNINGS

#define _CRT_SECURE_NO_WARNINGS

#endif



#include <queue>

#include <vector>

#include <string>

using namespace std;



#define MAXN	3001

#define MAXH	30001

#define INF		0x7fffffff



int N, dwp, hrp;

int map[MAXN][MAXN];

int delHole[MAXH];

vector<int> dmap[MAXN][MAXN];



struct Diag {

	int aRow;	int bRow;

	int aCol;	int bCol;

} diag[MAXN];



struct Hole {

	int row; int col;

} hole[MAXH];

Hole result;



struct ListNode {

	int id;

	ListNode* next;

};

ListNode heap[10000000];



ListNode* appendListNode(int id, ListNode* oldHead) {

	ListNode* node = &heap[hrp++];

	node->id = id;

	node->next = oldHead;

	return node;

}

ListNode* ROW[MAXN];

ListNode* COL[MAXN];



void init(int N)

{

	::N = N;

	hrp = 0;

	dwp = 1;



	for (int i = 0; i < MAXH; i++) {

		hole[i] = {};

		delHole[i] = 0;

	}



	for (int i = 0; i < MAXN; i++) {		

		for (int j = 0; j < MAXN; j++) {

			dmap[i][j].clear();

			map[i][j] = 0;

		}

		diag[i] = {};

		ROW[i] = 0;

		COL[i] = 0;

	}

}



void addDiagonal(int mARow, int mACol, int mBRow, int mBCol)	// *3'000

{

	int stRow = mARow < mBRow ? mARow : mBRow;

	int edRow = mARow < mBRow ? mBRow : mARow;

	int stCol = mARow == stRow ? mACol : mBCol;

	int edCol = mARow == stRow ? mBCol : mACol;

	int row = 0, col = 0;

	diag[dwp] = { stRow, edRow, stCol,edCol };



	for (int i = 0; i <= (edRow - stRow); i++) {

		if (stCol < edCol) {

			row = (stRow + i);

			col = (stCol + i);

		}

		else {

			row = (stRow + i);

			col = (stCol - i);

		}

		dmap[row][col].push_back(dwp);

	}

	dwp++;

}



void addHole(int mRow, int mCol, int mID)	// *30'000

{

	map[mRow][mCol] = mID;

	hole[mID] = { mRow,mCol };

	ROW[mRow] = appendListNode(mID, ROW[mRow]);

	COL[mCol] = appendListNode(mID, COL[mCol]); 

}



void eraseHole(int mRow, int mCol)	// *3'000

{

	if (map[mRow][mCol] == 0)

		return;

	delHole[map[mRow][mCol]] = 2;

}



void Init_delHole() {

	for (int i = 0; i < MAXH; i++) {

		if (delHole[i] == 1)

			delHole[i] = 0;

	}

}



int checkDiag(int mRow, int mCol) {

	if (dmap[mRow][mCol].size() == 0)

		return 0;

	return dmap[mRow][mCol].front();

}



int hitMarble(int mRow, int mCol, int mK)	// *10'000

{

	int Row = mRow;

	int Col = mCol;

	result = { 0,0 };

	int cnt = 0;



	Init_delHole();



	while (cnt != mK) {

		int dist = INF;



		if (cnt != 0 && result.row == INF) {

			return -1;

		}



		ListNode* temp = COL[Col];



		while (temp != NULL) {

			int id = temp->id;

			int nrow = hole[id].row;

			int idx = map[nrow][Col];



			if (delHole[idx] >= 1 || abs(Row - nrow) * 10 > dist) {

				temp = temp->next;

				continue;

			}

			else if (abs(Row - nrow) * 10 < dist) {

				dist = (abs(Row - nrow) * 10);

				result = { nrow,Col };

			}

			else if (abs(Row - nrow) * 10 == dist && nrow < result.row) {

				dist = (abs(Row - nrow) * 10);

				result = { nrow,Col };

			}

			temp = temp->next;

		}



		temp = ROW[Row];

		while (temp != NULL) {

			int id = temp->id;

			int ncol = hole[id].col;

			int idx = map[Row][ncol];



			if (delHole[idx] >= 1 || abs(Col - ncol) * 10 > dist) {

				temp = temp->next;

				continue;

			}

			else if (abs(Col - ncol) * 10 < dist) {

				dist = (abs(Col - ncol) * 10);

				result = { Row,ncol };

			}

			else if (abs(Col - ncol) * 10 == dist && Row < result.row) {

				dist = (abs(Col - ncol) * 10);

				result = { Row,ncol };

			}

			else if (abs(Col - ncol) * 10 == dist && Row == result.row && ncol < result.col) {

				dist = (abs(Col - ncol) * 10);

				result = { Row,ncol };

			}			

			temp = temp->next;

		}

		// diag check

		int diagId = checkDiag(Row, Col);



		if (diagId != 0) {

			int rcId = map[Row][Col];

			int n = dmap[Row][Col].size();



			if (n <= 1) {

				for (int i = 0; i <= (diag[diagId].bRow - diag[diagId].aRow); i++) {

					if (diag[diagId].aCol < diag[diagId].bCol)

						rcId = map[diag[diagId].aRow + i][diag[diagId].aCol + i];

					else

						rcId = map[diag[diagId].aRow + i][diag[diagId].aCol - i];



					if (delHole[rcId] >= 1)

						continue;



					if (rcId != 0 && abs(hole[rcId].row - Row) * 14 < dist) {

						dist = abs(hole[rcId].row - Row) * 14;

						result.row = hole[rcId].row;

						result.col = hole[rcId].col;

					}

					else if (rcId != 0 && abs(hole[rcId].row - Row) * 14 == dist) {

						if (result.row > hole[rcId].row) {

							dist = abs(hole[rcId].row - Row) * 14;

							result.row = hole[rcId].row;

							result.col = hole[rcId].col;

						}

					}

				}

			}

			else if (n >= 2) {

				vector<int> temp;

				int trcId = 0;



				while (n > 0) {

					diagId = dmap[Row][Col].back(); dmap[Row][Col].pop_back();

					temp.push_back(diagId);



					for (int i = 0; i <= (diag[diagId].bRow - diag[diagId].aRow); i++) {

						if (diag[diagId].aCol < diag[diagId].bCol)

							trcId = map[diag[diagId].aRow + i][diag[diagId].aCol + i];

						else

							trcId = map[diag[diagId].aRow + i][diag[diagId].aCol - i];



						if (delHole[trcId] >= 1)

							continue;



						if (abs(hole[trcId].row - Row) * 14 < dist) {

							dist = abs(hole[trcId].row - Row) * 14;

							result.row = hole[trcId].row;

							result.col = hole[trcId].col;

						}

						else if (rcId != 0 && abs(hole[rcId].row - Row) * 14 == dist) {

							if (result.row > hole[rcId].row) {

								dist = abs(hole[rcId].row - Row) * 14;

								result.row = hole[rcId].row;

								result.col = hole[rcId].col;

							}

						}

					}

					n--;

				}

				while (!temp.empty()) {

					auto cur = temp.back(); temp.pop_back();

					dmap[Row][Col].push_back(cur);

				}

			}

		}		

		// hole Closed

		if (delHole[map[result.row][result.col]] == 0) {

			delHole[map[result.row][result.col]] = 1;

			Row = result.row;

			Col = result.col;

			cnt++;

		}

		else

			break;

	}



	if (map[result.row][result.col] == 0)

		return -1;



	return map[result.row][result.col];

}
```


### 박종환

```cpp
// 각 행과 열을 index로 하여 hole위치를 찾는 방식입니다.









#define MAXN 3001



int abs(int a) { return a < 0? -a: a; }





int N;



int holes[MAXN][MAXN];



int visited[MAXN][MAXN];

int nVisited;



int dist, cid;

int rNext, cNext;



struct Coordinate

{

    int row, col;

};



struct Node

{

    Node* next;

    Coordinate location;

    

    Node(int row, int col)

    {

        location.row = row; location.col = col;

    }

};



class LinkedList

{

public:

    int length;

    Node* head;

    

    void init() { head = nullptr; }

    

    void push(int row, int col)

    {

        Node* node = new Node(row, col);

        

        node->next = head;

        head = node;

        

        length++;

    }

    

    void searchHole(int row, int col)

    {

        Node* node = head;

        

        while (node)

        {

            int dr = node->location.row; int dc = node->location.col;

            

            if (holes[dr][dc] > 0 && visited[dr][dc] < nVisited)

            {

                int newDist = (abs(dr - row) + abs(dc - col)) * 10;

                

                if (newDist < dist)

                {

                    dist = newDist;

                    rNext = dr; cNext = dc;

                }

                else if (newDist == dist && dr < rNext)

                {

                    rNext = dr; cNext = dc;

                }

                else if (newDist == dist && dr == rNext && dc < cNext)

                {

                    rNext = dr; cNext = dc;

                }

            }

            

            node = node->next;

        }

    }

};



LinkedList hashRow[MAXN];

LinkedList hashCol[MAXN];



class Diagonal   // row = -y

{

public:

    Coordinate st, ed; // row, col

    int slope, intercept;  // x, y

    

    bool isOnTheLine(int row, int col)

    {

        int x = col; int y = -row;

        

        int _y = x * slope + intercept;

        

        if (_y != y ) { return false; }

        

        if (col < st.col || col > ed.col) { return false;}

        

        return true;

    }

    

    void searchHole(int row, int col)

    {

        

        for (int x = st.col; x <= ed.col; x++)

        {

            int y = slope * x + intercept;

            int dr = -y; int dc = x;

            

            if (holes[dr][dc] > 0 && visited[dr][dc] < nVisited)

            {

                int newDist = abs(dc - col) * 14;

                

                if (newDist < dist)

                {

                    dist = newDist;

                    rNext = dr; cNext = dc;

                }

                else if (newDist == dist && dr < rNext)

                {

                    rNext = dr; cNext = dc;

                }

                else if (newDist == dist && dr == rNext && dc < cNext)

                {

                    rNext = dr; cNext = dc;

                }

                

            }

            

        }

    }

};





Diagonal diags[MAXN * 2][5];

int idxDiag[MAXN * 2];





void checkDiagonal(int row, int col)

{

    int x = col; int y = -row;

    

    int key1 = abs(y - x);

    int key2 = abs(y + x);

    

    for (int i = 0; i < idxDiag[key1]; i++)

    {

        if (!diags[key1][i].isOnTheLine(row, col)) { continue; }

        

        diags[key1][i].searchHole(row, col);

    }

    

    

    for (int i = 0; i < idxDiag[key2]; i++)

    {

        if (!diags[key2][i].isOnTheLine(row, col)) { continue; }

        

        diags[key2][i].searchHole(row, col);

    }

    

}





void init(int _N)

{

    nVisited = 0;

    

    N = _N;

    

    for (int r = 0; r <= N; r++)

    {

        hashRow[r].init();

        hashCol[r].init();

        idxDiag[r] = 0;

        idxDiag[r + N] = 0;

        

        for (int c = 0; c <= N; c++)

        {

            holes[r][c] = -1;

            visited[r][c] = 0;

        }

    }



}







void addDiagonal(int mARow, int mACol, int mBRow, int mBCol)

{

    int x1, x2, y1, y2;

    

    if (mACol < mBCol)

    {

        x1 = mACol; y1 = -mARow;

        x2 = mBCol; y2 = -mBRow;

    }

    else

    {

        x2 = mACol; y2 = -mARow;

        x1 = mBCol; y1 = -mBRow;

    }

    

    int slope = (y2 - y1) / (x2 - x1);

    int intercept = y1 - slope * x1;

    

    int key = abs(intercept);

    

    diags[key][idxDiag[key]].st = { -y1, x1 };

    diags[key][idxDiag[key]].ed = { -y2, x2 };

    diags[key][idxDiag[key]].slope = slope;

    diags[key][idxDiag[key]].intercept = intercept;

    idxDiag[key]++;

}







void addHole(int mRow, int mCol, int mID)

{

    holes[mRow][mCol] = mID;

    

    hashRow[mRow].push(mRow, mCol);

    hashCol[mCol].push(mRow, mCol);

}







void eraseHole(int mRow, int mCol)

{

    holes[mRow][mCol] = -1;

}







int hitMarble(int mRow, int mCol, int mK)

{

    nVisited++;

    

    cid = -1;

    

    Coordinate curr = { mRow, mCol };

    

    visited[curr.row][curr.col] = nVisited;

    

    while (mK > 0)

    {

        rNext = MAXN; cNext = MAXN;

        dist = MAXN * 15;

        

        hashRow[curr.row].searchHole(curr.row, curr.col);

        hashCol[curr.col].searchHole(curr.row, curr.col);

        

        checkDiagonal(curr.row, curr.col);

        

        if (dist == MAXN * 15) { break; }

        

        curr = { rNext, cNext };

        

        cid = holes[curr.row][curr.col];

        visited[curr.row][curr.col] = nVisited;

        

        mK--;

    }



    return cid;



}
```
