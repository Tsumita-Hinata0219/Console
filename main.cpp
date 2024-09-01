#include <stdio.h>
#include <iostream>
#include <algorithm>

float convertToRange(int input) {
    // 入力範囲と出力範囲を定義
    const float inputMin = 0.0f;
    const float inputMax = 1280.0f;
    const float outputMin = -1.0f;
    const float outputMax = 1.0f;

    // 入力を0〜1の範囲に正規化
    float normalizedValue = (input - inputMin) / (inputMax - inputMin);

    // 正規化された値を出力範囲にスケーリング
    return normalizedValue * (outputMax - outputMin) + outputMin;
}

int main(void) {

    int input = 1280.0f;  // 例として640を変換
    float output = convertToRange(input);
    std::cout << "Converted value: " << output << std::endl;


	return 0;
}

