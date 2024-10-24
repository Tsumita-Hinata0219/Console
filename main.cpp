#include <iostream>
#include <vector>
using namespace std;

int CountDonuts(const vector<string>& str, int h, int w) {

	int count = 0;

	// 少なくとも判定するのに1マス分余裕が必要なので
	// 1 <= i <= h-2 && 1 <= j <= w-2 の範囲で探索
	for (int i = 1; i < h - 1; ++i) {
		for (int j = 1; j < w - 1; ++j) {
			// 中心が空白なら
			if (str[i][j] == '.') {
				// 周囲のマスが全て黒ならcountを加算
				if (str[i - 1][j - 1] == '#' && str[i - 1][j] == '#' && str[i - 1][j + 1] == '#' && // 上の行 
					str[i][j - 1] == '#' && str[i][j + 1] == '#' && // 同じ行									 
					str[i + 1][j - 1] == '#' && str[i + 1][j] == '#' && str[i + 1][j + 1] == '#') // 下の行
				{
					count++;
				}
			}
		}
	}

	return count;
}

int main(void) {

	// マスの数
	int h = 0, w = 0;
	cin >> h; cin >> w;

	// マスの中身
	vector<string> strArray(h);

	// 入力
	for (int i = 0; i < h; ++i) {
		cin >> strArray[i];
	}

	// ドーナツを見つける
	int result = CountDonuts(strArray, h, w);
	// 見つかった数を出力
	cout << result << endl;

	return 0;
}
