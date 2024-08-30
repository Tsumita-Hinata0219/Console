#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(void) {

	// 商品数
	int N = 0;
	cin >> N;

	// 適用価格の下限
	int L = 0;
	cin >> L;

	// 商品の価格
	vector<int> u(N);
	for (int i = 0; i < N; ++i) {
		cin >> u[i];
	}

	// 合計金額
	int cash = 0;

	// 最高高額商品
	auto maxU = max_element(u.begin(), u.end());

	if (maxU != u.end()) {
		// それのインデックス
		int index = distance(u.begin(), maxU);

		if (u[index] >= L) {
			// 半額
			u[index] = u[index] / 2;
		}
	}


	for (int i = 0; i < N; ++i) {

		cash += u[i];
	}

	cout << cash << endl;


	return 0;
}