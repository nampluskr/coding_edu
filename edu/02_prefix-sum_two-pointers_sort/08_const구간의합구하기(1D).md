## const구간의 합 구하기(1D)

### 문제


1차원 배열에 N개의 수들이 입력되어 있다.

이 배열의 임의의 구간에 있는 수들의 합을 물어보는 M개의 쿼리에 답하는 프로그램을 작성하시오.

쿼리에 답하는 중간에 배열의 어떤 원소도 값이 변경되지 않는다.




### 입력
첫 행에 원소의 수 N이 입력된다. (1≤N≤1,000,000)

다음 행에 N개의 수 $A_i$ 가 공백을 구분하여 입력된다. (−1,000,000≤$A_i$≤1,000,000)

다음 행에 쿼리의 수 M이 입력된다. (1≤M≤1,000,000) 

이어서 M개의 행에 쿼리의 정보 $s_i, e_i$ 가 공백으로 구분되어 입력된다. (1≤ $s_i$ ≤ $e_i$ ≤N)




### 출력
각 쿼리에 대한 결과를 행으로 구분하여 출력한다.




### 예제
입력
```
10 
7 3 2 4 -5 1 6 -3 0 9 
5 
1 3 
1 10 
5 5 
7 8 
4 6
```

출력
```
12 
24 
-5 
3 
0
```