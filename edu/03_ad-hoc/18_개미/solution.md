### Solution

```cpp
#include<stdio.h>

int t,w,h,x,y;

// 주기=2*w
//O(2w)
int getPos(int w, int x) {
    int xt = t % (2*w);
    while(xt && x < w) x++, xt--;
    while(xt && x > 0) x--, xt--;
    while(xt) x++, xt--;
    return x;
}

// O(1)
int getPos2(int w, int x) {
    x = (x+t) % (2*w);
    return x <= w ? x : 2*w-x;
}

int main() {
    scanf("%d%d%d%d%d",&w,&h,&x,&y,&t);

    //printf("%d %d\n", getPos(w, x), getPos(h, y));
    printf("%d %d\n", getPos2(w, x), getPos2(h, y));
    return 0;
}
```