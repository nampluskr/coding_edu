### Solution

```cpp
#include<stdio.h>

int w, h;
char A[1005][1005], B[1005][1005];

void swap(int&a,int&b) { int c=a;a=b;b=c;}
int main() {
    scanf("%d%d",&w,&h);
    for(int i = 0; i<h; i++)
        scanf("%s",A[i]);

    int cmd;
    scanf("%d",&cmd);

    for(int i=0; i<h; i++)
    for(int j=0; j<w; j++) {
        if (cmd==0) B[j][h-1-i] = A[i][j];
        if (cmd==1) B[h-1-i][w-1-j] = A[i][j];
        if (cmd==2) B[w-1-j][i] = A[i][j];
        if (cmd==3) B[h-1-i][j] = A[i][j];
        if (cmd==4) B[i][w-1-j] = A[i][j];
    }
    if(cmd==0 || cmd==2) swap(w,h);

    printf("%d %d\n",w,h);
    for(int i=0; i<h; i++)
        printf("%s\n", B[i]);

    return 0;
}
```