### Solution

```cpp
#include<stdio.h>

struct Rect{
    int sr,sc,er,ec;
}a,b,c;

int max(int a, int b) { return a>b ? a:b;}
int min(int a, int b) { return a<b ? a:b;}

int main() {
    for(int i=0; i<4; i++) {
        scanf("%d%d%d%d",&a.sr,&a.sc,&a.er,&a.ec);
        scanf("%d%d%d%d",&b.sr,&b.sc,&b.er,&b.ec);
        c.sr = max(a.sr,b.sr);
        c.sc = max(a.sc,b.sc);
        c.er = min(a.er,b.er);
        c.ec = min(a.ec,b.ec);

        if(c.sr > c.er || c.sc > c.ec) printf("d\n");
        else if(c.sr == c.er && c.sc == c.ec) printf("c\n");
        else if(c.sr < c.er && c.sc < c.ec) printf("a\n");
        else printf("b\n");
    }
    return 0;
}
```