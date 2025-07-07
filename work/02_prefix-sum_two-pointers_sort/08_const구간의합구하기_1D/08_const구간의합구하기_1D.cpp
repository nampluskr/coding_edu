#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

# define MAX_SIZE 1'000'001
int N, M;
int arr[MAX_SIZE];
int s, e;
long long prefixSum[MAX_SIZE + 1] = {};

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        prefixSum[i + 1] = prefixSum[i] + arr[i];
    }

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &s, &e);
        printf("%lld\n", prefixSum[e] - prefixSum[s - 1]);
    }

    return 0;
}