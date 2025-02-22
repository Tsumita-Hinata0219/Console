#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

void Check(int check, int start, int end);

int main() {

	// ある時刻と開始時刻、終了時刻
	int check = 0, start = 0, end = 0;

	// ある時刻の入力
	cin >> check;

	// 開始時刻と終了時刻の入力
	cin >> start; cin >> end;

	// チェック
	Check(check, start, end);

	return 0;
}

void Check(int check, int start, int end) {

	// 全て同じ場合は「含まれる」
	// 早期return
	if (start == check && end == check) {
		cout << "含まれる" << endl;
		return;
	}

	// 日を跨ぐかチェック
	if (start > end) { 

		// 日を跨いだ場合
		// ある時刻に12を加算してチェック
		if (start >= check && check + 12 > end) {
			cout << "含まれる" << endl;
		}
		else {
			cout << "含まれない" << endl;
		}
	}
	else {

		// 日を跨がない場合
		if (start <= check && check < end) {
			cout << "含まれる" << endl;
		}
		else {
			cout << "含まれない" << endl;
		}
	}
}