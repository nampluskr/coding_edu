#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 1'001

int N;
int arr[MAX_SIZE][MAX_SIZE];
long long prefixSum[MAX_SIZE + 1][MAX_SIZE + 1];
int M;
int sr, sc, er, ec;
long long result;

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            scanf("%d", &arr[i][j]);

            prefixSum[i+1][j+1] = prefixSum[i][j+1] + prefixSum[i+1][j] - prefixSum[i][j] + arr[i][j];
        }

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d", &sr, &sc, &er, &ec);

        result = prefixSum[er][ec] - prefixSum[sr-1][ec] - prefixSum[er][sc-1] + prefixSum[sr-1][sc-1];
        printf("%lld\n", result);
    }

    return 0;
}