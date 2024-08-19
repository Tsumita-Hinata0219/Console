#include <stdio.h>
#include <iostream>
#include <type_traits>
#include <vector>
#include <bitset>
#include <string>


static uint32_t BitSeparate32(uint32_t n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}
static uint32_t Get2DMortonNumber(uint32_t x, uint32_t y)
{
	return (BitSeparate32(x) | (BitSeparate32(y) << 1));
}
// ビット列から最上位ビットの位置を取得する関数
static int findHighestBitPosition(int bitmask) {
	int position = 0;
	while (bitmask != 0) {
		bitmask >>= 1;
		++position;
	}
	return position;
}


int continueLoop = 1;

int main(void) {

	// ルート空間の辺
	int ROOT_EDGE_LENGTH = 100;
	// 孫空間の一辺
	float U = float(ROOT_EDGE_LENGTH / std::pow(2, 3));

	// 出力
	std::cout << "ルート空間の一辺 : " << ROOT_EDGE_LENGTH << std::endl;
	std::cout << "孫空間の一辺　　 : " << U << std::endl;


	// ループ処理
	while (continueLoop == 1) {
		std::cout << std::endl << std::endl << std::endl << std::endl; // 改行

		// 所属空間か空間レベルを求める
		int number;
		std::cout << "所属空間 -> 1  空間レベル -> 2 " << std::endl;
		std::cout << "Enter a number : ";
		std::cin >> number;
		std::cout << std::endl << std::endl << std::endl;

		if (number == 1) {

			std::cout << "/* ========== 座標から所属空間を求める ========== */" << std::endl << std::endl;

			// 座標から所属空間を求める
			std::cout << "座標を入力してください。0 ~ 100" << std::endl;

			// 点の座標の入力を受け付ける
			int pos_x = 0, pos_y = 0;
			std::cout << "  X座標 : ";
			std::cin >> pos_x;
			std::cout << "  Y座標 : ";
			std::cin >> pos_y;
			// 入力された座標を表示する
			std::cout << "入力された座標 : (" << pos_x << ", " << pos_y << ")" << std::endl;
			std::cout << std::endl;


			// 座標をU(孫空間の一辺)で割ったもの
			float x_div_u = float(pos_x / U);
			float y_div_u = float(pos_y / U);
			// int型でキャスト
			int x_casted = static_cast<int>(x_div_u);
			int y_casted = static_cast<int>(y_div_u);
			// キャストしたものをbitで表したもの
			std::bitset<4> x_bit(x_casted);
			std::bitset<4> y_bit(y_casted);
			// 所属空間
			int spaceID = Get2DMortonNumber(x_casted, y_casted);

			// 出力
			std::cout << "U(孫空間の一辺)で除算　　 : (" << x_div_u << ", " << y_div_u << ")" << std::endl;
			std::cout << "int型でキャスト　　　　　 : (" << x_casted << ", " << y_casted << ")" << std::endl;
			std::cout << "キャストしたものをbit表示 : (" << x_bit << ", " << y_bit << ")" << std::endl;
			std::cout << std::endl;
			std::cout << "所属空間 : " << spaceID << std::endl;
			std::cout << std::endl;
			std::cout << "/* ========== ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ ========== */" << std::endl << std::endl;

			std::cout << std::endl << std::endl << std::endl << std::endl;
		}
		else if (number == 2) {

			std::cout << "/* ========== 所属空間から空間レベルを求める ========== */" << std::endl << std::endl;

			// 所属空間から空間レベルを求める
			std::cout << "所属空間を入力してください。0 ~ 63" << std::endl;

			// 所属空間の入力を受け付ける
			int LT = 0, RD = 0;
			std::cout << "  左上 : ";
			std::cin >> LT;
			std::cout << "  右下 : ";
			std::cin >> RD;
			// 入力された所属空間を表示する
			std::cout << "入力された所属空間 : (" << LT << ", " << RD << ")" << std::endl;
			std::cout << std::endl;


			// 所属空間レベル
			int LTxorRD = LT ^ RD;
			// 最上位ビット位置を求める
			int highestBitPosition = findHighestBitPosition(LTxorRD);
			// どの空間のどの番号に所属しているか
			int spaceIndex = LT >> highestBitPosition;

			// 出力
			std::cout << "XOR              : " << LTxorRD << std::endl;
			std::cout << "空間レベル       : " << std::bitset<6>(LTxorRD) << std::endl;
			std::cout << "最上位ビット位置 : " << highestBitPosition << std::endl;
			std::cout << "所属空間Bit      : " << std::bitset<6>(spaceIndex) << std::endl;
			std::cout << "所属空間         : " << spaceIndex << std::endl;
			std::cout << std::endl;
			std::cout << "/* ========== ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ ========== */" << std::endl << std::endl;
			std::cout << std::endl << std::endl << std::endl << std::endl;
		}

		std::cout << "もう一回求めますか？ 1: 続ける  2: 終了" << std::endl;
		std::cout << "Enter a number : ";
		std::cin >> continueLoop;
	}



	return 0;
}