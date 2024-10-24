#include <iostream>
#include <vector>
using namespace std;

int CountDonuts(const vector<string>& str, int h, int w) {

	int count = 0;

	// ���Ȃ��Ƃ����肷��̂�1�}�X���]�T���K�v�Ȃ̂�
	// 1 <= i <= h-2 && 1 <= j <= w-2 �͈̔͂ŒT��
	for (int i = 1; i < h - 1; ++i) {
		for (int j = 1; j < w - 1; ++j) {
			// ���S���󔒂Ȃ�
			if (str[i][j] == '.') {
				// ���͂̃}�X���S�č��Ȃ�count�����Z
				if (str[i - 1][j - 1] == '#' && str[i - 1][j] == '#' && str[i - 1][j + 1] == '#' && // ��̍s 
					str[i][j - 1] == '#' && str[i][j + 1] == '#' && // �����s									 
					str[i + 1][j - 1] == '#' && str[i + 1][j] == '#' && str[i + 1][j + 1] == '#') // ���̍s
				{
					count++;
				}
			}
		}
	}

	return count;
}

int main(void) {

	// �}�X�̐�
	int h = 0, w = 0;
	cin >> h; cin >> w;

	// �}�X�̒��g
	vector<string> strArray(h);

	// ����
	for (int i = 0; i < h; ++i) {
		cin >> strArray[i];
	}

	// �h�[�i�c��������
	int result = CountDonuts(strArray, h, w);
	// �������������o��
	cout << result << endl;

	return 0;
}
