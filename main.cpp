#include <iostream>
#include <vector>
#include <set>

using namespace std;

// �r���S�J�[�h�̏�Ԃ��m�F����֐�
int countBingos(const vector<vector<bool>>& opened, int N) {
    int bingoCount = 0;

    // �s�`�F�b�N
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

    // ��`�F�b�N
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

    // ��Ίp���`�F�b�N
    bool diag1Bingo = true;
    for (int i = 0; i < N; ++i) {
        if (!opened[i][i]) {
            diag1Bingo = false;
            break;
        }
    }
    if (diag1Bingo) ++bingoCount;

    // ���Ίp���`�F�b�N
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
    int N; // �r���S�J�[�h�̃T�C�Y
    cin >> N;

    int K; // ���I��
    cin >> K;

    vector<vector<int>> card(N, vector<int>(N));
    set<int> drawnNumbers;

    // �r���S�J�[�h�̓���
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> card[i][j];
        }
    }

    // ���I���ʂ̓���
    for (int i = 0; i < K; ++i) {
        int number;
        cin >> number;
        drawnNumbers.insert(number);
    }

    // �J�����Ă��邩�ǂ�����ǐՂ��� 2D �x�N�^�[
    vector<vector<bool>> opened(N, vector<bool>(N, false));

    // ���I���ꂽ�����ɂ���ăr���S�J�[�h���X�V
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (card[i][j] == 0 || drawnNumbers.count(card[i][j])) {
                opened[i][j] = true;
            }
        }
    }

    // �r���S�̐����J�E���g
    int bingoCount = countBingos(opened, N);

    cout << bingoCount << endl;

    return 0;
}
