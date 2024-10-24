#include <iostream>
#include <vector>
using namespace std;
int main(void) {

	// 金額、ポイント、乗車回数
	int amount = 0, point = 0, takeCount = 0;
	
	// 初期金額と乗車回数の入力
	cin >> amount; cin >> takeCount;

	// 運賃
	vector<int> fares(takeCount);
	for (auto& fare : fares) {
		cin >> fare;
	}

	// 計算
	for (auto& fare : fares) {

		// 運賃のほうが高ければ金額で支払い
		if (point <= fare) {
			amount -= fare;
			point += int(float(fare) * 0.1f); // 運賃の10%を加算
		}
		else { // ポイントのほうが高ければポイントで支払う
			point -= fare;
		}
		// 現在の金額とポイントの出力
		cout << amount << " " << point << endl;
	}

	return 0;
}