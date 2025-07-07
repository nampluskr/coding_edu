struct Data {
    int strike, ball;
};
extern Data query(int suppose[]);

bool used[10];
int arr[4];
int *ans;

// ==================================================================
// 순열 생성 (완전탐색)
// ==================================================================
bool recur1(int depth) {
    if (depth == 4) {
        Data result = query(arr);
        if (result.strike == 4) {
            for (int i = 0; i < 4; i++) ans[i] = arr[i];    // 정답 저장
            return true;
        }
        return false;
    }

    for (int i = 0; i <= 9; i++) {
        if (used[i]) continue;

        arr[depth] = i;
        used[i] = true;

        if (recur1(depth + 1)) {
            used[i] = false;
            return true;
        }
        used[i] = false;
    }
    return false;
}

// ==================================================================
// 순열 생성 (필터링 적용)
// ==================================================================

// 이전 질의들을 저장하는 구조체
struct Query {
    int data[4];
    int strike, ball;
};

Query queries[100];  // 최대 100개의 질의 저장
int queryCount = 0;  // 현재까지 실행한 질의 수

// 두 4자리 수를 비교하여 strike와 ball 계산
Data compare(int a[4], int b[4]) {
    Data result = {0, 0};
    bool usedA[4] = {false, false, false, false};
    bool usedB[4] = {false, false, false, false};

    // Strike 계산 (위치와 숫자가 모두 일치)
    for (int i = 0; i < 4; i++) {
        if (a[i] == b[i]) {
            result.strike++;
            usedA[i] = true;
            usedB[i] = true;
        }
    }

    // Ball 계산 (숫자는 일치하지만 위치가 다름)
    for (int i = 0; i < 4; i++) {
        if (!usedA[i]) {
            for (int j = 0; j < 4; j++) {
                if (!usedB[j] && a[i] == b[j]) {
                    result.ball++;
                    usedA[i] = true;
                    usedB[j] = true;
                    break;
                }
            }
        }
    }

    return result;
}

// 현재 후보가 모든 이전 질의 결과와 일치하는지 확인
bool isPossible(int data[4]) {
    for (int i = 0; i < queryCount; i++) {
        Data result = compare(data, queries[i].data);

        // 계산된 결과가 실제 질의 결과와 다르면 일치하지 않음
        if (result.strike != queries[i].strike ||
            result.ball != queries[i].ball) {
            return false;
        }
    }
    return true;
}


// 순열 생성 (필터링 적용)
bool recur2(int depth) {
    if (depth == 4) {
        // 이전 질의 결과들과 일치하는지 먼저 확인
        if (isPossible(arr)) {
            Data result = query(arr);

            // 질의 결과를 저장
            for (int i = 0; i < 4; i++) {
                queries[queryCount].data[i] = arr[i];
            }
            queries[queryCount].strike = result.strike;
            queries[queryCount].ball = result.ball;
            queryCount++;

            if (result.strike == 4) {
                for (int i = 0; i < 4; i++) ans[i] = arr[i];    // 정답 저장
                return true;
            }
        }
        return false;
    }

    for (int i = 0; i <= 9; i++) {
        if (used[i]) continue;

        arr[depth] = i;
        used[i] = true;

        if (recur2(depth + 1)) {
            used[i] = false;
            return true;
        }
        used[i] = false;
    }
    return false;
}

void tryBest(int suppose[]) {
    ans = suppose;

    // recur1(0);       // 순열 생성 (완전탐색)

    queryCount = 0;
    recur2(0);          // 순열 생성 (필터링 적용)
}