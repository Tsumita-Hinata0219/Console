#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(void) {

	// �l��
	int N;
	cin >> N;

	// ���i�_
	int M;
	cin >> M;
	
	//�@�_���ƌ��ȓ���
	vector<pair<int, int>> a(N);
	for (int i = 0; i < N; ++i) {
		cin >> a[i].first;
		cin >> a[i].second;
	}

	// ���i�҂̏o�Ȕԍ��̏o��
	for (int i = 1; i <= N; ++i) {

		// ���ۂ̌v�Z
		int s = a[i - 1].first - (a[i - 1].second * 5);

		if (s <= 0) {
			s = 0;
		}

		if (s >= M) {
			cout << i << endl;
		}
	}



	return 0;
}