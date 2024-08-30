#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(void) {

	// ���i��
	int N = 0;
	cin >> N;

	// �K�p���i�̉���
	int L = 0;
	cin >> L;

	// ���i�̉��i
	vector<int> u(N);
	for (int i = 0; i < N; ++i) {
		cin >> u[i];
	}

	// ���v���z
	int cash = 0;

	// �ō����z���i
	auto maxU = max_element(u.begin(), u.end());

	if (maxU != u.end()) {
		// ����̃C���f�b�N�X
		int index = distance(u.begin(), maxU);

		if (u[index] >= L) {
			// ���z
			u[index] = u[index] / 2;
		}
	}


	for (int i = 0; i < N; ++i) {

		cash += u[i];
	}

	cout << cash << endl;


	return 0;
}