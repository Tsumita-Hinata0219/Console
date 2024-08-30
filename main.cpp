#include <iostream>
#include <vector>
#include <set>

using namespace std;

// ビンゴカードの状態を確認する関数
int countBingos(const vector<vector<bool>>& opened, int N) {
    int bingoCount = 0;

    // 行チェック
    for (int i = 0; i < N; ++i) {
        bool rowBingo = true;
        for (int j = 0; j < N; ++j) {
            if (!opened[i][j]) {
                rowBingo = false;
                break;
            }
        }
        if (rowBingo) ++bingoCount;
    }

    // 列チェック
    for (int j = 0; j < N; ++j) {
        bool colBingo = true;
        for (int i = 0; i < N; ++i) {
            if (!opened[i][j]) {
                colBingo = false;
                break;
            }
        }
        if (colBingo) ++bingoCount;
    }

    // 主対角線チェック
    bool diag1Bingo = true;
    for (int i = 0; i < N; ++i) {
        if (!opened[i][i]) {
            diag1Bingo = false;
            break;
        }
    }
    if (diag1Bingo) ++bingoCount;

    // 副対角線チェック
    bool diag2Bingo = true;
    for (int i = 0; i < N; ++i) {
        if (!opened[i][N - 1 - i]) {
            diag2Bingo = false;
            break;
        }
    }
    if (diag2Bingo) ++bingoCount;

    return bingoCount;
}

int main() {
    int N; // ビンゴカードのサイズ
    cin >> N;

    int K; // 抽選回数
    cin >> K;

    vector<vector<int>> card(N, vector<int>(N));
    set<int> drawnNumbers;

    // ビンゴカードの入力
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> card[i][j];
        }
    }

    // 抽選結果の入力
    for (int i = 0; i < K; ++i) {
        int number;
        cin >> number;
        drawnNumbers.insert(number);
    }

    // 開けられているかどうかを追跡する 2D ベクター
    vector<vector<bool>> opened(N, vector<bool>(N, false));

    // 抽選された数字によってビンゴカードを更新
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (card[i][j] == 0 || drawnNumbers.count(card[i][j])) {
                opened[i][j] = true;
            }
        }
    }

    // ビンゴの数をカウント
    int bingoCount = countBingos(opened, N);

    cout << bingoCount << endl;

    return 0;
}
