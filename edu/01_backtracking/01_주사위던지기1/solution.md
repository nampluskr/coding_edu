### Solution

```cpp
#include<stdio.h>

int N, M;
int dice[10] = {1}; // dice[0]=1, 나머지는 0
bool used[10];

// 중복 순열
// c번째 주사위 던져!
void recur(int c) {
    // base case
    if(c==N+1) {

        for(int i=1; i<=N; i++)
            printf("%d ",dice[i]);
        printf("\n");
        return;
    }

    // normal case
    for(int i=1; i<=6; i++) {
        // c번째 값을 i로 설정
        dice[c] = i;

        recur(c+1);
    }
    //return;
}

// 중복조합
void recur2(int c) {
    // base case
    if(c==N+1) {
        for(int i=1; i<=N; i++)
            printf("%d ",dice[i]);
        printf("\n");
        return;
    }

    // normal case
    for(int i=dice[c-1]; i<=6; i++) {
        dice[c] = i;

        recur2(c+1);
    }
}

// 순열
void recur3(int c) {
    // base case
    if(c==N+1) {

        for(int i=1; i<=N; i++)
            printf("%d ",dice[i]);
        printf("\n");
        return;
    }

    // normal case
    for(int i=1; i<=6; i++) {
        // dice[1~c-1]와 i가 같은게 있으면 continue
        if(used[i]) continue;
        
        dice[c] = i;
        used[i] = 1;

        recur3(c+1);

        used[i] = 0;
    }
}

int main() {
    scanf("%d%d",&N,&M);

    // for(int i=1; i<=6; i++)
    //     for(int j=1; j<=6; j++)
    //         for(int k=1; k<=6; k++)
    //             printf("%d %d %d\n",i,j,k);

    if(M==1) recur(1);
    if(M==2) recur2(1);
    if(M==3) recur3(1);


    return 0;
}
```