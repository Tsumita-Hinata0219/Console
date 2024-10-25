#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    // 一片の長さ
    int length = 0;
    cin >> length;

    // ブロック
    vector<vector<int>> blocks(length, vector<int>(length));
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            cin >> blocks[i][j];
        }
    }

    // それぞれの時間
    vector<int> fractions(4, 0); // size, initValue
    // トータル移動数
    int totalMoveCount = length * length;
    // 移動回数
    int count = 0;
    // 上下左右の境界
    int up = 0, down = length - 1, left = 0, right = length - 1;
    // 合計
    int sum = 0;

    while (count < totalMoveCount) {
        // 右に移動
        for (int i = left; i <= right; i++) {
            sum += blocks[up][i]; // 値を加算
            count++; // 進行度
            if (count % (totalMoveCount / 4) == 0) {
                cout << sum << endl; // 1/4毎に出力
            }
        }
        up++; // 上を一行走査済み

        // 下に移動
        for (int i = up; i <= down; i++) {
            sum += blocks[i][right];
            count++;
            if (count % (totalMoveCount / 4) == 0) {
                cout << sum << endl;
            }
        }
        right--; // 右を一列走査済み

        // 左に移動
        if (up <= down) { // 境界を確認
            for (int i = right; i >= left; i--) {
                sum += blocks[down][i];
                count++;
                if (count % (totalMoveCount / 4) == 0) {
                    cout << sum << endl;
                }
            }
            down--; // 下を一行走査済み
        }

        // 上に移動
        if (left <= right) { // 境界を確認
            for (int i = down; i >= up; i--) {
                sum += blocks[i][left];
                count++;
                if (count % (totalMoveCount / 4) == 0) {
                    cout << sum << endl;
                }
            }
            left++; // 左を一列走査済み
        }
    }

    return 0;
}
