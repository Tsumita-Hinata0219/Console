#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(void) {

	// 人数
	int N;
	cin >> N;

	// 合格点
	int M;
	cin >> M;
	
	//　点数と欠席日数
	vector<pair<int, int>> a(N);
	for (int i = 0; i < N; ++i) {
		cin >> a[i].first;
		cin >> a[i].second;
	}

	// 合格者の出席番号の出力
	for (int i = 1; i <= N; ++i) {

		// 合否の計算
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