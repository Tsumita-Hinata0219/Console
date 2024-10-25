#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;



int main(void) {

	// 人数、試合数の入力
	int totalPeople = 0, totalMatch = 0;
	cin >> totalPeople; cin >> totalMatch;

	// 列車の初期状態
	vector<string> mat(totalPeople, "1");

	for (int i = 0; i < totalMatch; ++i) {
		// 勝敗の入力
		int win = 0, lose = 0;
		cin >> win; cin >> lose;

		// 移動したのち、空にする
		mat[win - 1] += mat[lose - 1];
		mat[lose - 1].clear();
	}

	int maxLength = 0;
	vector<int> longestIndices;

	for (int i = 0; i < mat.size(); ++i) {
		const auto& element = mat[i];
		int length = int(element.length());
		
		if (length > maxLength) {
			maxLength = length;
			longestIndices.clear();
			longestIndices.push_back(i);
		}
		else if (length == maxLength) {
			longestIndices.push_back(i);
		}
	}

	// 結果を表示
	if (!longestIndices.empty()) {
		
		for (const int index : longestIndices) {
			cout << index + 1 << endl;
		}
	}

	return 0;
}
