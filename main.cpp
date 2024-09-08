#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>


void PrintStickAngle(float x, float y) {
    // スティックの入力から角度を計算
    float angle = std::atan2(y, x);  // y, xの順で渡す

    // 角度をラジアンから度に変換
    float angleInDegrees = angle * (180.0f / 3.14159265359f);

    // 結果を出力
    std::cout << "Stick Input (x, y): (" << x << ", " << y << ")" << std::endl;
    std::cout << "Angle (radians): " << angle << std::endl;
    std::cout << "Angle (degrees): " << angleInDegrees << std::endl;
}

int main() {
    PrintStickAngle(1.0f, 0.0f);  // Right
    PrintStickAngle(0.0f, 1.0f);  // Up
    PrintStickAngle(-1.0f, 0.0f); // Left
    PrintStickAngle(0.0f, -1.0f); // Down

    return 0;
}
